class ActionViewBinoculars : ActionViewOptics
{
	void ActionViewBinoculars()
	{
		m_CallbackClass = ActionRaiseAndViewCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_LOOKOPTICS;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_LOOKOPTICS;
	}
	
	override int GetType()
	{
		return AT_VIEW_BINOCULARS;
	}
		
	override string GetText()
	{
		return "Use binoculars";
	}
	
	// TODO: Rangefinder does not measure ATM
	override void EnterOptics(ItemOptics optic, PlayerBase player)
	{
		optic.EnterOptics();
		optic.HideSelection("hide");
		if ( optic.HasEnergyManager() )
		{
			optic.GetCompEM().SwitchOn();
			/*if ( GetGame().IsClient() )
			{*/
				Rangefinder.Cast(optic).StartPeriodicMeasurement(player);
			//}
		}
	}
	
	override void ExitOptics(ItemOptics optic, PlayerBase player)
	{
		optic.ShowSelection("hide");
		optic.ExitOptics();
		if ( optic.HasEnergyManager() )
		{
			optic.GetCompEM().SwitchOff();
			/*if ( GetGame().IsClient() )
			{*/
				Rangefinder.Cast(optic).StopPeriodicMeasurement();
			//}
		}
	}
}