class AdminTools extends UIScriptedMenu
{
	
	/*Made by 420Gaming DayZ Community
	Author: DaOne*/

	Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("gui/layouts/Admin_Menu.layout");
		return layoutRoot;

	}
	
	bool UseKeyboard() 
	{
		return true;
	}
	
	bool UseMouse()
	{
		return true;
	}
}
