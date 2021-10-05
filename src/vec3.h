#pragma once

#include <iostream>
#include <sstream>
#include <cmath>

// note: adding inline or defining in a different class wont make a difference, compiler will probably optimise on its own.
namespace spx
{
	class Vec3
	{
	public:
		Vec3();
		Vec3(float value);
		Vec3(float x, float y, float z);

		inline float getX();
		inline float getY();
		inline float getZ();

		inline float getR();
		inline float getG();
		inline float getB();

		inline void setX(float vx);
		inline void setY(float vy);
		inline void setZ(float vz);

		inline Vec3& operator+=(const Vec3& other);
		inline Vec3& operator-=(const Vec3& other);
		inline Vec3& operator*=(const Vec3& other);
		inline Vec3& operator/=(const Vec3& other);

		inline Vec3& operator*=(float value);
		inline Vec3& operator/=(float value);

		inline Vec3 operator-();

		inline float getLength();
		inline float getLengthSquare();

		inline Vec3& normalize();
		inline Vec3 getNormalized();

		inline friend Vec3 operator+(const Vec3& a, const Vec3& b);
		inline friend Vec3 operator-(const Vec3& a, const Vec3& b);
		inline friend Vec3 operator*(const Vec3& a, const Vec3& b);
		inline friend Vec3 operator/(const Vec3& a, const Vec3& b);

		inline friend float dot(const Vec3& a, const Vec3& b);
		inline friend Vec3 cross(const Vec3& a, const Vec3& b);

		inline friend std::ostream& operator<<(std::ostream& out, const Vec3& vec);
		inline friend void display(const Vec3& vec);

		inline static Vec3 zero();

	private:
		float x;
		float y;
		float z;
	};

	inline Vec3::Vec3(): x(0.0f), y(0.0f), z(0.0f)
	{
	}

	inline Vec3::Vec3(float value): x(value), y(value), z(value)
	{
	}

	inline Vec3::Vec3(float x, float y, float z): x(x), y(y), z(z)
	{
	}

	inline float Vec3::getX()
	{
		return x;
	}

	inline float Vec3::getY()
	{
		return y;
	}

	inline float Vec3::getZ()
	{
		return z;
	}

	inline float Vec3::getR()
	{
		return x;
	}

	inline float Vec3::getG()
	{
		return y;
	}

	inline float Vec3::getB()
	{
		return z;
	}

	inline void Vec3::setX(float vx)
	{
		x = vx;
	}

	inline void Vec3::setY(float vy)
	{
		y = vy;
	}

	inline void Vec3::setZ(float vz)
	{
		z = vz;
	}

	inline Vec3& Vec3::operator+=(const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	inline Vec3& Vec3::operator-=(const Vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	inline Vec3& Vec3::operator*=(const Vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	inline Vec3& Vec3::operator/=(const Vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	inline Vec3& Vec3::operator*=(float value)
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}


	inline Vec3& Vec3::operator/=(float value)
	{
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}

	inline Vec3 Vec3::operator-()
	{
		return Vec3(-x, -y, -z);
	}

	inline float Vec3::getLength()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	inline float Vec3::getLengthSquare()
	{
		return getLength() * getLength();
	}

	inline Vec3& Vec3::normalize()
	{
		*this /= getLength();
		return *this;
	}

	inline Vec3 Vec3::getNormalized()
	{
		Vec3 result = Vec3(x / getLength(), y / getLength(), z / getLength());
		return result;
	}

	inline Vec3 operator+(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	inline Vec3 operator-(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

 	inline Vec3 operator*(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	inline Vec3 operator/(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	inline float dot(const Vec3& a, const Vec3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	inline Vec3 cross(const Vec3& a, const Vec3& b)
	{
		Vec3 product;
		product.x = a.y * b.z - a.z * b.y;
		product.y = -(a.x * b.z - a.z * b.x);
		product.z = a.x * b.y - b.x * a.y;

		return product;
	}

	inline std::ostream& operator<<(std::ostream& out, const Vec3& vec)
	{
		out << (int)vec.x << ", " << (int)vec.y << ", " << (int)vec.z;
		return out;
	}

	inline void display(const Vec3& vec)
	{
		printf("%d %d %d \n", (int)vec.x, (int)vec.y, (int)vec.z);
	}

	inline Vec3 Vec3::zero()
	{
		return Vec3(0.0f);
	}
}