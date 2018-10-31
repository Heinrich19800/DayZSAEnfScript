class ActionAttach: ActionSingleUseBase
{
	void ActionAttach()
	{
		m_MessageSuccess = "I've attached the object.";
	}

	override void CreateConditionComponents() 
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ATTACHITEM;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override int GetType()
	{
		return AT_ATTACH;
	}
		
	override string GetText()
	{
		return "#attach";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( item );
		
		if ( target_entity && item_entity )
		{
			if ( target_entity.GetInventory() && target_entity.GetInventory().CanAddAttachment( item_entity ) )
			{
				return true;
			}
		}	
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( action_data.m_MainItem );
		
		//find inventory location for attachment
		InventoryLocation target_location = new InventoryLocation;
		
		if( target_entity.GetInventory().FindFirstFreeLocationForNewEntity( item_entity.GetType(), FindInventoryLocationType.ATTACHMENT, target_location ) )
		{
			action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx( target_entity, item_entity, target_location.GetSlot() );
		}
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( action_data.m_MainItem );
		
		//find inventory location for attachment
		InventoryLocation target_location = new InventoryLocation;
		
		if( target_entity.GetInventory().FindFirstFreeLocationForNewEntity( item_entity.GetType(), FindInventoryLocationType.ATTACHMENT, target_location ) )
		{
			action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx( target_entity, item_entity, target_location.GetSlot() );
		}
	}
}