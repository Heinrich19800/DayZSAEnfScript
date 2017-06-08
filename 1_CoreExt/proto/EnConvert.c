class bool
{
	string ToString()
	{
		if (value) return "true";
		else "false";
	}
};

class int
{
	protected const int ZERO_PAD_SIZE = 8;
	protected static string m_ZeroPad[ZERO_PAD_SIZE] = {"", "0", "00", "000", "0000", "00000", "000000", "0000000"};
	
	proto string ToString();
	
	/**
	\brief Converts ASCII code to string
		\param ascii ASCII code for convert to \p string.
		\return \p string - Converted \p int.
		@code
			int ascii_code = 77;
			string str = ascii_code.AsciiToString();
			Print(str);

			>> str = 'M'
		@endcode
	*/
	proto string AsciiToString();
	
	/**
	\brief Integer to string with fixed length, padded with zeroes
		\param num \p int integer to convert
		\param len \p int fixed length
		\return \p vector Converted s as vector
		@code
			int num = 123;
			string s = num.ToStringLen(5);
			Print(s);

			>> s = '00123'
		@endcode
	*/
	string ToStringLen(int len)
	{
		string str = value.ToString();

		int l = len - str.Length();

		if (l > 0 && l < ZERO_PAD_SIZE )
			return m_ZeroPad[l] + str;

		return str;
	}
};

class float
{
	proto string ToString();
};

class vector
{
	static const vector Up = "0 1 0";
	static const vector Zero = "0 0 0";
	
	/**
	\brief Vector to  string
		\param beautify If true verbose vector in more human readable form "<1, 1, 1>" instead of simple form "1 1 1"
		\return \p string Converted vector as parsed string
		@code
			vector v = "1 0 1";
			Print( v.ToString() );
			Print( v.ToString(false) );

			>> '<1, 0, 1>'
			>> '1 0 1'
		@endcode
	*/
	proto string ToString(bool beautify = true);
	
	/**
	\brief Normalizes vector. Returns length
		\return \p float Length of origin vector
		@code
			vector vec = "1 0 1";
			float length = vec.Normalize();
			Print( vec );
			Print( length );

			>> vec = <0.707107,0,0.707107>
			>> length = 1.41421
		@endcode
	*/
	proto float Normalize();

	//! return normalized vector (keeps orginal vector untouched)
	proto vector Normalized();
	
	/**
	\brief Returns length of vector (magnitude)
		\return \p float Length of vector
		@code
			vector vec = "1 0 1";
			float length = vec.Length();
			Print( length );

			>> length = 1.41421
		@endcode
	*/
	proto native float Length();

	/**
	\brief Returns squared length (magnitudeSqr)
		\return \p float Length of vector
		@code
			vector vec = "1 1 0";
			float length = vec.LengthSq();
			Print( length );

			>> length = 2
		@endcode
	*/
	proto native float LengthSq();
	
	/**
	\brief Returns the distance between tips of two 3D vectors.
		\param v1 \p vector 3D Vector 1
		\param v2 \p vector 3D Vector 2
		\return \p float Distance
		@code
			float dist = vector.Distance( "1 2 3", "4 5 6" );
			Print( dist );

			>> dist = 5.19615
		@endcode
	*/
	proto static native float Distance(vector v1, vector v2);
	
	/**
	\brief Returns the squere distance between tips of two 3D vectors.
		\param v1 \p vector 3D Vector 1
		\param v2 \p vector 3D Vector 2
		\return \p float Squere distance
		@code
			float dist = vector.DistanceSq( "0 0 0", "0 5 0" );
			Print( dist );

			>> dist = 25
		@endcode
	*/
	proto static native float DistanceSq(vector v1, vector v2);

	/**
	\brief Returns perpendicular vector. Perpendicular vector is computed as cross product between input vector and up vector (0, 1, 0).
	    \return \p vector perpendicular vector
		@code
			vector vec = "1 0 0";
			Print( vec.Perpend() );

			>> <0,0,1>
		@endcode
	*/
	vector Perpend()
	{
		return value * vector.Up;
	}
	
	/**
	\brief Returns direction vector from point p1 to point p2
	    \param p1 \p vector point from
		\param p2 \p vector point to
		\return \p vector direction vector
	*/
	static vector Direction(vector p1, vector p2)
	{
		vector dir_vec;
		
		dir_vec[0] = p2[0] - p1[0];
		dir_vec[1] = p2[1] - p1[1];
		dir_vec[2] = p2[2] - p1[2];
		
		return dir_vec;
	}
	
