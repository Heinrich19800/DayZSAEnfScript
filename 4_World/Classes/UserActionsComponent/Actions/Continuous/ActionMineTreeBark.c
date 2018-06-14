class ActionMineTreeBark: ActionMineTree
{			
	void ActionMineTreeBark()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_PRONE;
		
		m_MessageStartFail = "My tool is too damaged to cut.";
		m_MessageStart = "I started cutting off the branch.";
		m_MessageSuccess = "I have cut off the branch.";
		m_MessageFail = "My tool is ruined.";
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override int GetType()
	{
		return AT_MINE_TREE_BARK;
	}
		
	override string GetText()
	{
		return "Cut bark off";
	}
};