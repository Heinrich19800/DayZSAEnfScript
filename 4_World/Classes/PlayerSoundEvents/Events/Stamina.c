class StaminaSoundEventBase extends PlayerSoundEventBase
{
	override bool HasPriority(EPlayerSoundEventID other_state_id)
	{
		if(PlayerSoundEventHandler.GetPlayerSoundEventType(other_state_id) == EPlayerSoundEventType.STAMINA)
		{
			return true;
		}
		return false;
	}
}
class StaminaDownLight extends StaminaSoundEventBase
{
	void StaminaDownLight()
	{
		EPlayerSoundEventType m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_DOWN_LIGHT;
		m_SoundSetNameRoot = "staminaDownLight";
	}
}

class StaminaDownHeavy extends StaminaSoundEventBase
{
	void StaminaDownHeavy()
	{
		EPlayerSoundEventType m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_DOWN_HEAVY;
		m_SoundSetNameRoot = "staminaDownHeavy";
	}
}

class StaminaUpHeavy extends StaminaSoundEventBase
{
	void StaminaUpHeavy()
	{
		EPlayerSoundEventType m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_UP_HEAVY;
		m_SoundSetNameRoot = "staminaUpHeavy";
	}
}

class StaminaUpLight extends StaminaSoundEventBase
{
	void StaminaUpLight()
	{
		EPlayerSoundEventType m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_UP_LIGHT;
		m_SoundSetNameRoot = "staminaUpLight";
	}
}

class StaminaUpEnd extends StaminaSoundEventBase
{
	void StaminaUpEnd()
	{
		EPlayerSoundEventType m_Type = EPlayerSoundEventType.STAMINA;
		m_ID = EPlayerSoundEventID.STAMINA_UP_END;
		m_SoundSetNameRoot = "staminaUpEnd";
	}
}