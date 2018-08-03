class OptionsMenuNew extends UIScriptedMenu
{
	protected TabberUI					m_Tabber;
	protected ref OptionsMenuGame		m_GameTab;
	protected ref OptionsMenuSounds		m_SoundsTab;
	protected ref OptionsMenuVideo		m_VideoTab;
	protected ref OptionsMenuControls	m_ControlsTab;
	
	protected ref GameOptions			m_Options;
	
	protected ButtonWidget				m_Apply;
	protected ButtonWidget				m_Back;
	protected ButtonWidget				m_Reset;
	
	protected Widget					m_Details;
	
	void OptionsMenuNew()
	{
		
	}
	
	override Widget Init()
	{
		m_Options			= new GameOptions();
		
		#ifdef PLATFORM_CONSOLE
			layoutRoot		= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/options/xbox/options_menu.layout", null );
		#else
		#ifdef PLATFORM_WINDOWS
			layoutRoot		= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/options/pc/options_menu.layout", null );
		#endif
		#endif
		
		layoutRoot.FindAnyWidget( "Tabber" ).GetScript( m_Tabber );
		
		m_Details			= layoutRoot.FindAnyWidget( "settings_details" );
		
		m_GameTab			= new OptionsMenuGame( layoutRoot.FindAnyWidget( "Tab_0" ), m_Details, m_Options );
		m_SoundsTab			= new OptionsMenuSounds( layoutRoot.FindAnyWidget( "Tab_1" ), m_Details, m_Options );
		
		#ifdef PLATFORM_CONSOLE
			m_ControlsTab	= new OptionsMenuControls( layoutRoot.FindAnyWidget( "Tab_2" ), m_Details, m_Options );
		#else
		#ifdef PLATFORM_WINDOWS
			m_VideoTab		= new OptionsMenuVideo( layoutRoot.FindAnyWidget( "Tab_2" ), m_Details, m_Options );
			m_ControlsTab	= new OptionsMenuControls( layoutRoot.FindAnyWidget( "Tab_3" ), m_Details, m_Options );
		#endif
		#endif
		
		m_Apply				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "apply" ) );
		m_Back				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "back" ) );
		m_Reset				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "reset" ) );
		return layoutRoot;
	}
	
	void ~OptionsMenuNew()
	{
		if( m_Options.IsChanged() )
			g_Game.GetUIManager().ShowDialog("#main_menu_configure", "You have unsaved changes in the configuration. Would you like to discard them?", 1337, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
		m_Options.Revert();
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		if( button == MouseState.LEFT )
		{
			if( w == m_Apply )
			{
				Apply();
				return true;
			}
			else if( w == m_Back )
			{
				Back();
				return true;
			}
			else if( w == m_Reset )
			{
				Reset();
				return true;
			}
		}
		return false;
	}
	
	void Apply()
	{
		m_Options.Test();
		m_Options.Apply();
		
		if( m_Options.NeedRestart() )
			g_Game.GetUIManager().ShowDialog("#main_menu_configure", "#menu_restart_needed", 117, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
	}
	
	void Back()
	{
		if( m_Options.IsChanged() )
			g_Game.GetUIManager().ShowDialog("#main_menu_configure", "You have unsaved changes in the configuration. Would you like to discard them?", 1337, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
		else
		{
			m_Options.Revert();
			GetGame().EndOptionsVideo();
			GetGame().GetUIManager().Back();
		}
	}
	
	void Reset()
	{
		m_Options.Revert();
	}
	
	void SliderFocus()
	{
		layoutRoot.FindAnyWidget( "Toggle" ).Show( false );
	}
	
	void ToggleFocus()
	{
		layoutRoot.FindAnyWidget( "Toggle" ).Show( true );
	}
	
	void ReloadOptions()
	{
		m_Options = new GameOptions();
		if( m_GameTab )
			m_GameTab.SetOptions( m_Options );
		if( m_SoundsTab )
			m_SoundsTab.SetOptions( m_Options );
		if( m_ControlsTab )
			m_ControlsTab.SetOptions( m_Options );
		
		#ifdef PLATFORM_WINDOWS
			if( m_VideoTab )
				m_VideoTab.SetOptions( m_Options );
		#endif
	}
	
	override bool OnModalResult( Widget w, int x, int y, int code, int result )
	{
		if( code == 1337 )
		{
			if( result == 2 )
			{
				m_Options.Revert();
				GetGame().EndOptionsVideo();
				GetGame().GetUIManager().Back();
			}
			return true;
		}
		else if( code == 117 )
		{
			g_Game.RequestRestart(IDC_MAIN_QUIT);
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
		if( x == -1 && y == 1 )
		{
			SliderFocus();
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
		if( x == -1 && y == 2 )
		{
			ToggleFocus();
		}
		return false;
	}
	
	bool IsFocusable( Widget w )
	{
		return ( w == m_Apply || w == m_Back || w == m_Reset );
	}
	
	override void OnShow()
	{
		super.OnShow();
		#ifdef PLATFORM_CONSOLE
			ColorRed( m_Apply );
		#endif
		Refresh();
	}
	
	override void OnHide()
	{
		super.OnHide();
	}
	
	override void Update( float timeslice )
	{
		super.Update( timeslice );
		if( GetGame().GetInput().GetActionDown( UAUITabLeft, false ) )
		{
			m_Tabber.PreviousTab();
		}
		
		//RIGHT BUMPER - TAB RIGHT
		if( GetGame().GetInput().GetActionDown( UAUITabRight, false ) )
		{
			m_Tabber.NextTab();
		}
		
		if( GetGame().GetInput().GetActionDown( UAUIFastEquipOrSplit, false ) )
		{
			Apply();
		}
		
		if( GetGame().GetInput().GetActionDown( UAQuickReload, false ) )
		{
			Reset();
		}
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
	}
	
	void ColorWhite( Widget w, Widget enterW )
	{
		if( w.IsInherited( ButtonWidget ) )
		{
			ButtonWidget button = ButtonWidget.Cast( w );
			button.SetTextColor( ARGB( 255, 255, 255, 255 ) );
			button.SetAlpha( 0.75 );
		}
	}
}