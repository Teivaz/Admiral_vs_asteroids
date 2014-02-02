#pragma once

template<typename T>
class CMat3
{
public:
    CMat3()
        : a1(static_cast<T>(0)), a2(static_cast<T>(0)), a3(static_cast<T>(0))
        , b1(static_cast<T>(0)), b2(static_cast<T>(0)), b3(static_cast<T>(0))
        , c1(static_cast<T>(0)), c2(static_cast<T>(0)), c3(static_cast<T>(0))
	{
	}

    CMat3(T value)
        : a1(value), a2(value), a3(value)
        , b1(value), b2(value), b3(value)
        , c1(value), c2(value), c3(value)
    {
    }
    
    CMat3(T row1col1, T row1col2, T row1col3,
          T row2col1, T row2col2, T row2col3, 
          T row3col1, T row3col2, T row3col3)
          : a1(row1col1), a2(row1col2), a3(row1col3)
          , b1(row2col1), b2(row2col2), b3(row2col3)
          , c1(row3col1), c2(row3col2), c3(row3col3)
    {
    }

    CMat3(T values[9])
        : a1(values[0]), a2(values[1]), a3(values[2])
        , b1(values[3]), b2(values[4]), b3(values[5])
        , c1(values[6]), c2(values[7]), c3(values[8])
    {
    }

    CMat3(const CMat3& mat)
        : a1(mat.a1), a2(mat.a2), a3(mat.a3)
        , b1(mat.b1), b2(mat.b2), b3(mat.b3)
        , c1(mat.c1), c2(mat.c2), c3(mat.c3)
	{
    }

    CMat3 Transpose() const
    {
        return CMat3(a1, b1, c1,
            a2, b2, c2,
            a3, b3, c3);
    }

    void SetIdentity()
    {
        a1 = static_cast<T>(1); a2 = static_cast<T>(0); a3 = static_cast<T>(0);
        b1 = static_cast<T>(0); b2 = static_cast<T>(1); b3 = static_cast<T>(0);
        c1 = static_cast<T>(0); c2 = static_cast<T>(0); c3 = static_cast<T>(1);
    }

    void SetScale(const CVec2<T>& scale)
    {
        a1 = scale.x;           a2 = static_cast<T>(0); a3 = static_cast<T>(0);
        b1 = static_cast<T>(0); b2 = scale.y;           b3 = static_cast<T>(0);
        c1 = static_cast<T>(0); c2 = static_cast<T>(0); c3 = static_cast<T>(1);
    }

    void SetTranslation(const CVec2<T>& pos)
    {
        a1 = static_cast<T>(1); a2 = static_cast<T>(0); a3 = pos.x;
        b1 = static_cast<T>(0); b2 = static_cast<T>(1); b3 = pos.y;
        c1 = static_cast<T>(0); c2 = static_cast<T>(0); c3 = static_cast<T>(1);
    }

    void SetRotatation(T rot)
    {
        T cosRot = cos(rot), sinRot = sin(rot);
        a1 = cosRot;            a2 = -sinRot;           a3 = static_cast<T>(0);
        b1 = sinRot;            b2 = cosRot;            b3 = static_cast<T>(0);
        c1 = static_cast<T>(0); c2 = static_cast<T>(0); c3 = static_cast<T>(1);
    }

    CMat3& operator =(const CMat3& mat)
    {
        a1 = mat.a1; a2 = mat.a2; a3 = mat.a3;
        b1 = mat.b1; b2 = mat.b2; b3 = mat.b3;
        c1 = mat.c1; c2 = mat.c2; c3 = mat.c3;
        return *this;
    };

	T a1, a2, a3;
	T b1, b2, b3;
	T c1, c2, c3;

	//-- Arifmetics

    CMat3 operator +(const CMat3& mat) const
	{
        return CMat3(a1 + mat.a1, a2 + mat.a2, a3 + mat.a3,
                     b1 + mat.b1, b2 + mat.b2, b3 + mat.b3,
                     c1 + mat.c1, c2 + mat.c2, c3 + mat.c3);
	}
	
    CMat3 operator +(T value) const
    {
        return CMat3(a1 + value, a2 + value, a3 + value,
                     b1 + value, b2 + value, b3 + value,
                     c1 + value, c2 + value, c3 + value);
	}

    CMat3& operator +=(const CMat3& mat)
    {
        a1 += mat.a1; a2 += mat.a2; a3 += mat.a3;
        b1 += mat.b1; b2 += mat.b2; b3 += mat.b3;
        c1 += mat.c1; c2 += mat.c2; c3 += mat.c3;
        return *this;
	}

    CMat3& operator +=(T value)
    {
        a1 += value; a2 += value; a3 += value;
        b1 += value; b2 += value; b3 += value;
        c1 += value; c2 += value; c3 += value;
        return *this;
	}

    CMat3 operator -() const
    {
        return CMat3() - *this;
    }

    CMat3 operator +() const
    {
        return *this;
    }

    CMat3 operator -(const CMat3& mat) const
    {
        return CMat3(a1 - mat.a1, a2 - mat.a2, a3 - mat.a3,
                     b1 - mat.b1, b2 - mat.b2, b3 - mat.b3,
                     c1 - mat.c1, c2 - mat.c2, c3 - mat.c3);
	}

    CMat3 operator -(T value) const
    {
        return CMat3(a1 - value, a2 - value, a3 - value,
                     b1 - value, b2 - value, b3 - value,
                     c1 - value, c2 - value, c3 - value);
    }

    CMat3& operator -=(const CMat3& mat)
    {
        a1 -= mat.a1; a2 -= mat.a2; a3 -= mat.a3;
        b1 -= mat.b1; b2 -= mat.b2; b3 -= mat.b3;
        c1 -= mat.c1; c2 -= mat.c2; c3 -= mat.c3;
        return *this;
    }

    CMat3& operator -=(T value)
    {
        a1 -= value; a2 -= value; a3 -= value;
        b1 -= value; b2 -= value; b3 -= value;
        c1 -= value; c2 -= value; c3 -= value;
        return *this;
    }

    CMat3 operator *(const CMat3& mat) explicit const
    {
        return CMat3(
            ((a1*mat.a1) + (a2*mat.b1) + (a3*mat.c1)), ((a1*mat.a2) + (a2*mat.b2) + (a3*mat.c2)), ((a1*mat.a3) + (a2*mat.b3) + (a3*mat.c3)),
            ((b1*mat.a1) + (b2*mat.b1) + (b3*mat.c1)), ((b1*mat.a2) + (b2*mat.b2) + (b3*mat.c2)), ((b1*mat.a3) + (b2*mat.b3) + (b3*mat.c3)),
            ((c1*mat.a1) + (c2*mat.b1) + (c3*mat.c1)), ((c1*mat.a2) + (c2*mat.b2) + (c3*mat.c2)), ((c1*mat.a3) + (c2*mat.b3) + (c3*mat.c3)));
    }

    T Det() const
    {
        return a1*b2*c3 + a2*b3*c1 + a3*b1*c2 - a3*b2*c1 - a2*b1*c3 - a1*b3*c2;
    }

    CVec3<T> operator *(const CVec3<T>& vec) const
    {
        return CVec3<T>(
            (a1*vec.x + a2*vec.y + a3*vec.z),
            (b1*vec.x + b2*vec.y + b3*vec.z),
            (c1*vec.x + c2*vec.y + c3*vec.z));
    }

};

