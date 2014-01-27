#pragma once

template<typename T>

class CVec2
{
public:
	CVec2()
		: x(0)
		, y(0)
	{
	};

	CVec2(const CVec2& vec)
		: x(vec.x)
		, y(vec.y)
	{
	};

	CVec2(T _x, T _y)
		: x(_x)
		, y(_y)
	{
	};

	// Should be implicit?
	CVec2(T value)
		: x(value)
		, y(value)
	{
	};

	CVec2& operator =(const CVec2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	};

	~CVec2()
	{
	};

	T x;
	T y;

	//-- Arifmetics

	CVec2 operator +(CVec2 value)
	{
		return CVec2(x + value.x, y + value.y);
	}

	// Should be implicit?
	CVec2 operator +(T value)
	{
		return CVec2(x + value, y + value);
	}

	CVec2& operator +=(CVec2 value)
	{
		x += value.x;
		y += value.y;
		return this;
	}

	// Should be implicit?
	CVec2& operator +=(T value)
	{
		x += value;
		y += value;
		return this;
	}

	CVec2 operator -(CVec2 value)
	{
		return CVec2(x - value.x, y - value.y);
	}

	// Should be implicit?
	CVec2 operator -(T value)
	{
		return CVec2(x - value, y - value);
	}

	CVec2& operator -=(CVec2 value)
	{
		x -= value.x;
		y -= value.y;
		return this;
	}

	// Should be implicit?
	CVec2& operator -=(T value)
	{
		x -= value;
		y -= value;
		return this;
	}

	//-- Comparison

	bool operator ==(CVec2 value)
	{
		return (x == value.x) && (y == value.y);
	}
};
