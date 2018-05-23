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
	}
	
	override int GetType()
	{
		return AT_ATTACH;
	}
		
	override string GetText()
	{
		return "attach";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( item );
		
		if ( target_entity.GetInventory() && target_entity.GetInventory().CanAddAttachment( item_entity ) )
		{
			return true;
		}
			
		return false;
	}

	override void OnCompleteServer( PlayerBase player, ActionTarget target, ItemBase item, Param acdata )
	{
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( item );
		
		//find inventory location for attachment
		InventoryLocation target_location = new InventoryLocation;
		
		if( target_entity.GetInventory().FindFirstFreeLocationForNewEntity( item.GetType(), FindInventoryLocationType.ATTACHMENT, target_location ) )
		{
			//target_entity.PredictiveTakeEntityToTargetAttachmentEx( target_entity, item_entity, target_location.GetSlot() );
			target_entity.LocalTakeEntityAsAttachmentEx( item_entity, target_location.GetSlot() );
		}
	}
	
	override void OnCompleteClient( PlayerBase player, ActionTarget target, ItemBase item, Param acdata )
	{
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( item );
		
		//find inventory location for attachment
		InventoryLocation target_location = new InventoryLocation;
		
		if( target_entity.GetInventory().FindFirstFreeLocationForNewEntity( item.GetType(), FindInventoryLocationType.ATTACHMENT, target_location ) )
		{
			//target_entity.PredictiveTakeEntityToTargetAttachmentEx( target_entity, item_entity, target_location.GetSlot() );
			target_entity.LocalTakeEntityAsAttachmentEx( item_entity, target_location.GetSlot() );
		}
	}
}