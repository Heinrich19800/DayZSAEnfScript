const float TICK_INTERVAL = 1;

const float STAMINA_SOUND_TR1 = 0.7;
const float STAMINA_SOUND_TR2 = 0.4;

enum eStaminaZones
{
	ZONE0,
	ZONE1,
	ZONE2,
}

enum eStaminaTendency
{
	UP,
	DOWN,
}

class StaminaSoundHandler
{
	StaminaHandler m_StaminaHandler;
	eStaminaZones m_StaminaZone;
	eStaminaZones m_LastStaminaZone;
	
	eStaminaTendency m_StaminaTendency;
	
	PlayerBase m_Player;
	
	float m_TimeAccu;
	float m_StaminaLastValue;
	float m_Stamina;
	
	bool m_StaminaUpEndPlayed = true;
	
	void StaminaSoundHandler(StaminaHandler handler, PlayerBase player)
	{
		m_StaminaHandler = handler;
		m_Player = player;
		
	}
	
	void Update(float stamina_value, float deltaT)
	{
		m_TimeAccu += deltaT;
		
		if ( m_TimeAccu >= TICK_INTERVAL )
		{
			Process(stamina_value);
			m_TimeAccu = 0;
		}
	}
	
	void Process(float stamina_value)
	{	
		m_Stamina = stamina_value;
		float stamina_delta = m_StaminaLastValue - m_Stamina;
		
		if(stamina_delta > 0)
		{
			m_StaminaTendency = eStaminaTendency.DOWN;
		}
		else
		{
			m_StaminaTendency = eStaminaTendency.UP;
		}
		
		m_StaminaLastValue = stamina_value;
		
		m_StaminaZone = GetZone();
		EPlayerSoundEventID sound_event_id = GetPlayerSoundEventID();
		/*
		PrintString("stamina delta " +stamina_delta.ToString());
		PrintString("stamina zone " +m_StaminaZone.ToString());
		PrintString("stamina tendency " +m_StaminaTendency.ToString());
		PrintString(" sound event id " +sound_event_id.ToString());
		*/
		if( sound_event_id !=0 ) m_Player.SendSoundEvent(sound_event_id);
		
	}

	eStaminaZones GetZone()
	{
		float stamina_normalized = Math.InverseLerp(0, m_StaminaHandler.GetStaminaCap(), m_Stamina);
		
		//PrintString(" stamina_normalized " +stamina_normalized.ToString());
		eStaminaZones stamina_zone = eStaminaZones.ZONE0;
		
		if( stamina_normalized < STAMINA_SOUND_TR1)
		{
			stamina_zone = eStaminaZones.ZONE1;
		}
		
		if( stamina_normalized < STAMINA_SOUND_TR2)
		{
			stamina_zone = eStaminaZones.ZONE2;
		}
		
		return stamina_zone;
	}
	
	EPlayerSoundEventID GetPlayerSoundEventID()
	{
		EPlayerSoundEventID sound_event_id;
		
		if(m_StaminaZone == eStaminaZones.ZONE1 && m_StaminaTendency == eStaminaTendency.DOWN)
		{
			sound_event_id = EPlayerSoundEventID.STAMINA_DOWN_LIGHT;
			m_StaminaUpEndPlayed = false;
		}
		
		if(m_StaminaZone == eStaminaZones.ZONE1 && m_StaminaTendency == eStaminaTendency.UP)
		{
			sound_event_id = EPlayerSoundEventID.STAMINA_UP_LIGHT;
			m_StaminaUpEndPlayed = false;
		}
		
		if(m_StaminaZone == eStaminaZones.ZONE2 && m_StaminaTendency == eStaminaTendency.DOWN)
		{
			sound_event_id = EPlayerSoundEventID.STAMINA_DOWN_HEAVY;
			m_StaminaUpEndPlayed = false;
		}
		
		if(m_StaminaZone == eStaminaZones.ZONE2 && m_StaminaTendency == eStaminaTendency.UP)
		{
			sound_event_id = EPlayerSoundEventID.STAMINA_UP_HEAVY;
			m_StaminaUpEndPlayed = false;
		}
		
		if(m_StaminaZone == eStaminaZones.ZONE0 && m_StaminaTendency == eStaminaTendency.UP && !m_StaminaUpEndPlayed)
		{
			sound_event_id = EPlayerSoundEventID.STAMINA_UP_END;
			m_StaminaUpEndPlayed = true;
		}
		
		return sound_event_id;
		
	}

}