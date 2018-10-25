class ActionSwitchSeats: ActionBase
{
	private Transport m_transport;
	private int       m_nextSeatIdx;
	private int       m_currSeatIdx;
	
	void ActionSwitchSeats()
	{
		//m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_STARTENGINE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
		m_SpecialtyWeight = 1.0;
		m_LockTargetOnUse = false;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}	
	
	override int GetType()
	{
		return AT_VEH_SWITCH_SEATS;
	}

	override string GetText()
	{
		return "#change_seat";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		
		m_transport = null;
		m_nextSeatIdx   = -1;
		
		HumanCommandVehicle vehCommand = player.GetCommand_Vehicle();

		if ( !vehCommand  )
			return false;
		
		int componentIndex = target.GetComponentIndex();		

		if ( !target )
			return false;

		if ( !Class.CastTo(m_transport, target.GetObject()) )
			return false;

		m_nextSeatIdx = m_transport.CrewPositionIndex( componentIndex );

		if ( m_nextSeatIdx < 0 )
			return false;

		Human crew = m_transport.CrewMember( m_nextSeatIdx );
		if ( crew )
			return false;
		
		m_currSeatIdx = m_transport.CrewMemberIndex( player );
		
		if ( !m_transport.CanReachSeatFromSeat( m_currSeatIdx, m_nextSeatIdx ) )
			return false;

		return true;
	}

	override void Start( ActionData action_data )
	{
		super.Start( action_data );
		HumanCommandVehicle vehCommand = action_data.m_Player.GetCommand_Vehicle();
		if ( vehCommand )
		{
			if ( m_transport )
			{
				int seat = m_transport.GetSeatAnimationType( m_nextSeatIdx );
				if ( seat >= 0 )
				{
					//pTransportPositionIndex, int pVehicleSeat
					vehCommand.SwitchSeat( m_nextSeatIdx, seat );
				}
			}
		}
	}
	
	override void OnUpdate(ActionData action_data)
	{

		if(action_data.m_State == UA_START)
		{
			if( !action_data.m_Player.GetCommand_Vehicle().IsSwitchSeat() )
			{
				if( !GetGame().IsMultiplayer() || GetGame().IsClient() )
				{
					action_data.m_Player.OnVehicleSwitchSeat( m_nextSeatIdx );
				}
				End(action_data);
			}
		}
	}
	
	override bool CanBeUsedInVehicle()
	{
		return true;
	}
};