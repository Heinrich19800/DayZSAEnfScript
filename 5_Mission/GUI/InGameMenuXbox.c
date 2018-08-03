class InGameMenuXbox extends UIScriptedMenu
{
	protected ref PlayerListScriptedWidget	m_ServerInfoPanel;
	protected ref PlayerListScriptedWidget	m_FriendsInfoPanel;
	
	protected TabberUI						m_TabScript;
	
	protected Widget						m_OnlineMenu;
	
	const int 								BUTTON_XBOX_CONTROLS = 201;
	
	void InGameMenuXbox()
	{
	}

	void ~InGameMenuXbox()
	{
		ClientData.SyncEvent_OnPlayerListUpdate.Remove( SyncEvent_OnRecievedPlayerList );
		OnlineServices.m_FriendsAsyncInvoker.Remove( OnFriendsUpdate );
		OnlineServices.m_PermissionsAsyncInvoker.Remove( OnPermissionsUpdate );
		
		Mission mission = GetGame().GetMission();
		if ( mission )
		{
			IngameHud hud = IngameHud.Cast( mission.GetHud() );
			if ( hud )
			{
				hud.ToggleHud( g_Game.GetProfileOption( EDayZProfilesOptions.HUD ), true );
			}
		}
		PPEffects.SetBlurMenu( 0 );
	}
	
	override Widget Init()
	{
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets("gui/layouts/xbox/day_z_ingamemenu_xbox.layout");
		m_OnlineMenu	= GetGame().GetWorkspace().CreateWidgets("gui/layouts/xbox/ingamemenu_xbox/online_info_menu.layout", layoutRoot);
		
		
		layoutRoot.FindAnyWidget( "OnlineInfo" ).GetScript( m_TabScript );
		
		m_OnlineMenu.Show( false );
		string version;
		GetGame().GetVersion(version);
		
		Man player = GetGame().GetPlayer();
		bool player_is_alive = false;
		if (player)
		{
			if( player.GetIdentity() && GetGame().IsMultiplayer() )
			{
				OnlineServices.Init( player.GetIdentity().GetPlainId() );
			}
				
			int life_state = player.GetPlayerState();

			if (life_state == EPlayerStates.ALIVE)
			{
				player_is_alive = true;
			}
		}
		
		if( !player_is_alive )
		{
			layoutRoot.FindAnyWidget( "ContinueBtn" ).Show( false );
		}
		
		if( GetGame().IsMultiplayer() )
		{
			layoutRoot.FindAnyWidget( "OnlineBtn" ).Show( true );
			
			m_ServerInfoPanel = new PlayerListScriptedWidget( m_OnlineMenu.FindAnyWidget( "ServerInfoPanel" ), "SERVER PLAYERS" );
			//m_FriendsInfoPanel = new PlayerListScriptedWidget( m_OnlineMenu.FindAnyWidget( "FriendsInfoPanel" ), "FRIENDS" );
			
			//OnlineServices.m_FriendsAsyncInvoker.Insert( OnFriendsUpdate );
			OnlineServices.m_PermissionsAsyncInvoker.Insert( OnPermissionsUpdate );
			ClientData.SyncEvent_OnPlayerListUpdate.Insert( SyncEvent_OnRecievedPlayerList );
			
			m_ServerInfoPanel.Reload( ClientData.m_PlayerList );
			m_ServerInfoPanel.ReloadLocal( OnlineServices.GetMuteList() );
			
			#ifndef PLATFORM_WINDOWS // if app is not on Windows with -XBOX parameter
				//ClientData.m_OnlineServices.LoadFriends();
				ClientData.m_OnlineServices.LoadPermissions( ClientData.GetSimplePlayerList() );
			#endif
			
			TextWidget mute_text = TextWidget.Cast( layoutRoot.FindAnyWidget( "Mute" ).FindAnyWidget( "MuteText" ) );
			
			string uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
			if( uid != "" )
			{
				if( IsLocalPlayer( uid ) || m_ServerInfoPanel.IsEmpty() )
				{
					layoutRoot.FindAnyWidget( "Mute" ).Show( false );
					layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
				}
				else
				{
					layoutRoot.FindAnyWidget( "Mute" ).Show( true );
					layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
					if( OnlineServices.IsPlayerMuted( uid ) )
					{
						mute_text.SetText( "Unmute" );
					}
					else
					{
						mute_text.SetText( "Mute" );
					}
				}
				
				if( m_ServerInfoPanel.IsGloballyMuted( uid ) )
				{
					layoutRoot.FindAnyWidget( "Mute" ).Show( false );
				}
			}
		}
		
		layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
		layoutRoot.FindAnyWidget( "Mute" ).Show( false );
		
		//RESPAWN & RESTART
		ButtonWidget restart_btn = ButtonWidget.Cast( layoutRoot.FindAnyWidgetById( IDC_INT_RETRY ) );
		if (GetGame().IsMultiplayer())
		{
			restart_btn.SetText("#main_menu_respawn");
		}
		else
		{
			restart_btn.SetText("#main_menu_restart");
		}
		
		if ( GetGame().IsMultiplayer() && !( GetGame().CanRespawnPlayer() || ( player && player.IsUnconscious() ) ) )
		{
			restart_btn.Enable( false );
		}
		//
		
	#ifdef BULDOZER
		delete restart_btn;
	#endif
		
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
		case IDC_INT_RETRY:
			if ( GetGame().IsMultiplayer() )
			{
				Respawn();
				
				return true;
			}
			else
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().RestartMission);
			}
			
			return true;
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
			GetGame().GetMission().AbortMission();
			g_Game.CancelQueueTime();	
			
			return true;		
		}
		else if ( code == IDC_INT_EXIT && result == DBB_NO )
		{
			g_Game.CancelQueueTime();
		}
		
		return false;
	}
	
	void Respawn()
	{
		//turns off dead screen, hides HUD for countdown
		//---------------------------------------------------
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if(player)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(player.ShowDeadScreen, DayZPlayerImplement.DEAD_SCREEN_DELAY, false, false);
		}
		
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().RespawnPlayer);
		
		MissionGameplay missionGP = MissionGameplay.Cast(GetGame().GetMission());
		missionGP.DestroyAllMenus();
		//---------------------------------------------------
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().Continue);
	}
	
	bool IsLocalPlayer( string uid )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		string local_uid;
		if( GetGame().GetUserManager() )
			local_uid = GetGame().GetUserManager().GetSelectedUser().GetUid();
		return ( uid == local_uid );
	}
	
	override void Update( float timeslice )
	{
		string uid;
		if( GetGame().IsMultiplayer() && layoutRoot.FindAnyWidget( "OnlineInfo" ).IsVisible() )
		{
			TextWidget mute_text = TextWidget.Cast( layoutRoot.FindAnyWidget( "Mute" ).FindAnyWidget( "MuteText" ) );
			if( GetGame().GetInput().GetActionDown( UAUIUp, false ) )
			{
				if( m_ServerInfoPanel && m_TabScript.GetSelectedIndex() == 0 )
				{
					m_ServerInfoPanel.SetPreviousActive();
					
					uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
					if( uid != "" )
					{
						if( IsLocalPlayer( uid ) || m_ServerInfoPanel.IsEmpty() )
						{
							layoutRoot.FindAnyWidget( "Mute" ).Show( false );
							layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
						}
						else
						{
							layoutRoot.FindAnyWidget( "Mute" ).Show( true );
							layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
							if( OnlineServices.IsPlayerMuted( uid ) )
							{
								mute_text.SetText( "Unmute" );
							}
							else
							{
								mute_text.SetText( "Mute" );
							}
						}
						
						if( m_ServerInfoPanel.IsGloballyMuted( uid ) )
						{
							layoutRoot.FindAnyWidget( "Mute" ).Show( false );
						}
					}
				}
				else if( m_FriendsInfoPanel && m_TabScript.GetSelectedIndex() == 1 )
				{
					m_FriendsInfoPanel.SetPreviousActive();
					
					uid = m_FriendsInfoPanel.FindPlayerByWidget( GetFocus() );
					if( IsLocalPlayer( uid ) || m_FriendsInfoPanel.IsEmpty() )
					{
						layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
					}
					else
					{
						layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
					}
				}
			}
			if( GetGame().GetInput().GetActionDown( UAUIDown, false ) )
			{
				if( m_ServerInfoPanel && m_TabScript.GetSelectedIndex() == 0 )
				{
					m_ServerInfoPanel.SetNextActive();
					
					uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
					if( uid != "" )
					{
						if( IsLocalPlayer( uid ) || m_ServerInfoPanel.IsEmpty() )
						{
							layoutRoot.FindAnyWidget( "Mute" ).Show( false );
							layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
						}
						else
						{
							layoutRoot.FindAnyWidget( "Mute" ).Show( true );
							layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
							if( OnlineServices.IsPlayerMuted( uid ) )
							{
								mute_text.SetText( "Unmute" );
							}
							else
							{
								mute_text.SetText( "Mute" );
							}
						}
						
						if( m_ServerInfoPanel.IsGloballyMuted( uid ) )
						{
							layoutRoot.FindAnyWidget( "Mute" ).Show( false );
						}
					}
				}
				else if( m_FriendsInfoPanel && m_TabScript.GetSelectedIndex() == 1 )
				{
					m_FriendsInfoPanel.SetNextActive();
					
					uid = m_FriendsInfoPanel.FindPlayerByWidget( GetFocus() );
					if( uid == "" )
						return;
					if( IsLocalPlayer( uid ) || m_FriendsInfoPanel.IsEmpty() )
					{
						layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
					}
					else
					{
						layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
					}
				}
			}
			
			if( GetGame().GetInput().GetActionDown( UAUITabLeft, false ) || GetGame().GetInput().GetActionDown( UAUITabRight, false ) )
			{
				m_TabScript.NextTab();
				ToggleInfos();
			}
			
			if( GetGame().GetInput().GetActionDown( UAUIFastEquipOrSplit, false ) )
			{
				bool muted;
				ScriptInputUserData ctx;
				if( m_ServerInfoPanel && m_TabScript.GetSelectedIndex() == 0 )
				{
					uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
					if( uid == "" )
						return;
					if( !IsLocalPlayer( uid ) && !m_ServerInfoPanel.IsGloballyMuted( uid ) )
					{
						muted = OnlineServices.IsPlayerMuted( uid );
						if ( uid != "" && ScriptInputUserData.CanStoreInputUserData() )
						{
							ctx = new ScriptInputUserData;
							ctx.Write( INPUT_UDT_USER_MUTE_XBOX );
							ctx.Write( uid );
							ctx.Write( !muted );
							ctx.Send();
							OnlineServices.MutePlayer( uid, !muted );
							m_ServerInfoPanel.MutePlayer( uid, !muted );
							if( !muted )
							{
								mute_text.SetText( "Unmute" );
							}
							else
							{
								mute_text.SetText( "Mute" );
							}
						}
					}
				}
			}
			
			if( GetGame().GetInput().GetActionDown( UAQuickReload, false ) )
			{
				if( m_TabScript.GetSelectedIndex() == 0 )
				{
					if( m_ServerInfoPanel )
					{
						uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
					}
				}
				else if( m_TabScript.GetSelectedIndex() == 1 )
				{
					if( m_FriendsInfoPanel )
					{
						uid = m_FriendsInfoPanel.FindPlayerByWidget( GetFocus() );
					}
				}
				if( uid == "" )
					return;
				OnlineServices.ShowUserProfile( uid );
			}
		}
		if ( GetGame().GetInput().GetActionDown(UAUIBack, false) )
		{
			//g_Game.CancelQueueTime();
		}
	}
	
	void ToggleInfos()
	{
		if( m_TabScript.GetSelectedIndex() == 1 )
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
		layoutRoot.FindAnyWidget( "Mute" ).Show( false );
		
		if( m_FriendsInfoPanel )
		{
			m_FriendsInfoPanel.FocusFirst();
			
			string uid = m_FriendsInfoPanel.FindPlayerByWidget( GetFocus() );
			if( IsLocalPlayer( uid ) || m_FriendsInfoPanel.IsEmpty() )
			{
				layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
			}
			else
			{
				layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
			}
		}
	}
	
	void SelectServer()
	{
		layoutRoot.FindAnyWidget( "Mute" ).Show( true );
		
		if( m_ServerInfoPanel )
		{
			m_ServerInfoPanel.FocusFirst();
			
			string uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
			if( IsLocalPlayer( uid ) || m_ServerInfoPanel.IsEmpty() )
			{
				layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
				layoutRoot.FindAnyWidget( "Mute" ).Show( false );
			}
			else
			{
				layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
				layoutRoot.FindAnyWidget( "Mute" ).Show( true );
			}
		}
	}
	
	override bool OnItemSelected(Widget w, int x, int y, int row, int column, int oldRow, int oldColumn)
	{
		return false;
	}
	
	void SyncEvent_OnRecievedPlayerList( SyncPlayerList player_list )
	{
		m_ServerInfoPanel.Reload( player_list );
		TextWidget mute_text = TextWidget.Cast( layoutRoot.FindAnyWidget( "Mute" ).FindAnyWidget( "MuteText" ) );
		string uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
		if( uid != "" )
		{
			if( IsLocalPlayer( uid ) || m_ServerInfoPanel.IsEmpty() )
			{
				layoutRoot.FindAnyWidget( "Mute" ).Show( false );
				layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
			}
			else
			{
				layoutRoot.FindAnyWidget( "Mute" ).Show( true );
				layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
				if( OnlineServices.IsPlayerMuted( uid ) )
				{
					mute_text.SetText( "Unmute" );
				}
				else
				{
					mute_text.SetText( "Mute" );
				}
			}
			
			if( m_ServerInfoPanel.IsGloballyMuted( uid ) )
			{
				layoutRoot.FindAnyWidget( "Mute" ).Show( false );
			}
		}
	}
	
	void OnFriendsUpdate( ref BiosFriendInfoArray friend_list )
	{

		m_FriendsInfoPanel.Reload( friend_list );
		string uid = m_FriendsInfoPanel.FindPlayerByWidget( GetFocus() );
		if( uid == "" )
			return;
		if( IsLocalPlayer( uid ) || m_FriendsInfoPanel.IsEmpty() )
		{
			layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
		}
		else
		{
			layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
		}
	}
	
	void OnPermissionsUpdate( BiosPrivacyUidResultArray result_list )
	{
		m_ServerInfoPanel.Reload( result_list );
		
		TextWidget mute_text = TextWidget.Cast( layoutRoot.FindAnyWidget( "Mute" ).FindAnyWidget( "MuteText" ) );
		string uid = m_ServerInfoPanel.FindPlayerByWidget( GetFocus() );
		if( uid != "" )
		{
			if( IsLocalPlayer( uid ) || m_ServerInfoPanel.IsEmpty() )
			{
				layoutRoot.FindAnyWidget( "Mute" ).Show( false );
				layoutRoot.FindAnyWidget( "Gamercard" ).Show( false );
			}
			else
			{
				layoutRoot.FindAnyWidget( "Mute" ).Show( true );
				layoutRoot.FindAnyWidget( "Gamercard" ).Show( true );
				if( OnlineServices.IsPlayerMuted( uid ) )
				{
					mute_text.SetText( "Unmute" );
				}
				else
				{
					mute_text.SetText( "Mute" );
				}
			}
			
			if( m_ServerInfoPanel.IsGloballyMuted( uid ) )
			{
				layoutRoot.FindAnyWidget( "Mute" ).Show( false );
			}
		}
	}
}
