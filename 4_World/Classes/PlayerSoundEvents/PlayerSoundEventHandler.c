enum EPlayerSoundEventID
{
	HOLD_BREATH = 1,
	RELEASE_BREATH,
	ENUM_COUNT,
	STAMINA_DOWN_LIGHT,
	STAMINA_DOWN_HEAVY,
	STAMINA_UP_LIGHT,
	STAMINA_UP_HEAVY,
	STAMINA_UP_END,
}

class PlayerSoundEventHandler
{
	PlayerBase m_Player;
	static ref PlayerSoundEventBase m_AvailableStates[128];
	ref PlayerSoundEventBase m_CurrentState;
	
	
	void PlayerSoundEventHandler(PlayerBase player)
	{
		m_Player = player;
		
		m_AvailableStates[EPlayerSoundEventID.HOLD_BREATH] = new HoldBreathSoundEvent();
		m_AvailableStates[EPlayerSoundEventID.RELEASE_BREATH] = new ReleaseBreathSoundEvent();
		m_AvailableStates[EPlayerSoundEventID.STAMINA_DOWN_LIGHT] = new StaminaDownLight();
		m_AvailableStates[EPlayerSoundEventID.STAMINA_DOWN_HEAVY] = new StaminaDownHeavy();
		m_AvailableStates[EPlayerSoundEventID.STAMINA_UP_LIGHT] = new StaminaUpLight();
		m_AvailableStates[EPlayerSoundEventID.STAMINA_UP_HEAVY] = new StaminaUpHeavy();
		m_AvailableStates[EPlayerSoundEventID.STAMINA_UP_END] = new StaminaUpEnd();
	}
	
	
	static EPlayerSoundEventID GetPlayerSoundEventID(EPlayerSoundEventID id)
	{
		return m_AvailableStates[id].GetPlayerSoundEventID();
	}
	
	static EPlayerSoundEventType GetPlayerSoundEventType(EPlayerSoundEventID id)
	{
		return m_AvailableStates[id].GetPlayerSoundEventType();
	}
	
	void OnTick(float delta_time)
	{
		if(m_CurrentState)
		{
			m_CurrentState.Tick();
			
			if( m_CurrentState.IsDestroyRequested() )
			{
				delete m_CurrentState;
			}
	
		}
	}
	
	void PlayRequest(EPlayerSoundEventID id)
	{
		PlayerSoundEventBase requested_state = m_AvailableStates[id].ClassName().ToType().Spawn();
		
		if(m_CurrentState)
		{
			if( m_CurrentState.HasPriority(id) )
			{
				// do nothing
			}
			else
			{
				m_CurrentState.Stop();
				m_CurrentState.Init(m_Player);
				m_CurrentState.Play();
			}
		}
		else
		{
			m_CurrentState = requested_state;
			m_CurrentState.Init(m_Player);
			m_CurrentState.Play();
		}
		
		

	}
}