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

	protected ref EffVehicleSmoke m_coolantFx;
	protected ref EffVehicleSmoke m_engineFx;
	protected ref EffVehicleSmoke m_exhaustFx;
		
	protected int m_enginePtcFx;
	protected int m_coolantPtcFx;
	protected int m_exhaustPtcFx;
	
	protected vector m_exhaustPtcPos;
	protected vector m_exhaustPtcDir;
	protected vector m_enginePtcPos;
	protected vector m_coolantPtcPos;
	
	protected float m_dmgContactCoef;
	protected float m_enviroCoef;
	
	protected bool m_PlayCrashSoundLight;
	protected bool m_PlayCrashSoundHeavy;
	
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
		m_FuelTankHealth = 1;
		m_RadiatorHealth = -1;

		m_enginePtcFx = -1;
		m_coolantPtcFx = -1;
		m_exhaustPtcFx = -1;

		m_dmgContactCoef = 0;
		m_enviroCoef = 0;

		//proto native vector GetMemoryPointPos(string memoryPointName);
 		//proto native bool MemoryPointExists(string memoryPoint);

		if 	( MemoryPointExists("ptcExhaust_end") )
		{
			Print( "CarScript Init " + GetType() );
			m_exhaustPtcPos = GetMemoryPointPos("ptcExhaust_end");
			if ( MemoryPointExists("ptcExhaust_start") )
			{
				vector exhaustStart = GetMemoryPointPos("ptcExhaust_start");
				vector tempOri = vector.Direction( exhaustStart, m_exhaustPtcPos);//.Normalized();//.VectorToAngles();
				
				//m_exhaustPtcDir = tempOri;

				m_exhaustPtcDir[0] = -tempOri[2];
				m_exhaustPtcDir[1] = tempOri[1];
				m_exhaustPtcDir[2] = tempOri[0];
				
				m_exhaustPtcDir = m_exhaustPtcDir.Normalized().VectorToAngles();

			}
		}
		else
		{
			m_exhaustPtcPos = "0 0 0";
			m_exhaustPtcDir = "1 1 1";
		}
	
		if 	( MemoryPointExists("ptcEnginePos") )
			m_enginePtcPos = GetMemoryPointPos("ptcEnginePos");
		else
			m_enginePtcPos = "0 0 0";		

		
		if 	( MemoryPointExists("ptcCoolantPos") )
			m_coolantPtcPos = GetMemoryPointPos("ptcCoolantPos");
		else
			m_coolantPtcPos = "0 0 0";		
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
	
		if ( dmgZone == "Engine" && GetHealth("Engine","") < 0.1 )
		{
			if ( GetHealth01("engine", "") <= 0.1 )
			{
				if ( !m_EngineSmoke )
				{
					Print("Smoke");
					EffVehicleSmoke engSmk = new EffEngineSmoke();
					SEffectManager.PlayOnObject(engSmk, this, "0 0.95 1.25" );
					// Particle is now playing on oject 'this'
				}
			}
		}
	}
