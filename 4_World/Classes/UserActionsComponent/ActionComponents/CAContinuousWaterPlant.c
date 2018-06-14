class CAContinuousWaterPlant : CAContinuousQuantity
{
	protected float m_PlantThirstyness;
	protected float	m_TimeToComplete;

	void CAContinuousWaterPlant( float quantity_used_per_second )
	{
		m_QuantityUsedPerSecond = quantity_used_per_second;
	}
	
	override void Setup( PlayerBase player, ActionTarget target, ItemBase item )
	{
		PlantBase target_PB;
		if (Class.CastTo(target_PB, target.GetObject()))
		{
			m_SpentQuantity = 0;
			if ( !m_SpentUnits )
			{ 
				m_SpentUnits = new Param1<float>(0);
			}
			else
			{	
				m_SpentUnits.param1 = 0;
			}
			if ( item )
			{
				m_ItemQuantity = item.GetQuantity();
			}
			if ( target_PB ) 
			{
				m_PlantThirstyness = target_PB.GetWaterMax() - target_PB.GetWater();
			}

			m_TimeToComplete = (Math.Min(m_PlantThirstyness,m_ItemQuantity))/m_QuantityUsedPerSecond;
		}
	}
	
	override int Execute( PlayerBase player, ActionTarget target, ItemBase item  )
	{
		if ( !player )
		{
			return UA_ERROR;
		}
		
		if ( m_ItemQuantity <= 0 )
		{
			return UA_SETEND_2;
		}
		else
		{
			if ( m_SpentQuantity < m_ItemQuantity  &&  m_SpentQuantity < m_PlantThirstyness )
			{
				m_AdjustedQuantityUsedPerSecond = player.GetSoftSkillManager().AddSpecialtyBonus( m_QuantityUsedPerSecond, m_Action.GetSpecialtyWeight(), true);		
				m_SpentQuantity += m_QuantityUsedPerSecond * player.GetDeltaT();
				
				if ( m_Action ) 
				{
					PlantBase plant;
					Class.CastTo(plant,  target.GetObject() );
					Slot slot = plant.GetSlot();

					m_Action.SendMessageToClient(player, slot.GiveWater( item, m_SpentQuantity ));
				}
				return UA_PROCESSING;
			}
			else
			{
				CalcAndSetQuantity(player, target, item);
				return UA_FINISHED;
			}
		}
	}
	
	override float GetProgress()
	{	
		//float progress = (m_SpentQuantity*m_QuantityUsedPerSecond)/m_TimeToComplete;
		return (m_SpentQuantity*m_QuantityUsedPerSecond)/m_TimeToComplete;
	}
};