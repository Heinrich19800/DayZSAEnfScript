class OffroadHatchback extends CarScript
{

	override int GetAnimInstance()
	{
		return VehicleAnimInstances.HATCHBACK;
	}

	override int GetSeatAnimationType( int posIdx )
	{
		switch( posIdx )
		{
		case 0:
			return DayZPlayerConstants.VEHICLESEAT_DRIVER;
		case 1:
			return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		case 2:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_L;
		case 3:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_R;
		}

		return 0;

	}

	override bool CanReleaseAttachment( EntityAI attachment )
	{
		CarDoor carDoor;
		string attSlot = "";

		attSlot = attachment.GetType();
		switch( attSlot )
		{
			case "HatchbackDoors_Driver":
				if ( GetCarDoorsState("NivaDriverDoors") != CarDoorState.DOORS_OPEN )
					return false;
			break;
			case "HatchbackDoors_CoDriver":
				if ( GetCarDoorsState("NivaCoDriverDoors") != CarDoorState.DOORS_OPEN )
					return false;
			break;
		}
		return true;
	}

	override int GetCarDoorsState( string slotType )
	{
		CarDoor carDoor;
		
		switch( slotType )
		{
			case "NivaDriverDoors":
				Class.CastTo( carDoor, FindAttachmentBySlotName("NivaDriverDoors") );
				if ( carDoor )
				{
					if ( GetAnimationPhase("DoorsDriver") > 0.5 )
					{
						return CarDoorState.DOORS_OPEN;
					}
					else
					{
						return CarDoorState.DOORS_CLOSED;
					}
				}

				return CarDoorState.DOORS_MISSING;
			break;
			
			case "NivaCoDriverDoors":
				Class.CastTo( carDoor, FindAttachmentBySlotName("NivaCoDriverDoors") );
				if ( carDoor )
				{
					if ( GetAnimationPhase("DoorsCoDriver") > 0.5 )
					{
						return CarDoorState.DOORS_OPEN;
					}
					else
					{
						return CarDoorState.DOORS_CLOSED;
					}
				}

				return CarDoorState.DOORS_MISSING;
			break;
			
			case "NivaHood":
				Class.CastTo( carDoor, FindAttachmentBySlotName("NivaHood") );
				if ( carDoor )
				{
					if ( GetAnimationPhase("DoorsHood") > 0.5 )
					{
						return CarDoorState.DOORS_OPEN;
					}
					else
					{
						return CarDoorState.DOORS_CLOSED;
					}
				}
		
				return CarDoorState.DOORS_MISSING;
			break;
			
			case "NivaTrunk":
				Class.CastTo( carDoor, FindAttachmentBySlotName("NivaTrunk") );
				if ( carDoor )
				{
					if ( GetAnimationPhase("DoorsTrunk") > 0.5 )
					{
						return CarDoorState.DOORS_OPEN;
					}
					else
					{
						return CarDoorState.DOORS_CLOSED;
					}
				}

				return CarDoorState.DOORS_MISSING;
			break;
		}

		return CarDoorState.DOORS_MISSING;
	}
	
	override bool CrewCanGetThrough( int posIdx )
	{
		CarDoor carDoor;
		switch( posIdx )
		{
			case 0:
				if ( GetCarDoorsState( "NivaDriverDoors" ) == CarDoorState.DOORS_CLOSED )
				{
					return false;
				}
				else
				{
					if ( GetAnimationPhase("SeatDriver") > 0.5 )
					{
						return false;
					}
				}
			
				return true;
			break;
			
			case 1:
				if ( GetCarDoorsState( "NivaCoDriverDoors" ) == CarDoorState.DOORS_CLOSED )
				{
					return false;
				}
				else
				{
					if ( GetAnimationPhase("SeatCoDriver") > 0.5 )
					{
						return false;
					}
				}
			
				return true;
			break;

			case 2:
				if ( GetCarDoorsState( "NivaDriverDoors" ) == CarDoorState.DOORS_CLOSED )
				{
					return false;
				}
				else
				{
					if ( GetAnimationPhase("SeatDriver") <= 0.5 )
					{
						return false;
					}
				}
			
				return true;
			break;

			case 3:
				if ( GetCarDoorsState( "NivaCoDriverDoors" ) == CarDoorState.DOORS_CLOSED )
				{
					return false;
				}
				else
				{
					if ( GetAnimationPhase("SeatCoDriver") <= 0.5 )
					{
						return false;
					}
				}
			
				return true;
			break;
		}

		return false;
	}
	
	override float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		switch ( ctrl )
		{
			case CarSoundCtrl.DOORS:
				float newValue = 0;

				//-----
				if ( GetCarDoorsState( "NivaDriverDoors" ) == CarDoorState.DOORS_CLOSED )
				{
					newValue = newValue + 0.85;
				}

				if ( GetCarDoorsState( "NivaCoDriverDoors" ) == CarDoorState.DOORS_CLOSED )
				{
					newValue = newValue + 0.85;
				}

				if ( GetCarDoorsState( "NivaTrunk" ) == CarDoorState.DOORS_CLOSED )
				{
					newValue = newValue + 0.6;
				}

				if ( newValue > 1 )
					newValue = 1;
			
				return newValue;
			break;
		}

		return oldValue;
	}

	override string GetAnimSourceFromSelection( string selection )
	{
		switch( selection )
		{
		case "doors_driver":
			return "DoorsDriver";
		case "doors_codriver":
			return "DoorsCoDriver";
		case "doors_hood":
			return "DoorsHood";
		case "doors_trunk":
			return "DoorsTrunk";
		case "seatback_driver":
			return "SeatDriver";
		case "seatback_codriver":
			return "SeatCoDriver";
		}

		return "";
	}

	override int GetCrewIndex( string selection )
	{
		switch( selection )
		{
		case "seatback_driver":
			return 0;
		case "seatback_codriver":
			return 1;
		}

		return -1;
	}

	override bool IsVitalTruckBattery()
	{
		return false;
	}

	override bool IsVitalGlowPlug()
	{
		return false;
	}
	
	override int CanReachSeatFromSeat( int currentSeat, int nextSeat )
	{
		switch( currentSeat )
		{
		case 0:
			if ( nextSeat == 1 )
			{
				return true;
			}
			break;
		case 1:
			if ( nextSeat == 0 )
			{
				return true;
			}
			break;
		case 2:
			if ( nextSeat == 3 )
			{
				return true;
			}
			break;
		case 3:
			if ( nextSeat == 2 )
			{
				return true;
			}
			break;
		}
		
		return false;
	}
}