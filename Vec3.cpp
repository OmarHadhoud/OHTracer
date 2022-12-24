#include "Vec3.hpp"
#include <cmath>

Vec3::Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec3::Vec3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 Vec3::operator-() const
{
	return Vec3{-x, -y, -z};
}

Vec3 Vec3::operator+(const Vec3 &other) const
{
	return Vec3{x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
	return Vec3{x - other.x, y - other.y, z - other.z};
}

Vec3 Vec3::operator+=(const Vec3 &other)
{
	*this = *this + other;
	return *this;
}

Vec3 Vec3::operator*(const Vec3 &other) const
{
	return Vec3{x * other.x, y * other.y, z * other.z};
}

Vec3 Vec3::operator*=(const Vec3 &other)
{
	*this = *this * other;
	return *this;
}

Vec3 Vec3::operator/(const Vec3 &other) const
{
	return Vec3{x / other.x, y / other.y, z / other.z};
}

Vec3 Vec3::operator/=(const Vec3 &other)
{
	*this = *this / other;
	return *this;
}

Vec3 Vec3::operator*(double t) const
{
	return Vec3{x * t, y * t, z * t};
}

Vec3 operator*(double t, const Vec3 &vec)
{
	return vec * t;
}

Vec3 Vec3::operator*=(double t)
{
	*this = *this * t;
	return *this;
}

Vec3 Vec3::operator/(double t) const
{
	return Vec3{x / t, y / t, z / t};
}

Vec3 Vec3::operator/=(double t)
{
	*this = *this / t;
	return *this;
}

std::ostream &operator<<(std::ostream &os, const Vec3 &vec)
{
	return os << vec.x << " " << vec.y << " " << vec.z;
}

double Vec3::LengthSquared() const
{
	return (x * x + y * y + z * z);
}

double Vec3::Length() const
{
	return sqrt(this->LengthSquared());
}

Vec3 Vec3::Cross(const Vec3 &other) const
{
	Vec3 res{};
	res.x = (this->y * other.z) - (this->z * other.y);
	res.y = (this->z * other.x) - (this->x * other.z);
	res.z = (this->x * other.y) - (this->y * other.x);
	return res;
}

double Vec3::Dot(const Vec3 &other) const
{
	return (this->x * other.x + this->y * other.y + this->z * other.z);
}

Vec3 Vec3::Normalize()
{
	*this = *this / this->Length();
	return *this;
}

Vec3 Cross(const Vec3 &a, const Vec3 &b)
{
	return a.Cross(b);
}

double Dot(const Vec3 &a, const Vec3 &b)
{
	return a.Dot(b);
}

Vec3 Lerp(const Vec3 &a, const Vec3 &b, double t)
{
	return a * (1.0 - t) + b * t;
}