class MainMenuNew extends UIScriptedMenu
{
	protected ref MainMenuNewsfeed	m_Newsfeed;
	protected ref MainMenuStats		m_Stats;
	
	protected MissionMainMenu		m_Mission;
	protected DayZIntroScene 		m_Scene;
	
	protected ButtonWidget			m_PlayerName;
	
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/tabber_prefab/tabber_prefab.layout" );
		return layoutRoot;
	}
	/*
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/main_menu.layout" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "play" ), this, "Play" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "choose_server" ), this, "ChooseServer" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "customize_character" ), this, "CustomizeCharacter" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "stat_button" ), this, "OpenStats" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "message_button" ), this, "OpenMessages" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "settings_button" ), this, "OpenSettings" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "exit_button" ), this, "Exit" );
		
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp( layoutRoot.FindAnyWidget( "news_main" ), this, "OpenNewsMain" );
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp( layoutRoot.FindAnyWidget( "news_sec_1" ), this, "OpenNewsSec1" );
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp( layoutRoot.FindAnyWidget( "news_sec_2" ), this, "OpenNewsSec2" );
		
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp( layoutRoot.FindAnyWidget( "feedback_tracker" ), this, "OpenFeedback" );
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp( layoutRoot.FindAnyWidget( "dayz_forums" ), this, "OpenForums" );
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp( layoutRoot.FindAnyWidget( "twitter" ), this, "OpenTwitter" );
		WidgetEventHandler.GetInstance().RegisterOnMouseButtonUp( layoutRoot.FindAnyWidget( "youtube" ), this, "OpenYoutube" );
		
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "play" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "choose_server" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "customize_character" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "stat_button" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "message_button" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "settings_button" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "exit_button" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "feedback_tracker" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "dayz_forums" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "twitter" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "youtube" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "news_feed_open" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "character_stats_open" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "news_feed_close" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "character_stats_close" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "news_main" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "news_sec_1" ), this, "ColorRed" );
		WidgetEventHandler.GetInstance().RegisterOnMouseEnter( layoutRoot.FindAnyWidget( "news_sec_2" ), this, "ColorRed" );
		
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "play" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "choose_server" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "customize_character" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "stat_button" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "message_button" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "settings_button" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "exit_button" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "feedback_tracker" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "dayz_forums" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "twitter" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "youtube" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "news_feed_open" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "character_stats_open" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "news_feed_close" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "character_stats_close" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "news_main" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "news_sec_1" ), this, "ColorWhite" );
		WidgetEventHandler.GetInstance().RegisterOnMouseLeave( layoutRoot.FindAnyWidget( "news_sec_2" ), this, "ColorWhite" );
		
		m_Newsfeed		= new MainMenuNewsfeed( layoutRoot.FindAnyWidget( "news_feed_root" ) );
		m_Stats			= new MainMenuStats( layoutRoot.FindAnyWidget( "character_stats_root" ) );
		
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "news_feed_open" ), this, "ShowNewsfeed" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "character_stats_open" ), this, "ShowStats" );
		
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "news_feed_close" ), this, "HideNewsfeed" );
		WidgetEventHandler.GetInstance().RegisterOnClick( layoutRoot.FindAnyWidget( "character_stats_close" ), this, "HideStats" );
		
		m_Mission		= MissionMainMenu.Cast( GetGame().GetMission() );
		m_Scene			= m_Mission.GetIntroScene();
		
		m_Scene.m_Camera.LookAt(Vector(m_Scene.m_DemoPos[0],m_Scene.m_DemoPos[1] + 1,m_Scene.m_DemoPos[2]));
		
		m_PlayerName	= ButtonWidget.Cast( layoutRoot.FindAnyWidget("character_name") );
		m_PlayerName.SetText( g_Game.GetPlayerGameName() );
		
		SetFocus( layoutRoot.FindAnyWidget( "play" ) );
		
		LockControls();
		
		return layoutRoot;
	}
	*/
	
	void ~MainMenuNew()
	{
		UnlockControls();
	}
	
	void OnShow()
	{
		LockControls();
		if( m_Scene && m_Scene.m_Camera )
		{
			m_Scene.m_Camera.LookAt(Vector(m_Scene.m_DemoPos[0],m_Scene.m_DemoPos[1] + 1,m_Scene.m_DemoPos[2]));
		}
		
	}
	
	void Play()
	{
		if (m_Scene && m_Scene.m_DemoUnit)
		{
			//saves demounit for further use
			if (m_Scene.m_DemoUnit.GetInventory().FindAttachment(InventorySlots.BODY) && m_Scene.CurrentCharacterID() == -1)
				m_Scene.SetCharacterInfo();
			
			m_Scene.SaveCharName();
			
			if (!g_Game.IsNewCharacter())
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallByName(this, "ConnectLastSession");
			else
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallByName(this, "ConnectBestServer");
		}
	}

	void ChooseServer()
	{
		m_Scene.SaveCharName();
		g_Game.GetUIManager().EnterServerBrowser(this);
		//saves demounit for further use
		if (m_Scene && m_Scene.m_DemoUnit && m_Scene.m_DemoUnit.GetInventory().FindAttachment(InventorySlots.BODY) && m_Scene.CurrentCharacterID() == -1)
			m_Scene.SetCharacterInfo();
	}
	
	void CustomizeCharacter()
	{
		EnterScriptedMenu(MENU_CHARACTER);
	}
	
	void OpenStats()
	{
		
	}
	
	void OpenMessages()
	{
		
	}
	
	void ShowStats()
	{
		m_Stats.ShowStats();
		layoutRoot.FindAnyWidget( "character_stats_open" ).Show( false );
	}
	
	void HideStats()
	{
		layoutRoot.FindAnyWidget( "character_stats_open" ).Show( true );
		m_Stats.HideStats();
	}
	
	void ShowNewsfeed()
	{
		m_Newsfeed.ShowNewsfeed();
		layoutRoot.FindAnyWidget( "news_feed_open" ).Show( false );
	}
	
	void HideNewsfeed()
	{
		m_Newsfeed.HideNewsfeed();
		layoutRoot.FindAnyWidget( "news_feed_open" ).Show( true );
	}
	
	void OpenSettings()
	{
		EnterScriptedMenu(MENU_OPTIONS);
	}
	
	void Exit()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(g_Game.RequestExit, IDC_MAIN_QUIT);
	}
	
	void OpenNewsMain()
	{
		GetGame().OpenURL( "https://dayz.com" );
	}
	
	void OpenNewsSec1()
	{
		GetGame().OpenURL( "https://dayz.com" );
	}
	
	void OpenNewsSec2()
	{
		GetGame().OpenURL( "https://dayz.com" );
	}
	
	void OpenFeedback()
	{
		GetGame().OpenURL( "https://feedback.bistudio.com/tag/dayz" );
	}
	
	void OpenForums()
	{
		GetGame().OpenURL( "https://forums.dayz.com" );
	}
	
	void OpenTwitter()
	{
		GetGame().OpenURL( "https://twitter.com/dayzdevteam" );
	}
	
	void OpenYoutube()
	{
		GetGame().OpenURL( "https://www.youtube.com/user/DayZDevTeam" );
	}
	
	void ConnectLastSession()
	{
		//TODO fix code-side
		if ( !g_Game.ConnectLastSession(this, m_Scene.CurrentCharacterID()) )
		{
			g_Game.GetUIManager().EnterServerBrowser(this);
		}
	}
	
	void ConnectBestServer()
	{
		//TODO add functionality! For now works as follows:
		ConnectLastSession();
	}
	
	//Coloring functions (Until WidgetStyles are useful)
	void ColorRed( Widget w, int x, int y )
	{
		if( w.IsInherited( ButtonWidget ) )
		{
			ButtonWidget button = ButtonWidget.Cast( w );
			button.SetTextColor( ARGB( 255, 255, 0, 0 ) );
			button.SetAlpha( 0.9 );
		}
		
		TextWidget text		= TextWidget.Cast(w.FindWidget( w.GetName() + "_text" ) );
		TextWidget text2	= TextWidget.Cast(w.FindWidget( w.GetName() + "_text_1" ) );
		ImageWidget image	= ImageWidget.Cast( w.FindWidget( w.GetName() + "_image" ) );
		
		if( text )
		{
			text.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		
		if( text2 )
		{
			text2.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		
		if( image )
		{
			image.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
	}
	
	void ColorWhite( Widget w, Widget enterW, int x, int y )
	{
		if( w.IsInherited( ButtonWidget ) )
		{
			ButtonWidget button = ButtonWidget.Cast( w );
			button.SetTextColor( ARGB( 255, 255, 255, 255 ) );
			button.SetAlpha( 0.75 );
		}
		
		TextWidget text		= TextWidget.Cast(w.FindWidget( w.GetName() + "_text" ) );
		TextWidget text2	= TextWidget.Cast(w.FindWidget( w.GetName() + "_text_1" ) );
		ImageWidget image	= ImageWidget.Cast( w.FindWidget( w.GetName() + "_image" ) );
		
		if( text )
		{
			text.SetColor( ARGB( 255, 255, 255, 255 ) );
		}
		
		if( text2 )
		{
			text2.SetColor( ARGB( 255, 255, 255, 255 ) );
		}
		
		if( image )
		{
			image.SetColor( ARGB( 255, 255, 255, 255 ) );
		}
	}
}