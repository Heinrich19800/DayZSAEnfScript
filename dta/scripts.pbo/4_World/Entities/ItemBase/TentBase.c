class TentBase extends ItemBase
{
	protected const bool PACKED 	= false;
	protected const bool PITCHED 	= true;
	
	protected bool m_State;
	
	protected ref map< ref ToggleAnimations, bool> m_ToggleAnimations;
	protected ref array<string> m_ShowAnimationsWhenPitched;
	protected ref array<string> m_ShowAnimationsWhenPacked;
	protected Object m_ClutterCutter;
	
	void TentBase()
	{
		m_ToggleAnimations = new map<ref ToggleAnimations, bool>;
		m_ShowAnimationsWhenPitched = new array<string>;
		m_ShowAnimationsWhenPacked = new array<string>;
		RegisterNetSyncVariableBool("m_State");
	}
	
	void ~TentBase()
	{
		if ( m_ClutterCutter )
		{
			DestroyClutterCutter();
		}
	}
	
	override void EEInit()
	{
		super.EEInit();

		Pack();
	}
	
	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
	{		
		super.OnItemLocationChanged(old_owner, new_owner);
		
		if ( new_owner || old_owner )
		{
			Pack();
		}
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if ( m_State )
		{
			Pitch();
		}
		else
		{
			Pack();
		}
	}
	
	void HideAllAnimationsAndProxyPhysics()
	{		
		string cfg_path = "cfgVehicles " + GetType() + " AnimationSources";
		
		if ( GetGame().ConfigIsExisting( cfg_path ) )
		{
			int	selections = GetGame().ConfigGetChildrenCount( cfg_path );
			string proxy_selection_name;
			
			for ( int i = 0; i < selections; i++ )
			{
				string selection_name;
				GetGame().ConfigGetChildName( cfg_path, i, selection_name );
				SetAnimationPhase( selection_name, 1 );
				
				proxy_selection_name = selection_name;
				proxy_selection_name.ToLower();	
				RemoveProxyPhysics( proxy_selection_name );
			}
		}
	}
	
	override bool IsDeployable()
	{
		return true;
	}
	
	bool ConditionIntoInventory( EntityAI player )
	{
		return CanBeManipulated();
	}

	override bool CanPutIntoHands( EntityAI parent )
	{
		if( !super.CanPutIntoHands( parent ) )
		{		
			return false;
		}
				
		return CanBeManipulated();
	}

	override bool CanPutInCargo( EntityAI parent )
	{
		if( !super.CanPutInCargo( parent ) )
		{			
			return false;
		}
				
		return CanBeManipulated();
	}
	
	bool ConditionOutOfHands( EntityAI player )
	{
		return CanBeManipulated();
	}
	
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);
		
		if ( item.IsKindOf ( "CamoNet" ) ) 
		{
			SetAnimationPhase( "camonet", 0 );
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
				
		if ( item.IsKindOf ( "CamoNet" ) ) 
		{
			SetAnimationPhase( "camonet", 1 );
		}
	}
	
	override void OnPlacementComplete( Man player )
	{
		Pitch( true );
	}
	
	int GetState()
	{
		return m_State;
	}

	bool CanBePacked()
	{
		if ( GetState() == PITCHED )
		{
			if ( GetInventory().GetCargo().GetItemCount() == 0 && GetInventory().AttachmentCount() == 0 )
			{
				return true;
			}
		}
		
		return false;
	}

	bool CanBeManipulated()
	{
		if ( GetState() == PACKED )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	bool CanAttach( ItemBase item )
	{
		if ( item.IsKindOf ( "CamoNet" ) ) 
		{
			return true;
		}
		
		return false;
	}
	
	void Pack( bool update_navmesh = true )
	{	
		HideAllAnimationsAndProxyPhysics();
		
		m_State = PACKED;
		string proxy_selection_name;
		string animation_name;

		for ( int i = 0; i < m_ShowAnimationsWhenPacked.Count(); i++ )
		{
			animation_name = m_ShowAnimationsWhenPacked.Get(i);
		
			SetAnimationPhase( animation_name, 0 );
			proxy_selection_name = animation_name;
			proxy_selection_name.ToLower();
			AddProxyPhysics( proxy_selection_name );
		}
	
		GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
		
		if ( update_navmesh ) 
		{
			RegenerateNavmesh();	
		}
						
		DestroyClutterCutter();
		
		SetViewIndex( PACKED );
		
		SetSynchDirty();
	}

	void Pitch( bool update_navmesh = true )
	{		
		HideAllAnimationsAndProxyPhysics();
		
		m_State = PITCHED;
		string proxy_selection_name;
		string animation_name;
		
		for ( int i = 0; i < m_ShowAnimationsWhenPitched.Count(); i++ )
		{
			animation_name = m_ShowAnimationsWhenPitched.Get(i);
			
			SetAnimationPhase( animation_name, 0 );
			proxy_selection_name = animation_name;
			proxy_selection_name.ToLower();
			AddProxyPhysics( proxy_selection_name );
		}
		
		GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
		
		if ( update_navmesh ) 
		{
			RegenerateNavmesh();	
		}
		
		SetViewIndex( PITCHED );
		
		SetSynchDirty();
	}
	
	bool CanToggleAnimations( string selection )
	{		
		for ( int i = 0; i < m_ToggleAnimations.Count(); i++ )
		{
			ToggleAnimations toggle = m_ToggleAnimations.GetKey(i);
			string toggle_off = toggle.GetToggleOff();
			toggle_off.ToLower();
			string toggle_on = toggle.GetToggleOn();
			toggle_on.ToLower();
			
			if ( toggle_off == selection || toggle_on == selection )
			{
				return true;
			}
		}
		
		return false;
	}

	void ToggleAnimation( string selection )
	{
		for ( int i = 0; i < m_ToggleAnimations.Count(); i++ )
		{
			ToggleAnimations toggle = m_ToggleAnimations.GetKey(i);
			
			string toggle_off = toggle.GetToggleOff();
			toggle_off.ToLower();
			string toggle_on = toggle.GetToggleOn();
			toggle_on.ToLower();
						
			if ( toggle_off == selection || toggle_on == selection )
			{
				if ( m_ToggleAnimations.GetElement(i) )
				{
					SetAnimationPhase( toggle.GetToggleOff(), 0 );
					AddProxyPhysics( toggle.GetToggleOff() );
					SetAnimationPhase( toggle.GetToggleOn(), 1 );
					RemoveProxyPhysics( toggle.GetToggleOn() );
					m_ToggleAnimations.Set( toggle, false );
				}
				else
				{				
					SetAnimationPhase( toggle.GetToggleOff(), 1 );
					RemoveProxyPhysics( toggle.GetToggleOff() );
					SetAnimationPhase( toggle.GetToggleOn(), 0 );
					AddProxyPhysics( toggle.GetToggleOn() );
					m_ToggleAnimations.Set( toggle, true );
				}
			}
		}
	}
	
	void RegenerateNavmesh()
	{
		SetAffectPathgraph( true, false );
		
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, this);
	}
	
	void DestroyClutterCutter()
	{
		if ( GetGame().IsMultiplayer() || GetGame().IsServer() )
		{
			if ( m_ClutterCutter )
			{
				GetGame().ObjectDelete( m_ClutterCutter );
			}
		}
	}
};
