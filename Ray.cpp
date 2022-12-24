#include "Ray.hpp"
#include "Utils.hpp"

Vec3 Ray::Reflect(const Vec3 &normal) const
{
	// the direction is v - 2b, where v is the incident vector, b is the same as the normal but of length v . n
	return direction - normal * 2 * Dot(direction, normal);
}
Vec3 Ray::Refract(const Vec3 &normal, double refractionIndexRatio) const
{
	auto cosTheta = Dot(-direction, normal);
	auto sinTheta = sqrt(1 - pow(cosTheta, 2));
	bool canRefract = refractionIndexRatio * sinTheta <= 1.0;
	// apply shlick approximation
	auto r0 = pow(((1 - refractionIndexRatio) / (1 + refractionIndexRatio)), 2);
	auto r = r0 + (1 - r0) * pow((1 - cosTheta), 5);

	if (canRefract == false || r > random())
		return Reflect(normal);

	Vec3 refracted_perp = (direction + normal * fmin(cosTheta, 1.0)) * refractionIndexRatio;
	Vec3 refracted_par = normal * -sqrt(fabs(1 - (refracted_perp).LengthSquared()));
	return refracted_perp + refracted_par;
}