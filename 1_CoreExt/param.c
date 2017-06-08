/**
 * \defgroup Tools
 * \desc Helpful functions & classes
 * @{
 */

//-----------------------------------------------------------------------------
/**
\brief Base Param Class with no parameters. Used as general purpose parameter overloaded with Param1 to Param4 templates
 */
class Param
{

};

/**
 \brief Param Class Template with one parameter.
 \n usage:
 @code
 Param paramA = new Param1<int>(55); 
 Param paramB = new Param1<string>("Hello");
 @endcode
 */
class Param1<Class T1> extends Param
{
	T1 param1;

	void Param1(T1 p1)
	{
		param1 = p1;
	}
};

/**
 \brief Param Class Template with two parameters.
 \n usage:
 @code
 Param param = new Param2<float, string>(3.14, "Pi");
 @endcode
 */
class Param2<Class T1, Class T2> extends Param
{
	T1 param1;
	T2 param2;

	void Param2(T1 p1, T2 p2)
	{
		param1 = p1;
		param2 = p2;
	}
};

/**
 \brief Param Class Template with three parameters.
 \n usage:
 @code
 Param param = new Param3<float, string, bool>(2.89, "Lala", true);
 @endcode
 */
class Param3<Class T1, Class T2, Class T3> extends Param
{
	T1 param1;
	T2 param2;
	T3 param3;

	void Param3(T1 p1, T2 p2, T3 p3)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
	}
};

/**
 \brief Param Class Template with four parameters.
 \n usage:
 @code
 Param param = new Param4<int, bool, float, string>(100, false, 79.9, "Test");
 @endcode
 */
class Param4<Class T1, Class T2, Class T3, Class T4> extends Param
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;

	void Param4(T1 p1, T2 p2, T3 p3, T4 p4)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
	}
};

/**
 \brief Param Class Template with five parameters.
 */
class Param5<Class T1, Class T2, Class T3, Class T4, Class T5> extends Param
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;
	T5 param5;

	void Param5(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
		param5 = p5;
	}
};

/**
 \brief Param Class Template with six parameters.
 */
class Param6<Class T1, Class T2, Class T3, Class T4, Class T5, Class T6> extends Param
{
	T1 param1;
	T2 param2;
	T3 param3;
	T4 param4;
	T5 param5;
	T6 param6;

	void Param6(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
	{
		param1 = p1;
		param2 = p2;
		param3 = p3;
		param4 = p4;
		param5 = p5;
		param6 = p6;
	}
};

/** @}*/