	/**
	\brief Returns Dot product of vector v1 and vector v2
	    \param v1 \p vector input vector
		\param v2 \p vector input vector
		\return \p vector direction vector
	*/
	static float Dot(vector v1, vector v2)
	{
		return ((v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]));
	}

	/**
	\brief Returns relative angles between -180 and 180, not 0 to 360
		\return \p float Relative angles
		@code
			vector angles = "-45 190 160";
			Print( angles.GetRelAngles() );
	
			>> <-45,-170,160>
		@endcode
	*/
	vector GetRelAngles()
	{
		for(int i = 0; i < 3; i++) {
			if(value[i] > 180)
				value[i] = value[i] - 360;
			if(value[i] < -180)
				value[i] = value[i] + 360;
		}
		return value;
	}
	
	/**
	\brief Returns yaw of vector
		\param vec \p vector Vector to convert yaw
		\return \p float Yaw of vector
		@code
			vector v1 = "0 1 0";
			vector v2 = "0.7 0.7 0";
			Print( v1.ToYaw() );
			Print( v2.ToYaw() );

			>> 90
			>> 45
		@endcode
	*/
	proto float VectorToYaw();

	/**
	\brief Returns vector of yaw
		\param yaw \p float Value of yaw
		\return \p vector Yaw converted in vector
		@code
			Print( vector.Yaw2Vector(90) );
			Print( vector.Yaw2Vector(45) );

			>> <0,1,0>
			>> <0.707107,0.707107,0>
		@endcode
	*/
	proto native static vector YawToVector(float yaw);

	/**
	\brief Converts vector to spherical coordinates with radius = 1
		\return \p vector containing polar angle as x component and azimuthal angle as y component
		@code
			vector v1 = "1 0 1";
			vector v2 = "1 1 1";
			Print( v1.VectorToAngles() );
			Print( v2.VectorToAngles() );

			>> <45,0,360>
			>> <35.2644,0,324.736>
		@endcode
	*/
	proto vector VectorToAngles();

	/**
	\brief Converts spherical coordinates to unit length vector
		\param ang \p vector which contains spherical coordinates - x component is polar angle and y component is azimuthal angle
		\return \p vector containing polar angle as x component and azimuthal angle as y component
		@code
			vector v1 = "45 0 0";
			vector v2 = "15 60 0";
			Print( v1.AnglesToVector() );
			Print( v2.AnglesToVector() );

			>> <0.707107,0,0.707107>
			>> <0.482963,0.836516,0.258819>
		@endcode
	*/
	proto vector AnglesToVector();

	/**
	\brief Creates rotation matrix from angles
		\param ang \p vector which contains angles
	    \param[out] mat \p vector created rotation matrix
		@code
	        vector mat[3];
			vector ang = "70 15 45";
	    	ang.RotationMatrixFromAngles( mat );
	    	Print( mat );

			>> <0.330366,0.0885213,-0.939693>,<0.458809,0.854988,0.241845>,<0.824835,-0.511037,0.241845>
		@endcode
	*/
	proto void RotationMatrixFromAngles(out vector mat[3]);
	
	/**
	\brief Transforms position
		\param mat \p vector[4] transformation matrix
		\param vec \p vector position to transform
		\return \p vector transformed position
		@code
			vector mat[4] = { "1 0 0 0", "0 1 0 0", "0 0 1 1", "3 1 2 1" }; // translation matrix
			vector pos = "1 1 1";
			Print( vector.Multiply4(mat, pos) );

			>> <4,2,3>
		@endcode
	*/
	proto static vector Multiply4(vector mat[4]);

	/**
	\brief Transforms vector
		\param mat \p vector[3] transformation matrix
		\param vec \p vector vector to transform
		\return \p vector transformed vector
		@code
			vector mat[3] = { "2 0 0", "0 3 0", "0 0 1" }; // scale matrix
			vector vec = "1 1 1";
			Print( vector.Multiply3(mat, vec) );

			>> <2,3,1>
		@endcode
	*/
	proto static vector Multiply3(vector mat[3]);

	/**
	\brief Invert-transforms position
		\param mat \p vector[4] transformation matrix
		\param vec \p vector position to transform
		\return \p vector transformed position
		@code
			vector mat[4] = { "1 0 0 0", "0 1 0 0", "0 0 1 1", "3 1 2 1" }; // translation matrix
			vector pos = "1 1 1";
			Print( vector.InvMultiply4(mat, pos) );

			>> <-2,0,-1>
		@endcode
	*/
	proto static vector InvMultiply4(vector mat[4]);

	/**
	\brief Invert-transforms vector
		\param mat \p vector[3] transformation matrix
		\param vec \p vector vector to transform
		\return \p vector transformed vector
		@code
			vector mat[3] = { "1.5 2.5 0", "0.1 1.3 0", "0 0 1" }; // rotation matrix
			vector vec = "1 1 1";
			Print( vector.InvMultiply3(mat, vec) );

			>> <4,1.4,1>
		@endcode
	*/
	proto static vector InvMultiply3(vector mat[3]);
};

class typename
{
	/**
	\brief Dynamic variant to 'new' keyword. It creates new instance of class
		\returns \p volatile instance of class
		@code
			???
		@endcode
	*/
	proto volatile Class Spawn();
	
	//!Returns type name of variable as string
	proto native owned string ToString();
	
	/**
	\brief Returns true when type is the same as 'baseType', or inherited one.
		\param baseType typename
		\returns \p bool true when type is the same as 'baseType', or inherited one.
		@code
			???
		@endcode
	*/
	proto native bool IsInherited(typename baseType);
};
