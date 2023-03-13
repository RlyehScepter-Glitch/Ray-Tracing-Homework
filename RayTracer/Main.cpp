#include "Color.h"
#include "Ray.h"
#include "Vec3.h"

#include <fstream>

bool HitSphere(const Vec3& center, float radius, const Ray& ray) {
	Vec3 oc = ray.Origin() - center;
	auto a = Dot(ray.Direction(), ray.Direction());
	auto b = 2.0 * Dot(oc, ray.Direction());
	auto c = Dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

Vec3 RayColor(const Ray& ray) {
	if (HitSphere(Vec3(0, 0, -1), 0.5, ray))
		return Vec3(1, 0, 0);
	Vec3 unitDirection = UnitVector(ray.Direction());
	auto t = 0.5 * (unitDirection.y() + 1.0);
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