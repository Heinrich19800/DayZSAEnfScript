class CAContinuousTimeCooking : CAContinuousBase
{
	protected float 			m_LocalTimeElpased;
	protected float				m_TimeElpased;
	protected float 			m_TimeElapsedRepeat;
	protected ref Param1<float>	m_SpentUnits;
	
	protected float 			m_TimeToCook;
	protected Cooking			m_CookingProcess;
	protected Edible_Base		m_ItemToCook;
	protected float 			m_CookingUpdateTime;
	
	void CAContinuousTimeCooking( float cooking_update_time )
	{
		m_CookingUpdateTime = cooking_update_time;
	}
	
	override void Setup( PlayerBase player, ActionTarget target, ItemBase item )
	{
		m_TimeElapsedRepeat = 0;
		
		if ( !m_SpentUnits )
		{ 
			m_SpentUnits = new Param1<float>(0);
		}
		else
		{	
			m_SpentUnits.param1 = 0;
		}
		
		//fireplace & cooking process
		FireplaceBase fireplace = FireplaceBase.Cast( target.GetObject() );
		m_CookingProcess = fireplace.GetCookingProcess();
		m_ItemToCook = m_CookingProcess.GetFoodOnStick( item );
		m_TimeToCook = m_CookingProcess.GetTimeToCook( m_ItemToCook, CookingMethodType.BAKING );
		
		//update elapsed time
		m_TimeElpased = m_ItemToCook.GetFoodStage().GetCookingTime();
	}
	
	override int Execute( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !player )
		{
			return UA_ERROR;
		}
		
		int cooking_state_update = 0;
		float cooking_time = m_ItemToCook.GetFoodStage().GetCookingTime();
		if ( m_TimeToCook > cooking_time )
		{
			m_TimeElpased += player.GetDeltaT();
			m_TimeElapsedRepeat += player.GetDeltaT();
				
			if ( m_TimeElapsedRepeat >= m_CookingUpdateTime )
			{
				cooking_state_update = m_CookingProcess.CookOnStick( m_ItemToCook, m_CookingUpdateTime );
				
				//refresh action when food changed state
				if ( cooking_state_update == 1 )
				{
					Setup( player, target, item );
				}
				
				m_TimeElapsedRepeat = 0;
			}				
			
			return UA_PROCESSING;
		}
		else
		{
			if ( m_SpentUnits )
			{
				m_SpentUnits.param1 = m_TimeElpased;
				SetACData(m_SpentUnits);
			}
			
			return UA_FINISHED;
		}
	}
	
	override float GetProgress()
	{	
		if ( m_TimeToCook != 0 )
		{
			return m_TimeElpased/m_TimeToCook;
		}

		return 1;
	}
};