class MainMenuNewsfeed extends ScriptedWidgetEventHandler
{
	protected Widget m_Root;
	
	void MainMenuNewsfeed( Widget root )
	{
		m_Root = root;
		float x, y;
		m_Root.FindAnyWidget( "news_main_screenshot" ).GetSize( x, y );
		Print( "" + x + "," + y );
	}
	
	void ShowNewsfeed()
	{
		m_Root.Show( true );
	}
	
	void HideNewsfeed()
	{
		m_Root.Show( false );
	}
}