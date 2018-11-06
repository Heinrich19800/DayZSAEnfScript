class CAContinuousFill : CAContinuousBase
{
	protected float 				m_TargetUnits;
	protected float 				m_SpentQuantity;
	protected float 				m_SpentQuantity_total;
	protected float 				m_ItemQuantity;
	protected float 				m_AdjustedQuantityFilledPerSecond;
	protected float 				m_QuantityFilledPerSecond;
	protected ref Param1<float>		m_SpentUnits;
	protected float 				m_TimeElpased;
	protected float 				m_DefaultTimeStep = 0.25;
	protected int 					m_liquid_type;
	
	void CAContinuousFill( float quantity_filled_per_second , int liquid_type )
	{
		m_QuantityFilledPerSecond = quantity_filled_per_second;
		m_liquid_type = liquid_type;
	}
	
	override void Setup( ActionData action_data )
	{
		m_TimeElpased = 0;
		
		if ( !m_SpentUnits )
		{ 
			m_SpentUnits = new Param1<float>(0);
		}
		else
		{	
			m_SpentUnits.param1 = 0;
		}
		
		m_ItemQuantity = action_data.m_MainItem.GetQuantity();
		EntityAI pg = EntityAI.Cast(action_data.m_Target.GetObject()); // get power generator
		m_TargetUnits = pg.GetCompEM().GetEnergyMax() - pg.GetCompEM().GetEnergy();
		m_AdjustedQuantityFilledPerSecond = action_data.m_Player.GetSoftSkillManager().AddSpecialtyBonus( m_QuantityFilledPerSecond, m_Action.GetSpecialtyWeight(), true );
	}
	
	override int Execute( ActionData action_data )
	{
		if ( !action_data.m_Player )
		{
			return UA_ERROR;
		}
		
		PowerGenerator pg = PowerGenerator.Cast(action_data.m_Target.GetObject()); // get power generator
		
		if ( pg.GetFuel() >= pg.GetMaxFuel() )
		{
			return UA_FINISHED;
		}
		else
		{
			if ( m_SpentQuantity_total < m_TargetUnits )
			{
				m_SpentQuantity += m_AdjustedQuantityFilledPerSecond * action_data.m_Player.GetDeltaT();
				m_TimeElpased += action_data.m_Player.GetDeltaT();
				
				if ( m_TimeElpased >= m_DefaultTimeStep )
				{
					CalcAndSetQuantity( action_data );
					m_TimeElpased = 0;
					//Setup(action_data);	//reset data after repeat
				}
				return UA_PROCESSING;
			}
			else
			{
				CalcAndSetQuantity( action_data );
				OnCompletePogress(action_data);
				return UA_FINISHED;
			}
		}
	}
	
	override int Cancel( ActionData action_data )
	{
		if ( !action_data.m_Player || !action_data.m_MainItem )
		{
			return UA_ERROR;
		}
		
		CalcAndSetQuantity( action_data );
		return UA_CANCEL;
	}
	
	override int Interrupt( ActionData action_data )
	{				
		if ( GetGame().IsServer() )
		{
			action_data.m_Player.GetSoftSkillManager().AddSpecialty( UASoftSkillsWeight.PRECISE_LOW );
		}
		
		return super.Interrupt( action_data );
	}
	
	override float GetProgress()
	{	
		return m_SpentQuantity_total/m_TargetUnits;
	}
	//---------------------------------------------------------------------------
	
	void CalcAndSetQuantity( ActionData action_data )
	{
		
		m_SpentQuantity_total += m_SpentQuantity;
	
		if ( m_SpentUnits )
		{
			m_SpentUnits.param1 = m_SpentQuantity;
			SetACData(m_SpentUnits);
		}
		
		
		if ( GetGame().IsServer() )
		{
			PowerGenerator pg = PowerGenerator.Cast(action_data.m_Target.GetObject()); // get power generator
			int consumed_fuel = pg.AddFuel( m_SpentQuantity );
			action_data.m_MainItem.AddQuantity( -consumed_fuel );
		}
		
		m_SpentQuantity = 0;
	}
};