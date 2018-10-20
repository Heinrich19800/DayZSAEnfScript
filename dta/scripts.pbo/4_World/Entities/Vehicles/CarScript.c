enum CarDoorState
{
	DOORS_MISSING,
	DOORS_OPEN,
	DOORS_CLOSED
}

/*!
	Base script class for all motorized wheeled vehicles.
*/
class CarScript extends Car
{
	protected float m_Time;

	//! keeps ammount of each fluid
	protected float m_FuelAmmount;
	protected float m_CoolantAmmount;
	protected float m_OilAmmount;
	protected float m_BrakeAmmount;
	
	//!
	protected float m_EngineHealth;
	protected float m_RadiatorHealth;
	protected float m_FuelTankHealth;

	protected bool m_EngineSmoke;
	
	float m_dmgContactCoef;

	void CarScript()
	{
		Init();
	}

	override void Init()
	{
		super.Init();
		SetEventMask(/*EntityEvent.CONTACT |*/ EntityEvent.POSTSIMULATE);

		m_Time = 0;

		// sets max health for all components at init
		m_EngineHealth = 1;
		m_RadiatorHealth = 1;
		m_FuelTankHealth = 1;

		m_EngineSmoke = false;
		
		m_dmgContactCoef = 0;
	}
/*
	here we should handle the damage dealt in OnContact event, but maybe we will react even in that event 
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos)
	{
		Print("CarScript>>> EEHitBy");
		Print( dmgZone );
		Print( damageResult );
		Print( source );
		Print( component );
		Print( damageResult.GetDamage("", "health") );
	}
*/
	override void EOnPostSimulate(IEntity other, float timeSlice)
	{
		m_Time += timeSlice;
		//! move it to constants.c const float CAR_UPDATE_INTERVAL = 1.0
		if ( m_Time >= 1 )
		{
			m_Time = 0;
			CarPartsHealthCheck();
			//! leaking of coolant from radiator when damaged
			if( GetFluidFraction(CarFluid.COOLANT) > 0 && m_RadiatorHealth < 1 )
				LeakFluid(CarFluid.COOLANT);

			//! leaking of fuel from damaged fuel tank
			//if( GetFluidFraction(CarFluid.FUEL) > 0 && m_FuelTankHealth < 1 )
			//	LeakFluid(CarFluid.FUEL);
	
			//! actions runned when the engine on
			if ( IsEngineOn() )
			{
			}
		}
	}

	//override void EOnContact( IEntity other, Contact extra )
	//{
	//	//Print(" contact impulse = " + extra.Impulse);
	//	//Print(" index of component of this car = " + extra.Index2);
	//}
	void OnContact( string zoneName, vector localPos, IEntity other, Contact data )
	{

		//Print(zoneName);

		switch( zoneName )
		{
			case "dmgZone_lightsLF":
				//Print("dmgZone_lightsLF");
			break;
			
			case "dmgZone_lightsRF":
				//Print("dmgZone_lightsRF");
			break;
			
			default:
				if ( GetGame().IsServer() || !GetGame().IsMultiplayer() )
				{
					if ( data.Impulse > 1000 )
					{
						//Print("Velkej Impulse - give some dmg");
						//DecreaseHealth("Engine", "Health", 400.0);

						float dmg = data.Impulse * m_dmgContactCoef;
						Print( zoneName );
						Print( dmg );
/*					
						if ( dmg > 1000 )
						{
							for( int i =0; i < CrewSize(); i++ )
							{
								Human crew = CrewMember( m_nextSeatIdx );
								if ( crew )
								{
									crew. ProcessDirectDamage( 3, null, zoneName, "EnviroDmg", "0 0 0", dmg );	
								}
							}
						}
*/			
					
						ProcessDirectDamage( 3, null, zoneName, "EnviroDmg", "0 0 0", dmg );

						//DecreaseHealth( zoneName, "Health", dmg);
					}
				}
			break;
		}



		//Print(zoneName);
		//Print(other);
		
		//Print( data.Impulse);
		//float		RelativeNormalVelocityBefore;
		//float		RelativeNormalVelocityAfter;
		//Print( data.Normal);
		//Print( data.Position);
		//vector		RelativeVelocityBefore;
		//vector		RelativeVelocityAfter;

	}

	/*!
		Gets called every sound simulation step.
		In this callback, user can modify behaviour of sound controllers
	*/
	float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		switch ( ctrl )
		{
			case CarSoundCtrl.DOORS:
				break;
		}

