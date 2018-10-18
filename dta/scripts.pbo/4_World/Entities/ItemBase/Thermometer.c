class Thermometer extends ItemBase
{
	string GetTemperatureMessage(PlayerBase player)
	{
		string temp;
		if( player.GetModifiersManager() && player.GetModifiersManager().IsModifierActive(eModifiers.MDF_FEVER) )
		{
			temp = PlayerConstants.HIGH_TEMPERATURE;
		}
		else
		{
			temp = PlayerConstants.NORMAL_TEMPERATURE;
		}
		return "Thermometer displays "+temp+" ?C";
	}
}