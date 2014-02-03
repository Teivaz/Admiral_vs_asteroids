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
    
	CVec2 operator +(const CVec2& value) const
	{
		return CVec2(x + value.x, y + value.y);
	}

	CVec2 operator +(T value)
	{
		return CVec2(x + value, y + value);
	}

	CVec2& operator +=(const CVec2& value)
	{
		x += value.x;
		y += value.y;
		return *this;
	}

	CVec2& operator +=(T value)
	{
		x += value;
		y += value;
		return *this;
	}

	CVec2 operator -(const CVec2& value) const
	{
		return CVec2(x - value.x, y - value.y);
	}

	CVec2 operator -(T value) const
	{
		return CVec2(x - value, y - value);
	}

    CVec2 operator -() const
    {
        return CVec2(-x, -y);
    }

	CVec2& operator -=(const CVec2& value)
	{
		x -= value.x;
		y -= value.y;
		return *this;
	}

  	CVec2& operator -=(T value)
	{
		x -= value;
		y -= value;
		return *this;
	}
    
	bool operator ==(const CVec2& value) const
	{
		return (x == value.x) && (y == value.y);
	}

    CVec2 operator *(T value) const
    {
        return CVec2(x * value, y * value);
    }

    CVec2& operator *=(T value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    CVec2 operator *(const CVec2& value) const
    {
        return CVec2(x * value.x, y * value.y);
    }

    CVec2 operator /(T value) const
    {
        return CVec2(x / value, y / value);
    }

    T Dot(const CVec2& vec) const
    {
        return x*vec.x + y*vec.y;
    }

    T SqLength() const
    {
        return x*x + y*y;
    }

    T Length() const
    {
        return sqrt(x*x + y*y);
    }

    void Normalize()
    {
        T l = Length*();
        x /= l;
        y /= l;
    }

};

template<typename T>
CVec2<T> abs(const CVec2<T>& vec)
{
    return CVec2<T>(abs(vec.x), abs(vec.y));
}
