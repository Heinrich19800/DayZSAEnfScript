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
			class Steering
			{
				maxAngle=30;
				increaseSpeed[]={0,45};
				decreaseSpeed[]={0,45};
				centeringSpeed[]={0,90};
			};
			class Axles
			{
				class Front
				{
					isDrive=1;
					isSteering=1;
					forceRatio=0.5;
					finalRatio=4.0999999;
					brakeForce=75;
					steerType=0;
					wheelHubRadius=0.15000001;
					class Suspension
					{
						stiffness=30;
						compression=4;
						damping=1.1;
						restLength=0.2;
						compLength=0.36199999;
						travelMax=0.2;
						forceMax=4000;
					};
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
					finalRatio=4.0999999;
					forceRatio=0.5;
					brakeForce=50;
					wheelHubRadius=0.15000001;
					class Suspension
					{
						stiffness=28;
						compression=4;
						damping=1;
						restLength=0.2;
						compLength=0.36199999;
						travelMax=0.2;
						forceMax=3500;
					};
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
		friction=0.99000001;
		width=0.2;
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
		radius=0.465;
		friction=-1;
		width=0.2;
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
		displayName="V3S Chassis";
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
		fuelConsumption=20;
		airDragCoefficient=0.50999999;
		class SimulationModule: SimulationModule
		{
			class Steering: Steering
			{
				maxAngle=35;
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
				powerMax=63.700001;
				powerRpm=2200;
				torqueMax=144;
				torqueRpm=1900;
				rpmIdle=800;
				rpmMin=850;
				rpmRedline=2600;
				rpmMax=3200;
				rpmClutch=1200;
				inertia=1;
				frictionC0=15;
				frictionC1=3.5;
				frictionC2=0.85000002;
			};
			class Gearbox
			{
				reverse=6.2800002;
				ratios[]={6.1900001,3.1300001,1.75,1};
				timeToUncoupleClutch=0.40000001;
				timeToCoupleClutch=0.1;
				maxClutchTorque=144;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					forceRatio=0.2;
					finalRatio=2.1500001;
					brakeForce=90;
					wheelHubRadius=0.2;
					class Suspension: Suspension
					{
						stiffness=22;
						compression=2.2;
						damping=1.1;
						restLength=0.5;
						compLength=0.465;
						travelMax=0.30000001;
						forceMax=6500;
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
					finalRatio=2.1400001;
					isDrive=1;
					class Suspension: Suspension
					{
						stiffness=20;
						compression=2.8;
						damping=1.2;
						restLength=0.5;
						compLength=0.465;
						travelMax=0.40000001;
						forceMax=6500;
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
					finalRatio=3.9000001;
					isDrive=1;
					class Suspension: Suspension
					{
						stiffness=20;
						compression=2.8;
						damping=1.2;
						restLength=0.5;
						compLength=0.465;
						travelMax=0.40000001;
						forceMax=6500;
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
									"dz\vehicles\wheeled\v3s\data\v3s_cab.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\V3S\data\v3s_cab_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\V3S\data\v3s_cab_destruct.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Fender_1_1",
						"Fender_2_1",
						"Engine",
						"Lights"
					};
					transferToZonesCoefs[]={0.30000001,0.30000001,0.80000001,0.5};
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
					inventorySlots[]=
					{
						"NivaTrunk"
					};
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
									"dz\vehicles\wheeled\v3s\data\v3s_cabin_a.rvmat"
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
									"dz\vehicles\wheeled\v3s\data\v3s_cab.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"dz\vehicles\wheeled\V3S\data\v3s_cab_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"dz\vehicles\wheeled\V3S\data\v3s_cab_destruct.rvmat"
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
					inventorySlots[]=
					{
						"GlowPlug"
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
				class Lights
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
					componentNames[]=
					{
						"dmgZone_lights_1_1",
						"dmgZone_lights_2_1"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"LightBulb"
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
				name="Engine";
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
				name="Body";
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
				name="Chassis";
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
		displayName="V3S Chassis Blue";
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
		displayName="V3S Chassis Orange";
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
		displayName="V3S Chassis Grey";
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
		displayName="V3S Cargo";
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
		displayName="V3S Cargo Blue";
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
		displayName="V3S Cargo Orange";
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
		displayName="V3S Cargo Grey";
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
	class TransitBusWheel: CarWheel
	{
		scope=2;
		model="\DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel.p3d";
		displayName="$STR_TransitBusWheel0";
		itemSize[]={6,6};
		weight=25000;
		physLayer="item_large";
		rotationFlags=12;
		inventorySlot[]=
		{
			"BusWheel_1_1",
			"BusWheel_2_1"
		};
		simulation="carwheel";
		radiusByDamage[]={0,0.50999999,0.30000001,0.44999999,0.99980003,0.38,0.99989998,0.30000001};
		radius=0.50999999;
		friction=0.99900001;
		width=0.213;
	};
	class TransitBusWheel_Ruined: CarWheel
	{
		scope=2;
		model="\DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_destroyed.p3d";
		displayName="$STR_TransitBusWheel_Ruined0";
		itemSize[]={6,6};
		weight=25000;
		physLayer="item_large";
		rotationFlags=12;
		inventorySlot[]=
		{
			"BusWheel_1_1",
			"BusWheel_2_1"
		};
		simulation="carwheel";
		radius=0.30000001;
		friction=-1;
		width=0.213;
	};
	class TransitBusWheelDouble: TransitBusWheel
	{
		model="\DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_rear.p3d";
		displayName="$STR_TransitBusWheelDouble0";
		width=0.426;
		inventorySlot[]=
		{
			"BusWheel_1_2",
			"BusWheel_2_2"
		};
	};
	class TransitBusWheelDouble_Ruined: TransitBusWheel_Ruined
	{
		model="\DZ\vehicles\wheeled\TransitBus\proxy\ikarusWheel_rear_destroyed.p3d";
		displayName="$STR_TransitBusWheelDouble_Ruined0";
		width=0.426;
		inventorySlot[]=
		{
			"BusWheel_1_2",
			"BusWheel_2_2"
		};
	};
	class BusDoors_Left: Inventory_Base
	{
		scope=2;
		model="\DZ\vehicles\wheeled\TransitBus\proxy\IkarusDoors_Left.p3d";
		displayName="$STR_BusDoors_Left0";
		itemSize[]={8,12};
		weight=15000;
		physLayer="item_large";
		inventorySlot[]=
		{
			"BusLeftDoors_1",
			"BusLeftDoors_2",
			"BusLeftDoors_3"
		};
		rotationFlags=4;
	};
	class BusDoors_Right: BusDoors_Left
	{
		model="\DZ\vehicles\wheeled\TransitBus\proxy\IkarusDoors_Right.p3d";
		displayName="$STR_BusDoors_Right0";
		rotationFlags=8;
		inventorySlot[]=
		{
			"BusRightDoors_1",
			"BusRightDoors_2",
			"BusRightDoors_3"
		};
	};
	class BusHood: Inventory_Base
	{
		scope=2;
		model="\DZ\vehicles\wheeled\TransitBus\proxy\ikarusHood.p3d";
		displayName="$STR_BusHood0";
		itemSize[]={8,8};
		weight=15000;
		physLayer="item_large";
		inventorySlot="BusHood";
		rotationFlags=8;
	};
	class TransitBus: CarScript
	{
		scope=2;
		displayName="$STR_TransitBus0";
		model="\dz\vehicles\wheeled\TransitBus\TransitBus.p3d";
		dashboardMatOn="dz\vehicles\wheeled\transitbus\data\ikarus_dashboarde.rvmat";
		dashboardMatOff="dz\vehicles\wheeled\transitbus\data\ikarus_dashboard.rvmat";
		frontReflectorMatOn="dz\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat";
		frontReflectorMatOff="dz\vehicles\wheeled\transitbus\data\ikarus_ext_details_cr.rvmat";
		frontReflectorMatDamaged="dz\vehicles\wheeled\transitbus\data\ikarus_ext_details_damage.rvmat";
		frontReflectorMatRuined="dz\vehicles\wheeled\transitbus\data\ikarus_ext_details_destruct.rvmat";
		fuelCapacity=180;
		fuelConsumption=25;
		attachments[]=
		{
			"TruckBattery",
			"TruckRadiator",
			"LightBulb",
			"EngineBelt",
			"GlowPlug",
			"BusLeftDoors_1",
			"BusLeftDoors_2",
			"BusLeftDoors_3",
			"BusRightDoors_1",
			"BusRightDoors_2",
			"BusRightDoors_3",
			"BusHood",
			"BusWheel_1_1",
			"BusWheel_1_2",
			"BusWheel_2_1",
			"BusWheel_2_2"
		};
		class SimulationModule: SimulationModule
		{
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
				torqueMax=114;
				torqueRpm=1700;
				rpmMin=800;
				rpmMax=2500;
			};
			class Gearbox
			{
				reverse=-39.439999;
				ratios[]={38.869999,19.66,10.99,6.2800002};
				timeToUncoupleClutch=0.5;
				timeToCoupleClutch=0.40000001;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					finalRatio=1;
					brakeForce=60;
					class Steering: Steering
					{
						maxAngle=55;
						increaseSpeed[]={0,45,50,5};
						decreaseSpeed[]={0,70};
						centeringSpeed[]={0.5,0,5,20,25,70};
					};
					class Suspension: Suspension
					{
						stiffness=39;
						compression=1.5;
						damping=0.94999999;
						restLength=0.16;
						compLength=0.50999999;
						travelMax=0.1;
						forceMax=6000;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="BusWheel_1_1";
						};
						class Right: Right
						{
							inventorySlot="BusWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					brakeForce=140;
					class Suspension: Suspension
					{
						stiffness=39;
						compression=1.5;
						damping=0.94999999;
						restLength=0.16;
						compLength=0.50999999;
						travelMax=0.1;
						forceMax=6000;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="BusWheel_1_2";
						};
						class Right: Right
						{
							inventorySlot="BusWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={7,15};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
		class AnimationSources: AnimationSources
		{
			class DoorsHood: DoorsDriver
			{
				animPeriod=0.80000001;
				initPhase=1;
			};
			class Doors_Front: DoorsDriver
			{
				animPeriod=0.80000001;
			};
			class Doors_Middle: Doors_Front
			{
			};
			class Doors_Rear: Doors_Front
			{
			};
		};
		class Sounds
		{
			soundSetsInt[]=
			{
				"v3s_Engine_Offload_Int_Rpm1_SoundSet",
				"v3s_Engine_Offload_Int_Rpm2_SoundSet",
				"v3s_Engine_Int_Open_Rpm0_SoundSet",
				"v3s_Engine_Int_Open_Rpm1_SoundSet",
				"v3s_Engine_Int_Open_Rpm2_SoundSet",
				"v3s_Tires_Asphalt_Slow_General_Int_SoundSet",
				"v3s_Tires_Asphalt_Fast_General_Int_SoundSet",
				"v3s_Tires_rock_slow_Int_SoundSet",
				"v3s_Tires_rock_fast_Int_SoundSet",
				"v3s_Tires_grass_slow_Int_SoundSet",
				"v3s_Tires_grass_fast_Int_SoundSet",
				"v3s_Tires_gravel_slow_Int_SoundSet",
				"v3s_Tires_gravel_fast_Int_SoundSet",
				"v3s_Tires_asphalt_slow_Int_SoundSet",
				"v3s_Tires_asphalt_fast_Int_SoundSet",
				"v3s_Tires_water_slow_Int_SoundSet",
				"v3s_Tires_water_fast_Int_SoundSet",
				"offroad_skid_dirt_SoundSet",
				"offroad_dirt_turn_SoundSet",
				"v3s_Wind_SoundSet",
				"v3s_Rain_Int_SoundSet",
				"v3s_Rain_Int_Open_SoundSet"
			};
			soundSetsExt[]=
			{
				"v3s_Engine_Offload_Ext_Rpm1_SoundSet",
				"v3s_Engine_Offload_Ext_Rpm2_SoundSet",
				"v3s_Engine_Ext_Rpm0_SoundSet",
				"v3s_Engine_Ext_Rpm1_SoundSet",
				"v3s_Engine_Ext_Rpm2_SoundSet",
				"v3s_Tires_rock_slow_Ext_SoundSet",
				"v3s_Tires_rock_fast_Ext_SoundSet",
				"v3s_Tires_grass_slow_Ext_SoundSet",
				"v3s_Tires_grass_fast_Ext_SoundSet",
				"v3s_Tires_gravel_slow_Ext_SoundSet",
				"v3s_Tires_gravel_fast_Ext_SoundSet",
				"v3s_Tires_asphalt_slow_Ext_SoundSet",
				"v3s_Tires_asphalt_fast_Ext_SoundSet",
				"v3s_Tires_water_slow_Ext_SoundSet",
				"v3s_Tires_water_fast_Ext_SoundSet",
				"offroad_skid_dirt_SoundSet",
				"offroad_dirt_turn_SoundSet",
				"v3s_Rain_Ext_SoundSet"
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
						radius=1.2;
						height=1.5;
						center[]={0,0,1.7};
					};
					class Cyl2
					{
						radius=1.2;
						height=1.5;
						center[]={0,0,0};
					};
					class Cyl3
					{
						radius=1.2;
						height=1.5;
						center[]={0,0,-1.7};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name="Engine";
				description="";
				attachmentSlots[]=
				{
					"TruckBattery",
					"TruckRadiator",
					"EngineBelt",
					"GlowPlug"
				};
				icon="missing";
			};
			class Body
			{
				name="Body";
				description="";
				attachmentSlots[]=
				{
					"LightBulb",
					"BusLeftDoors_1",
					"BusLeftDoors_2",
					"BusLeftDoors_3",
					"BusRightDoors_1",
					"BusRightDoors_2",
					"BusRightDoors_3",
					"BusHood"
				};
				icon="missing";
			};
			class Chassis
			{
				name="Chassis";
				description="";
				attachmentSlots[]=
				{
					"BusWheel_1_1",
					"BusWheel_1_2",
					"BusWheel_2_1",
					"BusWheel_2_2"
				};
				icon="missing";
			};
		};
	};
	class CivSedanWheel: CarWheel
	{
		scope=2;
		displayName="$STR_CivSedanWheel0";
		model="\DZ\vehicles\wheeled\civiliansedan\proxy\sedanwheel.p3d";
		weight=12000;
		itemSize[]={6,6};
		inventorySlot[]=
		{
			"CivSedanWheel_1_1",
			"CivSedanWheel_1_2",
			"CivSedanWheel_2_1",
			"CivSedanWheel_2_2"
		};
		rotationFlags=4;
		physLayer="item_large";
		radiusByDamage[]={0,0.34,0.30000001,0.30000001,0.99980003,0.25,0.99989998,0.2};
		radius=0.34;
		friction=0.95999998;
		width=0.16;
	};
	class CivSedanWheel_Ruined: CarWheel
	{
		scope=2;
		displayName="$STR_CivSedanWheel_Ruined0";
		model="\DZ\vehicles\wheeled\civiliansedan\proxy\sedanwheel_destroyed.p3d";
		weight=12000;
		itemSize[]={6,6};
		inventorySlot[]=
		{
			"CivSedanWheel_1_1",
			"CivSedanWheel_1_2",
			"CivSedanWheel_2_1",
			"CivSedanWheel_2_2"
		};
		rotationFlags=4;
		physLayer="item_large";
		radius=0.15000001;
		friction=-1;
		width=0.2;
	};
	class CivSedanDoors_Driver: CarDoor
	{
		scope=2;
		displayName="$STR_CivSedanDoors_Driver0";
		model="\DZ\vehicles\wheeled\civilianSedan\proxy\sedanDoors_Driver.p3d";
		weight=15000;
		itemSize[]={10,8};
		inventorySlot="CivSedanDriverDoors";
		rotationFlags=8;
		physLayer="item_large";
	};
	class CivSedanDoors_CoDriver: CivSedanDoors_Driver
	{
		displayName="$STR_CivSedanDoors_CoDriver0";
		model="\DZ\vehicles\wheeled\civilianSedan\proxy\sedanDoors_coDriver.p3d";
		inventorySlot="CivSedanCoDriverDoors";
		rotationFlags=4;
	};
	class CivSedanDoors_BackLeft: CivSedanDoors_Driver
	{
		displayName="$STR_CivSedanDoors_BackLeft0";
		model="\DZ\vehicles\wheeled\civilianSedan\proxy\sedanDoors_cargo1.p3d";
		inventorySlot="CivSedanCargo1Doors";
	};
	class CivSedanDoors_BackRight: CivSedanDoors_Driver
	{
		displayName="$STR_CivSedanDoors_BackRight0";
		model="\DZ\vehicles\wheeled\civilianSedan\proxy\sedanDoors_cargo2.p3d";
		inventorySlot="CivSedanCargo2Doors";
		rotationFlags=4;
	};
	class CivSedanHood: CarDoor
	{
		scope=2;
		displayName="$STR_CivSedanHood0";
		model="\DZ\vehicles\wheeled\civilianSedan\proxy\sedanhood.p3d";
		weight=15000;
		itemSize[]={12,10};
		inventorySlot="CivSedanHood";
		rotationFlags=4;
		physLayer="item_large";
		class Damage
		{
			tex[]={};
			mat[]=
			{
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan.rvmat",
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan_damage.rvmat",
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan_destruct.rvmat"
			};
		};
	};
	class CivSedanTrunk: CarDoor
	{
		scope=2;
		displayName="$STR_CivSedanTrunk0";
		model="\DZ\vehicles\wheeled\civilianSedan\proxy\sedanTrunk.p3d";
		weight=15000;
		itemSize[]={12,10};
		inventorySlot="CivSedanTrunk";
		rotationFlags=4;
		physLayer="item_large";
		class Damage
		{
			tex[]={};
			mat[]=
			{
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan.rvmat",
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan_damage.rvmat",
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan_destruct.rvmat"
			};
		};
	};
	class CivilianSedan: CarScript
	{
		scope=2;
		displayName="$STR_CivilianSedan0";
		model="\DZ\vehicles\wheeled\civiliansedan\CivilianSedan.p3d";
		attachments[]=
		{
			"CarBattery",
			"CarRadiator",
			"LightBulb",
			"EngineBelt",
			"SparkPlug",
			"CivSedanHood",
			"CivSedanTrunk",
			"CivSedanDriverDoors",
			"CivSedanCoDriverDoors",
			"CivSedanCargo1Doors",
			"CivSedanCargo2Doors",
			"CivSedanWheel_1_1",
			"CivSedanWheel_1_2",
			"CivSedanWheel_2_1",
			"CivSedanWheel_2_2"
		};
		dashboardMatOn="dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int2e_.rvmat";
		dashboardMatOff="dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int2e_off.rvmat";
		frontReflectorMatOn="dz\vehicles\wheeled\civiliansedan\data\civiliansedan_lights.rvmat";
		frontReflectorMatOff="dz\vehicles\wheeled\civiliansedan\data\civiliansedan_cr.rvmat";
		frontReflectorMatDamaged="dz\vehicles\wheeled\civiliansedan\data\civiliansedan_damage.rvmat";
		frontReflectorMatRuined="dz\vehicles\wheeled\civiliansedan\data\civiliansedan_destruct.rvmat";
		fuelCapacity=55;
		fuelConsumption=15;
		airDragCoefficient=0.75;
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
				getInPos="pos_cargo1";
				getInDir="pos_cargo1_dir";
			};
			class Cargo2
			{
				actionSel="seat_cargo2";
				proxyPos="crewCargo2";
				getInPos="pos_cargo2";
				getInDir="pos_cargo2_dir";
			};
		};
		class SimulationModule: SimulationModule
		{
			class Steering: Steering
			{
				increaseSpeed[]={0,45,30,30,60,20,120,5};
				decreaseSpeed[]={0,45,60,20,120,8};
				centeringSpeed[]={0,90,60,60,100,30};
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
				powerMax=100;
				powerRpm=4500;
				torqueMax=82;
				torqueRpm=2500;
				rpmIdle=900;
				rpmMin=1000;
				rpmRedline=5000;
				rpmMax=6000;
				rpmClutch=1200;
				inertia=0.5;
				frictionC0=15;
				frictionC1=3.5;
				frictionC2=0.85000002;
			};
			class Gearbox
			{
				reverse=3.54;
				ratios[]={3.5,2.26,1.45,1};
				timeToUncoupleClutch=0.2;
				timeToCoupleClutch=0.1;
				maxClutchTorque=75;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					forceRatio=0.050000001;
					finalRatio=1;
					brakeForce=90;
					class Suspension: Suspension
					{
						stiffness=28;
						compression=2.2;
						damping=0.89999998;
						restLength=0.34999999;
						compLength=0.36199999;
						travelMax=0.15000001;
						forceMax=3000;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="CivSedanWheel_1_1";
						};
						class Right: Right
						{
							inventorySlot="CivSedanWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					forceRatio=0.94999999;
					brakeForce=50;
					finalRatio=4.0999999;
					isDrive=1;
					class Suspension: Suspension
					{
						stiffness=28;
						compression=2.2;
						damping=0.89999998;
						restLength=0.34999999;
						compLength=0.36199999;
						travelMax=0.15000001;
						forceMax=3000;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="CivSedanWheel_1_2";
						};
						class Right: Right
						{
							inventorySlot="CivSedanWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={7,12};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
		class AnimationSources: AnimationSources
		{
			class DoorsCargo1
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
			class DoorsCargo2
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
		};
		class Damage
		{
			tex[]={};
			mat[]=
			{
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_damage.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_destruct.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\gaz_wheel.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\gaz_wheel_damage.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\gaz_wheel_destruct.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int1.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int1_damage.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int1_destruct.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int2.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int2_damage.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\civiliansedan_int2_destruct.rvmat",
				"dz\vehicles\wheeled\civiliansedan\data\glass.rvmat",
				"dz\vehicles\wheeled\data\auta_skla_damage.rvmat",
				"dz\vehicles\wheeled\data\auta_skla_damage.rvmat"
			};
		};
		class Sounds
		{
			thrust=0.60000002;
			thrustTurbo=1;
			thrustGentle=0.30000001;
			thrustSmoothCoef=0.1;
			camposSmoothCoef=0.029999999;
			soundSetsFilter[]=
			{
				"offroad_Engine_Offload_Ext_Rpm1_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm2_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm3_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm4_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm5_SoundSet",
				"offroad_Engine_Ext_Rpm0_SoundSet",
				"offroad_Engine_Ext_Rpm1_SoundSet",
				"offroad_Engine_Ext_Rpm2_SoundSet",
				"offroad_Engine_Ext_Rpm3_SoundSet",
				"offroad_Engine_Ext_Rpm4_SoundSet",
				"offroad_Engine_Ext_Rpm5_SoundSet",
				"offroad_Tires_rock_slow_Ext_SoundSet",
				"offroad_Tires_rock_fast_Ext_SoundSet",
				"offroad_Tires_grass_slow_Ext_SoundSet",
				"offroad_Tires_grass_fast_Ext_SoundSet",
				"offroad_Tires_gravel_slow_Ext_SoundSet",
				"offroad_Tires_gravel_fast_Ext_SoundSet",
				"offroad_Tires_asphalt_slow_Ext_SoundSet",
				"offroad_Tires_asphalt_fast_Ext_SoundSet",
				"offroad_Tires_water_slow_Ext_SoundSet",
				"offroad_Tires_water_fast_Ext_SoundSet",
				"Offroad_skid_dirt_SoundSet",
				"offroad_dirt_turn_SoundSet",
				"offroad_Rain_Ext_SoundSet"
			};
			soundSetsInt[]=
			{
				"Offroad_Tires_Asphalt_Slow_General_Int_SoundSet",
				"Offroad_Tires_Asphalt_Fast_General_Int_SoundSet",
				"Offroad_Wind_SoundSet"
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
						center[]={0,0,0.80000001};
					};
					class Cyl3
					{
						radius=1;
						height=1.5;
						center[]={0,0,-0.80000001};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name="Engine";
				description="";
				attachmentSlots[]=
				{
					"CarBattery",
					"EngineBelt",
					"CarRadiator",
					"SparkPlug"
				};
				icon="missing";
			};
			class Body
			{
				name="Body";
				description="";
				attachmentSlots[]=
				{
					"CarRadiator",
					"LightBulb",
					"CivSedanHood",
					"CivSedanTrunk",
					"CivSedanDriverDoors",
					"CivSedanCoDriverDoors",
					"CivSedanCargo1Doors",
					"CivSedanCargo2Doors"
				};
				icon="missing";
			};
			class Chassis
			{
				name="Chassis";
				description="";
				attachmentSlots[]=
				{
					"CivSedanWheel_1_1",
					"CivSedanWheel_1_2",
					"CivSedanWheel_2_1",
					"CivSedanWheel_2_2",
					"CivSedanWheel_Spare_1"
				};
				icon="missing";
			};
		};
	};
	class CivVanWheel: CarWheel
	{
		scope=2;
		model="\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVan_wheel.p3d";
		displayName="$STR_CivVanWheel0";
		descriptionShort="$STR_CivVanWheel1";
		itemSize[]={6,6};
		weight=12000;
		physLayer="item_large";
		rotationFlags=4;
		inventorySlot[]=
		{
			"CivVanWheel_1_1",
			"CivVanWheel_1_2",
			"CivVanWheel_2_1",
			"CivVanWheel_2_2"
		};
		SingleUseActions[]={548};
		simulation="carwheel";
		radiusByDamage[]={0,0.34,0.30000001,0.30000001,0.99980003,0.25,0.99989998,0.2};
		radius=0.34;
		friction=0.95999998;
		width=0.16;
	};
	class CivVanWheel_Ruined: CarWheel
	{
		scope=2;
		model="\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVan_wheel_dam.p3d";
		displayName="$STR_CivVanWheel_Ruined0";
		descriptionShort="$STR_CivVanWheel_Ruined1";
		itemSize[]={6,6};
		weight=12000;
		physLayer="item_large";
		rotationFlags=4;
		inventorySlot[]=
		{
			"CivVanWheel_1_1",
			"CivVanWheel_1_2",
			"CivVanWheel_2_1",
			"CivVanWheel_2_2"
		};
		simulation="carwheel";
		radius=0.15000001;
		friction=-1;
		width=0.2;
	};
	class CivVanDoors_Driver: Inventory_Base
	{
		scope=2;
		model="\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Driver.p3d";
		displayName="$STR_CivVanDoors_Driver0";
		descriptionShort="$STR_CivVanDoors_Driver1";
		itemSize[]={10,8};
		weight=15000;
		physLayer="item_large";
		inventorySlot="CivVanDriverDoors";
		rotationFlags=2;
	};
	class CivVanDoors_CoDriver: CivVanDoors_Driver
	{
		model="\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_CoDriver.p3d";
		displayName="$STR_CivVanDoors_CoDriver0";
		inventorySlot="CivVanCoDriverDoors";
		rotationFlags=2;
	};
	class CivVanDoors_BackRight: CivVanDoors_Driver
	{
		model="\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Cargo1.p3d";
		displayName="$STR_CivVanDoors_BackRight0";
		inventorySlot="CivVanCargo1Doors";
	};
	class CivVanDoors_TrunkDown: CivVanDoors_Driver
	{
		model="\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Cargo2.p3d";
		displayName="$STR_CivVanDoors_TrunkDown0";
		inventorySlot="CivVanTrunkDown";
		rotationFlags=2;
	};
	class CivVanDoors_TrunkUp: CivVanDoors_Driver
	{
		model="\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Cargo3.p3d";
		displayName="$STR_CivVanDoors_TrunkUp0";
		inventorySlot="CivVanTrunkUp";
		rotationFlags=2;
	};
	class CivVanTrunk: Inventory_Base
	{
		scope=2;
		model="\DZ\vehicles\wheeled\civilianVan\proxy\CivilianVanDoors_Cargo3.p3d";
		displayName="$STR_CivVanTrunk0";
		descriptionShort="$STR_CivVanTrunk1";
		itemSize[]={12,10};
		weight=15000;
		physLayer="item_large";
		inventorySlot="CivVanTrunk";
		rotationFlags=4;
		class Damage
		{
			tex[]={};
			mat[]=
			{
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan.rvmat",
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan_damage.rvmat",
				"DZ\vehicles\wheeled\civiliansedan\data\civiliansedan_destruct.rvmat"
			};
		};
	};
	class CivilianVan: CarScript
	{
		scope=2;
		displayName="$STR_CivilianVan0";
		model="\dz\vehicles\wheeled\CivilianVan\CivilianVan.p3d";
		InteractActions[]={1035,1046,1043};
		dashboardMatOn="dz\vehicles\wheeled\CivilianVan\data\niva_dashboard_light.rvmat";
		dashboardMatOff="dz\vehicles\wheeled\CivilianVan\data\niva_dashboard.rvmat";
		frontReflectorMatOn="dz\vehicles\wheeled\CivilianVan\data\niva_lights.rvmat";
		frontReflectorMatOff="dz\vehicles\wheeled\CivilianVan\data\niva.rvmat";
		frontReflectorMatDamaged="dz\vehicles\wheeled\CivilianVan\data\niva_damage.rvmat";
		frontReflectorMatRuined="dz\vehicles\wheeled\CivilianVan\data\niva_destruct.rvmat";
		fuelCapacity=42;
		fuelConsumption=11;
		attachments[]=
		{
			"CarBattery",
			"LightBulb",
			"CarRadiator",
			"EngineBelt",
			"SparkPlug",
			"CivVanDriverDoors",
			"CivVanCoDriverDoors",
			"CivVanCargo1Doors",
			"CivVanTrunkDown",
			"CivVanTrunkUp",
			"CivVanWheel_1_1",
			"CivVanWheel_1_2",
			"CivVanWheel_2_1",
			"CivVanWheel_2_2"
		};
		class SimulationModule: SimulationModule
		{
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
				torqueMax=114;
				torqueRpm=3400;
				rpmMin=900;
				rpmMax=5400;
			};
			class Gearbox
			{
				reverse=3.526;
				ratios[]={3.6670001,2.0999999,1.3609999,1};
				timeToUncoupleClutch=0.40000001;
				timeToCoupleClutch=0.30000001;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					forceRatio=0.5;
					finalRatio=4.0999999;
					brakeForce=75;
					wheelHubRadius=0.12;
					class Steering: Steering
					{
						increaseSpeed[]={0,45,60,25,100,15};
						decreaseSpeed[]={0,45,60,25,100,15};
						centeringSpeed[]={0,90,60,50,90,30};
					};
					class Suspension: Suspension
					{
						restLength=0.25;
						compLength=0.34;
						travelMax=0.30000001;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="CivVanwheel_1_1";
						};
						class Right: Right
						{
							inventorySlot="CivVanwheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					class Suspension: Suspension
					{
						restLength=0.25;
						compLength=0.34;
						travelMax=0.30000001;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="CivVanWheel_1_2";
						};
						class Right: Right
						{
							inventorySlot="CivVanWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={7,10};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
			class DamageZones
			{
				class Front
				{
					class Health
					{
						hitpoints=100;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"dmgZone_front"
					};
					fatalInjuryCoef=1;
					inventorySlots[]={};
				};
				class Back
				{
					class Health
					{
						hitpoints=100;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"dmgZone_back"
					};
					fatalInjuryCoef=1;
					inventorySlots[]={};
				};
				class Roof
				{
					class Health
					{
						hitpoints=500;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"dmgZone_roof"
					};
					fatalInjuryCoef=1;
					inventorySlots[]={};
				};
				class Fender_LF
				{
					class Health
					{
						hitpoints=500;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"dmgZone_fenderLF"
					};
					fatalInjuryCoef=1;
					inventorySlots[]={};
				};
				class Fender_LR: Fender_LF
				{
					componentNames[]=
					{
						"dmgZone_fenderLR"
					};
				};
				class Fender_RF: Fender_LF
				{
					componentNames[]=
					{
						"dmgZone_fenderRF"
					};
				};
				class Fender_RR: Fender_LF
				{
					componentNames[]=
					{
						"dmgZone_fenderRR"
					};
				};
				class Engine
				{
					class Health
					{
						hitpoints=400;
						transferToGlobalCoef=1;
					};
					componentNames[]=
					{
						"dmgZone_engine"
					};
					fatalInjuryCoef=1;
					inventorySlots[]=
					{
						"hull"
					};
				};
				class Chassis
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=-1;
					};
					componentNames[]=
					{
						"dmgZone_chassis"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]={};
				};
				class FuelTank
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=-1;
					};
					componentNames[]=
					{
						"dmgZone_fuelTank"
					};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"hull"
					};
				};
			};
		};
		class Sounds
		{
			thrust=0.60000002;
			thrustTurbo=1;
			thrustGentle=0.30000001;
			thrustSmoothCoef=0.1;
			camposSmoothCoef=0.029999999;
			soundSetsFilter[]=
			{
				"offroad_Engine_Offload_Ext_Rpm1_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm2_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm3_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm4_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm5_SoundSet",
				"offroad_Engine_Ext_Rpm0_SoundSet",
				"offroad_Engine_Ext_Rpm1_SoundSet",
				"offroad_Engine_Ext_Rpm2_SoundSet",
				"offroad_Engine_Ext_Rpm3_SoundSet",
				"offroad_Engine_Ext_Rpm4_SoundSet",
				"offroad_Engine_Ext_Rpm5_SoundSet",
				"offroad_Tires_rock_slow_Ext_SoundSet",
				"offroad_Tires_rock_fast_Ext_SoundSet",
				"offroad_Tires_grass_slow_Ext_SoundSet",
				"offroad_Tires_grass_fast_Ext_SoundSet",
				"offroad_Tires_gravel_slow_Ext_SoundSet",
				"offroad_Tires_gravel_fast_Ext_SoundSet",
				"offroad_Tires_asphalt_slow_Ext_SoundSet",
				"offroad_Tires_asphalt_fast_Ext_SoundSet",
				"offroad_Tires_water_slow_Ext_SoundSet",
				"offroad_Tires_water_fast_Ext_SoundSet",
				"Offroad_skid_dirt_SoundSet",
				"offroad_dirt_turn_SoundSet",
				"offroad_Rain_Ext_SoundSet"
			};
			soundSetsInt[]=
			{
				"Offroad_Tires_Asphalt_Slow_General_Int_SoundSet",
				"Offroad_Tires_Asphalt_Fast_General_Int_SoundSet",
				"Offroad_Wind_SoundSet"
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
				name="Engine";
				description="";
				attachmentSlots[]=
				{
					"CarBattery",
					"EngineBelt",
					"CarRadiator",
					"SparkPlug"
				};
				icon="missing";
			};
			class Body
			{
				name="Body";
				description="";
				attachmentSlots[]=
				{
					"CarRadiator",
					"LightBulb",
					"CivVanDriverDoors",
					"CivVanCoDriverDoors",
					"CivVanCargo1Doors",
					"CivVanTrunkDown",
					"CivVanTrunkUp"
				};
				icon="missing";
			};
			class Chassis
			{
				name="Chassis";
				description="";
				attachmentSlots[]=
				{
					"CivVanWheel_1_1",
					"CivVanWheel_1_2",
					"CivVanWheel_2_1",
					"CivVanWheel_2_2"
				};
				icon="missing";
			};
		};
	};
	class HatchbackWheel: CarWheel
	{
		scope=2;
		displayName="$STR_HatchbackWheel0";
		model="\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel.p3d";
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
		radiusByDamage[]={0,0.36199999,0.30000001,0.30000001,0.99980003,0.25,0.99989998,0.15000001};
		radius=0.36199999;
		friction=0.98000002;
		width=0.18000001;
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
		displayName="$STR_HatchbackWheel_Ruined0";
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
		radius=0.15000001;
		friction=-1;
		width=0.17;
	};
	class HatchbackDoors_Driver: CarDoor
	{
		scope=2;
		displayName="$STR_HatchbackDoors_Driver0";
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
		model="\DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaDoors_coDriver.p3d";
		inventorySlot="NivaCoDriverDoors";
		rotationFlags=4;
	};
	class HatchbackHood: CarDoor
	{
		scope=2;
		displayName="$STR_HatchbackHood0";
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
		airDragCoefficient=0.70999998;
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
			class Steering: Steering
			{
				increaseSpeed[]={0,40,60,20,100,10};
				decreaseSpeed[]={0,80,60,40,90,20};
				centeringSpeed[]={0,40,60,20,100,10};
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
				powerMax=53.700001;
				powerRpm=5400;
				torqueMax=114;
				torqueRpm=3400;
				rpmIdle=850;
				rpmMin=900;
				rpmRedline=6000;
				rpmMax=8000;
				rpmClutch=1500;
				inertia=0.44999999;
				frictionC0=15;
				frictionC1=3.5;
				frictionC2=0.85000002;
			};
			class Gearbox
			{
				reverse=3.526;
				ratios[]={3.6670001,2.0999999,1.3609999,1};
				timeToUncoupleClutch=0.2;
				timeToCoupleClutch=0.30000001;
				maxClutchTorque=75;
			};
			class Axles: Axles
			{
				class Front: Front
				{
					brakeForce=50;
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="NivaWheel_1_1";
						};
						class Right: Right
						{
							inventorySlot="NivaWheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					isDrive=1;
					brakeForce=40;
					class Wheels: Wheels
					{
						class Left: Left
						{
							inventorySlot="NivaWheel_1_2";
						};
						class Right: Right
						{
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
						"Radiator",
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
						"NivaHood"
					};
				};
				class Radiator
				{
					class Health
					{
						hitpoints=100000;
						transferToGlobalCoef=0;
					};
					memoryPoints[]={};
					componentNames[]={};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"CarRadiator"
					};
				};
				class DoorsDriver
				{
					class Health
					{
						hitpoints=100;
						transferToGlobalCoef=0;
					};
					memoryPoints[]=
					{
						"dmgZone_doorsDriver"
					};
					componentNames[]={};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"NivaDriver"
					};
				};
				class DoorsCoDriver
				{
					class Health
					{
						hitpoints=100;
						transferToGlobalCoef=0;
					};
					memoryPoints[]=
					{
						"dmgZone_doorsCoDriver"
					};
					componentNames[]={};
					fatalInjuryCoef=-1;
					inventorySlots[]=
					{
						"NivaDriver"
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
						"CarRadiator",
						"WindowFront"
					};
					transferToZonesThreshold[]={0.2,0.89999998,0.89999998,0.2,0.5};
					transferToZonesCoefs[]={0.30000001,0.30000001,0.60000002,0.5,0.40000001};
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
						"NivaWheel_1_1"
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
						"NivaHood",
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
						"CarRadiator",
						"WindowFront",
						"Battery"
					};
					transferToZonesThreshold[]={0.2,0.89999998,0.89999998,0.2,0.5,0.5};
					transferToZonesCoefs[]={0.30000001,0.30000001,0.60000002,0.5,0.40000001,0.69999999};
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
						"NivaWheel_2_1"
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
				name="Engine";
				description="";
				attachmentSlots[]=
				{
					"Reflector_1_1",
					"Reflector_2_1",
					"CarBattery",
					"CarRadiator",
					"SparkPlug"
				};
				icon="missing";
			};
			class Body
			{
				name="Body";
				description="";
				attachmentSlots[]=
				{
					"NivaHood",
					"NivaTrunk",
					"NivaDriverDoors",
					"NivaCoDriverDoors"
				};
				icon="missing";
			};
			class Chassis
			{
				name="Chassis";
				description="";
				attachmentSlots[]=
				{
					"NivaWheel_1_1",
					"NivaWheel_1_2",
					"NivaWheel_2_1",
					"NivaWheel_2_2",
					"NivaWheel_Spare_1"
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
