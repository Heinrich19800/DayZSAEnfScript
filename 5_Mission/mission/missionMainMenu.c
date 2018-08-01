class MissionMainMenu extends MissionBase
{
	private UIScriptedMenu m_mainmenu;
	private ref DayZIntroScene m_intro_scene;
	bool m_NoCutscene;

	DayZIntroScene GetIntroScene()
	{
		return m_intro_scene;
	}

	override void OnInit()
	{
		if (!m_NoCutscene)
		{
			CreateIntroScene();
		}
		
		if (!m_mainmenu)
		{
			#ifdef PLATFORM_XBOX
				m_mainmenu = UIScriptedMenu.Cast( g_Game.GetUIManager().EnterScriptedMenu( MENU_TITLE_SCREEN, null ) );
			#else
				m_mainmenu = UIScriptedMenu.Cast( g_Game.GetUIManager().EnterScriptedMenu( MENU_MAIN, null ) );
			#endif
		}
	}

	void CreateIntroScene()
	{
		m_intro_scene = new DayZIntroScene;
		//m_intro_scene.CreateDefaultCharacter();
	}

	override void OnMissionStart()
	{
		if (m_mainmenu)
		{
			//m_mainmenu.FadeIn(2.0);	//Fade in method is currently commented in MainMenu class
		}
		g_Game.GetUIManager().ShowUICursor(true);
		g_Game.SetMissionState( DayZGame.MISSION_STATE_MAINMENU );
	}
	
	override void OnMissionFinish()
	{
		if( m_mainmenu )
			m_mainmenu.Cleanup();
		GetGame().GetUIManager().CloseAll();
		m_mainmenu = NULL;
		
		m_intro_scene = NULL;
		g_Game.GetUIManager().ShowUICursor(false);
	}

	override void OnUpdate(float timeslice)
	{
		if (g_Game.IsLoading()) return;
		
		if (m_intro_scene)
		{
			m_intro_scene.Update();
		}

		if( m_mainmenu )
		{
			m_mainmenu.Update(timeslice);
		}

		if (GetGame().GetInput().GetActionDown(UAUIBack, false))
		{
			if (GetGame().GetUIManager().GetMenu() != m_mainmenu)
			{
				GetGame().GetUIManager().Back();
			}
		}
	}
}
