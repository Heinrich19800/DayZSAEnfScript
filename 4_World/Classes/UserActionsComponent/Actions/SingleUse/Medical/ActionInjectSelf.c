class ActionInjectSelf: ActionSingleUseBase
{
	void ActionInjectSelf()
	{
		m_MessageStartFail = "There's nothing left.";
		m_MessageStart = "I have started injecting myself";
		m_MessageSuccess = "I have injected myself.";
		m_MessageFail = "I have moved and injecting was canceled.";
		m_MessageCancel = "I stopped injecting.";
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INJECTION;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_MEDIUM;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override int GetType()
	{
		return AT_INJECT_S;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "Inject";
	}

	override void OnExecuteServer( PlayerBase player, ActionTarget target, ItemBase item, Param acdata )
	{	
		item.Delete();
		player.GetSoftSkillManager().AddSpecialty( m_SpecialtyWeight );
	}
};