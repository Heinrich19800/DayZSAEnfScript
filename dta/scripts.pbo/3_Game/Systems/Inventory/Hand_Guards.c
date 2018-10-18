///@{ guards

/**@class	HandGuardBase
 * @brief	represents guard on a transition from state to state
 **/
class HandGuardBase
{
	/**@fn			GuardCondition
	 * @brief		enable or disable transition based on condition
	 * the guard is a boolean operation executed first and which can prevent the transition from firing by returning false
	 * @return		true if transition is allowed
	 **/
	bool GuardCondition (HandEventBase e) { return true; }
};


class HandGuardAnd extends HandGuardBase
{
	ref HandGuardBase m_arg0;
	ref HandGuardBase m_arg1;

	void HandGuardAnd (HandGuardBase arg0 = NULL, HandGuardBase arg1 = NULL) { m_arg0 = arg0; m_arg1 = arg1; }

	override bool GuardCondition (HandEventBase e)
	{
		bool result = m_arg0.GuardCondition(e) && m_arg1.GuardCondition(e);
		hndDebugPrint("[hndfsm] HandGuardAnd guard - " + m_arg0.Type() + " && " + m_arg1.Type() + " = " + result);
		return result;
	}
};

class HandGuardNot extends HandGuardBase
{
	ref HandGuardBase m_arg0;

	void HandGuardNot (HandGuardBase arg0 = NULL) { m_arg0 = arg0; }

	override bool GuardCondition (HandEventBase e)
	{
		bool result = !m_arg0.GuardCondition(e);
		hndDebugPrint("[hndfsm] HandGuardNot guard - ! " + m_arg0.Type() + " = " + result);
		return result;
	}
};

class HandGuardOr extends HandGuardBase
{
	ref HandGuardBase m_arg0;
	ref HandGuardBase m_arg1;

	void HandGuardOr (HandGuardBase arg0 = NULL, HandGuardBase arg1 = NULL) { m_arg0 = arg0; m_arg1 = arg1; }

	override bool GuardCondition (HandEventBase e)
	{
		bool result = m_arg0.GuardCondition(e) || m_arg1.GuardCondition(e);
		hndDebugPrint("[hndfsm] HandGuardOr guard - " + m_arg0.Type() + " || " + m_arg1.Type() + " = " + result);
		return result;
	}
};

class HandGuardHasItemInEvent extends HandGuardBase
{
	protected Man m_Player;
	void HandGuardHasItemInEvent (Man p = NULL) { m_Player = p; }

	override bool GuardCondition (HandEventBase e)
	{
		EntityAI eai = e.m_Entity;
		if (eai != NULL /* && CanTakeInHands*/)
		{
			hndDebugPrint("[hndfsm] HandGuardHasItemInEvent guard - has valid entity in event");
			return true;
		}
		hndDebugPrint("[hndfsm] HandGuardHasItemInEvent guard - no entity in event");
		return false;
	}
};

class HandGuardHasWeaponInEvent extends HandGuardHasItemInEvent
{
	void HandGuardHasWeapoonInEvent (Man p = NULL) { }

	override bool GuardCondition (HandEventBase e)
	{
		EntityAI eai = e.m_Entity;
		if (eai != NULL)
		{
			if (eai.IsWeapon())
			{
				hndDebugPrint("[hndfsm] HandGuardHasWeaponInEvent guard - has valid weapon in event");
				return true;
			}
			else
			{
				hndDebugPrint("[hndfsm] HandGuardHasWeaponInEvent guard - entity, but not weapon in event");
				return false;
			}
		}
		hndDebugPrint("[hndfsm] HandGuardHasWeaponInEvent guard - no entity in event");
		return false;
	}
};

class HandGuardHasAnimatedAtachmentInEvent extends HandGuardHasItemInEvent
{
	void HandGuardHasAnimatedAtachmentInEvent (Man p = NULL) { }

	override bool GuardCondition (HandEventBase e)
	{
		EntityAI eai = e.m_Entity;
		if (eai != NULL)
		{
			InventoryLocation src = new InventoryLocation;
			if (eai.GetInventory().GetCurrentInventoryLocation(src))
			{
				if (eai.IsWeapon())
				{
					if (src.GetType() == InventoryLocationType.ATTACHMENT && src.GetParent().GetHierarchyRootPlayer() == m_Player)
					{
						// @TODO: check slots
						// belt with knife/pistol in cargo (?)
						hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInEvent guard - has valid weapon in event");
						return true;
					}
	
					hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInEvent guard - weapon, but not attachment");
					return false;
				}
				else
				{
					if (src.GetType() == InventoryLocationType.ATTACHMENT && src.GetParent().GetHierarchyRootPlayer() == m_Player)
					{	
						int animType = SlotToAnimType(m_Player, src);
						if (animType != -1)
						{
							hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInEvent guard - has valid animated item=" + eai + " in event, anim=" + animType);
							return true;
						}
						hndDebugPrint("[hndfsm] guard - has valid animated item (not weapon) in event");
						return false;
					}

					hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInEvent guard - entity, but not animated item in event");
					return false;
				}
			}
		}
		hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInEvent guard - no entity in event");
		return false;
	}
};

class HandGuardHasAnimatedAtachmentInHands extends HandGuardBase
{
	protected Man m_Player;
	void HandGuardHasAnimatedAtachmentInHands (Man p = NULL) { m_Player = p; }

