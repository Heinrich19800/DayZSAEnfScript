class BarrelHoles_ColorBase extends FireplaceBase
{
	//Visual animations
	const string ANIMATION_OPENED 			= "LidOff";
	const string ANIMATION_CLOSED			= "LidOn";
	
	protected bool m_IsOpened 				= false;
	protected bool m_IsOpenedClient			= false;
	
	void BarrelHoles_ColorBase()
	{
		//Particles - default for FireplaceBase
		PARTICLE_FIRE_START 	= ParticleList.BARREL_FIRE_START;
		PARTICLE_SMALL_FIRE 	= ParticleList.BARREL_SMALL_FIRE;
		PARTICLE_NORMAL_FIRE	= ParticleList.BARREL_NORMAL_FIRE;
		PARTICLE_SMALL_SMOKE 	= ParticleList.BARREL_SMALL_SMOKE;
		PARTICLE_NORMAL_SMOKE	= ParticleList.BARREL_NORMAL_SMOKE;
		PARTICLE_FIRE_END 		= ParticleList.BARREL_FIRE_END;
		PARTICLE_STEAM_END		= ParticleList.BARREL_FIRE_STEAM_2END;
		
		//synchronized variables
		RegisterNetSyncVariableBool( "m_IsOpened" );
	}
	
	override void EEInit()
	{
		super.EEInit();
		
		//hide in inventory
		//GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
	}
	
	override bool IsBarrelWithHoles()
	{
		return true;
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if ( !IsBeingPlaced() )
		{
			//refresh if opened/closed state changed
			if ( m_IsOpenedClient != m_IsOpened )
			{
				m_IsOpenedClient = m_IsOpened;
				
				//Refresh particles and sounds
				RefreshFireParticlesAndSounds( true );
			}
			
			//sound sync
			if ( IsOpened() && IsSoundSynchRemote() )
			{
				SoundBarrelOpenPlay();
			}
			
			if ( !IsOpened() && IsSoundSynchRemote() )
			{
				SoundBarrelClosePlay();
			}
		}
	}
	
	//ATTACHMENTS
	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		ItemBase item = ItemBase.Cast( attachment );
		
		//kindling items
		if ( IsKindling ( item ) && IsOpened() )
		{
			return true;
		}
		
		//fuel items
		if ( IsFuel ( item ) && IsOpened() )
		{
			return true;
		}
		
		//cookware
		if ( item.Type() == ATTACHMENT_COOKING_POT && !IsOpened() )
		{
			return true;
		}
		
		return false;
	}

	override bool CanReleaseAttachment( EntityAI attachment )
	{
		ItemBase item = ItemBase.Cast( attachment );
		
		//kindling items
		if ( IsKindling ( item ) && !IsBurning() && IsOpened() )
		{
			if ( HasLastFuelKindlingAttached() )
			{
				if ( HasLastAttachment() )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return true;
			}
		}
		
		//fuel items
		if ( IsFuel ( item ) && !IsBurning() && IsOpened() )
		{
			if ( HasLastFuelKindlingAttached() )
			{	
				if ( HasLastAttachment() )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return true;
			}
		}
		
		//cookware
		if ( item.Type() == ATTACHMENT_COOKING_POT )
		{
			return true;
		}

		
		return false;
	}

	override void EEItemAttached ( EntityAI item, string slot_name ) 
	{
		super.EEItemAttached ( item, slot_name );
		
		ItemBase item_base = ItemBase.Cast( item );
		
		//kindling / fuel
		if ( IsKindling ( item_base ) || IsFuel ( item_base ) )
		{
			//add to consumables
			AddToFireConsumables ( item_base );
		}
		
		//cookware
		if ( item_base.Type() == ATTACHMENT_COOKING_POT )
		{
			SetCookingEquipment( item_base );
			
			//rotate handle
			item_base.SetAnimationPhase ( ANIMATION_COOKWARE_HANDLE, 0 );
		}
		
		//refresh fireplace visuals
		RefreshFireplaceVisuals();
	}

	override void EEItemDetached ( EntityAI item, string slot_name ) 
	{
		super.EEItemDetached ( item, slot_name );
		
		ItemBase item_base = ItemBase.Cast( item );
		
		//kindling / fuel
		if ( IsKindling ( item_base ) || IsFuel ( item_base ) )
		{
			//remove from consumables
			RemoveFromFireConsumables ( GetFireConsumableByItem( item_base ) );
		}

		//cookware
		if ( item_base.Type() == ATTACHMENT_COOKING_POT )
		{
			ClearCookingEquipment();
			
			//rotate handle
			item_base.SetAnimationPhase ( ANIMATION_COOKWARE_HANDLE, 1 );
			
			//remove audio visuals
			Bottle_Base cooking_pot = Bottle_Base.Cast( item );
			cooking_pot.RemoveAudioVisualsOnClient();	
		}
		
		//refresh fireplace visuals
		RefreshFireplaceVisuals();
	}
	
	//CONDITIONS
	//this into/outo parent.Cargo
	override bool CanPutInCargo( EntityAI parent )
	{
		if( !super.CanPutInCargo(parent) ) {return false;}
		return false;
	}

	override bool CanRemoveFromCargo( EntityAI parent )
	{
		return true;
	}

	//cargo item into/outo this.Cargo
	override bool CanReceiveItemIntoCargo( EntityAI cargo )
	{
		if ( !IsOpened() || GetHierarchyParent() )
		{
			return false;
		}
		
		return true;
	}

	override bool CanReleaseCargo( EntityAI cargo )
	{
		if ( IsBurning() && IsOpened() )
		{
			return false;
		}
		else if ( !IsOpened() )
		{
			return false;
		}
		
		return true;
	}
	
	//hands
	override bool CanPutIntoHands( EntityAI parent )
	{
		if( !super.CanPutIntoHands( parent ) )
		{
			return false;
		}
		if ( HasAshes() || IsBurning() || !IsCargoEmpty() || IsItemTypeAttached( ATTACHMENT_COOKING_POT ) || IsOpened() )
		{
			return false;
		}
		
		return true;
	}
	
	//INVENTORY DISPLAY CONDITIONS
	override bool CanDisplayCargo()
	{
		//super
		if( !super.CanDisplayCargo() )
		{
			return false;
		}
		//
		
		return IsOpened();
	}
	
	override bool CanDisplayAttachmentSlot( string slot_name )
	{
		//super
		if( !super.CanDisplayAttachmentSlot( slot_name ) )
		{
			return false;
		}
		//
		
		if ( slot_name == "CookingEquipment" )
		{
			return !IsOpened();
		}
		
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		//super
		if( !super.CanDisplayAttachmentCategory( category_name ) )
		{
			return false;
		}
		//
		
		if ( category_name == "CookingEquipment" )
		{
			return !IsOpened();
		}			
		else
		{
			return IsOpened();
		}
		
		return true;
	}	
	// ---	

	//ACTIONS
	bool IsOpened()
	{
		return m_IsOpened;
	}
	
	override void SetOpenState( bool state )
	{
		m_IsOpened = state;
		
		Synchronize();
	}

	void SoundBarrelOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "barrel_open_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void Open()
	{
		//update visual
		SetAnimationPhase ( ANIMATION_OPENED, 0 );
		SetAnimationPhase ( ANIMATION_CLOSED, 1 );
		
		//set open state
		SetOpenState( true );
		
		//show in inventory
		//GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
		
		SoundSynchRemote();
	}
	
	void SoundBarrelClosePlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "barrel_close_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void Close()
	{
		//update visual
		SetAnimationPhase ( ANIMATION_OPENED, 1 );
		SetAnimationPhase ( ANIMATION_CLOSED, 0 );
		
		//set open state
		SetOpenState( false );
		
		//hide in inventory
		//GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
		
		SoundSynchRemote();
	}
	
	//Can extinguish fire
	override bool CanExtinguishFire()
	{
		if ( IsOpened() && IsBurning() )
		{
			return true;
		}
		
		return false;
	}	
	
	//particles
	override bool CanShowSmoke()
	{
		return IsOpened();
	}
	
	// Item-to-item fire distribution
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override bool CanBeIgnitedBy( EntityAI igniter = NULL )
	{
		if ( HasAnyKindling() && !IsBurning() && IsOpened() )
		{
			return true;
		}
			
		return false;
	}
	
	override bool CanIgniteItem( EntityAI ignite_target = NULL )
	{
		if ( IsBurning() && IsOpened() )
		{
			return true;
		}
		
		return false;
	}
	
	override bool IsIgnited()
	{
		return IsBurning();
	}
	
	override void OnIgnitedTarget( EntityAI ignited_item )
	{
	}
	
	override void OnIgnitedThis( EntityAI fire_source )
	{	
		//remove grass
		Object cc_object = GetGame().CreateObject ( OBJECT_CLUTTER_CUTTER , GetPosition() );
		cc_object.SetOrientation ( GetOrientation() );
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( DestroyClutterCutter, 0.2, false, cc_object );
		
		//start fire
		StartFire(); 
	}
	
	void DestroyClutterCutter( Object clutter_cutter )
	{
		GetGame().ObjectDelete( clutter_cutter );
	}	
	
	override bool IsThisIgnitionSuccessful( EntityAI item_source = NULL )
	{
		//check kindling
		if ( !HasAnyKindling() && IsOpened() )
		{
			return false;
		}
		
		//check roof
		if ( !IsEnoughRoomForFireAbove() )
		{
			return false;
		}
		
		//check surface
		if ( IsWaterSurface() )
		{
			return false;
		}

		//check wetness/rain/wind
		if ( IsWet() || IsRainingAbove() || IsWindy() )
		{
			return false;
		}
		
		return true;	
	}
	
	//================================================================
	// ADVANCED PLACEMENT
	//================================================================
	
	override string GetPlaceSoundset()
	{
		return "placeBarrel_SoundSet";
	}
}
