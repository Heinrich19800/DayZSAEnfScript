class ActionWringClothesCB : ActionContinuousBaseCB
{
	private const float QUANTITY_WRINGLED_PER_SECOND = 0.03;
	
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousEmpty(QUANTITY_WRINGLED_PER_SECOND);
	}
};

class ActionWringClothes: ActionContinuousBase
{
	void ActionWringClothes()
	{
		m_CallbackClass = ActionWringClothesCB;
		//m_CommandUID = DayZPlayerConstants.CMD_ACTION_WRING;
		m_MessageStartFail = "It's ruined.";
		m_MessageStart = "I have started wringing clothes.";
		m_MessageSuccess = "I have finished wringing clothes.";
		m_MessageFail = "Player moved and stopped wringing clothes.";
		m_MessageCancel = "I stopped wringing clothes.";
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_WRING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_LOW;
	}
	
	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override int GetType()
	{
		return AT_WRING_CLOTHES;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "Wring the clothes";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if( item && item.GetWet() >= 0.1 && item.GetWet() <= item.GetWetMax())
		{
			return true;	
		}
		else
		{	
			return false;		
		}	
	}	

	override void OnCompleteServer( ActionData action_data )
	{
		//action_data.m_MainItem.TransferModifiers(action_data.m_Player);
		Param1<float> nacdata = Param1<float>.Cast( action_data.m_ActionComponent.GetACData() );		
		float delta = nacdata.param1;
		action_data.m_MainItem.AddWet( -delta );

		action_data.m_Player.GetSoftSkillManager().AddSpecialty( m_SpecialtyWeight );
	}	
};