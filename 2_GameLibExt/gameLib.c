#ifdef GAME_TEMPLATE
Game g_Game;

Game GetGame()
{
	return g_Game;
}
#endif

class Game
{
	ScriptModule GameScript;
	bool m_Debug;

	bool IsDebug()
	{
		return m_Debug;
	}

	void SetDebug(bool isDebug)
	{
		m_Debug = isDebug;
	}

	//! 
	/**
  	\brief Called when some system event occur.
  	@param eventTypeId event type.
	@param params Param object, cast to specific param class to get parameters for particular event.
	*/
	void OnEvent(EventType eventTypeId, Param params)
	{
		Print("OnEvent");
	}

	/**
	\brief Called after full initialization of Game instance
	*/
	void OnAfterInit()
	{
		Print("OnAfterInit");
	}
	
	/**
  	\brief Called on World update
	@param timeslice time elapsed from last call
	*/
	void OnUpdate(float timeslice) 
	{

	}

	/**
  	\brief Sets world file to be loaded. Returns false if file doesn't exist.
	@param path Path to the ent file
	@param reload Force reload the world
	*/
	proto native bool SetWorldFile(string path, bool reload);
	/**
  	\brief Returns path of world file loaded
	*/
	proto native string GetWorldFile();
	/**
  	\brief Event which is called right before game starts (all entities are created and initialized). Returns true if the game can start.
	*/
	bool OnGameStart()
	{
		return true;
	}

	/**
	\brief Safely instantiate the entity and calls EOnInit if the entity sets event mask EntityEvent.INIT.
	@param typename Name of entity's type to instantiate.
	@return instantiated entity
	*/
	proto native IEntity SpawnEntity(typename typeName);

	/**
	\brief Safely destroys the entity.
	@param entity instance
	*/
	proto native void DestroyEntity(IEntity entity);

	proto native WorkspaceWidget GetWorkspace();

	/**
	\brief Setting request flag for engine to exit the game
	*/
	proto native void RequestClose();

	/**
	\brief Returns version of the game
	*/
	proto native string GetBuildVersion();

	/**
	\brief Returns date and time when the game was built
	*/
	proto native string GetBuildTime();

#ifdef GAME_TEMPLATE	
	/**
  	\brief Returns World entity
	*/
	proto native GenericWorldEntity GetWorldEntity();
#endif	
}

void GameLibInit()
{

}
