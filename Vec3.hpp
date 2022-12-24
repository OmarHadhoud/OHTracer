#pragma once

#include <iostream>

class Vec3
{
public:
	union
	{
		struct
		{
			double x, y, z;
		};

		struct
		{
			double r, g, b;
		};

		double val[3];
	};

	// Constructor
	Vec3();
	Vec3(double x, double y, double z);
	// Operators Overloading
	Vec3 operator-() const;
	Vec3 operator+(const Vec3 &other) const;
	Vec3 operator-(const Vec3 &other) const;
	Vec3 operator+=(const Vec3 &other);
	Vec3 operator*(const Vec3 &other) const;
	Vec3 operator*=(const Vec3 &other);
	Vec3 operator/(const Vec3 &other) const;
	Vec3 operator/=(const Vec3 &other);
	Vec3 operator*(double t) const;
	Vec3 operator*=(double t);
	Vec3 operator/(double t) const;
	Vec3 operator/=(double t);
	friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec);
	// Vector functions
	double LengthSquared() const;
	double Length() const;
	Vec3 Cross(const Vec3 &other) const;
	double Dot(const Vec3 &other) const;
	Vec3 Normalize();
};

// Non member functions
Vec3 Cross(const Vec3 &a, const Vec3 &b);
double Dot(const Vec3 &a, const Vec3 &b);
Vec3 Lerp(const Vec3 &a, const Vec3 &b, double t);