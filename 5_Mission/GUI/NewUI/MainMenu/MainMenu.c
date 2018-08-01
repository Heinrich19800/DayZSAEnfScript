class MainMenu extends UIScriptedMenu
{
	protected ref MainMenusfeed	m_Newsfeed;
	protected ref MainMenuStats		m_Stats;
	
	protected MissionMainMenu		m_Mission;
	protected DayZIntroScene 		m_Scene;
	
	protected TextWidget			m_PlayerName;
	protected TextWidget			m_Version;
	
	protected Widget				m_CharacterRotationFrame;
	
	protected Widget				m_Play;
	protected ButtonWidget			m_ChooseServer;
	protected ButtonWidget			m_CustomizeCharacter;
	protected ButtonWidget			m_PlayVideo;
	protected Widget				m_StatButton;
	protected Widget				m_MessageButton;
	protected Widget				m_SettingsButton;
	protected Widget				m_Exit;
	protected Widget				m_NewsFeedOpen;
	protected Widget				m_NewsFeedClose;
	protected Widget				m_CharacterStatsOpen;
	protected Widget				m_CharacterStatsClose;
	protected Widget				m_NewsMain;
	protected Widget				m_NewsSec1;
	protected Widget				m_NewsSec2;
	protected Widget				m_PrevCharacter;
	protected Widget				m_NextCharacter;
	
	protected VideoWidget			m_Video;
	protected ref Timer				m_VideoPlayTimer;
	protected ref WidgetFadeTimer	m_VideoFadeTimer;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/main_menu.layout" );
		
		m_Play						= layoutRoot.FindAnyWidget( "play" );
		m_ChooseServer				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "choose_server" ) );
		m_CustomizeCharacter		= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "customize_character" ) );
		m_PlayVideo					= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "play_video" ) );
		m_StatButton				= layoutRoot.FindAnyWidget( "stat_button" );
		m_MessageButton				= layoutRoot.FindAnyWidget( "message_button" );
		m_SettingsButton			= layoutRoot.FindAnyWidget( "settings_button" );
		m_Exit						= layoutRoot.FindAnyWidget( "exit_button" );
		m_NewsFeedOpen				= layoutRoot.FindAnyWidget( "news_feed_open" );
		m_NewsFeedClose				= layoutRoot.FindAnyWidget( "news_feed_close" );
		m_CharacterStatsOpen		= layoutRoot.FindAnyWidget( "character_stats_open" );
		m_CharacterStatsClose		= layoutRoot.FindAnyWidget( "character_stats_close" );
		m_PrevCharacter				= layoutRoot.FindAnyWidget( "prev_character" );
		m_NextCharacter				= layoutRoot.FindAnyWidget( "next_character" );
		
		m_Video						= VideoWidget.Cast( layoutRoot.FindAnyWidget( "video" ) );

		m_Version					= TextWidget.Cast( layoutRoot.FindAnyWidget( "version" ) );
		m_CharacterRotationFrame	= layoutRoot.FindAnyWidget( "character_rotation_frame" );
			
		m_Newsfeed					= new MainMenusfeed( layoutRoot.FindAnyWidget( "news_feed_root" ) );
		m_Stats						= new MainMenuStats( layoutRoot.FindAnyWidget( "character_stats_root" ) );
		
		m_Mission					= MissionMainMenu.Cast( GetGame().GetMission() );
		m_Scene						= m_Mission.GetIntroScene();
		
		if( m_Scene && m_Scene.m_Camera && m_Scene.m_DemoPos )
		{
			m_Scene.m_Camera.LookAt(Vector(m_Scene.m_DemoPos[0],m_Scene.m_DemoPos[1] + 1,m_Scene.m_DemoPos[2]));
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( m_Scene.SceneCharacterSetPos, 250 );
		}
		
		m_PlayerName				= TextWidget.Cast( layoutRoot.FindAnyWidget("character_name_text") );
		
		#ifdef PLATFORM_XBOX
			m_PlayerName			= TextWidget.Cast( layoutRoot.FindAnyWidget("character_name_xbox") );
			//m_VideoPlayTimer		= new Timer();
			//m_VideoFadeTimer		= new WidgetFadeTimer();
			layoutRoot.FindAnyWidget( "character_name_xbox_background" ).Show( true );
			layoutRoot.FindAnyWidget( "settings_panel_root" ).Show( false );
			layoutRoot.FindAnyWidget( "ConsoleToolbar" ).Show( true );
			layoutRoot.FindAnyWidget( "character" ).Show( false );
			layoutRoot.FindAnyWidget( "news_feed_root" ).Show( false );
			//m_PlayVideo.Show( true );
			m_CustomizeCharacter.SetText( "OPTIONS" );
			m_ChooseServer.SetText( "CONTROLS" );
		#endif
		
		Refresh();
		
		string version;
		GetGame().GetVersion( version );
		if( version != "" )
			m_Version.SetText( "#main_menu_version" + " " + version );
		else
			m_Version.Show( false );
		
		GetGame().GetUIManager().ScreenFadeOut(0);

		#ifdef PLATFORM_XBOX
			ColorRed( m_Play );
		#else
			SetFocus( layoutRoot );
		#endif
		
		return layoutRoot;
	}
	
	void ~MainMenu()
	{
	}
	
	override bool OnMouseButtonDown( Widget w, int x, int y, int button )
	{
		if ( w == m_CharacterRotationFrame )
		{
			if (m_Scene)
				m_Scene.CharacterRotationStart();
			return true;
		}
		return false;
	}
	
	override bool OnMouseButtonUp( Widget w, int x, int y, int button )
	{
		if (m_Scene)
			m_Scene.CharacterRotationStop();
		return false;
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		if( button == MouseState.LEFT )
		{
			if( w == m_Play )
			{
				Play();
				return true;
			}
			else if ( w == m_ChooseServer )
			{
				ChooseServer();
				return true;
			}
			else if ( w == m_CustomizeCharacter )
			{
				#ifdef PLATFORM_XBOX
					OpenSettings();
				#else
					CustomizeCharacter();
				#endif
				return true;
			}
			else if ( w == m_StatButton )
			{
				OpenStats();
				return true;
			}
			else if ( w == m_MessageButton )
			{
				OpenMessages();
				return true;
			}
			else if ( w == m_SettingsButton )
			{
				OpenSettings();
				return true;
			}
			else if ( w == m_Exit )
			{
				Exit();
				return true;
			}
			else if ( w == m_PrevCharacter )
			{
				PreviousCharacter();
				return true;
			}
			else if ( w == m_NextCharacter )
			{
				NextCharacter();
				return true;
			}
			else if ( w == m_NewsFeedOpen )
			{
				ShowNewsfeed();
				return true;
			}
			else if ( w == m_NewsFeedClose )
			{
				HideNewsfeed();
				return true;
			}
			else if ( w == m_CharacterStatsOpen )
			{
				ShowStats();
				return true;
			}
			else if ( w == m_CharacterStatsClose )
			{
				HideStats();
				return true;
			}
			else if ( w == m_PlayVideo )
			{
				PlayVideo();
				return true;
			}
		}
		return false;
	}
	
	override bool OnMouseEnter( Widget w, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorRed( w );
			return true;
		}
		return false;
	}
	
	override bool OnMouseLeave( Widget w, Widget enterW, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorWhite( w, enterW );
			return true;
		}
		return false;
	}
	
	override bool OnFocus( Widget w, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorRed( w );
			return true;
		}
		return false;
	}
	
	override bool OnFocusLost( Widget w, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorWhite( w, null );
			return true;
		}
		return false;
	}
	
	bool IsFocusable( Widget w )
	{
		if( w == m_Play || w == m_ChooseServer || w == m_CustomizeCharacter || w == m_StatButton || w == m_MessageButton || w == m_SettingsButton );
			return true;
		if( w == m_Exit || w == m_NewsFeedOpen || w == m_NewsFeedClose || m_PlayVideo );
			return true;
		if( w == m_CharacterStatsOpen || w == m_CharacterStatsClose || w == m_NewsMain || w == m_NewsSec1 || w == m_NewsSec2 || w == m_PrevCharacter || w == m_NextCharacter );
			return true;
		return false;
	}
	
	override void Refresh()
	{
		string name;
		
		#ifdef PLATFORM_XBOX
			if( GetGame().GetUserManager() && GetGame().GetUserManager().GetSelectedUser() )
			{
				name = GetGame().GetUserManager().GetSelectedUser().GetName();
				if( name.LengthUtf8() > 18 )
				{
					name = name.SubstringUtf8(0, 18);
					name += "...";
				}
			}
		#else
			g_Game.GetPlayerNameShort( 14, name );
		#endif
		
		m_PlayerName.SetText( name );
	}
	
	override void OnShow()
	{
		#ifdef PLATFORM_XBOX
			ColorRed( m_Play );
		#else
			SetFocus( layoutRoot );
		#endif
		Refresh();
		
		if( m_Scene && m_Scene.m_Camera )
		{
			m_Scene.m_Camera.LookAt(Vector(m_Scene.m_DemoPos[0],m_Scene.m_DemoPos[1] + 1,m_Scene.m_DemoPos[2]));
		}
	}
	
	override void OnHide()
	{
		//super.OnHide();
	}

