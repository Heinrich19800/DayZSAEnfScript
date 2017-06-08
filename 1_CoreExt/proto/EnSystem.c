/**
 * \defgroup System System API definition
 * @{
 */

/**
\brief Returns world time
	\param[out] hour \p int Hour
	\param[out] minute \p int Minute
	\param[out] second \p int Second
	\return \p void
	@code
		int hour = 0;
		int minute = 0;
		int second = 0;

		GetHourMinuteSecondUTC(hour, minute, second);

		Print(hour);
		Print(minute);
		Print(second);

		>> hour = 16
		>> minute = 38
		>> second = 7
	@endcode
*/
proto void GetHourMinuteSecond(out int hour, out int minute, out int second);

/**
\brief Returns world date
	\param[out] year \p int Year
	\param[out] month \p int Month
	\param[out] day \p int Day
	\return \p void
	@code
		int year = 0;
		int month = 0;
		int day = 0;

		GetYearMonthDay(year, month, day);

		Print(year);
		Print(month);
		Print(day);

		>> year = 2015
		>> month = 3
		>> day = 24
	@endcode
*/
proto void GetYearMonthDay(out int year, out int month, out int day);

/**
\brief Returns UTC world time
	\param[out] hour \p int Hour
	\param[out] minute \p int Minute
	\param[out] second \p int Second
	\return \p void
	@code
		int hour = 0;
		int minute = 0;
		int second = 0;

		GetHourMinuteSecondUTC(hour, minute, second);

		Print(hour);
		Print(minute);
		Print(second);

		>> hour = 15
		>> minute = 38
		>> second = 7
	@endcode
*/
proto void GetHourMinuteSecondUTC(out int hour, out int minute, out int second);

/**
\brief Returns UTC world date
	\param[out] year \p int Year
	\param[out] month \p int Month
	\param[out] day \p int Day
	\return \p void
	@code
		int year = 0;
		int month = 0;
		int day = 0;

		GetYearMonthDayUTC(year, month, day);

		Print(year);
		Print(month);
		Print(day);

		>> year = 2015
		>> month = 3
		>> day = 24
	@endcode
*/
proto void GetYearMonthDayUTC(out int year, out int month, out int day);


/**
	performance counter. Returns number of CPU ticks between 'prev' and 'now'
*/
proto native int TickCount(int prev);

/**
\brief Switches memory validation (huge slowdown! Use with care only for certain section of code!)
	\param enable \p bool Enable
	\return \p void
	@code
		???
	@endcode
*/
proto native void MemoryValidation(bool enable);

#ifdef ENF_DONE

//!developer tool - start video grabber
proto native void StartVideo(string name);
//!developer tool - stop video grabber
proto native void StopVideo();
#endif


/**
 * \defgroup Keyboard Keyboard input API
 * @{
 */
