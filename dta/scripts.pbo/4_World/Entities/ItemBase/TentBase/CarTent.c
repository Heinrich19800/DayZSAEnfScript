class CarTent extends TentBase
{
	void CarTent()
	{		
		m_ToggleAnimations.Insert( new ToggleAnimations("EntranceO", "EntranceC"), 0 );
			
		m_ShowAnimationsWhenPitched.Insert( "Body" );
		m_ShowAnimationsWhenPitched.Insert( "EntranceO" );

		m_ShowAnimationsWhenPacked.Insert( "Inventory" );
	}
		
	override void EEInit()
	{		
		super.EEInit();
	}
	
	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
	{		
		super.OnItemLocationChanged(old_owner, new_owner);
	}
	
	override string GetSoundOpen()
	{
		return "CarTent_Door_Open_SoundSet";
	}
	
	override string GetSoundClose()
	{
		return "CarTent_Door_Close_SoundSet";
	}
	
	//================================================================
	// ADVANCED PLACEMENT
	//================================================================
	
	override void OnPlacementComplete( Man player )
	{		
		super.OnPlacementComplete( player );
	}

	override bool IsDeployable()
	{
		return true;
	}
	
	override string GetDeploySoundset()
	{
		return "placeCarTent_SoundSet";
	}
	
	override string GetLoopDeploySoundset()
	{
		return "cartent_deploy_SoundSet";
	}
};
