// #include "Scripts\Classes\Gui\AssignmentTimer.c"

class AssignmentMenu extends UIScriptedMenu
{
	void AssignmentMenu()
	{
		m_keys = new TIntArray;
		m_specialKeys = new TIntArray;
		g_Game.SetKeyboardHandle(this);
		m_timer = new AssignmentTimer(this);
	}

	void ~AssignmentMenu()
	{
		CancelCapture();
		m_timer.Stop();
		g_Game.SetKeyboardHandle(NULL);
	}
	
	Widget Init()
	{
		Widget layoutRoot = GetGame().GetWorkspace().CreateWidgets("gui/layouts/day_z_assignments.layout");
		
		m_assignedList = (TextListboxWidget)layoutRoot.FindAnyWidget("AssignedListboxWidget");
		m_assignedList.ClearItems();

		m_specialKeysList = (TextListboxWidget)layoutRoot.FindAnyWidget("SpecialKeysListboxWidget");
		m_specialKeysList.ClearItems();

		m_actionNameText = (TextWidget)layoutRoot.FindAnyWidget("ActionNameTextWidget");

		m_MainWindow = (Widget)layoutRoot.FindAnyWidget("MainWindowWidget");
		m_MainWindow.Show(true);

		m_AssignWindow = (Widget)layoutRoot.FindAnyWidget("AssignWindowWidget");
		m_AssignWindow.Show(false);

		m_addButton = (ButtonWidget)layoutRoot.FindAnyWidget("AddButton");
		
		m_addSpecialButton = (ButtonWidget)layoutRoot.FindAnyWidget("AddSpecialButton");
		m_addSpecialButton.Show(false);

		m_removeButton = (ButtonWidget)layoutRoot.FindAnyWidget("RemoveButton");
		m_removeButton.Show(false);

		m_resetButton = (ButtonWidget)layoutRoot.FindAnyWidget("ResetButton");
		m_defaultButton = (ButtonWidget)layoutRoot.FindAnyWidget("DefaultButton");

		// init special keys
		g_Game.GetInput().GetSpecialKeys(m_specialKeys);

		m_specialKeysList.ClearItems();

		string name;
		for (int i = 0; i < m_specialKeys.Count(); i++)
		{
			int key = m_specialKeys.Get(i);
			g_Game.GetInput().GetActionKeyName(key, name);
			m_specialKeysList.AddItem(name, NULL, 0);
		}

		CancelCapture();
		return layoutRoot;
	}
	
	bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick( w, x, y, button);
		
		switch (w.GetUserID())
		{
		case IDC_OK:
			g_Game.GetInput().SetActionKeys(m_action_index, m_keys);
			Close();
			return true;
			
		case IDC_CANCEL:
			Close();
			return true;
		}

		if (w == m_addButton)
		{
			AddKey();
			return true;
		}

		if (w == m_addSpecialButton)
		{
			AddSpecialKey();
			return true;
		}
		
		if (w == m_removeButton)
		{
			RemoveKey();
			return true;
		}

		if (w == m_resetButton)
		{
			ResetAssignments();
			return true;
		}

		if (w == m_defaultButton)
		{
			DefaultAssignments();
			return true;
		}

		if (w == m_specialKeysList)
		{
			if (m_specialKeysList.GetSelectedRow() != -1)
			{
				m_addSpecialButton.Show(true);
			}
			else
			{
				m_addSpecialButton.Show(false);
			}
			return true;
		}