enum KeyCode
{
	KC_ESCAPE,
	KC_1,
	KC_2,
	KC_3,
	KC_4,
	KC_5,
	KC_6,
	KC_7,
	KC_8,
	KC_9,
	KC_0,
	KC_MINUS,   ///< - on main keyboard 
	KC_EQUALS,
	KC_BACK,    ///< backspace 
	KC_TAB,
	KC_Q,
	KC_W,
	KC_E,
	KC_R,
	KC_T,
	KC_Y,
	KC_U,
	KC_I,
	KC_O,
	KC_P,
	KC_LBRACKET,
	KC_RBRACKET,
	KC_RETURN,   ///< Enter on main keyboard 
	KC_LCONTROL,
	KC_A,
	KC_S,
	KC_D,
	KC_F,
	KC_G,
	KC_H,
	KC_J,
	KC_K,
	KC_L,
	KC_SEMICOLON,
	KC_APOSTROPHE,
	KC_GRAVE,    ///< accent grave 
	KC_LSHIFT,
	KC_BACKSLASH,
	KC_Z,
	KC_X,
	KC_C,
	KC_V,
	KC_B,
	KC_N,
	KC_M,
	KC_COMMA,
	KC_PERIOD,   ///< . on main keyboard 
	KC_SLASH,    ///< / on main keyboard 
	KC_RSHIFT,
	KC_MULTIPLY,    ///< * on numeric keypad 
	KC_LMENU,    ///< left Alt 
	KC_SPACE,
	KC_CAPITAL,
	KC_F1,
	KC_F2,
	KC_F3,
	KC_F4,
	KC_F5,
	KC_F6,
	KC_F7,
	KC_F8,
	KC_F9,
	KC_F10,
	KC_NUMLOCK,
	KC_SCROLL,    ///< Scroll Lock 
	KC_NUMPAD7,
	KC_NUMPAD8,
	KC_NUMPAD9,
	KC_SUBTRACT,    ///< - on numeric keypad 
	KC_NUMPAD4,
	KC_NUMPAD5,
	KC_NUMPAD6,
	KC_ADD,    ///< + on numeric keypad 
	KC_NUMPAD1,
	KC_NUMPAD2,
	KC_NUMPAD3,
	KC_NUMPAD0,
	KC_DECIMAL,   ///< . on numeric keypad 
	KC_OEM_102,    ///< < > | on UK/Germany keyboards 
	KC_F11,
	KC_F12,
	KC_NUMPADEQUALS,    ///< = on numeric keypad (NEC PC98) 
	KC_PREVTRACK,    ///< Previous Track (DIKC_CIRCUMFLEX on Japanese keyboard) 
	KC_AT,    ///<                     (NEC PC98) 
	KC_COLON,    ///<                     (NEC PC98) 
	KC_UNDERLINE,    ///<                     (NEC PC98) 
	KC_STOP,    ///<                     (NEC PC98) 
	KC_AX,    ///<                     (Japan AX) 
	KC_UNLABELED,    ///<                        (J3100) 
	KC_NEXTTRACK,    ///< Next Track 
	KC_NUMPADENTER,    ///< Enter on numeric keypad 
	KC_RCONTROL,
	KC_MUTE,    ///< Mute 
	KC_CALCULATOR,    ///< Calculator 
	KC_PLAYPAUSE,    ///< Play / Pause 
	KC_MEDIASTOP,    ///< Media Stop 
	KC_VOLUMEDOWN,    ///< Volume - 
	KC_VOLUMEUP,    ///< Volume + 
	KC_WEBHOME,    ///< Web home 
	KC_NUMPADCOMMA,    ///< , on numeric keypad (NEC PC98) 
	KC_DIVIDE,    ///< / on numeric keypad 
	KC_SYSRQ,
	KC_RMENU,    ///< right Alt 
	KC_PAUSE,    ///< Pause 
	KC_HOME,    ///< Home on arrow keypad 
	KC_UP,    ///< UpArrow on arrow keypad 
	KC_PRIOR,    ///< PgUp on arrow keypad 
	KC_LEFT,    ///< LeftArrow on arrow keypad 
	KC_RIGHT,    ///< RightArrow on arrow keypad 
	KC_END,    ///< End on arrow keypad 
	KC_DOWN,    ///< DownArrow on arrow keypad 
	KC_NEXT,    ///< PgDn on arrow keypad 
	KC_INSERT,    ///< Insert on arrow keypad 
	KC_DELETE,    ///< Delete on arrow keypad 
	KC_LWIN,    ///< Left Windows key 
	KC_RWIN,    ///< Right Windows key 
	KC_APPS,    ///< AppMenu key 
	KC_POWER,    ///< System Power 
	KC_SLEEP,    ///< System Sleep 
	KC_WAKE,    ///< System Wake 
	KC_MEDIASELECT   ///< Media Select 
};

/*!
zjisti stav klavesy
\param key	Key code
\returns 0 when not pressed, 15. bit set when pressed, 0.-14. bit pressed count 
*/
proto native int KeyState(KeyCode key);

/*!
	"shodi" klavesu.Zamezi se tim "autorepeatu". Klavesa muze byt Set az pote, co je uvolnena a opet stisknuta
*/
proto native void ClearKey(KeyCode key);
/** @}*/

//returns index of defined key in InputDevice by its name
//proto native int GetDefKey(string name);
//proto native int DefKeyState(int defkey, bool clear);


/**
 * \defgroup Mouse Mouse API
 * @{
 */

enum MouseState
{
	LEFT,
	MIDDLE,
	RIGHT,
	X,
	Y
};
	
proto native int GetMouseState(MouseState index);

//vraci aktualni pozici mysi v GUI systemu ktera byla nastavena pomoci funkce ReportMouse (ReportMouse muze byt volanej i z c++ strany herniho kodu)
proto void GetMousePos(out int x, out int y);
//vraci rozmer obrazovky v pixelech
proto void GetScreenSize(out int x, out int y);

