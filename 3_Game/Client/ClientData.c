class ClientData
{
	static ref ScriptInvoker SyncEvent_OnPlayerListUpdate = new ScriptInvoker();
	
	static ref SyncPlayerList		m_PlayerList;
	
	static ref OnlineServices		m_OnlineServices;
	
	
	static void SyncEvent_OnRecievedPlayerList( SyncPlayerList player_list )
	{
		if ( m_PlayerList )
		{
			delete m_PlayerList;
		}
		
		m_PlayerList = player_list;
		
		#ifdef PLATFORM_XBOX
			OnlineServices.LoadPermissions( GetSimplePlayerList() );
		#endif
		SyncEvent_OnPlayerListUpdate.Invoke( player_list );
	}
	
	static array<string> GetSimplePlayerList()
	{
		ref array<string> ids = new array<string>;
		if( m_PlayerList )
		{
			for( int i = 0; i < m_PlayerList.m_PlayerList.Count(); i++ )
			{
				SyncPlayer player = m_PlayerList.m_PlayerList.Get( i );
				ids.Insert( player.m_UID );
			}
		}
			
		return ids;
	}
}