class Watchtower extends BaseBuildingBase
{	
	typename ATTACHMENT_BARBED_WIRE			= BarbedWire;
	typename ATTACHMENT_CAMONET 			= CamoNet;
	
	void Watchtower()
	{
		CONSTRUCTION_KIT		= "WatchtowerKit";
	}

	//TODO
	//Temporary solution to missing slot_id parameter in CanReceiveAttachment() method
	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached ( item, slot_name );
		
		//drop materials if they are not supported by selected floor (or roof)
		//level 2
		if ( slot_name.Contains( "Material_L2" ) )
		{
			if ( !GetConstruction().IsPartConstructed( "level_1_roof" ) )
			{
				//drop item on ground
				if ( GetGame().IsMultiplayer() )
				{
					GetInventory().DropEntity( InventoryMode.PREDICTIVE, this, item );
				}
				else
				{
					GetInventory().DropEntity( InventoryMode.LOCAL, this, item );
				}
			}
		}
		//level 3
		else if ( slot_name.Contains( "Material_L3" ) )
		{
			if ( !GetConstruction().IsPartConstructed( "level_2_roof" ) )
			{
				//drop item on ground
				if ( GetGame().IsMultiplayer() )
				{
					GetInventory().DropEntity( InventoryMode.PREDICTIVE, this, item );
				}
				else
				{
					GetInventory().DropEntity( InventoryMode.LOCAL, this, item );
				}
			}			
		}
	}
	
	//--- ATTACHMENT & CONDITIONS
	override bool CanReceiveAttachment( EntityAI attachment )
	{
		if ( attachment.Type() == ATTACHMENT_BARBED_WIRE || attachment.Type() == ATTACHMENT_CAMONET )
		{
			if ( !HasBase() )
			{
				return false;
			}
		}
			
		return true;
	}	
	
	//TODO - add proper direction conditions to IsFacingBack and IsFacingFront
	//--- ACTION CONDITIONS
	override bool IsFacingFront( PlayerBase player )
	{
		return true;
	}
	
	override bool IsFacingBack( PlayerBase player )
	{
		return true;
	}
}