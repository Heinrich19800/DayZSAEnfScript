class InGameMenuXbox extends UIScriptedMenu
{
	protected ref PlayerListScriptedWidget	m_ServerInfoPanel;
	protected ref PlayerListScriptedWidget	m_FriendsInfoPanel;
	protected ref AutoHeightSpacer			m_ButtonsSpacer;
	protected Widget						m_OnlineMenu;
	
	const int BUTTON_XBOX_CONTROLS		= 201;
	
	void InGameMenuXbox()
	{
	}

	void ~InGameMenuXbox()
	{
		if( GetGame().IsMultiplayer() )
		{
			ClientData.SyncEvent_OnPlayerListUpdate.Remove( SyncEvent_OnRecievedPlayerList );
			OnlineServices.m_FriendsAsyncInvoker.Remove( OnFriendsUpdate );
			OnlineServices.m_PermissionsAsyncInvoker.Remove( OnPermissionsUpdate );
		}
		
		Mission mission = GetGame().GetMission();
		if ( mission )
		{
			IngameHud hud = IngameHud.Cast( mission.GetHud() );
			if ( hud )
			{
				hud.ToggleHud( true, true );
			}
		}
		PPEffects.SetBlurMenu( 0 );
	}
	
	override Widget Init()
	{
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets("gui/layouts/xbox/day_z_ingamemenu_xbox.layout");
		m_OnlineMenu	= GetGame().GetWorkspace().CreateWidgets("gui/layouts/xbox/ingamemenu_xbox/online_info_menu.layout", layoutRoot);
		
		m_OnlineMenu.FindAnyWidget( "ButtonsFrame" ).GetScript( m_ButtonsSpacer );
		
		m_OnlineMenu.Show( false );
		string version;
		GetGame().GetVersion(version);
		
		Man player = GetGame().GetPlayer();
		bool player_is_alive = false;
		if (player)
		{
			if( player.GetIdentity() && GetGame().IsMultiplayer() )
			{
				OnlineServices.Init( player.GetIdentity().GetId() );
			}
				
			int life_state = player.GetPlayerState();

			if (life_state == EPlayerStates.ALIVE)
			{
				player_is_alive = true;
			}
		}
		
		if( GetGame().IsMultiplayer() )
		{
			AutoHeightSpacer spacer;
			layoutRoot.FindAnyWidget( "CampaignMenuWindow" ).GetScript( spacer );
			layoutRoot.FindAnyWidget( "OnlineBtn" ).Show( true );
			spacer.Update();
			OnlineServices.m_FriendsAsyncInvoker.Insert( OnFriendsUpdate );
			OnlineServices.m_PermissionsAsyncInvoker.Insert( OnPermissionsUpdate );
			
			m_ServerInfoPanel = new PlayerListScriptedWidget( m_OnlineMenu.FindAnyWidget( "ServerInfoPanel" ), "SERVER PLAYERS" );
			m_FriendsInfoPanel = new PlayerListScriptedWidget( m_OnlineMenu.FindAnyWidget( "FriendsInfoPanel" ), "FRIENDS" );
			
			ClientData.SyncEvent_OnPlayerListUpdate.Insert( SyncEvent_OnRecievedPlayerList );
			m_ServerInfoPanel.Reload( ClientData.m_PlayerList );
			
			ClientData.m_OnlineServices.LoadFriends();
			ClientData.m_OnlineServices.LoadPermissions( ClientData.GetSimplePlayerList() );
			
			SelectServer();
		}
		
		/*
		if (GetGame().IsMultiplayer())
		{
			restart_btn.SetText("#main_menu_respawn");
		}
		else
		{
			restart_btn.SetText("#main_menu_restart");
		}

		if (GetGame().IsMultiplayer() && GetGame().CanRespawnPlayer() == false)
		{
			restart_btn.Enable(false);
		}
		
#ifdef BULDOZER
		restart_btn.Destroy();
#endif
		*/
	
		Mission mission = GetGame().GetMission();
		if ( mission )
		{
			IngameHud hud = IngameHud.Cast( mission.GetHud() );
			if ( hud )
			{
				hud.ToggleHud( false, true );
			}
		}
		PPEffects.SetBlurMenu( 0.6 );
	
		return layoutRoot;
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		
		Mission mission = GetGame().GetMission();

		switch (w.GetUserID())
		{
		case IDC_MAIN_CONTINUE:
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().Continue);
			return true;

		case IDC_MAIN_OPTIONS:
			EnterScriptedMenu(MENU_OPTIONS);
			return true;
		break;
			
		case BUTTON_XBOX_CONTROLS:
			EnterScriptedMenu(MENU_XBOX_CONTROLS);
			return true;

		case IDC_MAIN_QUIT:
			GetGame().GetUIManager().ShowDialog("EXIT", "Are you sure you want to exit?", IDC_INT_EXIT, DBT_YESNO, DBB_YES, DMT_QUESTION, NULL);
			return true;
		/*
		case IDC_INT_RETRY:
			if (!GetGame().IsMultiplayer())
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().RestartMission);
			}
			else
			{
				GetGame().GetUIManager().ShowDialog("#main_menu_respawn", "#main_menu_respawn_question", 0, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
			}
			return true;
		*/
		case IDC_MAIN_ONLINE:
			m_OnlineMenu.Show( true );
			layoutRoot.FindAnyWidget( "CampaignMenuLeftPanel" ).Show( false );
			m_ServerInfoPanel.FocusFirst();
			return true;
		}

		return false;
	}
	
	override bool OnModalResult(Widget w, int x, int y, int code, int result)
	{
		super.OnModalResult(w, x, y, code, result);
		
		if ( code == IDC_INT_EXIT && result == DBB_YES )
		{
			if (GetGame().IsMultiplayer())
			{
				GetGame().LogoutRequestTime();
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().CreateLogoutMenu, this);
			}
			else
			{
				// skip logout screen in singleplayer
				GetGame().GetMission().AbortMission();
			}	
			g_Game.CancelQueueTime();	
			return true;	
		
		}
		else if (result == DBB_YES && GetGame().IsMultiplayer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().RespawnPlayer);
			//turns off dead screen, hides HUD for countdown
			//---------------------------------------------------
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if(player) 	
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(player.ShowDeadScreen, DayZPlayerImplement.DEAD_SCREEN_DELAY, false, false);
			}
			
			MissionGameplay missionGP = MissionGameplay.Cast(GetGame().GetMission());
			missionGP.m_hud_root_widget.Show(false);
			//---------------------------------------------------
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().Continue);
			return true;
		}
	
		return false;
	}
	
	bool IsLocalPlayer( string uid )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		string local_uid;
		if( player )
		{
			PlayerIdentity ident = player.GetIdentity();
			if( ident )
			{
				local_uid = ident.GetId();
			}
		}
		
			
		return ( uid == local_uid );
	}
	
	override void Update( float timeslice )
	{
		string uid;
		if( GetGame().IsMultiplayer() )
		{
			if( GetGame().GetInput().GetActionDown( UAUIUp, false ) )
			{
				if( m_ServerInfoPanel && layoutRoot.FindAnyWidget( "ServerInfoPanel" ).IsVisible() )
				{
					m_ServerInfoPanel.SetPreviousActive();
					
					uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
					if( IsLocalPlayer( uid ) )
					{
						layoutRoot.FindAnyWidget( "MuteButtonHelperFrame" ).Show( false );
						layoutRoot.FindAnyWidget( "GamercardButtonHelperFrame" ).Show( false );
					}
					else
					{
						layoutRoot.FindAnyWidget( "MuteButtonHelperFrame" ).Show( true );
						layoutRoot.FindAnyWidget( "GamercardButtonHelperFrame" ).Show( true );
					}
					m_ButtonsSpacer.Update();
				}
			}
	
			if( GetGame().GetInput().GetActionDown( UAUIDown, false ) )
			{
				if( m_ServerInfoPanel && layoutRoot.FindAnyWidget( "ServerInfoPanel" ).IsVisible() )
				{
					m_ServerInfoPanel.SetNextActive();
					
					uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
					if( IsLocalPlayer( uid ) )
					{
						layoutRoot.FindAnyWidget( "MuteButtonHelperFrame" ).Show( false );
						layoutRoot.FindAnyWidget( "GamercardButtonHelperFrame" ).Show( false );
					}
					else
					{
						layoutRoot.FindAnyWidget( "MuteButtonHelperFrame" ).Show( true );
						layoutRoot.FindAnyWidget( "GamercardButtonHelperFrame" ).Show( true );
					}
					m_ButtonsSpacer.Update();
				}
			}
			
			if( GetGame().GetInput().GetActionDown( UAUITabLeft, false ) || GetGame().GetInput().GetActionDown( UAUITabRight, false ) )
			{
				ToggleInfos();
			}
			
			if( GetGame().GetInput().GetActionDown( UAUIFastEquipOrSplit, false ) )
			{
				if( m_ServerInfoPanel )
				{
					uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
					if( !IsLocalPlayer( uid ) )
					{
						bool muted = OnlineServices.IsPlayerMuted( uid );
						if ( uid != "" && ScriptInputUserData.CanStoreInputUserData() )
						{
							ScriptInputUserData ctx = new ScriptInputUserData;
							ctx.Write(INPUT_UDT_USER_MUTE_XBOX);
							ctx.Write( uid );
							ctx.Write( !muted );
							ctx.Send();
						}
					}
				}
			}
			
			if( GetGame().GetInput().GetActionDown( UAUIRadialMenuPick, false ) )
			{
				if( layoutRoot.FindAnyWidget( "ServerInfoPanel" ).IsVisible() )
				{
					if( m_ServerInfoPanel )
					{
						uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
					}
				}
				else if( layoutRoot.FindAnyWidget( "FriendsInfoPanel" ).IsVisible() )
				{
					if( m_FriendsInfoPanel )
					{
						uid = m_FriendsInfoPanel.FindPlayerByWidget( GetFocus() );
					}
				}
				OnlineServices.ShowUserProfile( uid );
			}
		}
		/*
		if( GetGame().GetInput().GetActionDown( UAUIBack, false ) )
		{
			layoutRoot.FindAnyWidget( "CampaignMenuInfoPanel" ).Show( false );
			layoutRoot.FindAnyWidget( "CampaignMenuLeftPanel" ).Show( true );
		}*/
	}
	
	void ToggleInfos()
	{
		if( layoutRoot.FindAnyWidget( "ServerInfoPanel" ).IsVisible() )
		{
			SelectFriends();
		}
		else
		{
			SelectServer();
		}
	}
	
	void SelectFriends()
	{
		layoutRoot.FindAnyWidget( "ServerInfoPanel" ).Show( false );
		layoutRoot.FindAnyWidget( "FriendsInfoPanel" ).Show( true );
		layoutRoot.FindAnyWidget( "ServerTab" ).SetAlpha(0.5);
		layoutRoot.FindAnyWidget( "FriendsTab" ).SetAlpha(1);
		layoutRoot.FindAnyWidget( "MuteButtonHelperFrame" ).Show( false );
		
		if( m_FriendsInfoPanel )
		{
			m_FriendsInfoPanel.FocusFirst();
			
			string uid = m_FriendsInfoPanel.FindPlayerByWidget( GetFocus() );
			if( IsLocalPlayer( uid ) )
			{
				layoutRoot.FindAnyWidget( "GamercardButtonHelperFrame" ).Show( false );
			}
			else
			{
				layoutRoot.FindAnyWidget( "GamercardButtonHelperFrame" ).Show( true );
			}
		}
		m_ButtonsSpacer.Update();
	}
	
	void SelectServer()
	{
		layoutRoot.FindAnyWidget( "FriendsInfoPanel" ).Show( false );
		layoutRoot.FindAnyWidget( "ServerInfoPanel" ).Show( true );
		layoutRoot.FindAnyWidget( "ServerTab" ).SetAlpha(1);
		layoutRoot.FindAnyWidget( "FriendsTab" ).SetAlpha(0.5);
		layoutRoot.FindAnyWidget( "MuteButtonHelperFrame" ).Show( true );
		
		if( m_ServerInfoPanel )
		{
			m_ServerInfoPanel.FocusFirst();
			
			string uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
			if( IsLocalPlayer( uid ) )
			{
				layoutRoot.FindAnyWidget( "GamercardButtonHelperFrame" ).Show( false );
				layoutRoot.FindAnyWidget( "MuteButtonHelperFrame" ).Show( false );
			}
			else
			{
				layoutRoot.FindAnyWidget( "GamercardButtonHelperFrame" ).Show( true );
				layoutRoot.FindAnyWidget( "MuteButtonHelperFrame" ).Show( true );
			}
		}
		
		m_ButtonsSpacer.Update();
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		return false;
	}
	
	void SyncEvent_OnRecievedPlayerList( SyncPlayerList player_list )
	{
		m_ServerInfoPanel.Reload( player_list );
	}
	
	void OnFriendsUpdate( ref BiosFriendInfoArray friend_list )
	{
		m_FriendsInfoPanel.Reload( friend_list );
	}
	
	void OnPermissionsUpdate( BiosPrivacyUidResultArray result_list )
	{
		m_ServerInfoPanel.Reload( result_list );
		m_FriendsInfoPanel.Reload( result_list );
	}
}