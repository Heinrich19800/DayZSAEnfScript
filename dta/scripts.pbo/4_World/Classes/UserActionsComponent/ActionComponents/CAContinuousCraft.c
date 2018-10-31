class CAContinuousCraft : CAContinuousTime
{		
	override void Setup( ActionData action_data  )
	{
		m_TimeElpased = 0;
		m_AdjustedTimeToComplete = 1000; //indication of arror if somting will be craft 1000 sec
		if ( !m_SpentUnits )
		{ 
			m_SpentUnits = new Param1<float>(0);
		}
		else
		{	
			m_SpentUnits.param1 = 0;
		}
		
		WorldCraftActionData action_data_wc;
		Class.CastTo(action_data_wc, action_data);
		
		int recipeID = action_data_wc.m_RecipeID;		
		
		PluginRecipesManager module_recipes_manager;
		Class.CastTo(module_recipes_manager, GetPlugin(PluginRecipesManager));
		if( module_recipes_manager )
		{
			m_AdjustedTimeToComplete = module_recipes_manager.GetRecipeLengthInSecs( recipeID );
			if( module_recipes_manager.GetIsInstaRecipe(recipeID) || module_recipes_manager.IsEnableDebugCrafting() )
			{
				m_AdjustedTimeToComplete = 0;
			}
			float specialty_weight = module_recipes_manager.GetRecipeSpecialty( recipeID );
			m_AdjustedTimeToComplete = action_data.m_Player.GetSoftSkillManager().AdjustCraftingTime( m_AdjustedTimeToComplete, specialty_weight );
			
			//PrintString("ttc:" + m_AdjustedTimeToComplete.ToString());
		}
	}
	
	override int Execute( ActionData action_data  )
	{
		if ( !action_data.m_Player )
		{
			return UA_ERROR;
		}
		
		if ( m_TimeElpased < m_AdjustedTimeToComplete )
		{
			m_TimeElpased += action_data.m_Player.GetDeltaT();
		}
		else
		{
			if ( m_SpentUnits )
			{
				m_SpentUnits.param1 = m_TimeElpased;
				SetACData(m_SpentUnits);
			}
			OnCompletePogress(action_data);
			return UA_FINISHED;
		}
		return UA_PROCESSING;
	}
	
	override float GetProgress()
	{	
		if( m_AdjustedTimeToComplete > 0 )
		{
			//float progress = m_TimeElpased/m_AdjustedTimeToComplete;
			return m_TimeElpased/m_AdjustedTimeToComplete;
		}
		return 1;
	}
};