#ifdef PLATFORM_XBOX
	override void Update(float timeslice)
	{
			if ( GetGame().GetInput().GetActionDown(UAUIBack, false) )
			{
				g_Game.SetLoadState( DayZLoadState.MAIN_MENU_START );
				GetGame().GetInput().ResetActiveGamepad();
			}
	}
#endif
	
	void Play()
	{
		if (m_Scene && m_Scene.m_DemoUnit)
		{
			//saves demounit for further use
			if (m_Scene.m_DemoUnit.GetInventory().FindAttachment(InventorySlots.BODY) && m_Scene.CurrentCharacterID() == -1)
				m_Scene.SetCharacterInfo();
			
			m_Scene.SaveCharName();
		}
		if (!g_Game.IsNewCharacter())
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallByName(this, "ConnectLastSession");
		else
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallByName(this, "ConnectBestServer");
	}

	void ChooseServer()
	{
		#ifdef PLATFORM_XBOX
			EnterScriptedMenu( MENU_XBOX_CONTROLS );
			return;
		#endif
		
		if( m_Scene )
			m_Scene.SaveCharName();
		
		#ifdef NEW_UI
			EnterScriptedMenu(MENU_SERVER_BROWSER);
		#else
			g_Game.GetUIManager().EnterServerBrowser(this);
		#endif
		
		//saves demounit for further use
		if (m_Scene && m_Scene.m_DemoUnit && m_Scene.m_DemoUnit.GetInventory().FindAttachment(InventorySlots.BODY) && m_Scene.CurrentCharacterID() == -1)
			m_Scene.SetCharacterInfo();
	}
	
	void CustomizeCharacter()
	{
		EnterScriptedMenu(MENU_CHARACTER);
	}
	
	void NextCharacter()
	{
		m_Scene.SaveCharName();
		m_Scene.ChangeCharacter( m_Scene.NextCharacterID() );
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( m_Scene.SceneCharacterSetPos, 250 );
		m_PlayerName.SetText( g_Game.GetPlayerGameName() );
	}
	
	void PreviousCharacter()
	{
		m_Scene.SaveCharName();
		m_Scene.ChangeCharacter( m_Scene.PrevCharacterID() );
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( m_Scene.SceneCharacterSetPos, 250 );
		m_PlayerName.SetText( g_Game.GetPlayerGameName() );
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
		m_CharacterStatsOpen.Show( false );
	}
	
	void HideStats()
	{
		m_CharacterStatsOpen.Show( true );
		m_Stats.HideStats();
	}
	
	void ShowNewsfeed()
	{
		m_Newsfeed.ShowNewsfeed();
		m_NewsFeedOpen.Show( false );
	}
	
	void HideNewsfeed()
	{
		m_Newsfeed.HideNewsfeed();
		m_NewsFeedOpen.Show( true );
	}
	
	void OpenSettings()
	{
		EnterScriptedMenu(MENU_OPTIONS);
	}
	
	void PlayVideo()
	{
		//m_Video.LoadVideo( "", 0 ); //TODO get video id
		//m_Video.Play( VideoCommand.REWIND );
		//m_Video.Play( VideoCommand.PLAY );
		time_tt = 0;
		m_Video.Show( true );
		m_VideoFadeTimer.FadeIn( m_Video, 1.5 );
		m_VideoPlayTimer.Run( 0.1, this, "PlayVideoLoop", null, true );
		Print( "Starting" );
	}
	
	float time_tt;
	void PlayVideoLoop()
	{/*
		if( !m_Video.Play( VideoCommand.ISPLAYING ) )
		{
			m_VideoPlayTimer.Stop();
			m_VideoFadeTimer.FadeOut( m_Video, 1.5 );
		}*/
		time_tt += 0.1;
		Print( "Time " + time_tt );
		if( time_tt >= 5 )
		{
			m_Video.Show( false );
			Print( "Stopping" );
			m_VideoPlayTimer.Stop();
			m_VideoFadeTimer.FadeOut( m_Video, 1.5 );
		}
	}
	
	void Exit()
	{
		GetGame().GetUIManager().ShowDialog("EXIT", "Are you sure you want to exit?", IDC_MAIN_QUIT, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
	}
	
	void ConnectLastSession()
	{
		//TODO fix code-side
		if ( m_Scene /*&& !g_Game.ConnectLastSession(this, m_Scene.CurrentCharacterID())*/ )
		{
			#ifdef NEW_UI
				EnterScriptedMenu(MENU_SERVER_BROWSER);
			#else
				#ifdef PLATFORM_XBOX
					EnterScriptedMenu(MENU_SERVER_BROWSER);
				#else
					g_Game.GetUIManager().EnterServerBrowser(this);
				#endif
			#endif
		}
		else
		{
			EnterScriptedMenu(MENU_SERVER_BROWSER);
		}
	}
	
	void ConnectBestServer()
	{
		//TODO add functionality! For now works as follows:
		ConnectLastSession();
	}
	
	//Coloring functions (Until WidgetStyles are useful)
	void ColorRed( Widget w )
	{
		SetFocus( w );
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
	
	void ColorWhite( Widget w, Widget enterW )
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
	
	override bool OnModalResult( Widget w, int x, int y, int code, int result )
	{
		if( code == IDC_MAIN_QUIT )
		{
			if( result == 2 )
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(g_Game.RequestExit, IDC_MAIN_QUIT);
			#ifdef PLATFORM_WINDOWS
			if( result == 3 )
				ColorWhite( GetFocus(), null );
			#endif
			return true;
		}
		return false;
	}
}