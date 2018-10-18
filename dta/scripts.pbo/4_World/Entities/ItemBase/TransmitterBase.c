//TRANSMITTER BASE
class TransmitterBase extends ItemTransmitter
{
	//Sounds
	const string SOUND_RADIO_START_NOISE 	= "radioStartNoise";
	
	// --- SYSTEM EVENTS
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		//store tuned frequency
		ctx.Write( GetTunedFrequencyIndex() );
	}
	
	override void OnStoreLoad( ParamsReadContext ctx )
	{
		super.OnStoreLoad( ctx );
		
		//load and set tuned frequency
		int tuned_frequency_idx;
		ctx.Read( tuned_frequency_idx );
		SetFrequencyByIndex( tuned_frequency_idx );
	}	
		
	
	override bool IsTransmitter()
	{
		return true;
	}
	
	//--- ACTIONS
	void SetNextFrequency( PlayerBase player = NULL )
	{
		SetNextChannel();
		
		if ( player )
		{
			DisplayRadioInfo( GetTunedFrequency().ToString(), player );
		}
	}
	
	//--- HUD
	protected Hud GetHud( PlayerBase player )
	{
		if ( !player ) 
		{
			return NULL;
		}
		
		return player.m_Hud;
	}
	
	void DisplayRadioInfo( string message, PlayerBase player )
	{
		Hud hud;
		if ( player )
		{
			hud = GetHud( player );
		}
		
		if ( hud ) 
		{	
			hud.SetWalkieTalkieText( message );
			hud.ShowWalkieTalkie( 3 );
		}
	}
	
	//--- POWER EVENTS
	override void OnSwitchOn()
	{
		if ( !GetCompEM().CanWork() )
		{
			GetCompEM().SwitchOff();
		}
	}	
	
	override void OnWorkStart()
	{
		//turn on broadcasting/receiving
		EnableBroadcast ( true );
		EnableReceive ( true );
		SwitchOn ( true );
		
		//play sound
		SoundRadioStartNoise();
	}

	override void OnWorkStop()
	{
		//auto switch off (EM)
		GetCompEM().SwitchOff();
		
		//turn off broadcasting/receiving
		EnableBroadcast ( false );
		EnableReceive ( false );
		SwitchOn ( false );
	}
	
	//--- SOUNDS
	//Radio start noise
	protected void SoundRadioStartNoise()
	{
		if ( GetGame() && ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) )
		{
			PlaySound( SOUND_RADIO_START_NOISE, 50 );
		}
	}
}
