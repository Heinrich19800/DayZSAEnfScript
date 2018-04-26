Mission CreateMission(string path)
{
	Print("Creating Mission: "+ path);
	
	g_Game.SetMissionPath(path);

	if (g_Game.IsMultiplayer() && g_Game.IsServer())
	{
		return new MissionServer;
	}

#ifdef NO_GUI
	return new MissionDummy;
#endif
	MissionMainMenu m;
	if (path.Contains("NoCutscene"))
	{
		m = new MissionMainMenu();
		m.m_NoCutscene = true;
		return m;
	}
	
	if (path.Contains("intro"))
	{
		m = new MissionMainMenu();
		m.m_NoCutscene = false;
		return m;
	}
	else
	{
#ifndef NO_GUI_INGAME
		return new MissionGameplay;
#else
		return new MissionDummy;
#endif
	}
}

	/*
		Entity m_playerEnt;
		string characterName;
		characterName = GetGame().CreateRandomPlayer();
		PlayerIdentity identity;
		PlayerBase player;
		identity = player.GetIdentity();
		m_playerEnt = GetGame().CreatePlayer(identity, characterName, "4548 0.0 10242", 0, "NONE");//Creates random player
		GetGame().SelectPlayer(identity, m_playerEnt);
		

		
		/*ref TStringArray items = new TStringArray;
		items.Insert("Hoodie_Blue");
		items.Insert("WoolCoat_Red"); 
		items.Insert("Raincoat_Orange"); 
		items.Insert("PressVest_Blue"); 
		items.Insert("Gorka_pants_summer"); 
		items.Insert("MilitaryBoots_Black");
		items.Insert("WoodAxe");
		items.Insert("Container_FirstAidKit");
		items.Insert("Consumable_DuctTape");
		items.Insert("Fruit_AppleFresh");
		items.Insert("ItemBookHunger");
		items.Insert("M4A1");
		items.Insert("M_STANAG_30Rnd");
		
		ref TStringArray items  = {"ACOGOptic","ReflexOptic","M4_CarryHandleOptic","Scout_Black","Mag_Scout_5Rnd","Mag_Scout_5Rnd","Mag_Scout_5Rnd","Mag_Scout_5Rnd","Mag_Scout_5Rnd","Mag_Scout_5Rnd","Mag_Scout_5Rnd","SVD","Mag_SVD_10Rnd","Mag_SVD_10Rnd","AKM","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","Mag_AKM_30Rnd","CivSedanWheel","CivSedanWheel","CivSedanWheel","CivSedanWheel","SparkPlug","CarBattery","BagAssaultBlack","Fruit_Cannabis","Compass","SmershVestBackpack","BallisticHelmet_Black","Att_Ghillie_Woodland","BookBible","Pen_Red","Consumable_Paper","Att_Ghillie_Woodland","CargoPants_Black","M65_Jacket_Black","Sneakers_Green","balaclavamask_blackskull","FirefighterAxe_Black","Mag_STANAG_30Rnd_Coupled","Mag_STANAG_30Rnd_Coupled","Mag_STANAG_30Rnd_Coupled","Mag_STANAG_30Rnd_Coupled","M4A1_Black","Att_Suppressor_M4","Att_Optic_Reflex","Att_Optic_M4T3NRDS","GrenadeRGD5","GrenadeRGD5","GrenadeRGD5","Att_Optic_ACOG","Att_Handguard_M4RIS_Black","Att_Buttstock_M4MP_Black","att_bipod_atlas","Ammo_556","Ammo_556","Ammo_556","Ammo_556","b95","Att_Optic_Hunting","Ammo_308Win","Ammo_308Win","Ammo_308Win","Ammo_308Win","workinggloves_Black","Medical_TransfusionKit","Medical_TransfusionKit","Medical_Morphine","Medical_Morphine","consumable_battery9V","Consumable_Rags"};
		Entity lolItem;
		for (int i = 0; i < items.Count(); i++)
		{
			string item = items.Get(i);
			vector item_pos = g_Game.GetPlayer().GetPosition();
			lolItem = g_Game.CreateObject(item, item_pos, false);
		}
	*/