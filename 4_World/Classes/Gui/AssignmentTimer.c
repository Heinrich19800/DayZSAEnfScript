class AssignmentMenu;

class AssignmentTimer extends TimerBase
{
	private AssignmentMenu m_menu;
	private int m_dik;

	void AssignmentTimer(AssignmentMenu menu)
	{
		m_menu = menu;
		OnInit(CALL_CATEGORY_GUI);
	}

	void Run(float duration, bool loop = false)
	{
		m_dik = -1;
		OnStart(duration, loop);
	}

	void OnTimer()
	{
		if (m_loop) // waiting second key
		{
			return;
		}

		if (m_dik != -1)
		{
			m_menu.OnKeyDown(NULL, 0, 0, m_dik);
			m_menu.OnKeyUp(NULL, 0, 0, m_dik);
		}

		m_menu.EndCapture();
	}

	void OnUpdate()
	{
		if (m_menu.m_first_key != -1) // waiting first key
		{
			return;
		}

		int dik = g_Game.GetInput().GetSpecialKeyPressed();
		if (dik != -1)
		{
			m_dik = dik;
			m_time = 0;
			m_duration = 1;
			m_loop = false;
		}
	}
}
