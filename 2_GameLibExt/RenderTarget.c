#ifdef GAME_TEMPLATE

[EditorAttribute("box", "GameLib/Scripted", "-0.25 -0.25 -0.25", "0.25 0.25 0.25", "255 0 0 255")]
class RenderTargetClass
{

}

RenderTargetClass RenderTargetSource;

class RenderTarget: GenericEntity
{
	[Attribute("0", "slider", "Camera index", "0 31 1")]
	int CameraIndex;
	[Attribute("0", "editbox", "Position X <0, 1>")]
	float X;
	[Attribute("0", "editbox", "Position Y <0, 1>")]
	float Y;
	[Attribute("1", "editbox", "Render target width <0, 1>")]
	float Width;
	[Attribute("1", "editbox", "Render target height <0, 1>")]
	float Height;
	[Attribute("-1", "editbox", "Sort index (the lesser the more important)")]
	int Sort;
	[Attribute("0", "combobox", "Autoinit", "", { ParamEnum("No", "0"), ParamEnum("Yes", "1") } )]
	int AutoInit;
	Widget m_RenderWidget;
	
	void RenderTarget()
	{
		SetFlags(EntityFlags.ACTIVE, false);

		if (AutoInit)
			Init();
	}

	void ~RenderTarget()
	{
		if (m_RenderWidget)
			m_RenderWidget.Destroy();
	}
	
	void Init()
	{
		#ifdef WORKBENCH // Workbench is using its own renderer for main camera, it is not using render target widget.
			if (CameraIndex == 0)
				return;
		#endif
		
		Print("Rendering target init");

		int screenW, screenH;
		GetScreenSize(screenW, screenH);

		int posX = (float)(screenW * X);
		int posY = (float)(screenH * Y);
		int widthPix = (float)(screenW * Width);
		int heightPix = (float)(screenH * Height);
		m_RenderWidget = GetGame().GetWorkspace().CreateWidget(RenderTargetWidgetTypeID, posX, posY, widthPix, heightPix, WidgetFlags.VISIBLE | WidgetFlags.HEXACTSIZE | WidgetFlags.VEXACTSIZE | WidgetFlags.HEXACTPOS | WidgetFlags.VEXACTPOS, 0xffffffff, Sort);
		SetWidgetWorld(m_RenderWidget, GetGame().GetWorldEntity(), CameraIndex);
	}
}

#endif