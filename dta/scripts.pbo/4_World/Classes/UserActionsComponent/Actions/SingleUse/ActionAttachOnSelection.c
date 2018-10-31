class AttachOnSelectionActionData : ActionData
{
	int m_attSlot;
}

class ActionAttachOnSelection: ActionSingleUseBase
{
	void ActionAttachOnSelection()
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
		return AT_ATTACH_SELECTION;
	}
		
	override string GetText()
	{
		//return "attach on Selection";
		return "#attach";
	}
	
	override ActionData CreateActionData()
	{
		AttachOnSelectionActionData action_data = new AttachOnSelectionActionData;
		return action_data;
	}
	
	override bool SetupAction(PlayerBase player, ActionTarget target, ItemBase item, out ActionData action_data, Param extraData = NULL)
	{
		if ( super.SetupAction( player, target, item, action_data, extraData))
		{
			if (!GetGame().IsMultiplayer() || GetGame().IsClient())
			{
				AttachOnSelectionActionData osActionData = AttachOnSelectionActionData.Cast(action_data);
			
				EntityAI target_entity = EntityAI.Cast( target.GetObject() );
				EntityAI item_entity = EntityAI.Cast( item );
			
				array<string> selections = new array<string>;
				target_entity.GetActionComponentNameList(target.GetComponentIndex(), selections);

				//if ( IsInReach(player, target, UAMaxDistances.DEFAULT )) return false;	

				for (int s = 0; s < selections.Count(); s++)
				{

					int carId = InventorySlots.GetSlotIdFromString( selections[s] );
					int slotsCnt = item_entity.GetInventory().GetSlotIdCount();

					for (int i=0; i < slotsCnt; i++ )
					{
						int itmSlotId = item_entity.GetInventory().GetSlotId(i);

						if ( carId == itmSlotId )
						{
							osActionData.m_attSlot = itmSlotId;
							return true;
						}
					}
				}
				return false;
			}
			return true;
		}
		return false;
	}
	
	override void WriteToContext (ParamsWriteContext ctx, ActionData action_data)
	{
		super.WriteToContext(ctx, action_data);
		AttachOnSelectionActionData osActionData = AttachOnSelectionActionData.Cast(action_data);
		ctx.Write(osActionData.m_attSlot);
	}
	
	override bool ReadFromContext(ParamsReadContext ctx, ActionData action_data )
	{
		if (super.ReadFromContext(ctx, action_data ))
		{
			AttachOnSelectionActionData osActionData = AttachOnSelectionActionData.Cast(action_data);
			if (ctx.Read(osActionData.m_attSlot))
				return true;
		} 
		return false;
	}
	
	
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		
		EntityAI target_entity = EntityAI.Cast( target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( item );
		
		if ( target_entity && item_entity )
		{
			if ( !target_entity.GetInventory() ) return false;
			if ( !target_entity.GetInventory().CanAddAttachment( item_entity ) ) return false;

			if (GetGame().IsMultiplayer() && GetGame().IsServer() ) return true;
			
			array<string> selections = new array<string>;
			target_entity.GetActionComponentNameList(target.GetComponentIndex(), selections);

			//if ( IsInReach(player, target, UAMaxDistances.DEFAULT )) return false;

			for (int s = 0; s < selections.Count(); s++)
			{

				int carId = InventorySlots.GetSlotIdFromString( selections[s] );
				int slotsCnt = item_entity.GetInventory().GetSlotIdCount();

				for (int i=0; i < slotsCnt; i++ )
				{
					int itmSlotId = item_entity.GetInventory().GetSlotId(i);

					if ( carId == itmSlotId )
					{
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
		EntityAI item_entity = EntityAI.Cast( action_data.m_MainItem );
		
		AttachOnSelectionActionData osActionData = AttachOnSelectionActionData.Cast(action_data);
		
		action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx(target_entity, item_entity, osActionData.m_attSlot );
		//target_entity.PredictiveTakeEntityAsAttachmentEx( item_entity, m_attSlot );

	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetObject() );
		EntityAI item_entity = EntityAI.Cast( action_data.m_MainItem );
		
		AttachOnSelectionActionData osActionData = AttachOnSelectionActionData.Cast(action_data);
		
		action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx(target_entity, item_entity, osActionData.m_attSlot );
		//target_entity.PredictiveTakeEntityAsAttachmentEx( item_entity, m_attSlot );

	}
}