class StaminaSoundEventBase extends PlayerSoundEventBase
{
	override bool ThisHasPriority(PlayerBase player, EPlayerSoundEventID other_state_id)
	{
		if(PlayerSoundEventHandler.GetSoundEventType(other_state_id) == EPlayerSoundEventType.STAMINA)
		{
			return true;
		}
		return false;
	}
	
	override void OnPlay(PlayerBase player)
	{
		//Material matColors = GetGame().GetWorld().GetMaterial("graphics/particles/materials/smoke/steam_small_cook_01");
		//matColors.SetParam("AlphaTest", 0/*+add_additional_modifiers_here*/);
		
		if( player.CanSpawnBreathVaporEffect() ) 
			player.SpawnBreathVaporEffect();
		
	}
}
class StaminaDownLight extends StaminaSoundEventBase
{
	void StaminaDownLight()
	{
		m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_DOWN_LIGHT;
		m_SoundVoiceAnimEventClassID = 1;
	}
}

class StaminaDownHeavy extends StaminaSoundEventBase
{
	void StaminaDownHeavy()
	{
		m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_DOWN_HEAVY;
		m_SoundVoiceAnimEventClassID = 2;
	}
}

class StaminaUpHeavy extends StaminaSoundEventBase
{
	void StaminaUpHeavy()
	{
		m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_UP_HEAVY;
		m_SoundVoiceAnimEventClassID = 3;
	}
}

class StaminaUpLight extends StaminaSoundEventBase
{
	void StaminaUpLight()
	{
		m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_UP_LIGHT;
		m_SoundVoiceAnimEventClassID = 4;
	}
}

class StaminaUpEnd extends StaminaSoundEventBase
{
	void StaminaUpEnd()
	{
		m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_UP_END;
		m_SoundVoiceAnimEventClassID = 5;
	}
}

class StaminaNormalDummy extends StaminaSoundEventBase
{
	void StaminaNormalDummy()
	{
		m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_NORMAL_DUMMY;
		m_IsDummyType = true;
		m_DummySoundLength = 3000;//in ms
	}
}