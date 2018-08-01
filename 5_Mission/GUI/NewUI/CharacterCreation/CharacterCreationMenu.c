class CharacterCreationMenu extends UIScriptedMenu
{
	DayZIntroScene							m_Scene;
	
	protected Widget						m_CharacterRotationFrame;
	protected Widget						m_Apply;
	protected Widget						m_RandomizeCharacter;
	protected Widget						m_BackButton;
	
	protected EditBoxWidget					m_PlayerName;
	protected TextWidget					m_Version;
	
	protected ref OptionSelectorMultistate	m_GenderSelector;
	protected ref OptionSelectorMultistate	m_SkinSelector;
	protected ref OptionSelectorMultistate	m_TopSelector;
	protected ref OptionSelectorMultistate	m_BottomSelector;
	protected ref OptionSelectorMultistate	m_ShoesSelector;
	
	void CharacterCreationMenu()
	{
		MissionMainMenu mission = MissionMainMenu.Cast( GetGame().GetMission() );
		
		m_Scene = mission.GetIntroScene();
		m_Scene.m_Camera.LookAt( Vector( m_Scene.m_DemoPos[0], m_Scene.m_DemoPos[1] + 1, m_Scene.m_DemoPos[2] ) );
	}
	
	override Widget Init()
	{
		layoutRoot							= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/character_creation.layout" );
		
		m_CharacterRotationFrame			= layoutRoot.FindAnyWidget( "character_rotation_frame" );
		m_Apply								= layoutRoot.FindAnyWidget( "apply" );
		m_RandomizeCharacter				= layoutRoot.FindAnyWidget( "randomize_character" );
		m_BackButton						= layoutRoot.FindAnyWidget( "back" );
		
		m_PlayerName						= EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "general_name_setting_text" ) );
		m_Version							= TextWidget.Cast( layoutRoot.FindAnyWidget( "version" ) );
		
		Refresh();
		
		string version;
		GetGame().GetVersion( version );
		if( version != "" )
			m_Version.SetText( "#main_menu_version" + " " + version );
		else
			m_Version.Show( false );
		
		m_GenderSelector					= new OptionSelectorMultistate( layoutRoot.FindAnyWidget( "character_gender_setting_option" ), 0, null, false, m_Scene.m_genderList );
		if ( m_Scene.m_female )
		{
			m_GenderSelector.SetValue( "Female" );
			m_SkinSelector	= new OptionSelectorMultistate( layoutRoot.FindAnyWidget( "character_head_setting_option" ), 0, null, false, m_Scene.m_personalityFemaleList );
		}
		else
		{
			m_GenderSelector.SetValue( "Male" );
			m_SkinSelector	= new OptionSelectorMultistate( layoutRoot.FindAnyWidget( "character_head_setting_option" ), 0, null, false, m_Scene.m_personalityMaleList );
		}
		
		m_TopSelector						= new OptionSelectorMultistate( layoutRoot.FindAnyWidget( "character_top_setting_option" ), 0, null, false, m_Scene.m_shirtList );
		m_BottomSelector					= new OptionSelectorMultistate( layoutRoot.FindAnyWidget( "character_bottom_setting_option" ), 0, null, false, m_Scene.m_pantsList );
		m_ShoesSelector						= new OptionSelectorMultistate( layoutRoot.FindAnyWidget( "character_shoes_setting_option" ), 0, null, false, m_Scene.m_shoesList );
		
		if( m_Scene && m_Scene.m_DemoUnit )
		{
			Object obj = m_Scene.m_DemoUnit.GetInventory().FindAttachment(InventorySlots.BODY);
			if( obj )
				m_TopSelector.SetValue( obj.GetType() );
			
			obj = m_Scene.m_DemoUnit.GetInventory().FindAttachment(InventorySlots.LEGS);
			if( obj )
				m_BottomSelector.SetValue( obj.GetType() );
			
			obj = m_Scene.m_DemoUnit.GetInventory().FindAttachment(InventorySlots.FEET);
			if( obj )
				m_ShoesSelector.SetValue( obj.GetType() );
			
			m_SkinSelector.SetValue( m_Scene.m_DemoUnit.GetType() );
		}
		
		m_GenderSelector.m_OptionChanged.Insert( GenderChanged );
		m_SkinSelector.m_OptionChanged.Insert( SkinChanged );
		m_TopSelector.m_OptionChanged.Insert( TopChanged );
		m_BottomSelector.m_OptionChanged.Insert( BottomChanged );
		m_ShoesSelector.m_OptionChanged.Insert( ShoesChanged );
		
		return layoutRoot;
	}
	
	void ~CharacterCreationMenu()
	{
		m_GenderSelector.m_OptionChanged.Remove( GenderChanged );
		m_SkinSelector.m_OptionChanged.Remove( SkinChanged );
		m_TopSelector.m_OptionChanged.Remove( TopChanged );
		m_BottomSelector.m_OptionChanged.Remove( BottomChanged );
		m_ShoesSelector.m_OptionChanged.Remove( ShoesChanged );
	}
	
	//Button Events
	void Apply()
	{
		g_Game.SetPlayerGameName( m_PlayerName.GetText() );
		m_Scene.SetCharacterInfo();
		m_Scene.SaveCharName();
		m_Scene.SaveDefaultCharacter();
		SetCharacter();
		GetGame().GetUIManager().Back();
	}
	
	void SetCharacter()
	{
		if (m_Scene.m_DemoUnit)
		{
			m_PlayerName.SetText( g_Game.GetPlayerGameName() );
			
			m_Scene.SetAttachment( m_TopSelector.GetStringValue(), InventorySlots.BODY );
			m_Scene.SetAttachment( m_BottomSelector.GetStringValue(), InventorySlots.LEGS );
			m_Scene.SetAttachment( m_ShoesSelector.GetStringValue(), InventorySlots.FEET );
			
			if (g_Game.IsNewCharacter())
			{
				m_Scene.SetAttachment("", InventorySlots.SHOULDER);
				m_Scene.SetAttachment("", InventorySlots.BOW);
				m_Scene.SetAttachment("", InventorySlots.MELEE);
				m_Scene.SetAttachment("", InventorySlots.VEST);
				m_Scene.SetAttachment("", InventorySlots.HIPS);
				m_Scene.SetAttachment("", InventorySlots.BACK);
				m_Scene.SetAttachment("", InventorySlots.HEADGEAR);
				m_Scene.SetAttachment("", InventorySlots.MASK);
				m_Scene.SetAttachment("", InventorySlots.EYEWEAR);
				m_Scene.SetAttachment("", InventorySlots.GLOVES);
				m_Scene.SetAttachment("", InventorySlots.ARMBAND);
				m_Scene.SetAttachment("", InventorySlots.HANDS);
			}
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( m_Scene.SceneCharacterSetPos, 250 );
		}
	}
	
	void RandomizeCharacter()
	{
		g_Game.SetNewCharacter(true);
		
		m_Scene.m_currentCharacterID = -1;
		
		// make random selection
		m_Scene.RandomSelectGender();
		
		if ( m_Scene.m_female )
		{
			m_GenderSelector.SetValue( "Female" );
			m_SkinSelector.LoadNewValues( m_Scene.m_personalityFemaleList, 0 );
			m_SkinSelector.SetRandomValue();
		}
		else
		{
			m_GenderSelector.SetValue( "Male" );
			m_SkinSelector.LoadNewValues( m_Scene.m_personalityMaleList, 0 );
			m_SkinSelector.SetRandomValue();
		}
		
		m_TopSelector.SetRandomValue();
		m_BottomSelector.SetRandomValue();
		m_ShoesSelector.SetRandomValue();
		
		SetCharacter();
		
		CheckNewOptions();
	}
	
	//Selector Events
	void GenderChanged()
	{
		m_Scene.m_female = ( m_GenderSelector.GetStringValue() == "Female" );
		
		if ( m_Scene.m_female )
		{
			m_SkinSelector.LoadNewValues( m_Scene.m_personalityFemaleList, 0 );
			m_SkinSelector.SetRandomValue();
		}
		else
		{
			m_SkinSelector.LoadNewValues( m_Scene.m_personalityMaleList, 0 );
			m_SkinSelector.SetRandomValue();
		}
	}
	
	void SkinChanged()
	{
		m_Scene.CreateNewCharacter( m_SkinSelector.GetStringValue() );
		
		layoutRoot.FindAnyWidget( "character_root" ).Show( g_Game.IsNewCharacter() );
		
		TopChanged();
		BottomChanged();
		ShoesChanged();
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( m_Scene.SceneCharacterSetPos, 100 );
	}
	
	void TopChanged()
	{
		m_Scene.SetAttachment( m_TopSelector.GetStringValue(), InventorySlots.BODY );
	}
	
	void BottomChanged()
	{
		m_Scene.SetAttachment( m_BottomSelector.GetStringValue(), InventorySlots.LEGS );
	}
	
	void ShoesChanged()
	{
		m_Scene.SetAttachment( m_ShoesSelector.GetStringValue(), InventorySlots.FEET );
	}
	
	override bool OnKeyPress( Widget w, int x, int y, int key )
	{
		super.OnKeyPress( w, x, y, key );
		return false;
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		if( w == m_Apply )
		{
			Apply();
			return true;
		}
		else if ( w == m_RandomizeCharacter )
		{
			RandomizeCharacter();
			return true;
		}
		else if ( w == m_BackButton )
		{
			GetGame().GetUIManager().Back();
			return true;
		}
		return false;
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
		return ( w == m_Apply || w == m_RandomizeCharacter || w == m_BackButton );
	}
	
	void CheckNewOptions()
	{
		layoutRoot.FindAnyWidget( "character_gender_button" ).Show( g_Game.IsNewCharacter() );
		layoutRoot.FindAnyWidget( "character_head_button" ).Show( g_Game.IsNewCharacter() );
		layoutRoot.FindAnyWidget( "character_top_button" ).Show( g_Game.IsNewCharacter() );
		layoutRoot.FindAnyWidget( "character_bottom_button" ).Show( g_Game.IsNewCharacter() );
		layoutRoot.FindAnyWidget( "character_shoes_button" ).Show( g_Game.IsNewCharacter() );
	}
	
	override void OnShow()
	{
		SetFocus( m_Apply );
		CheckNewOptions();
		
		if( m_Scene && m_Scene.m_Camera )
		{
			m_Scene.m_Camera.LookAt( Vector( m_Scene.m_DemoPos[0],m_Scene.m_DemoPos[1] + 1,m_Scene.m_DemoPos[2] ) );
		}
	}
	
	override void Refresh()
	{
		string name;
		#ifdef PLATFORM_CONSOLE
			if( GetGame().GetUserManager() && GetGame().GetUserManager().GetSelectedUser() )
			{
				name = GetGame().GetUserManager().GetSelectedUser().GetName();
				if( name.LengthUtf8() > 16 )
				{
					name = name.SubstringUtf8(0, 16);
					name += "...";
				}
			}
		#else
			g_Game.GetPlayerNameShort( 14, name );
		#endif
		
		m_PlayerName.SetText( name );
	}
	
	override void OnHide()
	{
		//super.OnHide();
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
}