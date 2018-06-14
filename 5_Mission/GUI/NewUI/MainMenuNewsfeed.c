class MainMenuNewsfeed extends ScriptedWidgetEventHandler
{
	protected Widget m_Root;
	
	void MainMenuNewsfeed( Widget root )
	{
		m_Root = root;
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