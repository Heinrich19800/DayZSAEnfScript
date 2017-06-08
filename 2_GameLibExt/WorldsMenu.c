#ifdef GAME_TEMPLATE

[EditorAttribute("box", "GameLib/Scripted", "-0.25 -0.25 -0.25", "0.25 0.25 0.25", "255 0 0 255")]
class WorldsMenuClass
{

}

WorldsMenuClass WorldsMenuSource;

class WorldsMenu: GenericEntity
{
	int m_DbgListSelection = 0;
	int m_WorldsCount = 0;
	string DEFAULT_WORLD = "worlds/default.ent";
	autoptr array<string> m_DbgOptions = {};
	ImageWidget m_MouseWidget;
	
	void WorldsMenu()
	{
		SetFlags(EntityFlags.ACTIVE, false);
		SetEventMask(EntityEvent.POSTFRAME);
		
		m_MouseWidget = GetGame().GetWorkspace().CreateWidgets("gui/layouts/mouse.layout");
		m_MouseWidget.SetSort(1024);
		SetCursorWidget(m_MouseWidget);
		ShowCursorWidget(true);

		LoadWorlds();
	}
	
	void ~WorldsMenu()
	{
		if (m_MouseWidget)
			m_MouseWidget.Destroy();
	}

	array<string> GetWorldList()
	{
		return m_DbgOptions;
	}

	void EOnPostFrame(IEntity other, int extra) //EntityEvent.POSTFRAME
	{
		DbgUI.Begin("Load world", 400, 100);

		DbgUI.Text("Select world to load from worlds directory");

		if (m_DbgOptions.Count() > 0)
		{
			DbgUI.List("Worlds", m_DbgListSelection, m_DbgOptions);
			if (DbgUI.Button("Start") || KeyState(KeyCode.KC_RETURN))
			{
				ClearKey(KeyCode.KC_RETURN);
				string worldToLoad = m_DbgOptions.Get(m_DbgListSelection);
				if (GetGame().SetWorldFile(worldToLoad, true))
					ShowCursorWidget(false);
			}
		}
		if (DbgUI.Button("Exit") || KeyState(KeyCode.KC_ESCAPE))
		{
			GetGame().RequestClose();
		}		
		DbgUI.End();
	}

	void LoadWorlds()
	{
		string fileName;
		FileAttr fileAttr;
		FindFileHandle worlds = FindFile("worlds/*.ent", fileName, fileAttr, 0);
		
		if (!worlds)
			return;

		InsertWorldToList(fileName);

		while(FindNextFile(worlds, fileName, fileAttr))
		{
			InsertWorldToList(fileName);
		}

		CloseFindFile(worlds);

		m_WorldsCount = m_DbgOptions.Count();
	}

	void InsertWorldToList(string fileName)
	{
		string path = String("worlds/" + fileName);
		if (path != DEFAULT_WORLD)
			m_DbgOptions.Insert(String(path));
	}
}

#endif