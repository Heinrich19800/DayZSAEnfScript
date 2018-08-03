#ifdef PLATFORM_CONSOLE
	static int	X_AXIS_OPTION_VALUE = AT_CONFIG_CONTROLLER_XAXIS;
	static int	Y_AXIS_OPTION_VALUE = AT_CONFIG_CONTROLLER_YAXIS;
	static int	INVERT_LOOK_VALUE	= AT_CONFIG_CONTROLLER_REVERSED_LOOK;
#else
#ifdef PLATFORM_WINDOWS
	static int	X_AXIS_OPTION_VALUE = AT_CONFIG_XAXIS;
	static int	Y_AXIS_OPTION_VALUE = AT_CONFIG_YAXIS;
	static int	INVERT_LOOK_VALUE	= AT_CONFIG_YREVERSED;
#endif
#endif

class OptionsMenuControls extends ScriptedWidgetEventHandler
{
	protected Widget						m_Root;
	
	protected Widget						m_SettingsRoot;
	protected Widget						m_DetailsRoot;
	protected TextWidget					m_DetailsLabel;
	protected RichTextWidget				m_DetailsText;
	
	protected GameOptions					m_Options;
	protected ref NumericOptionsAccess		m_VSensitivityOption;
	protected ref NumericOptionsAccess		m_HSensitivityOption;
	protected ref SwitchOptionsAccess		m_InvertOption;
	
	protected ref OptionSelectorSlider		m_VSensitivitySelector;
	protected ref OptionSelectorSlider		m_HSensitivitySelector;
	protected ref OptionSelectorMultistate	m_InvertSelector;
	
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	
	void OptionsMenuControls( Widget parent, Widget details_root, GameOptions options )
	{
		#ifdef PLATFORM_CONSOLE
			m_Root					= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/options/xbox/controls_tab.layout", parent );
		#else
		#ifdef PLATFORM_WINDOWS
			m_Root					= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/options/pc/controls_tab.layout", parent );
		#endif
		#endif
		
		m_DetailsRoot			= details_root;
		m_DetailsLabel			= TextWidget.Cast( m_DetailsRoot.FindAnyWidget( "details_label" ) );
		m_DetailsText			= RichTextWidget.Cast( m_DetailsRoot.FindAnyWidget( "details_content" ) );
		
		m_Options 				= options;
		
		m_VSensitivityOption	= NumericOptionsAccess.Cast( m_Options.GetOptionByType( X_AXIS_OPTION_VALUE ) );
		m_HSensitivityOption	= NumericOptionsAccess.Cast( m_Options.GetOptionByType( Y_AXIS_OPTION_VALUE ) );
		m_InvertOption			= SwitchOptionsAccess.Cast( m_Options.GetOptionByType( INVERT_LOOK_VALUE ) );
		
		m_Root.FindAnyWidget( "vsensitivity_setting_option" ).SetUserID( X_AXIS_OPTION_VALUE );
		m_Root.FindAnyWidget( "hsensitivity_setting_option" ).SetUserID( Y_AXIS_OPTION_VALUE );
		m_Root.FindAnyWidget( "invert_setting_option" ).SetUserID( INVERT_LOOK_VALUE );

		ref array<string> opt	= { "Disabled", "Enabled" };
	
		m_VSensitivitySelector	= new OptionSelectorSlider( m_Root.FindAnyWidget( "vsensitivity_setting_option" ), m_VSensitivityOption.ReadValue(), this, false, m_VSensitivityOption.GetMin(), m_VSensitivityOption.GetMax() );
		m_HSensitivitySelector	= new OptionSelectorSlider( m_Root.FindAnyWidget( "hsensitivity_setting_option" ), m_HSensitivityOption.ReadValue(), this, false, m_HSensitivityOption.GetMin(), m_HSensitivityOption.GetMax() );
		m_InvertSelector		= new OptionSelectorMultistate( m_Root.FindAnyWidget( "invert_setting_option" ), m_InvertOption.GetIndex(), this, false, opt );
		
		m_VSensitivitySelector.m_OptionChanged.Insert( UpdateVerticalSensitivity );
		m_HSensitivitySelector.m_OptionChanged.Insert( UpdateHorizontalSensitivity );
		m_InvertSelector.m_OptionChanged.Insert( UpdateInvertView );
		
		FillTextMap();
	}
	
	override bool OnFocus( Widget w, int x, int y )
	{
		OptionsMenuNew menu = OptionsMenuNew.Cast( GetGame().GetUIManager().GetMenu() );
		if( menu )
			menu.OnFocus( w, x, y );
		if( w )
		{
			Param2<string, string> p = m_TextMap.Get( w.GetUserID() );
			if( p )
			{
				m_DetailsRoot.Show( true );
				m_DetailsLabel.SetText( p.param1 );
				m_DetailsText.SetText( p.param2 );
				int sx, sy;
				float lines = m_DetailsText.GetContentHeight();
				m_DetailsText.SetSize( 1, lines );
				return true;
			}
		}
		m_DetailsRoot.Show( false );
		return ( w != null );
	}
	
	void UpdateVerticalSensitivity( float value )
	{
		m_VSensitivityOption.WriteValue( value );
	}
	
	void UpdateHorizontalSensitivity( float value )
	{
		m_HSensitivityOption.WriteValue( value );
	}
	
	void UpdateInvertView( int index )
	{
		m_InvertOption.Switch();
	}
	
	void ReloadOptions()
	{
		OptionsMenuNew menu = OptionsMenuNew.Cast( GetGame().GetUIManager().GetMenu() );
		if( menu )
			menu.ReloadOptions();
	}
	
	void SetOptions( GameOptions options )
	{
		m_Options = options;
	}
	
	void FillTextMap()
	{
		m_TextMap = new map<int, ref Param2<string, string>>;
		m_TextMap.Insert( X_AXIS_OPTION_VALUE, new Param2<string, string>( "Vertical Sensitivity", "Sets the turn rate of looking up and down." ) );
		m_TextMap.Insert( Y_AXIS_OPTION_VALUE, new Param2<string, string>( "Horizontal Sensitivity", "Sets the turn rate of looking left and right." ) );
		m_TextMap.Insert( INVERT_LOOK_VALUE, new Param2<string, string>( "Invert Vertical View", "Inverts the input for looking up and down." ) );
	}
}