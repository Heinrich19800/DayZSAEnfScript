class ActionGetOutTransport: ActionInteractBase
{
	private Transport m_transport;
	private int       m_crewIdx;


	void ActionGetOutTransport()
	{
		m_MessageSuccess = "";
		//m_CommandUID = DayZPlayerConstants.;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		m_HUDCursorIcon = "GetInDriver";
	}


	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override int GetType()
	{
		return AT_GETOUT_TRANSPORT;
	}

	override string GetText()
	{
		return "get out";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		
		if ( player.GetCommand_Vehicle() )
			return true;
		
		return false;
	}

	override void Start( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Print("Vypadni z auta!");
	}
	
	override bool IsLocal()
	{
		return true;
	}
	
	override bool IsInstant()
	{
		return true;
	}
};
