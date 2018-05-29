class ActionDigStashCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionComponent = new CAContinuousTime(UATimeSpent.DIG_STASH);
	}
};

class ActionDigStash: ActionContinuousBase
{
	private const float ROUGH_SPECIALTY_WEIGHT = 0.01;
	
	void ActionDigStash()
	{
		m_CallbackClass = ActionDigStashCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DIGSHOVEL;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		
		m_MessageStartFail = "I can't dig here.";
		m_MessageStart = "I've started digging.";
		m_MessageSuccess = "I have stashed the chest.";
		m_MessageFail = "I couldn't dig the hole.";
		m_MessageCancel = "I've stopped digging.";
		m_SpecialtyWeight = ROUGH_SPECIALTY_WEIGHT;
	}
	
	override void CreateConditionComponents()  
	{	
		
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}

	override int GetType()
	{
		return AT_DIG_STASH;
	}

	override string GetText()
	{
		return "Dig stash";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		ItemBase target_IB;
		if ( Class.CastTo(target_IB, target.GetObject()) )
		{			
			// Check surface
			string surface_type;
			vector position = target_IB.GetPosition();
			GetGame().SurfaceGetType ( position[0], position[2], surface_type );
			
			if ( target_IB.ConfigGetBool("canBeDigged") )
			{
				if ( target_IB.IsInherited(UndergroundStash) )
				{
					return true;
				}
				
				// TO DO: Create IsOnSoftSurface() method and use that instead of this long if
				if ( surface_type == "cp_dirt"  ||  surface_type == "cp_broadleaf_dense1"  ||  surface_type == "cp_broadleaf_dense2"  ||  surface_type == "cp_broadleaf_sparse1"  ||  surface_type == "cp_broadleaf_sparse2"  ||  surface_type == "cp_conifer_common1"  ||  surface_type == "cp_grass"  ||  surface_type == "cp_grass_tall"  ||  surface_type == "grass_dry_ext" )
				{
					// Check slope angle
					vector posA = position + "0.5 0 0.5";
					vector posB = position + "-0.5 0 0.5";
					vector posC = position + "0.5 0 -0.5";
					vector posD = position + "-0.5 0 -0.5";
					
					array<vector> positions = new array<vector>;
					positions.Insert( posA );
					positions.Insert( posB );
					positions.Insert( posC );
					positions.Insert( posD );
					
					float difference = GetGame().GetHighestSurfaceYDifference(positions);
					
					if ( difference < 0.6 )
					{
						return true;
					}
				}
			}
		}
		
		return false;
	}

	override void OnCompleteServer( PlayerBase player, ActionTarget target, ItemBase item, Param acdata )
	{
		Object targetObject = target.GetObject();
		UndergroundStash target_stash;		
		if ( Class.CastTo(target_stash, targetObject) )
		{
			ItemBase chest = target_stash.GetStashedItem();
			
			if (chest)
			{
				chest.SetPosition( target_stash.GetPosition() );
				target_stash.SetStashedItem(NULL);
			}
			
			g_Game.ObjectDelete( target_stash );
		}
		else
		{
			ItemBase stashed_item;
			UndergroundStash stash;
			vector pos = targetObject.GetPosition();
			
			targetObject.SetPosition( targetObject.GetPosition() + "0 -5 0" ); // TO DO: Do not use teleportation hack if possible!
			
			Class.CastTo(stashed_item,  targetObject );
			Class.CastTo(stash,  GetGame().CreateObject("UndergroundStash", pos, false) );
			
			if ( stash )
			{
				stash.SetStashedItem(stashed_item);
				stash.PlaceOnGround();
			}
			else
			{
				Print("ERROR! Stash not spawned!");
			}
		}

		player.GetSoftSkillManager().AddSpecialty( m_SpecialtyWeight );
	}
};