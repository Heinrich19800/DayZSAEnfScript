class MediumTent extends TentBase
{
	void MediumTent()
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
		return "MediumTent_Door_Open_SoundSet";
	}
	
	override string GetSoundClose()
	{
		return "MediumTent_Door_Close_SoundSet";
	}
	
	//================================================================
	// ADVANCED PLACEMENT
	//================================================================
		
	override void OnPlacementComplete( Man player )
	{		
		super.OnPlacementComplete( player );
		
		PlayerBase pb = PlayerBase.Cast( player );
				
		if ( GetGame().IsServer() )
		{
			m_ClutterCutter = GetGame().CreateObject( "MediumTentClutterCutter", pb.GetLocalProjectionPosition(), false );	
			m_ClutterCutter.SetOrientation( pb.GetLocalProjectionOrientation() );
		}	
	}
		
	override bool IsTwoHandedBehaviour()
	{
		return true;
	}
		
	override string GetDeploySoundset()
	{
		return "placeMediumTent_SoundSet";
	}
	
	override string GetLoopDeploySoundset()
	{
		return "mediumtent_deploy_SoundSet";
	}	
};
