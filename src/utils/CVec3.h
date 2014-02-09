#pragma once

template<typename T>

class CVec3
{
public:
	CVec3()
		: x(0)
		, y(0)
		, z(0)
	{
	};

	CVec3(const CVec3& vec)
		: x(vec.x)
		, y(vec.y)
		, z(vec.z)
	{
    };

    CVec3(const CVec2<T>& vec, T v)
        : x(vec.x)
        , y(vec.y)
        , z(v)
    {
    };

	CVec3(T _x, T _y, T _z)
		: x(_x)
		, y(_y)
		, z(_z)
	{
	};

	CVec3(T value)
		: x(value)
		, y(value)
		, z(value)
	{
	};

	CVec3& operator =(const CVec3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	};

	~CVec3()
	{
	};

	T x;
	T y;
	T z;

	//-- Arifmetics

	CVec3 operator +(CVec3 value)
	{
		return CVec3(x + value.x, y + value.y, z + value.z);
	}
	
	CVec3 operator +(T value)
	{
		return CVec3(x + value, y + value, z + value);
	}

	CVec3& operator +=(CVec3 value)
	{
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}

	CVec3& operator +=(T value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}

	CVec3 operator -(CVec3 value)
	{
		return CVec3(x - value.x, y - value.y, z - value.z);
	}

	CVec3 operator -(T value)
	{
		return CVec3(x - value, y - value, z - value);
	}

	CVec3& operator -=(CVec3 value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}

	CVec3& operator -=(T value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}

};
