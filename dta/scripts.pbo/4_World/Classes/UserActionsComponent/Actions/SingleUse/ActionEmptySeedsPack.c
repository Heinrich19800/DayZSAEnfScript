/*
	User action for emptying packs of seeds (horticulture)
*/


class ActionEmptySeedsPack: ActionSingleUseBase
{
	void ActionEmptySeedsPack()
	{
		m_MessageSuccess = "I've emptied the pack.";
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_EMPTYSEEDSPACK;
		m_FullBody = false;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override int GetType()
	{
		return AT_EMPTY_SEEDS_PACK;
	}

	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "#unbox";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		SeedPackBase item_SPB = SeedPackBase.Cast( action_data.m_MainItem );
		item_SPB.EmptySeedPack( action_data.m_Player );
	}
};