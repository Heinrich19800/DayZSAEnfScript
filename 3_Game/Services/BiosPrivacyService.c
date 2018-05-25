//!	EBiosPrivacyPermission represents possible privacy permissions
/*!
	See individual values for platform support and meaning.
*/
enum EBiosPrivacyPermission
{
	COMMUNICATE_VOICE,		//!< Xbox: represents CommunicateUsingVoice permissions, see Xbox Docs.
	COMMUNICATE_TEXT,		//!< Xbox: represents CommunicateUsingText permissions, see Xbox Docs.
	VIEW_PROFILE,			//!< Xbox: represents ViewTargetProfile permissions, see Xbox Docs.
	VIEW_PRESENCE,			//!< Xbox: represents ViewTargetPresence permissions, see Xbox Docs.
};

//! BiosPrivacyPermissionResult represents the per permission result of the GetPermissionsAsync reqeust.

class BiosPrivacyPermissionResult
{
	EBiosPrivacyPermission	m_Permission;	//!< The reqeusted permission.
	bool					m_IsAllowed;	//!< Result.
	
	static bool Compare( BiosPrivacyPermissionResult a, BiosPrivacyPermissionResult b )
	{
		return ( a.m_Permission == b.m_Permission && a.m_IsAllowed == b.m_IsAllowed );
	}
};


typedef array<ref BiosPrivacyPermissionResult> BiosPrivacyPermissionResultArray;

//! BiosPrivacyUidResult represents the per user result of the GetPermissionsAsync request.

class BiosPrivacyUidResult
{
	string									m_Uid;			//!< Uid of the target user.
	ref BiosPrivacyPermissionResultArray	m_Results;		//!< Array of permission results for this target user.
};

typedef array<ref BiosPrivacyUidResult> BiosPrivacyUidResultArray;

//! BiosPrivacyService is used to query privacy permissions for a target user/s.

class BiosPrivacyService
{
	//! Query for privacy permissions
	/*!
		The async result is returned in the OnPermissionsAsync callback.
		Expected errors:
			BAD_PARAMETER -	if atleast one of the permissions is not supported on the current platform, 
							or atleast one of the input arrays is NULL.
			
		@param uid_list list of target user Uid's for which to query privacy permissions.
		@param permission_list list of requested permissions for each target user.
		@return EBiosError indicating if the async operation is pending.
		
	*/
	proto native EBiosError GetPermissionsAsync(ref array<string> uid_list, ref array<EBiosPrivacyPermission> permission_list);

	//! Async callback for GetPermissionsAsync
	/*!
		@param result_list list of results for each requested user. NULL if failed.
		@param error error indicating success or fail of the async operation.
	
	*/
	void OnPermissionsAsync(ref BiosPrivacyUidResultArray result_list, EBiosError error)
	{
		if (result_list == null)
		{
			Print("biapi privacy error: " + error);
			return;
		}
		
		Print("biapi: uid result count: " + result_list.Count());
		
		for (int i = 0; i < result_list.Count(); ++i)
		{
			Print("biapi: uid result index: " + i);
			
			BiosPrivacyUidResult uidResult = result_list.Get(i);
			Print("biapi: uid result uid: " + uidResult.m_Uid);
			Print("biapi: uid result result count: " + uidResult.m_Results.Count());
			
			for (int j = 0; j < uidResult.m_Results.Count(); ++j)
			{
				Print("biapi: uid result result index: " + j);
				
				BiosPrivacyPermissionResult result = uidResult.m_Results.Get(j);
				Print("biapi: uid result result permission: " + result.m_Permission);
				Print("biapi: uid result result is allowed: " + result.m_IsAllowed);
			}
		}
		
		OnlineServices.OnPermissionsAsync( result_list, error );
	}
};
