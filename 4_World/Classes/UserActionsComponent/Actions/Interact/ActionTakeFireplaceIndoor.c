class ActionTakeFireplaceIndoor: ActionInteractBase
{
	void ActionTakeFireplaceIndoor()
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_PICKUP_HANDS;
		m_StanceMask        = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_MessageSuccess = "I took the fireplace.";
	}

	override int GetType()
	{
		return AT_TAKE_FIREPLACE_INDOOR;
	}

	override string GetText()
	{
		return "Take fireplace";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		//empty hands	--interact action base condition
		if ( target_object )
		{
			FireplaceIndoor fireplace_indoor = FireplaceIndoor.Cast( target_object );
	
			if ( !fireplace_indoor.HasAshes() && !fireplace_indoor.IsBurning() && fireplace_indoor.IsCargoEmpty() && !fireplace_indoor.GetCookingEquipment() )
			{
				return true;
			}
		}

		return false;
	}

	override void OnCompleteServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();
		FireplaceIndoor fireplace_indoor = FireplaceIndoor.Cast( target_object );
		
		//create fireplace object
		vector spawn_pos = action_data.m_Player.GetPosition();
		Fireplace fireplace = Fireplace.Cast( GetDayZGame().CreateObject( "Fireplace", spawn_pos ) );
		action_data.m_Player.PredictiveTakeEntityToHands( fireplace );
		
		//transfer all required parameters to this object (damage, wetness)
		fireplace.SetHealth( "", "", fireplace_indoor.GetHealth("", "") );
		fireplace.SetWet( fireplace_indoor.GetWet() );
		
		//transfer all cargo items to this object, position of all items must be preserved
		//fireplace in hands cannot have any items in it but this can be changed in the future
		CargoBase cargo = fireplace_indoor.GetInventory().GetCargo();
		for ( int i = 0; i < cargo.GetItemCount(); i++ )
		{	
			EntityAI c = cargo.GetItem(i);
			InventoryLocation srcc = new InventoryLocation;
			if ( c.GetInventory().GetCurrentInventoryLocation( srcc ) )
			{
				InventoryLocation dstc = new InventoryLocation;
				dstc.SetCargo( fireplace, c, srcc.GetIdx(), srcc.GetRow(), srcc.GetCol() );
				action_data.m_Player.ServerTakeEntityToTargetCargoEx( fireplace, c, srcc.GetIdx(), srcc.GetRow(), srcc.GetCol() );
			}
		}
		
		//transfer all attachments to this object
		int att_count = fireplace_indoor.GetInventory().AttachmentCount();
		for ( int j = 0; j < att_count; j++ )
		{
			EntityAI a = fireplace_indoor.GetInventory().GetAttachmentFromIndex( 0 );
			InventoryLocation srca = new InventoryLocation;
			if ( a.GetInventory().GetCurrentInventoryLocation( srca ) )
			{
				InventoryLocation dsta = new InventoryLocation;
				dsta.SetAttachment( fireplace, a, srca.GetSlot() );
				action_data.m_Player.ServerTakeEntityToTargetAttachmentEx( fireplace, a, srca.GetSlot() );
			}
		}
	}
}