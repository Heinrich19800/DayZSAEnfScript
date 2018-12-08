class CfgPatches
{
	class DZ_Vehicles_Wheeled
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class CarWheel: Inventory_Base
	{
		InteractActions[]={573};
		SingleUseActions[]={577};
		simulation="carwheel";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
		};
	};
	class CarDoor: Inventory_Base
	{
		scope=1;
		InteractActions[]={1043,1042,573};
		SingleUseActions[]={548};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
			class DamageZones
			{
				class Window
				{
					class Health
					{
						hitpoints=50;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								{}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								{}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									""
								}
							}
						};
					};
					componentNames[]=
					{
						"dmgZone_window"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Doors
				{
					class Health
					{
						hitpoints=500;
						transferToGlobalCoef=1;
						healthLevels[]=
						{
							
							{
								1,
								{}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								{}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									""
								}
							}
						};
					};
					componentNames[]=
					{
						"dmgZone_doors"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
			};
		};
	};
	class Car;
	class CarScript: Car
	{
		InteractActions[]={1047,1035};
		rotationFlags=64;
		storageCategory=4;
		insideSoundCoef=0.89999998;
		fuelCapacity=50;
		brakeFluidCapacity=1;
		oilCapacity=4;
		coolantCapacity=6;
		brakeFluidLeakDebit[]={0,0};
		oilLeakDebit[]={0,0};
		coolantLeakDebit[]={0,0};
		brakeFluidForceCoef[]={0,1,1,1};
		damageFromOil[]={0,0,1,0};
		damageFromCoolant[]={0,0,1,0};
		engineBeltSlot="EngineBelt";
		batterySlot="CarBattery";
		electricPowerResName="power";
		electricConsumptionIgnition=3001;
		electricConsumptionEngine=0;
		electricConsumptionLights=0;
		electricOutputEngine=5;
		selectionDashboard="light_dashboard";
		selectionLightFrontL="light_left";
		selectionLightFrontR="light_right";
		selectionShowDamage="poskozeni";
		selectionBackLights="light_back";
		selectionBrakeLights="light_break";
		class Crew
		{
			class Driver
			{
				actionSel="seat_driver";
				proxyPos="crewDriver";
				getInPos="pos_driver";
				getInDir="pos_driver_dir";
				isDriver=1;
			};
			class CoDriver
			{
				actionSel="seat_coDriver";
				proxyPos="crewCoDriver";
				getInPos="pos_coDriver";
				getInDir="pos_coDriver_dir";
			};
		};
		class SimulationModule
		{
			class Axles
			{
				class Front
				{
					class Wheels
					{
						class Left
						{
							inventorySlot="";
							animTurn="turnfrontleft";
							animRotation="wheelfrontleft";
							animDamper="damperfrontleft";
							wheelHub="wheel_1_1_damper_land";
						};
						class Right
						{
							inventorySlot="";
							animTurn="turnfrontright";
							animRotation="wheelfrontright";
							animDamper="damperfrontright";
							wheelHub="wheel_2_1_damper_land";
						};
					};
				};
				class Rear
				{
					class Wheels
					{
						class Left
						{
							inventorySlot="";
							animTurn="turnbackleft";
							animRotation="wheelbackleft";
							animDamper="damperbackleft";
							wheelHub="wheel_1_2_damper_land";
						};
						class Right
						{
							inventorySlot="";
							animTurn="turnbacktright";
							animRotation="wheelbackright";
							animDamper="damperbackright";
							wheelHub="wheel_2_2_damper_land";
						};
					};
				};
			};
		};
		attachments[]=
		{
			"CarBattery",
			"LightBulb",
			"SparkPlug",
			"V3SWheel_1_1",
			"V3SWheel_2_1"
		};
		engineVitalParts[]=
		{
			"SparkPlug",
			"CarBattery"
		};
		electricalVitalParts[]=
		{
			"CarBattery",
			"HeadlightH7"
		};
		hiddenSelections[]=
		{
			""
		};
		hiddenSelectionsTextures[]=
		{
			""
		};
		class ViewPilot
		{
			initFov=0.76899999;
			minFov=0.41429999;
			maxFov=1.192;
			initFovEXT=0.73000002;
			minFovEXT=0.41429999;
			maxFovEXT=0.94999999;
			initAngleX=0;
			minAngleX=-85;
			maxAngleX=85;
			initAngleY=0;
			minAngleY=-150;
			maxAngleY=150;
		};
		class AnimationSources
		{
			class DoorsDriver
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
			class DoorsCoDriver: DoorsDriver
			{
			};
			class DoorsHood: DoorsDriver
			{
			};
			class DoorsTrunk: DoorsDriver
			{
			};
			class HideDestroyed_1_1
			{
				source="user";
				initPhase=0;
				animPeriod=0.001;
			};
			class HideDestroyed_1_2
			{
				source="user";
				initPhase=0;
				animPeriod=0.001;
			};
			class HideDestroyed_2_1
			{
				source="user";
				initPhase=0;
				animPeriod=0.001;
			};
			class HideDestroyed_2_2
			{
				source="user";
				initPhase=0;
				animPeriod=0.001;
			};
			class AnimHitWheel_1_1
			{
				source="Hit";
				hitpoint="HitWheel_1_1";
				raw=1;
			};
			class AnimHitWheel_1_2: AnimHitWheel_1_1
			{
				hitpoint="HitWheel_1_2";
			};
			class AnimHitWheel_2_1: AnimHitWheel_1_1
			{
				hitpoint="HitWheel_2_1";
			};
			class AnimHitWheel_2_2: AnimHitWheel_1_1
			{
				hitpoint="HitWheel_2_2";
			};
			class HitDoorsHood: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsHood";
			};
			class HitDoorsTrunk: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsTrunk";
			};
			class HitDoorsDrivers: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsDriver";
			};
			class HitDoorsCoDrivers: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsCoDriver";
			};
			class HitDoorsCargo: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsCargo";
			};
		};
		class Exhausts
		{
			class Exhaust1
			{
				position="exhaust_start";
				direction="exhaust_end";
				effect="ExhaustsEffect";
			};
		};
		class Reflectors
		{
			class Left
			{
				color[]={1,0.80000001,0.60000002,1};
				brightness=1;
				radius=50;
				angle=120;
				angleInnerRatio=0.25;
				dayLight=1;
				flareAngleBias=40;
				position="light_left";
				direction="light_left_dir";
				hitpoint="dmgZone_lights";
				selection="dmgZone_lights";
			};
			class Right: Left
			{
				position="light_right";
				direction="light_right_dir";
				hitpoint="dmgZone_lights";
				selection="dmgZone_light";
			};
		};
	};
	class V3SWheel: CarWheel
	{
		scope=2;
		displayName="$STR_V3SWheel0";
		model="\DZ\vehicles\wheeled\V3S\proxy\v3s_wheel.p3d";
		weight=30000;
		itemSize[]={7,7};
		inventorySlot[]=
		{
			"V3SWheel_1_1",
			"V3SWheel_2_1",
			"V3SWheel_Spare_1",
			"V3SWheel_Spare_2"
		};
		rotationFlags=12;
		physLayer="item_large";
		radiusByDamage[]={0,0.465,0.30000001,0.38,0.99980003,0.34999999,0.99989998,0.28};
		radius=0.465;
		width=0.2;
		tyre="TYRE_OFFROAD_TRUCK";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\vehicles\wheeled\V3S\data\v3s_tire.rvmat",
								"DZ\vehicles\wheeled\V3S\data\v3s_rim.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\vehicles\wheeled\V3S\data\v3s_tire_damage.rvmat",
								"DZ\vehicles\wheeled\V3S\data\v3s_rim_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\vehicles\wheeled\V3S\data\v3s_tire_destruct.rvmat",
								"DZ\vehicles\wheeled\V3S\data\v3s_rim_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class V3SWheel_Ruined: CarWheel
	{
		scope=2;
		displayName="$STR_V3SWheel_Ruined0";
		model="\DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_new_burst.p3d";
		itemSize[]={6,6};
		weight=25000;
		physLayer="item_large";
		inventorySlot[]=
		{
			"V3SWheel_1_1",
			"V3SWheel_2_1",
			"V3SWheel_Spare_1",
			"V3SWheel_Spare_2"
		};
		rotationFlags=12;
		radius=0.30000001;
		width=0.2;
		tyre="TYRE_DESTROYED";
	};
	class V3SWheelDouble: V3SWheel
	{
		displayName="$STR_V3SWheelDouble0";
		model="\DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_double.p3d";
		inventorySlot[]=
		{
			"V3SWheel_1_2",
			"V3SWheel_1_3",
			"V3SWheel_2_2",
			"V3SWheel_2_3"
		};
		width=0.40000001;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\vehicles\wheeled\V3S\data\v3s_tire.rvmat",
								"DZ\vehicles\wheeled\V3S\data\v3s_rim.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\vehicles\wheeled\V3S\data\v3s_tire_damage.rvmat",
								"DZ\vehicles\wheeled\V3S\data\v3s_rim_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\vehicles\wheeled\V3S\data\v3s_tire_destruct.rvmat",
								"DZ\vehicles\wheeled\V3S\data\v3s_rim_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class V3SWheelDouble_Ruined: V3SWheel_Ruined
	{
		displayName="$STR_V3SWheelDouble_Ruined0";
		model="\DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_burst_double.p3d";
		inventorySlot[]=
		{
			"V3SWheel_1_2",
			"V3SWheel_1_3",
			"V3SWheel_2_2",
			"V3SWheel_2_3"
		};
		width=0.40000001;
	};
	class V3SDoors_Driver: CarDoor
	{
		scope=2;
		displayName="$STR_V3SDoors_Driver0";
		model="\DZ\vehicles\wheeled\V3S\proxy\v3s_doors_Driver.p3d";
		weight=15000;
		itemSize[]={10,8};
		inventorySlot="V3SDriverDoors";
		rotationFlags=8;
		physLayer="item_large";
		hiddenSelections[]=
		{
			"camo_Door"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_door_co.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
			class DamageZones
			{
				class Window
				{
					class Health
					{
						hitpoints=50;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\V3S\data\v3s_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\data\auta_skla_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									""
								}
							}
						};
					};
					componentNames[]=
					{
						"dmgZone_window"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Doors
				{
					class Health
					{
						hitpoints=500;
						transferToGlobalCoef=1;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\V3S\data\v3s_door.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\V3S\data\v3s_door_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\V3S\data\v3s_door_destruct.rvmat"
								}
							}
						};
					};
					componentNames[]=
					{
						"dmgZone_doors"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
			};
		};
	};
	class V3SDoors_CoDriver: V3SDoors_Driver
	{
		displayName="$STR_V3SDoors_CoDriver0";
		model="\DZ\vehicles\wheeled\V3S\proxy\v3s_doors_coDriver.p3d";
		inventorySlot="V3SCoDriverDoors";
		rotationFlags=4;
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_door_co.paa"
		};
	};
	class V3SDoors_Driver_Orange: V3SDoors_Driver
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_door_orange_co.paa"
		};
	};
	class V3SDoors_CoDriver_Orange: V3SDoors_CoDriver
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_door_orange_co.paa"
		};
	};
	class V3SDoors_Driver_Blue: V3SDoors_Driver
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_door_blue_co.paa"
		};
	};
	class V3SDoors_CoDriver_Blue: V3SDoors_CoDriver
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_door_blue_co.paa"
		};
	};
	class V3SDoors_Driver_Grey: V3SDoors_Driver
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_door_grey_co.paa"
		};
	};
	class V3SDoors_CoDriver_Grey: V3SDoors_CoDriver
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_door_grey_co.paa"
		};
	};
	class V3SHood: CarDoor
	{
		scope=2;
		displayName="$STR_V3SHood0";
		model="\DZ\vehicles\wheeled\V3S\proxy\v3s_hood.p3d";
		weight=15000;
		itemSize[]={12,10};
		inventorySlot="V3SHood";
		rotationFlags=2;
		physLayer="item_large";
		hiddenSelections[]=
		{
			"camo_Door"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_green_co.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"dz\vehicles\wheeled\V3S\data\v3s_hood_green.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"dz\vehicles\wheeled\V3S\data\v3s_hood_green_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"dz\vehicles\wheeled\V3S\data\v3s_hood_green_destruct.rvmat"
							}
						}
					};
				};
				componentNames[]=
				{
					"dmgZone_doors"
				};
			};
		};
	};
	class V3SHood_Orange: V3SHood
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_orange_co.paa"
		};
	};
	class V3SHood_Blue: V3SHood
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_Blue_co.paa"
		};
	};
	class V3SHood_Grey: V3SHood
	{
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_Grey_co.paa"
		};
	};
	class V3S_Chassis: CarScript
	{
		scope=2;
		displayName="$STR_v3s_chassis0";
		model="\dz\vehicles\wheeled\V3S\V3S_chassis.p3d";
		InteractActions[]={1047,1035};
		attachments[]=
		{
			"TruckBattery",
			"LightBulb",
			"V3SDriverDoors",
			"V3SCoDriverDoors",
			"V3SHood",
			"V3SWheel_1_1",
			"V3SWheel_1_2",
			"V3SWheel_1_3",
			"V3SWheel_2_1",
			"V3SWheel_2_2",
			"V3SWheel_2_3",
			"V3SWheel_Spare_1",
			"V3SWheel_Spare_2"
		};
		extCameraPosition[]={0,1.5,-8.5};
		dashboardMatOn="dz\vehicles\wheeled\v3s\data\v3s_dashboard_light.rvmat";
		dashboardMatOff="dz\vehicles\wheeled\v3s\data\v3s_dashboard.rvmat";
		frontReflectorMatOn="dz\vehicles\wheeled\v3s\data\v3s_cab_lights.rvmat";
		frontReflectorMatOff="dz\vehicles\wheeled\v3s\data\v3s_cab_chrome.rvmat";
		frontReflectorMatDamaged="dz\vehicles\wheeled\v3s\data\v3s_cab_damage.rvmat";
		frontReflectorMatRuined="dz\vehicles\wheeled\v3s\data\v3s_cab_destruct.rvmat";
		fuelCapacity=120;
		fuelConsumption=30;
		class SimulationModule: SimulationModule
		{
			drive="DRIVE_642";
			airDragCoefficient=0.50999999;
			class Steering
			{
				increaseSpeed[]={0,25,50,15};
				decreaseSpeed[]={0,50,50,40};
				centeringSpeed[]={0,25,50,15};
			};
			class Throttle
			{
				reactionTime=1;
				defaultThrust=0.85000002;
				gentleThrust=0.69999999;
				turboCoef=3;
				gentleCoef=0.5;
			};
			class Engine
			{
				inertia=1.5;
				powerMax=72;
				powerRpm=2100;
				torqueMax=360;
				torqueRpm=1400;
				rpmIdle=600;
				rpmMin=650;
				rpmClutch=700;
				rpmRedline=2600;
				rpmMax=3000;
			};
			class Gearbox
			{
				reverse=6.2800002;
				ratios[]={6.1900001,3.1300001,1.75,1};
				timeToUncoupleClutch=0.40000001;
				timeToCoupleClutch=0.2;
				maxClutchTorque=400;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle=35;
					finalRatio=6.8400002;
					brakeBias=0.5;
					brakeForce=8000;
					wheelHubMass=25;
					wheelHubRadius=0.30000001;
					wheelHubRatio=2.1400001;
					class Suspension
					{
						stiffness=65000;
						compression=6000;
						damping=11500;
						travelMaxUp=0.25;
						travelMaxDown=0.15000001;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="V3SWheel_1_1";
						};
						class Right: Right
						{
							inventorySlot="V3SWheel_2_1";
						};
					};
				};
				class Middle: Rear
				{
					maxSteeringAngle=0;
					finalRatio=6.8400002;
					brakeBias=0.25;
					brakeForce=7500;
					wheelHubMass=45;
					wheelHubRadius=0.30000001;
					wheelHubRatio=2.1400001;
					class Suspension
					{
						stiffness=60000;
						compression=7000;
						damping=12000;
						travelMaxUp=0.25;
						travelMaxDown=0.15000001;
					};
					class Wheels: Wheels
					{
						class Left
						{
							inventorySlot="V3SWheel_1_2";
							animTurn="turnmiddleleft";
							animRotation="wheelmiddleleft";
							animDamper="dampermiddleleft";
							wheelHub="wheel_1_2_damper_land";
						};
						class Right
						{
							inventorySlot="V3SWheel_2_2";
							animTurn="turnmiddletright";
							animRotation="wheelmiddleright";
							animDamper="dampermiddleright";
							wheelHub="wheel_2_2_damper_land";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle=0;
					finalRatio=6.8400002;
					brakeBias=0.25;
					brakeForce=7500;
					wheelHubMass=45;
					wheelHubRadius=0.30000001;
					wheelHubRatio=2.1400001;
					class Suspension
					{
						stiffness=60000;
						compression=7000;
						damping=12000;
						travelMaxUp=0.25;
						travelMaxDown=0.15000001;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="V3SWheel_1_3";
							wheelHub="wheel_1_3_damper_land";
						};
						class Right: Right
						{
							inventorySlot="V3SWheel_2_3";
							wheelHub="wheel_2_3_damper_land";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={7,8};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
		class AnimationSources: AnimationSources
		{
			class WheelSidePlate1
			{
				source="user";
				initPhase=0;
				animPeriod=1.3;
			};
			class WheelSidePlate2: WheelSidePlate1
			{
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
			class DamageZones
			{
				class Chassis
				{
					class Health
					{
						hitpoints=3000;
						transferToGlobalCoef=1;
					};
					componentNames[]=
					{
						"dmgZone_chassis"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Front
				{
					class Health
					{
						hitpoints=2500;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_destruct.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Fender_1_1",
						"Fender_2_1",
						"Engine"
					};
					transferToZonesThreshold[]={0.2,0.2,0};
					transferToZonesCoefs[]={0.60000002,0.60000002,0.80000001};
					memoryPoints[]=
					{
						"dmgZone_front"
					};
					componentNames[]=
					{
						"dmgZone_front"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"NivaHood"
					};
				};
				class Back
				{
					class Health
					{
						hitpoints=3000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\v3s\data\v3s_cargo.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\V3S\data\V3S_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\V3S\data\V3S_destruct.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Fender_1_2",
						"Fender_2_2",
						"WindowLR",
						"WindowRR"
					};
					transferToZonesCoefs[]={0.30000001,0.30000001,0.2,0.2};
					memoryPoints[]=
					{
						"dmgZone_back"
					};
					componentNames[]=
					{
						"dmgZone_back"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Roof
				{
					class Health
					{
						hitpoints=500;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cabin_a.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cabin_a_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cabin_a_destruct.rvmat"
								}
							}
						};
					};
					memoryPoints[]=
					{
						"dmgZone_roof"
					};
					componentNames[]=
					{
						"dmgZone_roof"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Fender_1_1
				{
					class Health
					{
						hitpoints=800;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\v3s_cab_destruct.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Front",
						"Engine",
						"Lights"
					};
					transferToZonesThreshold[]={0.5,0.25,1};
					transferToZonesCoefs[]={0.30000001,0.60000002,0.80000001};
					memoryPoints[]=
					{
						"dmgZone_fender_1_1"
					};
					componentNames[]=
					{
						"dmgZone_fender_1_1"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"V3SWheel_1_1"
					};
				};
				class Fender_2_1: Fender_1_1
				{
					memoryPoints[]=
					{
						"dmgZone_fender_2_1"
					};
					componentNames[]=
					{
						"dmgZone_fender_2_1"
					};
					inventorySlots[]=
					{
						"V3SWheel_2_1"
					};
				};
				class WindowFrontLeft
				{
					class Health
					{
						hitpoints=50;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\V3S\data\V3S_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\data\auta_skla_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									""
								}
							}
						};
					};
					memoryPoints[]=
					{
						"dmgZone_windowFrontLeft"
					};
					componentNames[]=
					{
						"dmgZone_windowFrontLeft"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class WindowFrontRight: WindowFrontLeft
				{
					memoryPoints[]=
					{
						"dmgZone_windowFrontRight"
					};
					componentNames[]=
					{
						"dmgZone_windowFrontRight"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Engine
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=1;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\v3s\data\v3s_chassis.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\V3S\data\V3S_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\V3S\data\V3S_destruct.rvmat"
								}
							}
						};
					};
					memoryPoints[]=
					{
						"dmgZone_engine"
					};
					componentNames[]=
					{
						"dmgZone_engine"
					};
					fatalInjuryCoef=0.001;
					inventorySlots[]={};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints=300;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\v3s\data\v3s_chassis.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\V3S\data\V3S_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\V3S\data\V3S_destruct.rvmat"
								}
							}
						};
					};
					componentNames[]=
					{
						"dmgZone_fuelTank"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Reflector_1_1
				{
					class Health
					{
						hitpoints=50;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								{}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								{}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								{}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Front",
						"Fender_1_1"
					};
					transferToZonesCoefs[]={1,1};
					memoryPoints[]=
					{
						"dmgZone_lights_1_1"
					};
					componentNames[]=
					{
						"dmgZone_lights_1_1"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"Reflector_1_1"
					};
				};
				class Reflector_2_1: Reflector_1_1
				{
					transferToZonesNames[]=
					{
						"Front",
						"Fender_2_1"
					};
					transferToZonesCoefs[]={1,1};
					memoryPoints[]=
					{
						"dmgZone_lights_2_1"
					};
					componentNames[]=
					{
						"dmgZone_lights_2_1"
					};
					inventorySlots[]=
					{
						"Reflector_2_1"
					};
				};
			};
		};
		class ObstacleGenerator
		{
			carve=1;
			timeToStationary=5;
			moveThreshold=0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius=1;
						height=1.5;
						center[]={0,0,1.5};
					};
					class Cyl2
					{
						radius=1;
						height=1.5;
						center[]={0,0,0};
					};
					class Cyl3
					{
						radius=1;
						height=1.5;
						center[]={0,0,-1.5};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name="$STR_attachment_Engine0";
				description="";
				attachmentSlots[]=
				{
					"TruckBattery",
					"EngineBelt"
				};
				icon="missing";
			};
			class Body
			{
				name="$STR_attachment_Body0";
				description="";
				attachmentSlots[]=
				{
					"LightBulb",
					"V3SDriverDoors",
					"V3SCoDriverDoors",
					"V3SHood"
				};
				icon="missing";
			};
			class Chassis
			{
				name="$STR_attachment_Chassis0";
				description="";
				attachmentSlots[]=
				{
					"V3SWheel_1_1",
					"V3SWheel_1_2",
					"V3SWheel_1_3",
					"V3SWheel_2_1",
					"V3SWheel_2_2",
					"V3SWheel_2_3",
					"V3SWheel_Spare_1",
					"V3SWheel_Spare_2"
				};
				icon="missing";
			};
		};
	};
	class V3S_Chassis_Blue: V3S_Chassis
	{
		scope=2;
		hiddenSelections[]=
		{
			"hood",
			"cabin",
			"doors_Driver",
			"doors_coDriver"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_blue_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_cab_blue_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_blue_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_blue_CO.paa"
		};
	};
	class V3S_Chassis_Orange: V3S_Chassis
	{
		scope=2;
		hiddenSelections[]=
		{
			"spare_wheels",
			"hood",
			"cabin",
			"doors_Driver",
			"doors_coDriver"
		};
		hiddenSelectionsTextures[]=
		{
			"",
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_orange_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_cab_orange_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_orange_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_orange_CO.paa"
		};
	};
	class V3S_Chassis_Grey: V3S_Chassis
	{
		scope=2;
		hiddenSelections[]=
		{
			"hood",
			"cabin",
			"doors_Driver",
			"doors_coDriver"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_grey_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_cab_grey_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_grey_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_grey_CO.paa"
		};
	};
	class V3S_Cargo: V3S_Chassis
	{
		displayName="$STR_v3s_cargo0";
		model="\dz\vehicles\wheeled\V3S\V3S_cargo.p3d";
		transportSoldier=9;
		class Cargo
		{
			itemsCargoSize[]={7,20};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
		class AnimationSources: AnimationSources
		{
			class DoorsTrunk
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
		};
	};
	class V3S_Cargo_Blue: V3S_Cargo
	{
		scope=2;
		hiddenSelections[]=
		{
			"hood",
			"cabin",
			"doors_Driver",
			"doors_coDriver"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_blue_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_cab_blue_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_blue_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_blue_CO.paa"
		};
	};
	class V3S_Cargo_Orange: V3S_Cargo
	{
		scope=2;
		hiddenSelections[]=
		{
			"hood",
			"cabin",
			"doors_Driver",
			"doors_coDriver"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_orange_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_cab_orange_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_orange_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_orange_CO.paa"
		};
	};
	class V3S_Cargo_Grey: V3S_Cargo
	{
		scope=2;
		hiddenSelections[]=
		{
			"hood",
			"cabin",
			"doors_Driver",
			"doors_coDriver"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\vehicles\wheeled\V3S\data\v3s_hood_grey_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_cab_grey_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_grey_CO.paa",
			"\dz\vehicles\wheeled\V3S\data\v3s_door_grey_CO.paa"
		};
	};
	class HatchbackWheel: CarWheel
	{
		scope=2;
		displayName="$STR_HatchbackWheel0";
		descriptionShort="$STR_hatchbackwheel1";
		model="\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel.p3d";
		weight=15000;
		itemSize[]={6,6};
		inventorySlot[]=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
		};
		rotationFlags=4;
		physLayer="item_large";
		radiusByDamage[]={0,0.36199999,0.30000001,0.30000001,0.99980003,0.25,0.99989998,0.2};
		radius=0.34999999;
		width=0.18000001;
		tyreRollResistance=0.015;
		tyreTread=0.69999999;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\vehicles\wheeled\OffroadHatchback\data\niva_wheel.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"DZ\vehicles\wheeled\OffroadHatchback\data\niva_wheel_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"DZ\vehicles\wheeled\OffroadHatchback\data\niva_wheel_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class HatchbackWheel_Ruined: CarWheel
	{
		scope=2;
		displayName="$STR_HatchbackWheel0";
		descriptionShort="$STR_hatchbackwheel1";
		model="\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel_destroyed.p3d";
		weight=10000;
		itemSize[]={6,6};
		inventorySlot[]=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
		};
		rotationFlags=4;
		physLayer="item_large";
		radius=0.2;
		width=0.17;
		tyreRollResistance=1;
		tyreTread=0.5;
	};
	class HatchbackDoors_Driver: CarDoor
	{
		scope=2;
		displayName="$STR_HatchbackDoors_Driver0";
		descriptionShort="$STR_HatchbackDoors_Driver1";
		model="\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Driver.p3d";
		weight=15000;
		itemSize[]={10,8};
		inventorySlot="NivaDriverDoors";
		rotationFlags=8;
		physLayer="item_large";
		class DamageSystem: DamageSystem
		{
			class GlobalHealth: GlobalHealth
			{
			};
			class DamageZones: DamageZones
			{
				class Window: Window
				{
					class Health: Health
					{
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\data\auta_skla_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								{}
							}
						};
					};
				};
				class Doors: Doors
				{
					class Health: Health
					{
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_door.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_door_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_door_destruct.rvmat"
								}
							}
						};
					};
				};
			};
		};
	};
	class HatchbackDoors_CoDriver: HatchbackDoors_Driver
	{
		displayName="$STR_HatchbackDoors_CoDriver0";
		descriptionShort="$STR_HatchbackDoors_CoDriver1";
		model="\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_coDriver.p3d";
		inventorySlot="NivaCoDriverDoors";
		rotationFlags=4;
	};
	class HatchbackHood: CarDoor
	{
		scope=2;
		displayName="$STR_HatchbackHood0";
		descriptionShort="$STR_HatchbackHood1";
		model="\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Hood.p3d";
		weight=15000;
		itemSize[]={12,10};
		inventorySlot="NivaHood";
		rotationFlags=2;
		physLayer="item_large";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"dz\vehicles\wheeled\offroadhatchback\data\niva_hood.rvmat"
							}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							
							{
								"dz\vehicles\wheeled\offroadhatchback\data\niva_hood_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							
							{
								"dz\vehicles\wheeled\offroadhatchback\data\niva_hood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
	class HatchbackTrunk: CarDoor
	{
		scope=2;
		displayName="$STR_HatchbackTrunk0";
		descriptionShort="$STR_HatchbackTrunk1";
		model="\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Trunk.p3d";
		weight=15000;
		itemSize[]={12,10};
		inventorySlot="NivaTrunk";
		rotationFlags=1;
		physLayer="item_large";
		class DamageSystem: DamageSystem
		{
			class DamageZones: DamageZones
			{
				class Window: Window
				{
					class Health: Health
					{
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\data\auta_skla_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									""
								}
							}
						};
					};
				};
				class Doors: Doors
				{
					class Health: Health
					{
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_backdoor.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_backdoor_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_backdoor_destruct.rvmat"
								}
							}
						};
					};
				};
			};
		};
	};
	class OffroadHatchback: CarScript
	{
		scope=2;
		displayName="$STR_OffroadHatchback0";
		descriptionShort="$STR_OffroadHatchback1";
		model="\dz\vehicles\wheeled\OffroadHatchback\OffroadHatchback.p3d";
		InteractActions[]={1048,1035};
		attachments[]=
		{
			"CarBattery",
			"Reflector_1_1",
			"Reflector_2_1",
			"CarRadiator",
			"SparkPlug",
			"NivaHood",
			"NivaTrunk",
			"NivaDriverDoors",
			"NivaCoDriverDoors",
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
		};
		dashboardMatOn="dz\vehicles\wheeled\offroadhatchback\data\niva_dashboard_light.rvmat";
		dashboardMatOff="dz\vehicles\wheeled\offroadhatchback\data\niva_dashboard.rvmat";
		frontReflectorMatOn="dz\vehicles\wheeled\offroadhatchback\data\niva_lights.rvmat";
		frontReflectorMatOff="dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat";
		fuelCapacity=42;
		fuelConsumption=11;
		class Crew: Crew
		{
			class Driver: Driver
			{
			};
			class CoDriver: CoDriver
			{
			};
			class Cargo1
			{
				actionSel="seat_cargo1";
				proxyPos="crewCargo1";
				getInPos="pos_driver";
				getInDir="pos_driver_dir";
			};
			class Cargo2
			{
				actionSel="seat_cargo2";
				proxyPos="crewCargo2";
				getInPos="pos_coDriver";
				getInDir="pos_coDriver_dir";
			};
		};
		class SimulationModule: SimulationModule
		{
			drive="DRIVE_AWD";
			airDragCoefficient=0.995;
			class Steering
			{
				increaseSpeed[]={0,45,60,23,100,12};
				decreaseSpeed[]={0,80,60,40,90,20};
				centeringSpeed[]={0,0,15,25,60,40,100,60};
			};
			class Throttle
			{
				reactionTime=1;
				defaultThrust=0.85000002;
				gentleThrust=0.69999999;
				turboCoef=4;
				gentleCoef=0.75;
			};
			class Engine
			{
				inertia=0.15000001;
				torqueMax=114;
				torqueRpm=3400;
				powerMax=53.700001;
				powerRpm=5400;
				rpmIdle=850;
				rpmMin=900;
				rpmClutch=1350;
				rpmRedline=6000;
				rpmMax=8000;
			};
			class Gearbox
			{
				reverse=3.526;
				ratios[]={3.6670001,2.0999999,1.3609999,1};
				timeToUncoupleClutch=0.30000001;
				timeToCoupleClutch=0.44999999;
				maxClutchTorque=260;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxSteeringAngle=30;
					finalRatio=4.0999999;
					brakeBias=0.60000002;
					brakeForce=4000;
					wheelHubMass=5;
					wheelHubRadius=0.15000001;
					class Suspension
					{
						swayBar=1700;
						stiffness=42000;
						compression=2100;
						damping=7500;
						travelMaxUp=0.088200003;
						travelMaxDown=0.083300002;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_1";
							inventorySlot="NivaWheel_1_1";
						};
						class Right: Right
						{
							animDamper="damper_2_1";
							inventorySlot="NivaWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxSteeringAngle=0;
					finalRatio=4.0999999;
					brakeBias=0.40000001;
					brakeForce=3800;
					wheelHubMass=5;
					wheelHubRadius=0.15000001;
					class Suspension
					{
						swayBar=1800;
						stiffness=43000;
						compression=2300;
						damping=7900;
						travelMaxUp=0.1587;
						travelMaxDown=0.1059;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_2";
							inventorySlot="NivaWheel_1_2";
						};
						class Right: Right
						{
							animDamper="damper_2_2";
							inventorySlot="NivaWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,32};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
		class AnimationSources: AnimationSources
		{
			class SeatDriver
			{
				source="user";
				initPhase=0;
				animPeriod=0.80000001;
			};
			class SeatCoDriver
			{
				source="user";
				initPhase=0;
				animPeriod=0.80000001;
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
			class DamageZones
			{
				class Chassis
				{
					class Health
					{
						hitpoints=3000;
						transferToGlobalCoef=1;
					};
					componentNames[]=
					{
						"dmgZone_chassis"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Front
				{
					class Health
					{
						hitpoints=1500;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_destruct.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Fender_1_1",
						"Fender_2_1",
						"Engine",
						"Reflector_1_1",
						"Reflector_2_1",
						"WindowFront"
					};
					transferToZonesThreshold[]={0.5,0.80000001,0.80000001,0.5,1,1,0.1};
					transferToZonesCoefs[]={0.80000001,0.60000002,0.60000002,0.60000002,0.050000001,0.050000001,0.69999999};
					memoryPoints[]=
					{
						"dmgZone_front"
					};
					componentNames[]=
					{
						"dmgZone_front"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"NivaHood",
						"CarRadiator"
					};
				};
				class Back
				{
					class Health
					{
						hitpoints=1500;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_destruct.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Fender_1_2",
						"Fender_2_2",
						"WindowLR",
						"WindowRR"
					};
					transferToZonesCoefs[]={0.30000001,0.30000001,0.2,0.2};
					memoryPoints[]=
					{
						"dmgZone_back"
					};
					componentNames[]=
					{
						"dmgZone_back"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"NivaTrunk"
					};
				};
				class Roof
				{
					class Health
					{
						hitpoints=700;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_destruct.rvmat"
								}
							}
						};
					};
					memoryPoints[]=
					{
						"dmgZone_roof"
					};
					componentNames[]=
					{
						"dmgZone_roof"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Fender_1_1
				{
					class Health
					{
						hitpoints=1200;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_destruct.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Front",
						"Engine",
						"Reflector_1_1",
						"WindowFront"
					};
					transferToZonesThreshold[]={0.2,0.5,0.89999998,0.5};
					transferToZonesCoefs[]={0.30000001,0.60000002,0.60000002,0.40000001};
					memoryPoints[]=
					{
						"dmgZone_fender_1_1"
					};
					componentNames[]=
					{
						"dmgZone_fender_1_1"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"NivaHood",
						"NivaWheel_1_1",
						"NivaDriverDoors"
					};
				};
				class Fender_1_2: Fender_1_1
				{
					transferToZonesNames[]=
					{
						"Back",
						"FuelTank",
						"WindowLR"
					};
					transferToZonesThreshold[]={0.2,0.2,0.2};
					transferToZonesCoefs[]={0.30000001,0.2,0.69999999};
					memoryPoints[]=
					{
						"dmgZone_fender_1_2"
					};
					componentNames[]=
					{
						"dmgZone_fender_1_2"
					};
					inventorySlots[]=
					{
						"NivaTrunk",
						"NivaWheel_1_2"
					};
				};
				class Fender_2_1: Fender_1_1
				{
					transferToZonesNames[]=
					{
						"Front",
						"Engine",
						"Reflector_1_1",
						"WindowFront",
						"Battery"
					};
					transferToZonesThreshold[]={0.2,0.5,0.89999998,0.5,0.5};
					transferToZonesCoefs[]={0.30000001,0.60000002,0.60000002,0.40000001,0.69999999};
					memoryPoints[]=
					{
						"dmgZone_fender_2_1"
					};
					componentNames[]=
					{
						"dmgZone_fender_2_1"
					};
					inventorySlots[]=
					{
						"NivaHood",
						"NivaWheel_2_1",
						"NivaDriverDoors"
					};
				};
				class Fender_2_2: Fender_1_1
				{
					transferToZonesNames[]=
					{
						"Back",
						"FuelTank",
						"WindowRR"
					};
					transferToZonesThreshold[]={0.2,0.2,0.2};
					transferToZonesCoefs[]={0.30000001,0.2,0.69999999};
					memoryPoints[]=
					{
						"dmgZone_fender_2_2"
					};
					componentNames[]=
					{
						"dmgZone_fender_2_2"
					};
					inventorySlots[]=
					{
						"NivaTrunk",
						"NivaWheel_2_2"
					};
				};
				class WindowFront
				{
					class Health
					{
						hitpoints=50;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\data\glass_i_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								{}
							}
						};
					};
					memoryPoints[]=
					{
						"dmgZone_windowFront"
					};
					componentNames[]=
					{
						"dmgZone_windowFront"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class WindowLR
				{
					class Health
					{
						hitpoints=50;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\niva_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\data\auta_skla_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									""
								}
							}
						};
					};
					memoryPoints[]=
					{
						"dmgZone_windowLeft"
					};
					componentNames[]=
					{
						"dmgZone_windowLeft"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class WindowRR: WindowLR
				{
					memoryPoints[]=
					{
						"dmgZone_windowRight"
					};
					componentNames[]=
					{
						"dmgZone_windowRight"
					};
				};
				class Engine
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=1;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\engine_niva.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\engine_niva_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\engine_niva_destruct.rvmat"
								}
							}
						};
					};
					memoryPoints[]=
					{
						"dmgZone_engine"
					};
					componentNames[]=
					{
						"dmgZone_engine"
					};
					fatalInjuryCoef=0.001;
					inventorySlots[]=
					{
						"CarBattery",
						"SparkPlug",
						"EngineBelt",
						"CarRadiator"
					};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints=600;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								{}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								{}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								{}
							}
						};
					};
					componentNames[]=
					{
						"dmgZone_fuelTank"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class Reflector_1_1
				{
					class Health
					{
						hitpoints=50;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\headlights_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\offroadhatchback\data\glass_i_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\data\glass_i_destruct.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Front",
						"Fender_1_1",
						"Engine"
					};
					transferToZonesCoefs[]={1,1,1};
					memoryPoints[]=
					{
						"dmgZone_lights_1_1"
					};
					componentNames[]=
					{
						"dmgZone_lights_1_1"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"Reflector_1_1"
					};
				};
				class Reflector_2_1: Reflector_1_1
				{
					transferToZonesNames[]=
					{
						"Front",
						"Fender_2_1",
						"Engine"
					};
					transferToZonesCoefs[]={1,1,1};
					memoryPoints[]=
					{
						"dmgZone_lights_2_1"
					};
					componentNames[]=
					{
						"dmgZone_lights_2_1"
					};
					inventorySlots[]=
					{
						"Reflector_2_1"
					};
				};
			};
		};
		class ObstacleGenerator
		{
			carve=1;
			timeToStationary=5;
			moveThreshold=0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius=1;
						height=1.5;
						center[]={0,0,0.69999999};
					};
					class Cyl3
					{
						radius=1;
						height=1.5;
						center[]={0,0,-0.69999999};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name="$STR_attachment_Engine0";
				description="";
				attachmentSlots[]=
				{
					"CarBattery",
					"CarRadiator",
					"SparkPlug"
				};
				icon="missing";
			};
			class Body
			{
				name="$STR_attachment_Body0";
				description="";
				attachmentSlots[]=
				{
					"Reflector_1_1",
					"Reflector_2_1",
					"NivaHood",
					"NivaTrunk",
					"NivaDriverDoors",
					"NivaCoDriverDoors",
					"NivaWheel_Spare_1"
				};
				icon="missing";
			};
			class Chassis
			{
				name="$STR_attachment_Chassis0";
				description="";
				attachmentSlots[]=
				{
					"NivaWheel_1_1",
					"NivaWheel_1_2",
					"NivaWheel_2_1",
					"NivaWheel_2_2"
				};
				icon="missing";
			};
		};
	};
};
class CfgDestroy
{
	class EngineHit
	{
		sound[]={};
	};
};
class CfgNonAIVehicles
{
	class ProxyFlag;
	class ProxyDriver;
	class ProxyCargo;
	class ProxyAttachment;
	class ProxyFlag_Auto: ProxyFlag
	{
	};
	class ProxyFlag_Alone: ProxyFlag
	{
	};
	class ProxyV3S_Driver: ProxyDriver
	{
	};
	class ProxyV3S_CargoA: ProxyCargo
	{
	};
	class ProxyCivilianSedan_Driver: ProxyDriver
	{
	};
	class ProxyCivilianSedan_Cargo: ProxyCargo
	{
	};
	class ProxyBus_Driver: ProxyDriver
	{
	};
	class ProxyBus_Cargo: ProxyCargo
	{
	};
	class ProxyHatchback_Cargo: ProxyCargo
	{
	};
	class ProxyEnduro_Driver: ProxyDriver
	{
	};
	class ProxyEnduro_Cargo: ProxyCargo
	{
	};
	class ProxyVehiclePart: ProxyAttachment
	{
		scope=2;
		simulation="ProxyInventory";
		autocenter=0;
		animated=0;
		shadow=1;
		reversed=0;
	};
	class Proxyv3s_wheel: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\V3S\proxy\v3s_wheel.p3d";
		inventorySlot[]=
		{
			"V3SWheel_1_1",
			"V3SWheel_2_1",
			"V3SWheel_Spare_1",
			"V3SWheel_Spare_2"
		};
	};
	class Proxyv3s_wheel_new_burst: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_new_burst.p3d";
		inventorySlot[]=
		{
			"V3SWheel_1_1",
			"V3SWheel_2_1",
			"V3SWheel_Spare_1",
			"V3SWheel_Spare_2"
		};
	};
	class Proxyv3s_wheel_double: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_double.p3d";
		inventorySlot[]=
		{
			"V3SWheel_1_2",
			"V3SWheel_1_3",
			"V3SWheel_2_2",
			"V3SWheel_2_3"
		};
	};
	class Proxyv3s_wheel_burst_double: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\V3S\proxy\v3s_wheel_burst_double.p3d";
		inventorySlot[]=
		{
			"V3SWheel_1_2",
			"V3SWheel_1_3",
			"V3SWheel_2_2",
			"V3SWheel_2_3"
		};
	};
	class Proxyv3s_doors_Driver: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\V3S\proxy\v3s_doors_Driver.p3d";
		inventorySlot="V3SDriverDoors";
	};
	class Proxyv3s_doors_coDriver: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\V3S\proxy\v3s_doors_coDriver.p3d";
		inventorySlot="V3SCoDriverDoors";
	};
	class Proxyv3s_hood: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\V3S\proxy\v3s_hood.p3d";
		inventorySlot="V3Shood";
	};
	class ProxySedanWheel: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\civiliansedan\proxy\sedanWheel.p3d";
		inventorySlot[]=
		{
			"CivSedanWheel_1_1",
			"CivSedanWheel_1_2",
			"CivSedanWheel_2_1",
			"CivSedanWheel_2_2"
		};
	};
	class ProxySedanWheel_destroyed: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\civiliansedan\proxy\sedanWheel_destroyed.p3d";
		inventorySlot[]=
		{
			"CivSedanWheel_1_1",
			"CivSedanWheel_1_2",
			"CivSedanWheel_2_1",
			"CivSedanWheel_2_2"
		};
	};
	class ProxySedanHood: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianSedan\proxy\sedanhood.p3d";
		inventorySlot="CivSedanHood";
	};
	class ProxySedanTrunk: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianSedan\proxy\sedanTrunk.p3d";
		inventorySlot="CivSedanTrunk";
	};
	class ProxysedanDoors_Driver: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianSedan\proxy\sedanDoors_Driver.p3d";
		inventorySlot="CivSedanDriverDoors";
	};
	class ProxysedanDoors_coDriver: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianSedan\proxy\sedanDoors_coDriver.p3d";
		inventorySlot="CivSedanCoDriverDoors";
	};
	class ProxysedanDoors_cargo1: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianSedan\proxy\sedanDoors_cargo1.p3d";
		inventorySlot="CivSedanCargo1Doors";
	};
	class ProxysedanDoors_cargo2: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianSedan\proxy\sedanDoors_cargo2.p3d";
		inventorySlot="CivSedanCargo2Doors";
	};
	class ProxyNivaWheel: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel.p3d";
		inventorySlot[]=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
		};
	};
	class ProxyNivaWheel_destroyed: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel_destroyed.p3d";
		inventorySlot[]=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
		};
	};
	class ProxyNivaDoors_Hood: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Hood.p3d";
		inventorySlot="NivaHood";
	};
	class ProxyNivaDoors_Trunk: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Trunk.p3d";
		inventorySlot="NivaTrunk";
	};
	class ProxynivaDoors_Driver: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_Driver.p3d";
		inventorySlot="NivaDriverDoors";
	};
	class ProxynivaDoors_coDriver: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_coDriver.p3d";
		inventorySlot="NivaCoDriverDoors";
	};
	class ProxyIkarusWheel: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\TransitBus\proxy\IkarusWheel.p3d";
		inventorySlot[]=
		{
			"BusWheel_1_1",
			"BusWheel_2_1"
		};
	};
	class ProxyIkarusWheel_destroyed: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_destroyed.p3d";
		inventorySlot[]=
		{
			"BusWheel_1_1",
			"BusWheel_2_1"
		};
	};
	class ProxyIkarusWheel_rear: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_rear.p3d";
		inventorySlot[]=
		{
			"BusWheel_1_2",
			"BusWheel_2_2"
		};
	};
	class ProxyIkarusWheel_rear_destroyed: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_rear_destroyed.p3d";
		inventorySlot[]=
		{
			"BusWheel_1_2",
			"BusWheel_2_2"
		};
	};
	class ProxyikarusHood: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\TransitBus\proxy\ikarusHood.p3d";
		inventorySlot="BusHood";
	};
	class ProxyIkarusDoors_Left: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\TransitBus\proxy\IkarusDoors_Left.p3d";
		inventorySlot[]=
		{
			"BusLeftDoors_1",
			"BusLeftDoors_2",
			"BusLeftDoors_3"
		};
	};
	class ProxyIkarusDoors_Right: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\TransitBus\proxy\IkarusDoors_Right.p3d";
		inventorySlot[]=
		{
			"BusRightDoors_1",
			"BusRightDoors_2",
			"BusRightDoors_3"
		};
	};
	class ProxyCivilianVan_wheel: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVan_wheel.p3d";
		inventorySlot[]=
		{
			"CivVanWheel_1_1",
			"CivVanWheel_1_2",
			"CivVanWheel_2_1",
			"CivVanWheel_2_2"
		};
	};
	class ProxyCivilianVan_wheel_dam: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVan_wheel_dam.p3d";
		inventorySlot[]=
		{
			"CivVanWheel_1_1",
			"CivVanWheel_1_2",
			"CivVanWheel_2_1",
			"CivVanWheel_2_2"
		};
	};
	class ProxyCivilianVanDoors_Driver: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_Driver.p3d";
		inventorySlot="CivVanDriverDoors";
	};
	class ProxyCivilianVanDoors_CoDriver: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_CoDriver.p3d";
		inventorySlot="CivVanCoDriverDoors";
	};
	class ProxyCivilianVanDoors_Cargo1: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_Cargo1.p3d";
		inventorySlot="CivVanCargo1Doors";
	};
	class ProxyCivilianVanDoors_Cargo2: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_Cargo2.p3d";
		inventorySlot="CivVanTrunkDown";
	};
	class ProxyCivilianVanDoors_Cargo3: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\CivilianVan\proxy\CivilianVanDoors_Cargo3.p3d";
		inventorySlot="CivVanTrunkUp";
	};
};
