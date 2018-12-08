class ActionAttachToConstruction: ActionSingleUseBase
{
	void ActionAttachToConstruction()
	{
		m_MessageSuccess = "I've attached the object.";
	}

	override void CreateConditionComponents() 
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}
	
	override int GetType()
	{
		return AT_ATTACH_TO_CONSTRUCTION;
	}
		
	override string GetText()
	{
		return "#attach";
	}
	
	override ActionData CreateActionData()
	{
		AttachActionData action_data = new AttachActionData;
		return action_data;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		
		if ( target_entity && target_entity.CanUseConstruction() )
		{
			string selection = target_entity.GetActionComponentName( target.GetComponentIndex() );
			int slot_id  = GetAttachmentSlotFromSelection( target_entity, item, selection );
			ConstructionActionData construction_action_data = player.GetConstructionActionData();
			
			if ( slot_id != -1 )
			{
				if( target_entity.GetInventory().CanAddAttachmentEx( item, slot_id ) )	
				{
					construction_action_data.SetSlotId( slot_id );
					return true;
				}
				else
				{
					//is entity on slot and can be combined?
					ItemBase attachment_item = ItemBase.Cast( target_entity.GetInventory().FindAttachment( slot_id ) );
					if ( attachment_item && attachment_item.CanBeCombined( item, player ) )
					{
						construction_action_data.SetSlotId( slot_id );
						return true;
					}
				}
			}
		}	
		return false;
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetObject() );
		ItemBase item = ItemBase.Cast( action_data.m_MainItem );
		
		ConstructionActionData construction_action_data = action_data.m_Player.GetConstructionActionData();
		int slot_id = construction_action_data.GetSlotId();
		
		if ( slot_id != -1 )
		{
			ItemBase attachment = ItemBase.Cast( target_entity.GetInventory().FindAttachment( slot_id ) );
			
			if ( attachment )
			{
				//combine
				CombineItems( attachment, item );
			}
			else
			{
				//attach
				if ( GetGame().IsMultiplayer() )
				{
					action_data.m_Player.ServerTakeEntityToTargetAttachmentEx( target_entity, item, slot_id );
				}
				else
				{
					action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx( target_entity, item, slot_id );
				}
			}
		}
	}
	
	protected int GetAttachmentSlotFromSelection( EntityAI target, ItemBase item_to_attach, string selection )
	{
		string cfg_path = "cfgVehicles" + " " + target.GetType() + " "+ "GUIInventoryAttachmentsProps";
		
		if ( GetGame().ConfigIsExisting( cfg_path ) )
		{
			int	child_count = GetGame().ConfigGetChildrenCount( cfg_path );
			
			for ( int i = 0; i < child_count; i++ )
			{
				string child_name;
				GetGame().ConfigGetChildName( cfg_path, i, child_name );
				
				string child_selection;
				GetGame().ConfigGetText( cfg_path + " " + child_name + " " + "selection", child_selection );
				
				if ( selection == child_selection )
				{
					ref array<string> attachment_slots = new array<string>;
					GetGame().ConfigGetTextArray( cfg_path + " " + child_name + " " + "attachmentSlots", attachment_slots );
					
					for ( int j = 0; j < attachment_slots.Count(); ++j )
					{
						int target_slot_id = InventorySlots.GetSlotIdFromString( attachment_slots.Get( j ) );
						int item_slot_count = item_to_attach.GetInventory().GetSlotIdCount();
						
						for ( int k = 0; k < item_slot_count; ++k )
						{
							int item_slot_id = item_to_attach.GetInventory().GetSlotId( k );
							
							if ( target_slot_id == item_slot_id )
							{
								return item_slot_id;
							}
						}
					}
				}
			}
		}
		
		return -1;
	}
	
	protected void CombineItems( ItemBase target, ItemBase item )
	{
		if ( target.ConfigGetBool( "canBeSplit" ) && item && !target.IsFullQuantity() )
		{
			int quantity_used = target.ComputeQuantityUsed( item, true );
			if( quantity_used != 0 )
			{
				target.AddQuantity( quantity_used );
				item.AddQuantity( -quantity_used );
			}
		}
	}
}