/** @}*/

//----------------------------------------------
/**
 * \defgroup File FileIO API
 * @{
 */

enum FileMode
{
	READ,
	WRITE,
	APPEND
};
	
typedef int[] ParseHandle;
typedef int[] FileHandle;

proto native ParseHandle BeginParse(string filename);
proto int ParseLine(ParseHandle tp, int num, string tokens[]);
proto native void EndParse(ParseHandle file);

//!Check existence of file
proto bool FileExist(string name);

/**
\brief Opens File
	@param name of a file to open, (you can use filesystem prefixes. For accessing profile dir use '$profile', e.g. '$profile:myFileName.txt')
	@param mode constants FileMode.WRITE, FileMode.READ or FileMode.APPEND flag can be used
	\return file handle ID or 0 if fails
	\n usage :
	@code
	FileHandle file = OpenFile("$profile:testiik.txt", FileMode.WRITE);
	//FileHandle file = OpenFile("$profile:testiik.txt", FileMode.APPEND);
	if (file != 0)
	{
		FPrintln(file, "line1");
		FPrintln(file, "line2");
		FPrintln(file, "line3");
		CloseFile(file);
	}
	@endcode
*/
proto FileHandle		OpenFile(string name, FileMode mode);

/**
Reads raw data from file.
\param param_array Receiving array for the data
\param length Length of data
\returns number of read bytes
*/
proto int ReadFile(FileHandle file, void param_array, int length);

/**
\brief Close the File
	@param file File handle ID of a opened file
	\return void
	\n usage :
	@code
	FileHandle file = OpenFile("$profile:testiik.txt", FileMode.WRITE);
	if (file != 0)
	{
		FPrintln(file, "line1");
		FPrintln(file, "line2");
		FPrintln(file, "line3");
		CloseFile(file);
	}
	@endcode
*/
proto void		CloseFile(FileHandle file);

/**
\brief Write to file
	@param file File handle ID of a opened file
	@param var Value to write
	\return void
	\n usage :
	@code
	FileHandle file = OpenFile("$profile:testiik.txt", FileMode.WRITE);
	if (file != 0)
	{
		FPrint(file, "A");
		FPrint(file, "B");
		FPrint(file, "C");
		CloseFile(file);
	}
	@endcode
*/
proto void		FPrint(FileHandle file, void var);

/**
\brief Write to file and add new line
	@param file File handle ID of a opened file
	@param var Value to write
	\return void
	\n usage :
	@code
	FileHandle file = OpenFile("$profile:testiik.txt", FileMode.WRITE);
	if (file != 0)
	{
		FPrintln(file, "line1");
		FPrintln(file, "line2");
		FPrintln(file, "line3");
		CloseFile(file);
	}
	@endcode
*/
proto void		FPrintln(FileHandle file, void var);

/**
\brief Get line from file, every next call of this function returns next line
	@param file File handle ID of a opened file
	@param var Value to write
	\return int Count of chars or -1 if is not any for read (end of file is EMPTY line)
	\n usage :
	@code
		FileHandle file_handle = OpenFile("$profile:testiik.txt", FileMode.READ);
		string line_content;

		while ( FGets( file_handle,  line_content ) > 0 )
		{
			Print(line_content);
		}

		CloseFile(file_handle);
	@endcode
*/
proto int		FGets(FileHandle file, string var);

typedef int[] FindFileHandle;

enum FileAttr
{
	DIRECTORY, ///<File is directory
	HIDDEN, ///<File is hidden
	READONLY, ///<File is read-only
	INVALID ///<Invalid file
};

proto FindFileHandle FindFile(string pattern, out string fileName, out FileAttr fileAttributes, int flags);
proto bool FindNextFile(FindFileHandle handle, out string fileName, out FileAttr fileAttributes);
proto native void CloseFindFile(FindFileHandle handle);

//!Makes a directory
proto native bool MakeDirectory(string name);

//!delete file. Works only on "$profile:" and "$saves:" locations
proto native bool DeleteFile(string name);

//! copy file. destName must be "$profile:" or "$saves:" location
proto native bool CopyFile(string sourceName, string destName);
/** @}*/

//returns all addons
proto int GetAddons(string addonNames[]);

//returns all plugins (addons and mods)
proto int GetPlugins(string pluginNames[]);


 //@}
