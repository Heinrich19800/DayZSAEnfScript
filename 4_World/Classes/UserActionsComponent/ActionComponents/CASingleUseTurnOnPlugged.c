class CASingleUseTurnOnPlugged : CASingleUse
{	
	override int Execute( ActionData action_data )
	{
		if ( !action_data.m_MainItem )
		{
			return UA_ERROR;
		}
		if ( !action_data.m_MainItem.GetCompEM().CanWork() )
		{
			return UA_SETEND_2;
		}
		return UA_FINISHED;
	}
};