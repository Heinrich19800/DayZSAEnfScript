class TestPage extends UIScriptedMenu
{
	ref ServerBrowserTab m_OfficialTab;
	ref ServerBrowserTab m_CommunityTab;
	ref ServerBrowserTab m_LANTab;
	
	Widget Init()
	{
		PPEffects.SetBlur( 0.6 );
		
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/server_browser/server_browser.layout" );
		m_OfficialTab	= new ServerBrowserTab( layoutRoot.FindAnyWidget( "Tab_0" ) );
		m_CommunityTab	= new ServerBrowserTab( layoutRoot.FindAnyWidget( "Tab_1" ) );
		m_LANTab		= new ServerBrowserTab( layoutRoot.FindAnyWidget( "Tab_2" ) );
		
		return layoutRoot;
	}
}

class ServerBrowserTab extends ScriptedWidgetEventHandler
{
	protected Widget					m_Root;
	ref array<ref ServerBrowserEntry>	m_Entries;
	
	void ServerBrowserTab( Widget parent )
	{
		m_Root		= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/server_browser/server_browser_tab.layout", parent );
		
		m_Entries = new array<ref ServerBrowserEntry>;
		
		for( int i = 0; i <= 100; i++ )
		{
			m_Entries.Insert( new ServerBrowserEntry( m_Root.FindAnyWidget( "server_list_content" ) ) );
		}
	}
}

class ServerBrowserEntry extends ScriptedWidgetEventHandler
{
	protected Widget			m_Root;
	protected CheckBoxWidget	m_Favorite;
	protected ButtonWidget		m_Expand;
	
	protected bool				m_IsExpanded;
	protected bool				m_IsFavorited;
	
	void ServerBrowserEntry( Widget parent )
	{
		m_Root		= GetGame().GetWorkspace().CreateWidgets( "gui/layouts/new_ui/server_browser/server_browser_list_entry.layout", parent );
		m_Favorite	= m_Root.FindAnyWidget( "favorite_checkbox" );
		m_Expand	= m_Root.FindAnyWidget( "expand_button" );
		
		WidgetEventHandler.GetInstance().RegisterOnClick( m_Favorite, this, "ToggleFavorite" );
		WidgetEventHandler.GetInstance().RegisterOnClick( m_Expand, this, "ToggleExpand" );
	}
	
	void ToggleFavorite()
	{
		
	}
	
	void ToggleExpand()
	{
		m_IsExpanded = !m_IsExpanded;
		m_Root.FindAnyWidget( "collapse_image" ).Show( m_IsExpanded );
		m_Root.FindAnyWidget( "expand_image" ).Show( !m_IsExpanded );
		m_Root.FindAnyWidget( "detailed_info" ).Show( m_IsExpanded );
	}
}