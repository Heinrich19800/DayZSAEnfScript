/**
 * \defgroup Constants
 * \desc static script constants
 * @{
 */


/**
 * \defgroup InputDevice
 * \desc constants for input device - inputInterfaceDef.h
 * @{
 */
const int INPUT_DEVICE_MASK       	= 0x00700000;
const int INPUT_DEVICE_KEYBOARD   	= 0x00000000;
const int INPUT_DEVICE_MOUSE      	= 0x00100000; // mouse button
const int INPUT_DEVICE_STICK		= 0x00200000;
const int INPUT_DEVICE_XINPUT     	= 0x00300000; // XInput device
const int INPUT_DEVICE_TRACKIR		= 0x00400000;
const int INPUT_DEVICE_GAMEPAD  	= 0x00500000;
const int INPUT_DEVICE_CHEAT		= 0x00600000;

const int INPUT_ACTION_TYPE_DOWN_EVENT = 0x00000200;
const int INPUT_ACTION_TYPE_COMBO =  0x00002000;
const int INPUT_ACTION_TYPE_DOUBLETAP = 0x00008000;

const int KEYBOARD_DOUBLE_TAP_OFFSET  	= INPUT_ACTION_TYPE_DOUBLETAP;
const int KEYBOARD_COMBO_OFFSET			= INPUT_ACTION_TYPE_COMBO;
const int MOUSE_CLICK_OFFSET      		= INPUT_ACTION_TYPE_DOWN_EVENT;
const int MOUSE_DOUBLE_CLICK_OFFSET 	 = INPUT_ACTION_TYPE_DOUBLETAP;

const int INPUT_AXIS = 0x00010000;
const int INPUT_DEVICE_MOUSE_AXIS = INPUT_DEVICE_MOUSE + INPUT_AXIS; // mouse axis
/** @}*/

/**
 * \defgroup String constants
 * \desc String constants
 * @{
 */
const string STRING_EMPTY = "";
/** @}*/


/**

 * \defgroup Colors
 * @{
 */
const int COLOR_RED = 0xFFF22613;
const int COLOR_GREEN = 0xFF2ECC71;
const int COLOR_BLUE = 0xFF4B77BE;
const int COLOR_YELLOW = 0xFFF7CA18;

const int COLOR_RED_A = 0x1fF22613;
const int COLOR_GREEN_A = 0x1f2ECC71;
const int COLOR_BLUE_A = 0x1f4B77BE;
const int COLOR_YELLOW_A = 0x1fF7CA18;

/** @}*/
	
