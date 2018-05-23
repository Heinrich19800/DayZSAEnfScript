class OnlineServices
{
	static ref ScriptInvoker												m_FriendsAsyncInvoker		= new ScriptInvoker();
	static ref ScriptInvoker												m_PermissionsAsyncInvoker	= new ScriptInvoker();
	
	protected static ref BiosClientServices									m_ClientServices;
	
	protected static ref map<string, ref BiosFriendInfo>					m_FriendsList;
	protected static ref map<string, ref BiosPrivacyPermissionResultArray>	m_PermissionsList;
	
	static void Init( string uid )
	{
		if( !m_FriendsList )
		{
			m_FriendsList = new map<string, ref BiosFriendInfo>;
		}
		
		if( !m_PermissionsList )
		{
			m_PermissionsList = new map<string, ref BiosPrivacyPermissionResultArray>;
		}
		
		m_FriendsList.Clear();
		m_PermissionsList.Clear();
		
		if( GetGame() && !m_ClientServices )
		{
			EBiosError err = GetGame().CreateClientServices( m_ClientServices, uid );
			switch( err )
			{
				case EBiosError.OK:
				{
					LoadFriends();
					LoadPermissions( ClientData.GetSimplePlayerList() );
					
					break;
				}
				case EBiosError.NOT_FOUND:
				{
					Print( "BiosClientServices Error: User not found." );
					break;
				}
				case EBiosError.BAD_SCRIPT:
				{
					Print( "BiosClientServices Error: Bad script linking." );
					break;
				}
				case EBiosError.NOT_IMPLEMENTED:
				{
					Print( "BiosClientServices Error: Function not implemented on this platform." );
					break;
				}
			}
		}
	}
	
	static void LoadFriends()
	{
		if( m_ClientServices )
		{
			m_ClientServices.GetSocialService().GetFriendsAsync();
		}
	}
	
	static void ShowUserProfile( string uid )
	{
		if( m_ClientServices )
		{
			m_ClientServices.GetSocialService().ShowUserProfileAsync( uid );
		}
	}
	
	static void OnUserProfileAsync(EBiosError error)
	{
		
	}
	
	static void OnFriendsAsync( ref BiosFriendInfoArray friend_list, EBiosError error )
	{
		if( error == EBiosError.OK )
		{
			m_FriendsAsyncInvoker.Invoke( friend_list );
			
			array<string> friends_simple = new array<string>;
			for( int i = 0; i < friend_list.Count(); i++ )
			{
				string uid = friend_list.Get( i ).m_Uid;
				if( m_FriendsList.Get( uid ) )
				{
					if( !BiosFriendInfo.Compare( m_FriendsList.Get( uid ), friend_list.Get( i ) ) )
					{
						friends_simple.Insert( friend_list.Get( i ).m_Uid );
					}
					m_FriendsList.Set( uid, friend_list.Get( i ) );
				}
				else
				{
					m_FriendsList.Insert( uid, friend_list.Get( i ) );
					friends_simple.Insert( friend_list.Get( i ).m_Uid );
				}
				
			}
			LoadPermissions( friends_simple );
		}
	}
	
	static void LoadPermissions( array<string> player_list )
	{
		if( m_ClientServices )
		{
			array<EBiosPrivacyPermission> perms = new array<EBiosPrivacyPermission>;
			perms.Insert( EBiosPrivacyPermission.COMMUNICATE_VOICE );
			
			m_ClientServices.GetPrivacyService().GetPermissionsAsync( player_list, perms );
		}
	}
	
	static void OnPermissionsAsync( ref BiosPrivacyUidResultArray result_list, EBiosError error )
	{
		if( error == EBiosError.OK )
		{
			ref BiosPrivacyUidResultArray new_list = new BiosPrivacyUidResultArray;
			for( int i = 0; i < result_list.Count(); i++ )
			{
				string uid = result_list.Get( i ).m_Uid;
				if( m_PermissionsList.Get( uid ) )
				{
					if( !BiosPrivacyPermissionResult.Compare( m_PermissionsList.Get( uid ).Get( 0 ), result_list.Get( i ).m_Results.Get( 0 ) ) )
					{
						Print( "Updated permission" );
						new_list.Insert( result_list.Get( i ) );
						m_PermissionsList.Set( uid, result_list.Get( i ).m_Results );
					}
				}
				else
				{
					Print( "New permission" );
					m_PermissionsList.Insert( uid, result_list.Get( i ).m_Results );
					new_list.Insert( result_list.Get( i ) );
				}
				
			}
			m_PermissionsAsyncInvoker.Invoke( new_list );
		}
	}
	
	static bool IsPlayerMuted( string id )
	{
		BiosPrivacyPermissionResultArray perms = m_PermissionsList.Get( id );
		if( perms )
		{
			for( int i = 0; i < perms.Count(); i++ )
			{
				BiosPrivacyPermissionResult result = perms.Get( i );
				if( result.m_Permission == EBiosPrivacyPermission.COMMUNICATE_VOICE )
				{
					return ( !result.m_IsAllowed );
				}
			}
		}
		return true;
	}
}