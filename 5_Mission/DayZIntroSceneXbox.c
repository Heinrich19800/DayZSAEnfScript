class DayZIntroSceneXbox: Managed
{
	bool m_IsCharFemale;
	int m_LastShavedSeconds;
	int m_LastPlayedCharacterID;
	
	ref TStringAdvanceArray m_genderList;
	ref TStringAdvanceArray m_CharPersonalityMaleList;
	ref TStringAdvanceArray m_CharPersonalityFemaleList;
	ref TStringArray 		m_allCharacters;
	ref TStringAdvanceArray m_CharShirtList;
	ref TStringAdvanceArray m_CharPantsList;
	ref TStringAdvanceArray m_CharShoesList;
	
	ref EntityAnimEndEventHandler 	m_anim_end_event_handler;

	Camera		m_SceneCamera;
	PlayerBase	m_SceneCharacter;
	Weather		m_Weather;
	vector		m_CharacterPos;
	vector		m_CharacterRot;
	float		m_BlurValue;

	MenuData m_MenuData;

	//==================================
	// DayZIntroSceneXbox
	//==================================
	void DayZIntroSceneXbox()
	{
		Print("DayZIntroSceneXbox Start");
		
		m_MenuData = g_Game.GetMenuData();
		m_MenuData.LoadCharacters();
		
		m_LastPlayedCharacterID = m_MenuData.GetLastPlayedCharacter();
		m_CharacterPos = "0 0 0";
		m_CharacterRot = "0 0 0";
		m_LastShavedSeconds = 0;
		
		//g_Game.m_PlayerName = "Survivor"; //default
		
		if ( m_LastPlayedCharacterID > -1 )
		{
			m_MenuData.GetCharacterName(m_LastPlayedCharacterID, g_Game.GetPlayerGameName());
		}
	
		// Camera Setup
		vector camera_position;
		camera_position[0] 			= 1318.25;	// X
		camera_position[1] 			= 1.91;		// Y
		camera_position[2] 			= 1602.17;	// Z
		float camera_rotation		= 115;
		float camera_fov			= 1;
		float camera_focus_distance	= 5.0;
		float camera_focus_streght	= 0.5;
		
		// Character
		float character_distance = 5.0;
		
		// Date
		TIntArray date = new TIntArray;
		date.Insert(2020);	// Year
		date.Insert(10);	// Month
		date.Insert(15);	// Day
		date.Insert(18);	// Hour
		date.Insert(00);	// Minite
		
		// Weather
		float weather_storm_density		= 0.0;
		float weather_storm_threshold	= 0.0;
		float weather_storm_time_out	= 0.0;
		float weather_overcast			= 0.2;
		float weather_rain				= 0.0;
		float weather_fog				= 0.1;
		float weather_windspeed			= 0.1;
		
		// Date Setup 
		g_Game.GetWorld().SetDate(date.Get(0), date.Get(1), date.Get(2), date.Get(3), date.Get(4));
		
		// Weather Setup 
		m_Weather = g_Game.GetWeather();
		m_Weather.GetOvercast().SetLimits( weather_overcast, weather_overcast );
		m_Weather.GetOvercast().Set( weather_overcast, 0, 0);
		m_Weather.GetRain().SetLimits( weather_rain, weather_rain );
		m_Weather.GetRain().Set( weather_rain, 0, 0);
		m_Weather.GetFog().SetLimits( weather_fog, weather_fog );
		m_Weather.GetFog().Set( weather_fog, 0, 0);
		m_Weather.SetStorm(weather_storm_density, weather_storm_threshold, weather_storm_time_out);
		m_Weather.SetWindSpeed(weather_windspeed);
		m_Weather.SetWindMaximumSpeed(weather_windspeed);
		m_Weather.SetWindFunctionParams(1, 1, 1);
		
		// Camera Setup 
		m_SceneCamera = CameraCreate(camera_position, camera_rotation, camera_fov, camera_focus_distance, camera_focus_streght);
		m_SceneCamera.SetActive(true);
		
		// Character Setup
		vector cam_dir = m_SceneCamera.GetDirection();
		m_CharacterPos = camera_position + ( cam_dir * character_distance );
		m_CharacterRot = cam_dir * -1;

Print("DayZIntroSceneXbox Init");
		
		Init();
Print("DayZIntroSceneXbox End");
	
	}
	
	//==================================
	// Init
	//==================================
	void Init()
	{
		//fill default lists
		m_genderList = new TStringAdvanceArray;
		m_CharPersonalityMaleList = new TStringAdvanceArray;
		m_CharPersonalityFemaleList = new TStringAdvanceArray;
		m_allCharacters = new TStringArray;
		m_CharShirtList = new TStringAdvanceArray;
		m_CharPantsList = new TStringAdvanceArray;
		m_CharShoesList = new TStringAdvanceArray;
		
		string character_CfgName;
		string root_path = "cfgCharacterCreation";
		
		g_Game.ConfigGetTextArray(root_path + " gender", m_genderList);
		g_Game.ConfigGetTextArray(root_path + " top", m_CharShirtList);
		g_Game.ConfigGetTextArray(root_path + " bottom", m_CharPantsList);
		g_Game.ConfigGetTextArray(root_path + " shoe", m_CharShoesList);

		m_allCharacters = GetGame().ListAvailableCharacters();
		for (int i = 0; i < m_allCharacters.Count(); i++)
		{
			character_CfgName = m_allCharacters.Get(i);
			if (GetGame().IsKindOf(character_CfgName, "SurvivorMale_Base"))
			{
				m_CharPersonalityMaleList.Insert(character_CfgName);
			}
			else
			{
				m_CharPersonalityFemaleList.Insert(character_CfgName);
			}
		}
		
		ChangeCharacter(m_LastPlayedCharacterID);
		
		PPEffects.Init();
		PPEffects.DisableBurlapSackBlindness(); //HOTFIX
		//PPEffects.ResetAll();
	}
	
	//==================================
	// CameraCreate
	//==================================
	protected Camera CameraCreate(vector cam_pos, float cam_rot, float cam_fov, float cam_focus_dist, float cam_focus_strg)
	{
		Camera cam = Camera.Cast( g_Game.CreateObject("staticcamera", SnapToGround(cam_pos), true));
		cam.SetOrientation( Vector( cam_rot, 0, 0) );
		cam.SetFOV( cam_fov );
		cam.SetFocus(cam_focus_dist, cam_focus_strg);
		
		return cam;
	}
	
	//==================================
	// GetCamera
	//==================================
	Camera GetCamera()
	{
		return m_SceneCamera;
	}
	
	//==================================
	// ResetIntroCamera
	//==================================
	void ResetIntroCamera()
	{
		
	}
	
	//==================================
	// SetCharacterFemale
	//==================================
	void SetCharacterFemale(bool fem)
	{
		m_IsCharFemale = fem;
	}
	
	//==================================
	// IsCharacterFemale
	//==================================
	bool IsCharacterFemale()
	{
		return m_IsCharFemale;
	}
	
	//==================================
	// GetIntroSceneCharacter
	//==================================
	PlayerBase GetIntroSceneCharacter()
	{
		return m_SceneCharacter;
	}
	
	//==================================
	// CreateRandomCharacter
	//==================================
	void CreateRandomCharacter()
	{
		string character_name;
		string params[2];
		
		m_IsCharFemale = Math.RandomInt(0, 2);
		
		if (m_IsCharFemale)
		{
			character_name = m_CharPersonalityFemaleList.GetRandomElement();
		}
		else
		{
			character_name = m_CharPersonalityMaleList.GetRandomElement();
		}
		CreateNewCharacter(character_name);
		
		if (m_SceneCharacter)
		{
			SetAttachment(m_CharShirtList.GetRandomElement(), InventorySlots.BODY);
			SetAttachment(m_CharPantsList.GetRandomElement(), InventorySlots.LEGS);
			SetAttachment(m_CharShoesList.GetRandomElement(), InventorySlots.FEET);
		}
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateCharacterPos, 250);
	}
	
	void SetAttachment(string type, int slot)
	{
		if (!m_SceneCharacter) return;
		g_Game.ObjectDelete(m_SceneCharacter.GetInventory().FindAttachment(slot));
		EntityAI entity;
		Class.CastTo(entity, g_Game.CreateObject(type, "0 2000 0", true));
		if (entity)
		{
			m_SceneCharacter.LocalTakeEntityAsAttachmentEx(entity, slot);
		}
	}
	
	void UpdateSelectedUserName()
	{
		string name;
		BiosUserManager user_manager = GetGame().GetUserManager();
		if( user_manager )
		{
			BiosUser user = user_manager.GetSelectedUser();
			if( user )
			{
				g_Game.SetPlayerGameName( user.GetName() );
				return;
			}
		}
		g_Game.SetPlayerGameName(DEFAULT_CHARACTER_NAME);
	}
	
	// ------------------------------------------------------------
	void ChangeCharacter(int characterID)
	{
		string name;
		if (m_SceneCharacter)
		{
			g_Game.ObjectDelete(m_SceneCharacter);
			m_SceneCharacter = NULL;
		}
		m_LastPlayedCharacterID = characterID;
		BiosUserManager user_manager;
		
		//random character
		if(characterID == - 1)
		{
			UpdateSelectedUserName();

			CreateRandomCharacter();
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateCharacterPos, 250);
			g_Game.SetNewCharacter(true);
			return;
		}
		
		PlayerBase.CastTo(m_SceneCharacter, m_MenuData.CreateCharacterPerson(characterID));
		
		if (m_SceneCharacter)
		{
			g_Game.SetNewCharacter(false);
			m_SceneCharacter.PlaceOnSurface();
			m_SceneCharacter.SetOrientation(m_CharacterRot);
			m_SceneCharacter.SetEventHandler(m_anim_end_event_handler);
			m_SceneCharacter.SetLastShavedSeconds(m_LastShavedSeconds);
	
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateCharacterPos, 250);
		}

		UpdateSelectedUserName();

		g_Game.SetPlayerGameName(name);
	}
	
	// ------------------------------------------------------------
	void CreateNewCharacter(string type)
	{
		if (m_SceneCharacter)
		{
			g_Game.ObjectDelete(m_SceneCharacter);
			m_SceneCharacter = NULL;
		}

		g_Game.PreloadObject(type, 1.0);
		Class.CastTo(m_SceneCharacter, g_Game.CreateObject(type, SnapToGround(Vector(m_CharacterPos[0],m_CharacterPos[1],m_CharacterPos[2]) + "0 0 333"), true));
		
		if (m_SceneCharacter)
		{
			m_SceneCharacter.PlaceOnSurface();
			m_SceneCharacter.SetOrientation(m_CharacterRot);
			m_SceneCharacter.SetEventHandler(m_anim_end_event_handler);
			m_SceneCharacter.SetLastShavedSeconds(m_LastShavedSeconds);

			// NEW STATS API
			string lvalue = "";
			m_SceneCharacter.StatGetCounter("playtime", lvalue);

			PluginLifespan module_lifespan;
			Class.CastTo(module_lifespan, PluginLifespan.Cast( GetPlugin( PluginLifespan ) ));
			module_lifespan.UpdateLifespanParam( m_SceneCharacter, lvalue, true );
		}
	}
	
	void UpdateCharacterPos()
	{
		if (m_SceneCharacter)
		{
			m_SceneCharacter.SetPosition(m_CharacterPos);
			m_SceneCharacter.SetOrientation(m_CharacterRot);
		}
	}
	
	void SaveCharName()
	{
		GetDayZGame().InitCharacterMenuDataInfo(m_MenuData.GetCharactersCount());
		
		if (!GetDayZGame().IsNewCharacter() && m_LastPlayedCharacterID > -1)
		{
			m_MenuData.SetCharacterName(m_LastPlayedCharacterID, GetDayZGame().GetPlayerGameName());			
		}
	}
	
	// ------------------------------------------------------------
	void Update()
	{
	
	}
	
	// ------------------------------------------------------------
	vector SnapToGround(vector pos)
	{
		float pos_x = pos[0];
		float pos_z = pos[2];
		float pos_y = GetGame().SurfaceY(pos_x, pos_z);
		vector tmp_pos = Vector(pos_x, pos_y, pos_z);
		tmp_pos[1] = tmp_pos[1] + pos[1];
	
		return tmp_pos;
	}
};