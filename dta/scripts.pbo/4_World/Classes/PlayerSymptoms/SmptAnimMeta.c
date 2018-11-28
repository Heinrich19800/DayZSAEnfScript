class SmptAnimMetaBase
{
	AnimType m_AnimType;
	bool	m_IsPlaying;
	SymptomManager m_Manager;
	PlayerBase m_Player;
	int m_AnimID;
	int m_SymptomUID;
	bool m_DestroyRequested;
	
	void SmptAnimMetaBase(ParamsReadContext ctx, AnimType type, SymptomManager manager, PlayerBase player)
	{
		m_AnimType = type;
		m_Manager = manager;
		m_Player = player;
		Init(ctx);
	}
	
	protected void Init(ParamsReadContext ctx);
	
	bool IsPlaying()
	{
		return m_IsPlaying;
	}
	
	bool IsDestroyReqested()
	{
		return m_DestroyRequested;
	}
	
	void AnimFinished()
	{
		SymptomBase Symptom = m_Manager.GetSymptomByUID(m_SymptomUID);
		if( Symptom ) 
			Symptom.OnAnimationFinish();
		m_DestroyRequested = true;
	}
	
	bool PlayRequest()
	{
		bool played = Play();
		
		if(played)
		{
			
		}
		else
		{
			SymptomBase Symptom = m_Manager.GetSymptomByUID(m_SymptomUID);
			if( Symptom ) 
				Symptom.OnAnimationPlayFailed();
		}
		
		return played;
	}
	
	protected bool Play();
	void Update();

};

class SmptAnimMetaFB extends SmptAnimMetaBase
{
	int m_StanceMask;
	float m_Duration;
	
	override void Init(ParamsReadContext ctx)
	{
		DayZPlayerSyncJunctures.ReadPlayerSymptomFBParams( ctx,  m_AnimID, m_SymptomUID, m_StanceMask, m_Duration);
	}
	
	override bool Play()
	{
		HumanCommandActionCallback callback = m_Player.GetCommand_Action();
		
		if (!callback)
		{
			callback = m_Player.GetCommandModifier_Action();
		}
		if( callback )
		{
			callback.InternalCommand(DayZPlayerConstants.CMD_ACTIONINT_INTERRUPT);
		}
		
		SymptomCB anim_callback = SymptomCB.Cast(m_Player.StartCommand_Action(m_AnimID, SymptomCB, m_StanceMask));
		
		if(anim_callback)
		{
			anim_callback.Init(m_SymptomUID, m_Duration, m_Player);
			m_IsPlaying = true;
			return true;
		}
		return false;
	}
}

class SmptAnimMetaADD extends SmptAnimMetaBase
{
	HumanCommandModifierAdditive m_Hcma;
	
	override void Init(ParamsReadContext ctx)
	{
		DayZPlayerSyncJunctures.ReadPlayerSymptomADDParams( ctx, m_AnimID, m_SymptomUID);
	}
	
	override bool Play()
	{
		HumanCommandActionCallback callback = m_Player.GetCommand_Action();
		if (!callback)
		{
			callback = m_Player.GetCommandModifier_Action();
		}
		if( !callback )
		{
			m_Hcma = m_Player.AddCommandModifier_Modifier(m_AnimID);
			
			if(m_Hcma)
			{
				m_IsPlaying = true;
				return true;
			}
		}
		return false;
	}
	
	override void Update()
	{
		{//crash hotfix
			//Print(m_Hcma);
		m_Manager.OnAnimationFinished(m_SymptomUID);
		return;
		}
		
		if( m_IsPlaying )
		{
			if(!m_Hcma)
			{
				m_Manager.OnAnimationFinished(m_SymptomUID);
			}
		}
	}
}