	override bool GuardCondition (HandEventBase e)
	{
		EntityAI eai = m_Player.GetHumanInventory().GetEntityInHands();
		if (eai)
		{
			if (eai.IsWeapon())
			{
				hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInHands guard - has valid weapon in event");
				return true;
			}
			else
			{
				InventoryLocation dst = e.GetDst();
				if (dst)
				{
					if (dst.GetType() == InventoryLocationType.ATTACHMENT && dst.GetParent().GetHierarchyRootPlayer() == m_Player)
					{
						int animType = SlotToAnimType(m_Player, dst);
						if (animType != -1)
						{
							hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInHands guard - has valid animated item=" + eai + " in event, anim=" + animType);
							return true;
						}
						hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInHands guard - has valid animated item (not weapon) in event");
						return false;
					}
				}
				hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInHands guard - entity, but not animated item event");
				return false;
			}
		}
		hndDebugPrint("[hndfsm] HandGuardHasAnimatedAtachmentInHands guard - no entity in hands");
		return false;
	}
};

class HandGuardIsSameItemInHands extends HandGuardBase
{
	protected Man m_Player;
	void HandGuardIsSameItemInHands (Man p = NULL) { m_Player = p; }

	override bool GuardCondition (HandEventBase e)
	{
		if (e.m_Entity == m_Player.GetHumanInventory().GetEntityInHands())
		{
			hndDebugPrint("[hndfsm] HandGuardIsSameItemInHands guard - has same entity in hands");
			return true;
		}

		hndDebugPrint("[hndfsm] HandGuardIsSameItemInHands guard - different entity in hands");
		return false;
	}
};

class HandGuardHasDestroyedItemInHands extends HandGuardBase
{
	protected Man m_Player;
	void HandGuardHasDestroyedItemInHands (Man p = NULL) { m_Player = p; }

	override bool GuardCondition (HandEventBase e)
	{
		hndDebugSpam("[hndfsm] HandGuardHasDestroyedItemInHands guard - has same entity in hands ev=" + e.m_Entity + " hnd=" + m_Player.GetHumanInventory().GetEntityInHands());
		EntityAI hnd = m_Player.GetHumanInventory().GetEntityInHands();
		if (e.m_Entity)
		{
			if (e.m_Entity == hnd)
			{
				hndDebugPrint("[hndfsm] HandGuardHasDestroyedItemInHands guard - has same entity in hands");
				return true;
			}

			if (hnd == null)
			{
				hndDebugPrint("[hndfsm] HandGuardHasDestroyedItemInHands guard - hands already empty");
				return true;
			}
		}
		else
		{
			hndDebugPrint("[hndfsm] HandGuardHasDestroyedItemInHands guard - hands already empty and item destroyed");
			return true;
		}

		hndDebugPrint("[hndfsm] HandGuardHasDestroyedItemInHands guard - destroyed entity not in hands");
		return false;
	}
};

class HandGuardHasItemInHands extends HandGuardBase
{
	protected Man m_Player;
	void HandGuardHasItemInHands (Man p = NULL) { m_Player = p; }

	override bool GuardCondition (HandEventBase e)
	{
		if (m_Player.GetHumanInventory().GetEntityInHands())
		{
			hndDebugPrint("[hndfsm] HandGuardHasItemInHands guard - has valid entity in hands");
			return true;
		}

		hndDebugPrint("[hndfsm] HandGuardHasItemInHands guard - no entity in hands");
		return false;
	}
};

class HandGuardHasRoomForItem extends HandGuardBase
{
	protected Man m_Player;
	void HandGuardHasRoomForItem (Man p = NULL) { m_Player = p; }

	override bool GuardCondition (HandEventBase e)
	{
		EntityAI eai = e.m_Entity;

		HandEventMoveTo es = HandEventMoveTo.Cast(e);
		if (es)
		{
			if (!GameInventory.LocationTestAddEntity(es.m_Dst, false, true, true, true))
				Error("[hndfsm] HandGuardHasRoomForItem - no room at dst=" + es.m_Dst.DumpToString());
			return true;
		}

		hndDebugPrint("[hndfsm] HandGuardHasRoomForItem guard - no room for item in hands");
		return false;
	}
};

class HandGuardHasRoomForAttachment extends HandGuardBase
{
	protected Man m_Player;
	void HandGuardHasRoomForAttachment (Man p = NULL) { m_Player = p; }

	override bool GuardCondition (HandEventBase e)
	{
		EntityAI eai = e.m_Entity;

		HandEventMoveTo es = HandEventMoveTo.Cast(e);
		if (es)
		{
			if (es.m_Dst.GetType() == InventoryLocationType.ATTACHMENT)
			{
				// @TODO: check slots
				if (GameInventory.LocationCanAddEntity(es.m_Dst))
				{
					hndDebugPrint("[hndfsm] HandGuardHasRoomForAttachment guard - has valid entity in hands");
					return true;
				}
				else
					Error("[hndfsm] HandGuardHasRoomForAttachment - no room at dst=" + es.m_Dst.DumpToString());

				return false;
			}
		}

		hndDebugPrint("[hndfsm] HandGuardHasRoomForAttachment guard - no room for item in hands");
		return false;
	}
};

///@} guards

