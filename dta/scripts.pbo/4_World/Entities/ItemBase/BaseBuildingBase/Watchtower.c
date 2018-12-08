class Watchtower extends BaseBuildingBase
{	
	typename ATTACHMENT_BARBED_WIRE			= BarbedWire;
	typename ATTACHMENT_CAMONET 			= CamoNet;
	
	void Watchtower()
	{
	}
	
	override string GetConstructionKitType()
	{
		return "WatchtowerKit";
	}		
	
	//--- ATTACHMENT & CONDITIONS
	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		if ( !super.CanReceiveAttachment( attachment, slotId ) )
			return false;

		string slot_name;
		InventorySlots.GetSelectionForSlotId( slotId , slot_name );
		slot_name.ToLower();
		
		//attachments
		if ( attachment.Type() == ATTACHMENT_BARBED_WIRE || attachment.Type() == ATTACHMENT_CAMONET )
		{
			return HasBase();
		}		
		
		//level 1
		if ( slot_name.Contains( "material_l1w" ) || slot_name.Contains( "level_1_wall" ) )
		{
			return GetConstruction().IsPartConstructed( "level_1_base" ) && CheckVerticalDistance( 0.5, "level_1" );
		}
		//level 2
		if ( slot_name.Contains( "material_l2" ) || slot_name.Contains( "level_2_" ) )
		{
			if ( slot_name.Contains( "material_l2w" ) || slot_name.Contains( "level_2_wall" ) )
			{
				return GetConstruction().IsPartConstructed( "level_2_base" ) && CheckVerticalDistance( 0.5, "level_2" );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_1_roof" ) && CheckVerticalDistance( 0.5, "level_2" );
			}
		}
		//level 3
		else if ( slot_name.Contains( "material_l3" ) || slot_name.Contains( "level_3" ) )
		{
			if ( slot_name.Contains( "material_l3w" ) || slot_name.Contains( "level_3_wall" ) )
			{
				return GetConstruction().IsPartConstructed( "level_3_base" ) && CheckVerticalDistance( 0.5, "level_3" );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_2_roof" ) && CheckVerticalDistance( 0.5, "level_3" );
			}
		}		
	
		return true;
	}
	
	//can put into hands
	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
	
	// --- INVENTORY
	override bool CanDisplayAttachmentSlot( string slot_name )
	{
		//super
		if ( !super.CanDisplayAttachmentSlot( slot_name ) )
		return false;
		//
		
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		//super
		if ( !super.CanDisplayAttachmentCategory( category_name ) )
		return false;
		//
	
		category_name.ToLower();
		
		//level 1
		if ( category_name.Contains( "level_1" ) )
		{
			if ( category_name.Contains( "level_1_" ) )
			{
				return GetConstruction().IsPartConstructed( "level_1_base" ) && CheckVerticalDistance( 0.5, "level_1" );
			}
			else
			{
				return CheckVerticalDistance( 0.5, "level_1" );
			}
		}
		//level 2
		if ( category_name.Contains( "level_2" ) )
		{
			if ( category_name.Contains( "level_2_" ) )
			{
				return GetConstruction().IsPartConstructed( "level_2_base" ) && CheckVerticalDistance( 0.5, "level_2" );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_1_roof" ) && CheckVerticalDistance( 0.5, "level_2" );
			}
		}
		//level 3
		if ( category_name.Contains( "level_3" ) )
		{
			if ( category_name.Contains( "level_3_" ) )
			{
				return GetConstruction().IsPartConstructed( "level_3_base" ) && CheckVerticalDistance( 0.5, "level_3" );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_2_roof" ) && CheckVerticalDistance( 0.5, "level_3" );
			}
		}
		
		return true;
	}	
	

	protected bool CheckVerticalDistance( float max_dist, string selection )
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			vector player_pos = GetGame().GetPlayer().GetPosition();
			vector pos;
			if ( MemoryPointExists( selection ) )
			{
				pos = ModelToWorld( GetMemoryPointPos( selection ) );
			}
			
			if ( Math.AbsFloat( player_pos[1] - pos[1] ) <= max_dist )
			{
				return true;
			}
		}
		
		return false;
	}
	// ---	
	
	//--- ACTION CONDITIONS
	//returns dot product of player->construction direction based on existing/non-existing reference point
	override bool IsFacingFront( PlayerBase player, string selection )
	{
		vector ref_pos;
		vector ref_dir;
		vector player_dir;
		float dot;
		bool has_memory_point = MemoryPointExists( selection );
		
		if ( has_memory_point )
		{
			ref_pos = ModelToWorld( GetMemoryPointPos( selection ) );
			ref_dir = ref_pos - GetPosition();
		}
		else
		{
			ref_pos = GetPosition();
			ref_dir = ref_pos - player.GetPosition();
		}
		
		ref_dir.Normalize();
		ref_dir[1] = 0;		//ignore height
		
		player_dir = player.GetDirection();
		player_dir.Normalize();
		player_dir[1] = 0;				//ignore height
		
		if ( ref_dir.Length() != 0 )
		{
			dot = vector.Dot( player_dir, ref_dir );
			
		}
		
		if ( has_memory_point )
		{
			if ( dot < 0 )
			{
				return true;
			}
		}
		else
		{
			if ( dot > 0 )
			{
				return true;
			}
		}
		
		return false;
	}
	
	override bool IsFacingBack( PlayerBase player, string selection )
	{
		return 	!IsFacingFront( player, selection );
	}	
}