//BASE BUILDING BASE
class BaseBuildingBase extends ItemBase
{
	//TODO - remove player messages???
	static const string MESSAGE_CANNOT_BE_CONSTRUCTED		= "This part cannot be constructed.";
	static const string MESSAGE_CANNOT_BE_DECONSTRUCTED		= "This part cannot be dismantled because of some other part.";
	
	const string ANIMATION_DEPLOYED			= "Deployed";
			string CONSTRUCTION_KIT			= "";
	
	float 	m_ConstructionKitHealth;			//stored health value for used construction kit
	
	ref Construction 	m_Construction;
	
	bool 	m_HasBase = false;
	bool 	m_HasGate = false;
	//variables for synchronization of base building parts (2x32 is the current limit)
	int 	m_SyncParts01;									//synchronization for already built parts (32)
	int 	m_SyncParts02;									//synchronization for already built parts (64)
	
	// Constructor
	void BaseBuildingBase() 
	{
		//TODO - damage triggers
		/*
		SetFlags(EntityFlags.TRIGGER, false);
		
		m_DmgTriggers = new array<BarbedWireTrigger>;
		m_BarbedWires = new map<string,BarbedWire>;
		*/
		
		//synchronized variables
		RegisterNetSyncVariableInt( "m_SyncParts01" );
		RegisterNetSyncVariableInt( "m_SyncParts02" );
	}

