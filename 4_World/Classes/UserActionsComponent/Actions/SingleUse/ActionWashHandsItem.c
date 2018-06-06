class ActionWashHandsItem: ActionSingleUseBase
{
	protected const float WASH_HANDS_AMOUNT = 250; //ml
	
	void ActionWashHandsItem()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_CLEANHANDSBOTTLE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_CLEANHANDSBOTTLE;
		m_StanceMask        = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_MessageSuccess = "I have washed my hands.";
		//m_Animation = "open";
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINotRuinedAndEmpty;
		m_ConditionTarget = new CCTNone;
	}

	override int GetType()
	{
		return AT_WASH_HANDS_ITEM;
	}

	override string GetText()
	{
		return "Wash hands";
	}
	
	override bool HasTarget()
	{
		return false;
	}

	override bool HasProneException()
	{
		return true;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( player.HasBloodyHands() && item.GetQuantity() >= WASH_HANDS_AMOUNT )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	override void OnCompleteServer( PlayerBase player, ActionTarget target, ItemBase item, Param acdata )
	{
		PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
		module_lifespan.UpdateBloodyHandsVisibility( player, false );
		
		item.AddQuantity( -WASH_HANDS_AMOUNT, false );
	}
};