		// if you don't wanna change the behaviour, just return the old value.
		return oldValue;
	}

	/*!
		Gets called everytime when the specified vehicle's fluid
		changes its current value eg. when car is consuming fuel.

		This callback is called on both server and client.
	*/
	void OnFluidChanged( CarFluid fluid, float newValue, float oldValue )
	{
		switch ( fluid )
		{
			case CarFluid.FUEL:
				m_FuelAmmount = newValue;
				break;

			case CarFluid.OIL:
				m_OilAmmount = newValue;
				break;

			case CarFluid.BRAKE:
				m_BrakeAmmount = newValue;
				break;

			case CarFluid.COOLANT:
				m_CoolantAmmount = newValue;
				break;
		}
	}

	/*!
		Gets called everytime the game wants to start the engine.
		This callback is called on server only.

		\return true if the engine can start, false otherwise.
	*/
	bool OnBeforeEngineStart()
	{
		// todo :: check if the battery is plugged-in
		//         check if we have enough power to start the engine
/*
		if ( GetHealth01("engine", "") <= 0 )
		{
			if ( !m_EngineSmoke )
			{
				Print("Smoke");
				EffVehicleSmoke engSmk = new EffEngineSmoke();
				SEffectManager.PlayOnObject(engSmk, this, "0 0.95 1.25" );
				// Particle is now playing on oject 'this'
	
	
	
	
				// Set particle to light smoke (this is default state after play)
				//engSmk.SetParticleStateLight();
	
				// Set particle to heavy smoke
				engSmk.SetParticleStateHeavy();
	
				// If needed, you can set the particle to anything you want.
				//engSmk.SetParticleState( int state );
				return true;
			}

			EffVehicleSmoke exhkSmk = new EffExhaustSmoke();
			SEffectManager.PlayOnObject(exhkSmk, this, "0.670 0.57 -2.05" );
			exhkSmk.SetParticleStateLight();

		}
*/
		//if ( GetFluidFraction(CarFluid.FUEL) <= 0 )
		//	return false;

		return true;
	}

	//! Gets called everytime the engine starts.
	void OnEngineStart()
	{
	}

	//! Gets called everytime the engine stops.
	void OnEngineStop()
	{
	}

	/*!
		Gets called everytime the game wants to switch the lights.
		\return true when lights can be switched, false otherwise.
	*/
	bool OnBeforeSwitchLights( bool toOn )
	{
		if ( toOn )
		{
			// todo :: check if the battery is plugged-in
			//         check if we have enough power to turn on the lights

			// this is the case from off -> on
			return true;
		}

		// this is the case on -> off
		return true;
	}
	
	protected void LeakFluid(CarFluid fluid)
	{
		float ammount = 0;
		
		switch (fluid)
		{
			case CarFluid.COOLANT:
				Print(m_RadiatorHealth);
				//! move this to constant.c
 				//! CAR_COOLANT_LEAK_PER_SEC_MIN = 0.02; CAR_COOLANT_LEAK_PER_SEC_MAX = 0.12;
				ammount = m_RadiatorHealth * Math.RandomFloat(0.02, 0.12);
				Print("coolant is leaking for: " + ammount);
				Leak(fluid, ammount);
			break;
		}
	}

	protected void CarPartsHealthCheck()
	{
		if ( GetGame().IsMultiplayer() && GetGame().IsServer() )
		{
			m_RadiatorHealth = GetHealth01("radiator", "");
			
			m_EngineHealth = GetHealth01("engine", "");
		}
/*
		if ( GetGame().IsMultiplayer() && GetGame().IsServer() )
		{
			m_EngineHealth = GetHealth01("engine", "");
			Print("tst Car Script");
			Print(m_EngineHealth);
		}
*/
	}
	
	string GetAnimSourceFromSelection( string selection )
	{
		return "";
	}
	
	int GetCrewIndex( string selection )
	{
		return -1;
	}

	bool IsVitalCarBattery()
	{
		return true;
	}
	
	bool IsVitalTruckBattery()
	{
		return true;
	}
	
	bool IsVitalSparkPlug()
	{
		return true;
	}
	
	bool IsVitalGlowPlug()
	{
		return true;
	}
	
	bool IsVitalEngineBelt()
	{
		return true;
	}

	//! camera type
	override int Get3rdPersonCameraType()
	{
		return DayZPlayerCameras.DAYZCAMERA_3RD_VEHICLE;

	}

	int GetCarDoorsState( string slotType )
	{
		return -1;
	}
};
