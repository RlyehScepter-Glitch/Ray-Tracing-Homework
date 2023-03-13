#include "Color.h"
#include "Ray.h"
#include "Vec3.h"

#include <fstream>

float HitSphere(const Vec3& center, float radius, const Ray& ray) {
	Vec3 oc = ray.Origin() - center;
	auto a = ray.Direction().LengthSquared();
	auto halfB = Dot(oc, ray.Direction());
	auto c = oc.LengthSquared() - radius * radius;
	auto discriminant = halfB * halfB - a * c;
	if(discriminant < 0)
	{
		return -1;
	}
	else 
	{
		return (-halfB - sqrt(discriminant)) / a;
	}
}

Vec3 RayColor(const Ray& ray) {
	auto t = HitSphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f, ray);

	if (t > 0.0f) {
		Vec3 N = UnitVector(ray.at(t) - Vec3(0.0f, 0.0f, -1.0f));
		return 0.5f * Vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}

	Vec3 unitDirection = UnitVector(ray.Direction());

	t = 0.5f * (unitDirection.y() + 1.0f);

	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

int main() {

	//Image
	const float aspectRatio = 16.0f / 9.0f;
	const int imageWidth = 1920;
	const int imageHeight = 1080;
	static const int maxColorComponent = 255;

	//Camera
	auto viewportHeight = 2.0;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0;

	auto origin = Vec3(0, 0, 0);
	auto horizontal = Vec3(viewportWidth, 0, 0);
	auto vertical = Vec3(0, viewportHeight, 0);
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

	//Render

	std::ofstream ppmFileStream("Sphere.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	for(int y = imageHeight - 1; y >= 0; y--)
	{
		std::cerr << "\rScanlines remaining: " << y << " " << std::flush;
		for (int x = 0; x < imageWidth; x++)
		{
			auto u = double(x) / (imageWidth - 1);
			auto v = double(y) / (imageHeight - 1);
			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			Vec3 pixelColor = RayColor(ray);
			WriteColor(ppmFileStream, pixelColor);
		}

	}

	ppmFileStream.close();

	std::cerr << "\nDone.\n";

}