#ifdef GAME_TEMPLATE

[EditorAttribute("box", "GameLib/Scripted", "-0.25 -0.25 -0.25", "0.25 0.25 0.25", "255 0 0 255")]
class ScriptCameraClass
{

}

ScriptCameraClass ScriptCameraSource;

class ScriptCamera: GenericEntity
{
	[Attribute("60", "slider", "Field of view", "0 180 1")]
	float FOV;
	[Attribute("1", "editbox", "Near plane clip")]
	float NearPlane;
	[Attribute("4000", "editbox", "Far plane clip")]
	float FarPlane;
	[Attribute("1", "combobox", "Projection type", "", { ParamEnum("Perspective", CameraType.PERSPECTIVE.ToString()), ParamEnum("Orthographic", CameraType.ORTHOGRAPHIC.ToString()) } )]
	int Type;
	[Attribute("0.5", "slider", "Camera speed", "0 5 0.1")]
	float Speed;
	[Attribute("1", "combobox", "Free Fly", "", { ParamEnum("No", "0"), ParamEnum("Yes", "1")} )]
	bool FreeFly;
	[Attribute("0", "slider", "Camera index", "0 31 1")]
	int Index;
	float m_MouseSensitivity = 0.001; // should be somewhere else.

	// debug variables
	int m_DbgListSelection = 0;
	autoptr array<string> m_DbgOptions = {"Perspective", "Orthographic", "None"};

	void ScriptCamera()
	{
		SetFlags(EntityFlags.ACTIVE, false);
		SetEventMask(EntityEvent.POSTFRAME);

		SetCameraVerticalFOV(Index, FOV);
		SetCameraFarPlane(Index, FarPlane);
		SetCameraNearPlane(Index, NearPlane);
		SetCameraType(Index, Type);
		SetCamera(Index, GetOrigin(), GetAngles());

		vector camMat[4];
		GetTransform(camMat);
		SetCameraEx(Index, camMat);
	}

	private void EOnPostFrame(IEntity other, int extra) //EntityEvent.POSTFRAME
	{
		if (FreeFly)
		{
			FreeFly();
		}
		if (GetGame().IsDebug())
		{
			DebugInfo();
		}
	}

	private void FreeFly()
	{
		vector camMat[4];
		GetTransform(camMat);	

		float deltaX = GetMouseState(MouseState.X) * m_MouseSensitivity;
		float deltaY = GetMouseState(MouseState.Y) * m_MouseSensitivity;
		
		vector camPosition = GetOrigin();
		vector angles = GetAngles();
		
		angles[1] = -(deltaY) + angles[1];
		angles[0] = (deltaX) + angles[0];
		angles[2] = 0;
	
		vector move = vector.Zero;
		vector forward, up, side;

		forward = camMat[2];
		up = camMat[1];
		side = camMat[0];
		
		if (KeyState(KeyCode.KC_W))
		{
			move = move + forward;			
		}
		if (KeyState(KeyCode.KC_S))
		{
			move = move - forward;
		}
		if (KeyState(KeyCode.KC_A))
		{
			move = move - side;
		}
		if (KeyState(KeyCode.KC_D))
		{
			move = move + side;
		}
		if (KeyState(KeyCode.KC_Q))
		{
			move = move + up;
		}
		if (KeyState(KeyCode.KC_E))
		{
			move = move - up;
		}
		if (KeyState(KeyCode.KC_R)) // restart
		{
			camPosition = "0 2 0";
			angles = vector.Zero;
		}
		move = move * Speed;
		camPosition = (move * ftime * Speed) + camPosition;
		
		Math3D.YawPitchRollMatrix(angles, camMat);
		camMat[3] = camPosition;
		SetTransform(camMat);
		SetCameraEx(Index, camMat);
	}

	private void DebugInfo()
	{
		DbgUI.Begin(String("Camera #" + Index.ToString()), 0, Index * 300);

		DbgUI.Text(String("Position : " + GetOrigin().ToString()));
		DbgUI.Text(String("Orientation : " + GetAngles().ToString()));
		DbgUI.Text(String("Speed : " + Speed.ToString()));
		DbgUI.Text(String("Mouse sensitivity : " + (2000 - (1 / m_MouseSensitivity)).ToString()));
		DbgUI.Check("Select Free fly", FreeFly);
		DbgUI.List("Camera type", m_DbgListSelection, m_DbgOptions);

		float speed = Speed * 10; 
		DbgUI.SliderFloat("Camera speed", speed, 1, 10);
		Speed = speed / 10;
		
		float sensitivity = 2000 - (1 / m_MouseSensitivity);
		DbgUI.SliderFloat("Mouse sensitivity", sensitivity, 1, 1999);
		m_MouseSensitivity = 1 / (2000 - sensitivity);

		DbgUI.End();
	}
}

#endif