*/
	
	override void EEItemAttached ( EntityAI item, string slot_name ) 
	{
		if ( GetGame().IsServer() )
		{
			if ( slot_name == "Reflector_1_1" )
				SetHealth( "Reflector_1_1", "Health", item.GetHealth() );

			if ( slot_name == "Reflector_2_1" )
				SetHealth( "Reflector_2_1", "Health", item.GetHealth() );
		}

	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		if ( GetGame().IsServer() )
		{
			//int slot_id = InventorySlots.GetSlotIdFromString(slot_name);
			if ( IsLightsOn() )
			{
				if ( slot_name == "CarBattery" || slot_name == "TruckBattery" )
					SwitchLights();

				if ( slot_name == "Reflector_1_1" )
				{
					SetHealth( "Reflector_1_1", "Health", 0 );
				
					item = FindAttachmentBySlotName( "Reflector_2_1" );
					if ( !item || GetHealth01("Reflector_2_1", "") <= 0 )
						SwitchLights();
				}

				if ( slot_name == "Reflector_2_1" )
				{
					SetHealth( "Reflector_2_1", "Health", 0 );

					item = FindAttachmentBySlotName( "Reflector_1_1" );
					if ( !item || GetHealth01("Reflector_1_1", "") <= 0 )
						SwitchLights();
				}
			}

			if ( EngineIsOn() )
			{
				//EngineBelt
				if ( slot_name == "GlowPlug" || slot_name == "SparkPlug" || slot_name == "CarBattery" || slot_name == "TruckBattery" )
					EngineStop();
			}

			if ( slot_name == "CarRadiator" )
			{
				LeakAll( CarFluid.COOLANT );
				SetHealth( "Radiator", "Health", 0);
			}
		}
	}


	override void EOnPostSimulate(IEntity other, float timeSlice)
	{
		m_Time += timeSlice;

		//! move it to constants.c const float CAR_UPDATE_INTERVAL = 1.0
		if ( m_Time >= CARS_FLUIDS_TICK )
		{
			m_Time = 0;

			CarPartsHealthCheck();

			//First of all check if the car should stop the engine
			if ( GetGame().IsServer() && EngineIsOn() )
			{
				if ( GetFluidFraction(CarFluid.FUEL) <= 0 || m_EngineHealth <= 0 )
					EngineStop();

				CheckVitalItem( IsVitalCarBattery(), "CarBattery" );
				CheckVitalItem( IsVitalTruckBattery(), "TruckBattery" );
				CheckVitalItem( IsVitalSparkPlug(), "SparkPlug" );
				CheckVitalItem( IsVitalGlowPlug(), "GlowPlug" );
				// engine belt is not needed right now
				//CheckVitalItem( IsVitalEngineBelt(), "EngineBelt" );
			}

			//! actions runned when the engine on
			if ( EngineIsOn() )
			{
				if ( GetGame().IsServer() )
				{
					float dmg;

					float test1 = EngineGetRPM();
					float test2 = EngineGetRPMRedline();
					
					if ( EngineGetRPM() >= EngineGetRPMRedline() )
					{
						if ( EngineGetRPM() > EngineGetRPMMax() )
							AddHealth( "Engine", "Health", -GetMaxHealth("Engine", "")); //CAR_RPM_DMG
							
						dmg = EngineGetRPM() * 0.001 * Math.RandomFloat( 0.02, 1.0 );  //CARS_TICK_DMG_MIN; //CARS_TICK_DMG_MAX
						//AddHealth( "Engine", "Health", -dmg); //CAR_RPM_DMG
						ProcessDirectDamage( 3, null, "Engine", "EnviroDmg", "0 0 0", dmg );
					}

					//! leaking of coolant from radiator when damaged
					if ( IsVitalRadiator() )
					{
						if ( GetFluidFraction(CarFluid.COOLANT) > 0 && m_RadiatorHealth < 0.5 ) //CARS_LEAK_THRESHOLD
							LeakFluid( CarFluid.COOLANT );
					}

					if ( GetFluidFraction(CarFluid.FUEL) > 0 && m_FuelTankHealth < 0.5 )
						LeakFluid( CarFluid.FUEL );

					if ( GetFluidFraction(CarFluid.BRAKE) > 0 && m_EngineHealth < 0.5 )
						LeakFluid( CarFluid.BRAKE );

					if ( GetFluidFraction(CarFluid.OIL) > 0 && m_EngineHealth < 0.5 )
						LeakFluid( CarFluid.OIL );

					if ( m_EngineHealth < 0.25 )
						LeakFluid( CarFluid.OIL );
/*Commented out till indicator of Oil in HUD will be ready
					if ( GetFluidFraction( CarFluid.OIL ) < 1 )
					{
						dmg = Math.Lerp( 0.02, 10, 1 - GetFluidFraction( CarFluid.OIL ) );  //CARS_TICK_DMG_MIN; //CARS_TICK_DMG_MAX
						AddHealth( "Engine", "Health", -dmg);
					}
*/
					if ( IsVitalRadiator() )
					{
						if ( GetFluidFraction( CarFluid.COOLANT ) < 0.5 && GetFluidFraction( CarFluid.COOLANT ) >= 0 )
						{
							dmg = ( 1 - GetFluidFraction(CarFluid.COOLANT) ) * Math.RandomFloat( 0.02, 10.00 );  //CARS_DMG_TICK_MIN_COOLANT; //CARS_DMG_TICK_MAX_COOLANT
							AddHealth( "Engine", "Health", -dmg );
						}
					}
				}
				
				//FX only on Client and in Single
				if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
				{
					if ( !SEffectManager.IsEffectExist( m_exhaustPtcFx ) )
					{
						m_exhaustFx = new EffExhaustSmoke();
						m_exhaustPtcFx = SEffectManager.PlayOnObject( m_exhaustFx, this, m_exhaustPtcPos, m_exhaustPtcDir );
					}

					m_exhaustFx.SetParticleStateLight();
				
					if ( IsVitalRadiator() && SEffectManager.IsEffectExist( m_coolantPtcFx ) )
						SEffectManager.Stop(m_coolantPtcFx);
					
					if ( IsVitalRadiator() && GetFluidFraction( CarFluid.COOLANT ) < 0.5 )
					{
						if ( !SEffectManager.IsEffectExist( m_coolantPtcFx ) )
						{
							m_coolantFx = new EffCoolantSteam();
							m_coolantPtcFx = SEffectManager.PlayOnObject( m_coolantFx, this, m_coolantPtcPos );
						}

						if ( GetFluidFraction( CarFluid.COOLANT ) > 0 )
							m_coolantFx.SetParticleStateLight();
						else
							m_coolantFx.SetParticleStateHeavy();
/*
						Particle ptc;
						if ( GetCarDoorsState("NivaHood") == CarDoorState.DOORS_CLOSED )
						{
							if ( Class.CastTo(ptc, m_coolantFx.GetParticle() ) )
							{
								ptc.SetParameter( -1, EmitorParam.AIR_RESISTANCE, 55 );
								ptc.SetParameter( -1, EmitorParam.SIZE, 0.05 );
							}
						}
						else
						{
							if ( Class.CastTo(ptc, m_coolantFx.GetParticle() ) )
							{
								ptc.SetParameter( -1, EmitorParam.AIR_RESISTANCE, 2 );
								ptc.SetParameter( -1, EmitorParam.SIZE, 0.5 );
							}
						}
*/
					}
					else
					{
						if ( SEffectManager.IsEffectExist( m_coolantPtcFx ) )
							SEffectManager.Stop(m_coolantPtcFx);
					}
				}
			}
			else
			{
				//FX only on Client and in Single
				if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
				{
					if ( SEffectManager.IsEffectExist( m_exhaustPtcFx ) )
						SEffectManager.Stop(m_exhaustPtcFx);
					
					if ( SEffectManager.IsEffectExist( m_coolantPtcFx ) )
						SEffectManager.Stop(m_coolantPtcFx);
				}
			}
		}

		//FX only on Client and in Single
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			if ( IsDamageDestroyed() )
			{
				if ( !SEffectManager.IsEffectExist( m_enginePtcFx ) )
				{
					m_engineFx = new EffEngineSmoke();
					m_enginePtcFx = SEffectManager.PlayOnObject( m_engineFx, this, m_enginePtcPos );
					//m_engineFx.SetParticleStateLight();
					m_engineFx.SetParticleStateHeavy();
				}
			}
		}
	}

	override void OnContact( string zoneName, vector localPos, IEntity other, Contact data )
	{

		//Print(zoneName);

		if ( zoneName == "" )
		{
			Print("CarScript >> ERROR >> OnContact dmg zone not defined!");
			return;
		}
		
		switch( zoneName )
		{
/*
			case "dmgZone_lightsLF":
				//Print("dmgZone_lightsLF");
			break;
			
			case "dmgZone_lightsRF":
				//Print("dmgZone_lightsRF");
			break;
*/
			default:
				if ( GetGame().IsServer() && zoneName != "")
				{
					float dmgMin = 150.0;	
					float dmgThreshold = 750.0;
					float dmgKillCrew = 3000.0;
					float dmg = data.Impulse * m_dmgContactCoef;

					if ( dmg < dmgThreshold )
					{					
						if ( dmg > dmgMin )
						{
							//Print( GetType() + " >>> " + " smlHit >>> " + "zoneName: "  + zoneName + " >>> - " + dmg.ToString() + " HP >>> in " + GetSpeedometer() + " km/h");
							AddHealth( zoneName, "Health", -dmg);
							m_PlayCrashSoundLight = true;
						}
					}
					else
					{
						//Print( GetType() + " >>> " + " BIGHit >>> " + "zoneName: " + zoneName + " >>> - " + dmg.ToString() + " HP >>> in " + GetSpeedometer() + " km/h" );
						for( int i =0; i < CrewSize(); i++ )
						{
							Human crew = CrewMember( i );
							if ( !crew )
								continue;

							PlayerBase player;
							if ( Class.CastTo(player, crew ) )
							{
								if ( dmg > dmgKillCrew )
								{		
									player.SetHealth(0.0);
								}
								else
								{
									//deal shock to player
									float shockTemp = Math.InverseLerp(dmgThreshold, dmgKillCrew, dmg);
									float shock = Math.Lerp( 50, 100, shockTemp );

									player.AddHealth("", "Shock", -shock );
									//Print( "SHOCK..........." + shock );
								}
							}
						}

						m_PlayCrashSoundHeavy = true;
						ProcessDirectDamage( 3, null, zoneName, "EnviroDmg", "0 0 0", dmg );
					}
				}
			break;
		}
	}

	/*!
		Gets called every sound simulation step.
		In this callback, user can modify behaviour of sound controllers
	*/
	override float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		if ( m_PlayCrashSoundLight )
		{
			SEffectManager.PlaySound("offroad_hit_light_SoundSet", GetPosition() );
			m_PlayCrashSoundLight = false;
		}
		
		if ( m_PlayCrashSoundHeavy )
		{
			SEffectManager.PlaySound("offroad_hit_heavy_SoundSet", GetPosition() );
			m_PlayCrashSoundHeavy = false;
		}
		
		switch ( ctrl )
		{
			// in this controller the higher returned value the more muted sounds inside the car
			case CarSoundCtrl.DOORS:
				break;
		}

		// if you don't wanna change the behaviour, just return the old value.
		return oldValue;
	}
	
	float enviroCoef()
	{
		//range <-1;1> higher number, higher heatcomfort
		return m_enviroCoef;
	}

	/*!
		Gets called everytime when the specified vehicle's fluid
		changes its current value eg. when car is consuming fuel.

		This callback is called on both server and client.
	*/
	override void OnFluidChanged( CarFluid fluid, float newValue, float oldValue )
	{
		if ( m_PlayCrashSoundLight )
		{
			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
				SEffectManager.PlaySound("offroad_hit_light_SoundSet", GetPosition() );

			m_PlayCrashSoundLight = false;
		}

		if ( m_PlayCrashSoundHeavy )
		{
			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
				SEffectManager.PlaySound("offroad_hit_heavy_SoundSet", GetPosition() );

			m_PlayCrashSoundHeavy = false;
		}
		
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
	override bool OnBeforeEngineStart()
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
	override void OnEngineStart()
	{
	}

	//! Gets called everytime the engine stops.
	override void OnEngineStop()
	{
	}

	/*!
		Gets called everytime the game wants to switch the lights.
		\return true when lights can be switched, false otherwise.
	*/
	override bool OnBeforeSwitchLights( bool toOn )
	{
		if ( toOn )
		{
			// todo :: check if the battery is plugged-in
			//         check if we have enough power to turn on the lights

			// this is the case from off -> on
			if ( GetHealth01("Reflector_1_1", "") > 0 && GetHealth01("Reflector_2_1", "") > 0 )
			{
				//if ( GetHealth01("Reflector_2_1", "") > 0 )
					return true;			
			}
			
			
		}

		// this is the case on -> off
		return true;
	}

	protected void CheckVitalItem( bool isVital, string itemName )
	{
		if ( !isVital )
			return;

		EntityAI item = FindAttachmentBySlotName(itemName);

		if ( !item )
			EngineStop();
		else if ( item.IsRuined() )
			EngineStop();
	}

	protected void LeakFluid(CarFluid fluid)
	{
		float ammount = 0;
		
		switch (fluid)
		{
			case CarFluid.COOLANT:
				ammount = (1- m_RadiatorHealth) * Math.RandomFloat(0.02, 0.05);//CARS_LEAK_TICK_MIN; CARS_LEAK_TICK_MAX
				Leak(fluid, ammount);
			break;
			
			case CarFluid.OIL:
				ammount =  ( 1 - m_EngineHealth ) * Math.RandomFloat(0.02, 1.0);//CARS_LEAK_OIL_MIN; CARS_LEAK_OIL_MAX
				Leak(fluid, ammount);
			break;
			
			case CarFluid.FUEL:
				ammount = ( 1 - m_FuelTankHealth ) * Math.RandomFloat(0.02, 0.05);//CARS_LEAK_TICK_MIN; CARS_LEAK_TICK_MAX
				Leak(fluid, ammount);
			break;
		}
	}

	protected void CarPartsHealthCheck()
	{
		if ( GetGame().IsServer() )
		{
			ItemBase radiator;
			Class.CastTo( radiator, FindAttachmentBySlotName("CarRadiator"));
			if ( radiator )
			{
				m_RadiatorHealth = radiator.GetHealth01("", "");
			}
			else
			{
				m_RadiatorHealth = 0;
			}
			
			m_EngineHealth = GetHealth01("Engine", "");

			m_FuelTankHealth = GetHealth01("FuelTank", "");
		}
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
	
	bool IsVitalRadiator()
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
