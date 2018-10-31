class ActionAttachMetalWire: ActionSingleUseBase
{
	void ActionAttachMetalWire()
	{
		m_MessageSuccess = "Metal wire attached.";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}

	override int GetType()
	{
		return AT_ATTACH_METAL_WIRE;
	}
		
	override string GetText()
	{
		return "#attach_metal_wire";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI target_EAI = EntityAI.Cast( target.GetObject() );
		
		if ( target_EAI.GetInventory().CanAddAttachment(item) )
		{
			return true;
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		EntityAI target_EAI = EntityAI.Cast( action_data.m_Target.GetObject() ); // cast to ItemBase
		if (target_EAI && action_data.m_MainItem)
		{
			action_data.m_Player.PredictiveTakeEntityToTargetAttachment(target_EAI, action_data.m_MainItem);
		}
	}
	override void OnExecuteClient( ActionData action_data )
	{
		EntityAI target_EAI = EntityAI.Cast( action_data.m_Target.GetObject() ); // cast to ItemBase
		if (target_EAI && action_data.m_MainItem)
		{
			action_data.m_Player.PredictiveTakeEntityToTargetAttachment(target_EAI, action_data.m_MainItem);
		}
	}
};