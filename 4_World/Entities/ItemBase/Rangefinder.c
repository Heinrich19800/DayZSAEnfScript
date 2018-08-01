class Rangefinder extends ItemOptics
{
	const float RANGEFINDER_MAX_DISTANCE = 900; //TODO adjust maximal distance to match RL rangefinder
	
	protected ref Timer 				m_timer;
	protected ref Param1<string> 		m_MessageParam;
	protected ref Param1<PlayerBase> 	m_Player;
	
	void Rangefinder()
	{
	}
	
	// How frequently the measurement should be taken
	float GetMeasurementUpdateInterval()
	{
		return 1.0;
	}
	
	void StartPeriodicMeasurement(PlayerBase player)
	{
		if ( m_timer == null )
		{
			m_timer = new Timer;
		}
		if ( m_MessageParam == null ) 	m_MessageParam = new Param1<string>("");
		if ( m_Player == null ) 		m_Player = new Param1<PlayerBase>(null);
		m_Player.param1 = player;
		m_timer.Run(GetMeasurementUpdateInterval(),this,"DoMeasurement",m_Player,true);
	}
	
	void StopPeriodicMeasurement()
	{
		if ( m_timer )
		{
			m_timer.Stop();
		}
	}
	
	// Measures the distance and returns result in formated string
	void DoMeasurement(PlayerBase player)
	{
		//string 		message			= "";
		const float	MAX_RANGE 		= 9999;
		float 		energy_needed 	= GetCompEM().GetEnergyUsage() * GetMeasurementUpdateInterval();
		vector 		from 			= GetGame().GetCurrentCameraPosition();
		vector 		to 				= from + (GetGame().GetCurrentCameraDirection() * MAX_RANGE);
		vector 		contact_pos;
		vector 		contact_dir;
		int 		contactComponent;
		
		// Use energy
		bool is_device_working = GetCompEM().ConsumeEnergy( energy_needed );
		
		// Fire raycast
		if (is_device_working)
		{
			DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contactComponent, NULL , NULL, player, false, false, ObjIntersectIFire);
	#ifdef DEVELOPER
			Debug.DrawArrow( from, contact_pos ); // Uncomment for debugging of raycast positions
	#endif
		}
		
		// Generate result
		if (is_device_working)
		{
			float dist = vector.Distance( from, contact_pos );
			dist = Math.Round(dist);
			if (dist < RANGEFINDER_MAX_DISTANCE)
			{
				m_MessageParam.param1 = "#range_finder_distance" + ": " + dist.ToString() + " #meters";
			}
			else
				m_MessageParam.param1 = "#range_finder_too_far";
		}
		else
		{
			return; //interrupts if no battery present
			m_MessageParam.param1 = "#range_finder_distance" + ": ----" + " #meters";
		}
		
		player.MessageAction(m_MessageParam.param1);
		/*if ( GetGame().IsServer() && player && player.IsAlive() && m_MessageParam.param1 != "" )
		{
			GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, m_MessageParam, true, player.GetIdentity());
		}*/
		//return message;
	}
}