	// --- SYNCHRONIZATION
	void Synchronize()
	{
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
		
			//Refresh visuals (server)
			Refresh();
		}
	}
	
	//refresh visual/physics state
	void Refresh()
	{
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( UpdateVisuals );
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( UpdatePhysics );
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		//update parts
		SetPartsFromSyncData();
		
		//update visuals (client)
		Refresh();
	}
	
	//TODO add support for more than 32 parts
	//parts synchronization
	void RegisterPartForSync( int part_id, bool synchronize )
	{
		if ( part_id >= 1 )		//part_id must starts from index = 1
		{
			int offset;
			int mask;
			
			m_SyncParts01 = m_SyncParts01 | mask;
			
			if ( part_id > 32 )
			{
				offset = ( part_id % 32 ) - 1;
				mask = 1 << offset;
				
				m_SyncParts02 = m_SyncParts02 | mask;
			}
			else
			{
				offset = part_id - 1;
				mask = 1 << offset;
				
				m_SyncParts01 = m_SyncParts01 | mask;
			}
			
			if ( synchronize ) 
			{
				Synchronize();
			}
		}
	}
	
	void UnregisterPartForSync( int part_id, bool synchronize )
	{
		if ( part_id >= 1 )		//part_id must starts from index = 1
		{
			int offset;
			int mask;
			
			m_SyncParts01 = m_SyncParts01 | mask;
			
			if ( part_id > 32 )
			{
				offset = ( part_id % 32 ) - 1;
				mask = 1 << offset;
				
				m_SyncParts02 = m_SyncParts02 & ~mask;
			}
			else
			{
				offset = part_id - 1;
				mask = 1 << offset;
				
				m_SyncParts01 = m_SyncParts01 & ~mask;
			}
			
			if ( synchronize ) 
			{
				Synchronize();
			}
		}		
	}	
	
	bool IsPartBuildInSyncData( int part_id )
	{
		if ( part_id >= 1 )		//part_id must starts from index = 1
		{
			int offset;
			int mask;
			
			m_SyncParts01 = m_SyncParts01 | mask;
			
			if ( part_id > 32 )
			{
				offset = ( part_id % 32 ) - 1;
				mask = 1 << offset;
				
				if ( ( m_SyncParts02 & mask ) > 0 )
				{
					return true;
				}
			}
			else
			{
				offset = part_id - 1;
				mask = 1 << offset;
				
				if ( ( m_SyncParts01 & mask ) > 0 )
				{
					return true;
				}
			}
		}			
		
		return false;
	} 
	//------
	
	//set construction parts based on synchronized data
	void SetPartsFromSyncData()
	{
		Construction construction = GetConstruction();
		map<string, ref ConstructionPart> construction_parts = construction.GetConstructionParts();
		
		for ( int i = 0; i < construction_parts.Count(); ++i )
		{
			string key = construction_parts.GetKey( i );
			ConstructionPart value = construction_parts.Get( key );
		
			bool is_part_built_sync = IsPartBuildInSyncData( value.GetId() );
			if ( is_part_built_sync )
			{
				if ( !value.IsBuilt() )
				{
					GetConstruction().BuildPart( key, false, false );
				}
			}
			else
			{
				if ( value.IsBuilt() )
				{
					GetConstruction().DismantlePart( key, false, false );
				}
			}
		}
	}
	//
	
	//Base
	bool HasBase()
	{
		return m_HasBase;
	}
	
	void SetBaseState( bool has_base )
	{
		m_HasBase = has_base;
	}
	
	//Gate
	bool HasGate()
	{
		return m_HasGate;
	}
	
	void SetGateState( bool has_gate )
	{
		m_HasGate = has_gate;
	}
	
	// --- PLACING
	override bool IsHeavyBehaviour()
	{
		return true;
	}
	
	override bool IsDeployable()
	{
		return true;
	}
	
	//--- CONSTRUCTION KIT
	ItemBase CreateConstructionKit()
	{
		ItemBase construction_kit = ItemBase.Cast( GetGame().CreateObject( CONSTRUCTION_KIT, GetPosition() ) );
		construction_kit.SetHealth( m_ConstructionKitHealth );
		
		return construction_kit;
	}
	
	void DestroyConstructionKit( ItemBase construction_kit )
	{
		m_ConstructionKitHealth = construction_kit.GetHealth();
		GetGame().ObjectDelete( construction_kit );
	}
	
	// --- EVENTS
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		//sync parts 01
		ctx.Write( m_SyncParts01 );
		ctx.Write( m_SyncParts02 );
	}
	
	override void OnStoreLoad( ParamsReadContext ctx )
	{
		super.OnStoreLoad( ctx );
		
		//Restore synced parts data
		//sync parts 01
		ctx.Read( m_SyncParts01 );
		ctx.Read( m_SyncParts02 );
		
		//restore parts from restored sync data
		SetPartsFromSyncData();
	}
	
	override void EEInit()
	{
		super.EEInit();
		
		//Construction init
		ConstructionInit();
		
		//update visuals and physics
		Refresh();
	}

	override void OnItemLocationChanged( EntityAI old_owner, EntityAI new_owner ) 
	{
		super.OnItemLocationChanged( old_owner, new_owner );
		
		//update visuals after location change
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( UpdatePhysics );
	}
	
	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached ( item, slot_name );
		
		//update visuals and physics
		Refresh();
	}
	
	override void EEItemDetached ( EntityAI item, string slot_name )
	{
		super.EEItemDetached ( item, slot_name );
		
		//update visuals and physics
		Refresh();
	}
	
	//CONSTRUCTION EVENTS
	void OnPartBuilt( string part_name, bool synchronize )
	{
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart( part_name );
		
		//check base state
		if ( constrution_part.IsBase() )
		{
			SetBaseState( true );
			
			//spawn kit
			if ( GetGame().IsServer() )
			{
				CreateConstructionKit();
			}
		}
	
		//check gate state
		if ( constrution_part.IsGate() )
		{
			SetGateState( true );
		}
	
		//register on server only
		if ( GetGame().IsServer() )
		{
			//register constructed parts for synchronization
			RegisterPartForSync( constrution_part.GetId(), synchronize );
		}
	}
	
	void OnPartDismantled( string part_name, bool synchronize )
	{
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart( part_name );
		
		//check base state
		if ( constrution_part.IsBase() )
		{
			//Destroy construction
			GetGame().ObjectDelete( this );
		}
		
		//check gate state
		if ( constrution_part.IsGate() )
		{
			SetGateState( false );
		}		
		
		//register on server only
		if ( GetGame().IsServer() )
		{
			//register constructed parts for synchronization
			UnregisterPartForSync( constrution_part.GetId(), synchronize );
		}
	}
	
	// --- UPDATE
	void UpdateVisuals()
	{
		//update attachments visuals
		ref array<string> attachment_slots = new ref array<string>;
		GetAttachmentSlots( this, attachment_slots );
		for ( int i = 0; i < attachment_slots.Count(); i++ )
		{
			string slot_name = attachment_slots.Get( i );
			EntityAI attachment = FindAttachmentBySlotName( slot_name );
			string slot_name_mounted = slot_name + "_Mounted";
		
			if ( attachment && !IsAttachmentSlotLocked( attachment ) )
			{
				if ( attachment.IsInherited( BarbedWire ) )
				{
					BarbedWire barbed_wire = BarbedWire.Cast( attachment );
					if ( barbed_wire.IsMounted() )
					{
						SetAnimationPhase( slot_name, 1 );
						SetAnimationPhase( slot_name_mounted, 0 );
					}
					else
					{
						SetAnimationPhase( slot_name_mounted, 1 );
						SetAnimationPhase( slot_name, 0 );
					}
				}
				else
				{
					SetAnimationPhase( slot_name, 0 );					
				}
			}
			else
			{
				SetAnimationPhase( slot_name_mounted, 1 );
				SetAnimationPhase( slot_name, 1 );
			}
		}	
	
		//check base
		if ( !HasBase() )
		{
			SetAnimationPhase( ANIMATION_DEPLOYED, 0 );
		}
		else
		{
			SetAnimationPhase( ANIMATION_DEPLOYED, 1 );
		}
		
		GetConstruction().UpdateVisuals();
	}
	
	void UpdatePhysics()
	{
		//update attachments physics
		ref array<string> attachment_slots = new ref array<string>;
		GetAttachmentSlots( this, attachment_slots );
		for ( int i = 0; i < attachment_slots.Count(); i++ )
		{
			string slot_name = attachment_slots.Get( i );
			EntityAI attachment = FindAttachmentBySlotName( slot_name );
			string slot_name_mounted = slot_name + "_Mounted";
			
			if ( attachment && !IsAttachmentSlotLocked( attachment ) )
			{
				if ( attachment.IsInherited( BarbedWire ) )
				{
					BarbedWire barbed_wire = BarbedWire.Cast( attachment );
					if ( barbed_wire.IsMounted() )
					{
						RemoveProxyPhysics( slot_name );
						AddProxyPhysics( slot_name_mounted );
					}
					else
					{
						RemoveProxyPhysics( slot_name_mounted );
						AddProxyPhysics( slot_name );						
					}
				}
				else
				{
					AddProxyPhysics( slot_name );
				}
			}
			else
			{
				RemoveProxyPhysics( slot_name_mounted );
				RemoveProxyPhysics( slot_name );
			}
		}
		
		//check base
		if ( !HasBase() )
		{
			AddProxyPhysics( ANIMATION_DEPLOYED );
		}
		else
		{
			RemoveProxyPhysics( ANIMATION_DEPLOYED );
		}
		
		GetConstruction().UpdatePhysics();
	}	
	
	override bool CanUseConstruction()
	{
		return true;
	}

	protected bool IsAttachmentSlotLocked( ItemBase attachment )
	{
		if ( attachment )
		{
			InventoryLocation inventory_location = new InventoryLocation;
			attachment.GetInventory().GetCurrentInventoryLocation( inventory_location );
			
			return GetInventory().GetSlotLock( inventory_location.GetSlot() );
		}
			
		return false;
	}
	
	//--- ATTACHMENT SLOTS
	void GetAttachmentSlots( EntityAI entity, out array<string> attachment_slots )
	{
		string config_path = "CfgVehicles" + " " + entity.GetType() + " " + "attachments";
		if ( GetGame().ConfigIsExisting( config_path ) )
		{
			GetGame().ConfigGetTextArray( config_path, attachment_slots );
		}
	}
	
	// --- INIT
	void ConstructionInit()
	{
		if ( !m_Construction )
		{
			m_Construction = new Construction( this );
		}
		
		GetConstruction().Init();
	}
	Construction GetConstruction()
	{
		return m_Construction;
	}
	
	//--- INVENTORY/ATTACHMENTS CONDITIONS
	//attachments
	override bool CanReceiveAttachment( EntityAI attachment )
	{
		return true;
	}

	//this into/outo parent.Cargo
	override bool CanPutInCargo( EntityAI parent )
	{
		return false;
	}
	
	override bool CanRemoveFromCargo( EntityAI parent )
	{
		return false;
	}

	//hands
	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
	
	//--- ACTION CONDITIONS
	//direction
	bool IsFacingFront( PlayerBase player )
	{
		return true;
	}
	
	bool IsFacingBack( PlayerBase player )
	{
		return true;
	}
	
	//folding
	bool CanFoldBaseBuildingObject()
	{
		if ( HasBase() || GetInventory().AttachmentCount() > 0 )
		{
			return false;
		}
		
		return true;
	}
	
	void FoldBaseBuildingObject()
	{
		CreateConstructionKit();
		GetGame().ObjectDelete( this );
	}
}