		return false;
	}
	
	bool OnKeyDown(Widget w, int x, int y, int key)
	{
		super.OnKeyDown( w, x, y, key);
		
		if (!IsCapturing()) return false;
		
		if (key == KeyCode.KC_ESCAPE)
		{
			CancelCapture();
			return true;
		}

		if (m_first_key == -1)
		{
			m_first_key = key;
			return true;
		}
		
		if (m_first_key == key && m_first_key_double_tap_enabled) // double tap
		{
			m_first_key = key + KEYBOARD_DOUBLE_TAP_OFFSET;
			EndCapture();
			return true;
		}

		if (g_Game.GetInput().IsKeyReserved(key)) return false;

		if (m_second_key == -1 && m_first_key != key)
		{
			m_second_key = key;
			return true;
		}
		
		if (m_second_key == key && m_second_key_double_tap_enabled) // double tap
		{
			m_second_key = key+KEYBOARD_DOUBLE_TAP_OFFSET;
			EndCapture();
			return true;
		}

		return false;
	}
	
	bool OnKeyUp(Widget w, int x, int y, int key)
	{
		super.OnKeyUp(w, x, y, key);
		
		if (!IsCapturing()) return false;
		
		m_timer.Run(0.5, false);
		
		if (m_first_key == key && m_second_key != -1)
		{
			EndCapture();
			return true;
		}

		if (m_first_key == key)
		{
			m_first_key_double_tap_enabled = true;
		}


		if (m_second_key == key)
		{
			m_second_key_double_tap_enabled = true;
		}

		return true;
	}
	
	void InitAssignment(int action_index)
	{
		m_action_index = action_index;
		ResetAssignments();

		string desc;
		g_Game.GetInput().GetActionDesc(m_action_index, desc);
		m_actionNameText.SetText("#options_controls_action_label " + desc);
	}

	void AddKey()
	{
		if (IsCapturing()) return;

		StartCapture();
	}

	void AddSpecialKey()
	{
		int specialKeyIndex = m_specialKeysList.GetSelectedRow();
		if (specialKeyIndex != -1)
		{
			int specialKey = m_specialKeys.Get(specialKeyIndex);
			m_keys.Insert(specialKey);
		}
		RefreshUI();
	}
	
	void RemoveKey()
	{
		int keyIndex = m_assignedList.GetSelectedRow();
		if (keyIndex != -1 && keyIndex < m_keys.Count())
		{
			m_keys.Remove(keyIndex);
		}

		RefreshUI();
	}

	void ResetAssignments()
	{
		g_Game.GetInput().GetActionKeys(m_action_index, m_keys);
		RefreshUI();
	}

	void DefaultAssignments()
	{
		g_Game.GetInput().GetActionDefaultKeys(m_action_index, m_keys);
		RefreshUI();
	}

	void RefreshUI()
	{
		string name;
		int i;
		int key;

		int lastKeyIndex = m_assignedList.GetSelectedRow();

		m_assignedList.ClearItems();

		if (m_keys.Count() == 0) 
		{
			m_removeButton.Show(false);
			return;
		}

		for (i = 0; i < m_keys.Count(); i++)
		{
			key = m_keys.Get(i);
			g_Game.GetInput().GetActionKeyName(key, name);
			int conflictAction = g_Game.GetInput().CheckKeyCollision(m_action_index, key);
			if (conflictAction != -1)
			{
				string conflictActionName;
				g_Game.GetInput().GetActionDesc(conflictAction, conflictActionName);
				name += "(";
				name += conflictActionName;
				name += ")";
			}
			
			m_assignedList.AddItem(name, NULL, 0);
			
			if (conflictAction != -1)
			{
				m_assignedList.SetItemColor(i,0,ARGBF(1, 1, 0, 0) );
			}			
			
		}

		if (lastKeyIndex != -1 && lastKeyIndex < m_keys.Count())
		{
			m_assignedList.SelectRow(lastKeyIndex);
		}
		else
		{
			m_assignedList.SelectRow(m_keys.Count() - 1);
		}

		m_removeButton.Show(true);
	}


	void StartCapture()
	{
		m_MainWindow.Show(false);
		m_AssignWindow.Show(true);

		m_first_key = -1;
		m_second_key = -1;
		m_capturing = true;
		m_first_key_double_tap_enabled = false;
		m_second_key_double_tap_enabled = false;

		m_timer.Run(0.5, true);
	}

	bool IsCapturing()
	{
		return m_capturing;
	}

	void EndCapture()
	{
		if (m_second_key != -1) // combo
		{
			int combo = m_first_key * KEYBOARD_COMBO_OFFSET + m_second_key;
			if ( !IsAlreadyAdded( combo ) )
			{
				m_keys.Insert( combo );
			}
		}
		else
		{
			if ( !IsAlreadyAdded( m_first_key ) && !g_Game.GetInput().IsKeyReserved( m_first_key ) )
			{
				m_keys.Insert( m_first_key );
			}
		}
		
		RefreshUI();
		CancelCapture();
	}
	
	bool IsAlreadyAdded( int m_first_key )
	{
		int key;
		for ( int i = 0; i < m_keys.Count(); i++ )
		{
			key = m_keys.Get(i);
			if( key == m_first_key )
			{
				return true;
			}
		}
		
		return false;
	}
	
	void CancelCapture()
	{
		m_MainWindow.Show(true);
		m_AssignWindow.Show(false);

		m_first_key = -1;
		m_second_key = -1;
		m_capturing = false;
		
		m_timer.Stop();
	}

	TextListboxWidget m_assignedList;
	TextListboxWidget m_specialKeysList;
	TextWidget m_actionNameText;
	Widget m_MainWindow;
	Widget m_AssignWindow;
	ButtonWidget m_addButton;
	ButtonWidget m_addSpecialButton;
	ButtonWidget m_removeButton;
	ButtonWidget m_resetButton;
	ButtonWidget m_defaultButton;
	
	autoptr TIntArray m_keys;
	autoptr TIntArray m_specialKeys;
	autoptr AssignmentTimer m_timer;

	int m_action_index;
	int m_first_key;
	int m_second_key;
	bool m_capturing;
	bool m_first_key_double_tap_enabled;
	bool m_second_key_double_tap_enabled;
}
