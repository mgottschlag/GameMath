
#include "GameMath.hpp"

#include <iostream>

using namespace math;

int main(int argc, char **argv)
{
	unsigned int errors = 0;
	{
		// Constructors:
		Plane plane;
		if (plane.normal != Vec3f(0, 1, 0) || plane.d != 0)
		{
			std::cout << "Default constructor wrong." << std::endl;
			errors++;
		}
		plane = Plane(Vec3f(0, 3, 0), 1);
		if (plane.normal != Vec3f(0, 3, 0) || plane.d != 1)
		{
			std::cout << "Constructor 2  wrong." << std::endl;
			errors++;
		}
		plane = Plane(1, 2, 3, 4);
		if (plane.normal != Vec3f(1, 2, 3) || plane.d != 4)
		{
			std::cout << "Constructor 3  wrong." << std::endl;
			errors++;
		}
		plane = Plane(Vec3f(0, 0, 1), Vec3f(0, 1, 1), Vec3f(1, 0, 1));
		if (plane.normal != Vec3f(0, 0, -1) || plane.d != -1)
		{
			std::cout << "Constructor 4 wrong." << std::endl;
			errors++;
		}
	}
	{
		// Line intersection
		Plane plane(Vec3f(1, 0, 1), 2);
		if (plane.intersectWithLine(Vec3f(0, 0, 0), Vec3f(0, 1, 0)))
		{
			std::cout << "No intersection expected (1)." << std::endl;
			errors++;
		}
		if (!plane.intersectWithLine(Vec3f(1, 0, 1), Vec3f(0, 1, 0)))
		{
			std::cout << "Intersection expected (1)." << std::endl;
			errors++;
		}
		Vec3f intersection(0, 0, 0);
		if (!plane.intersectWithLine(Vec3f(0, 0, 0), Vec3f(1, 1, 1), &intersection))
		{
			std::cout << "Intersection expected (2)." << std::endl;
			errors++;
		}
		if (intersection != Vec3f(1, 1, 1))
		{
			std::cout << "Wrong intersection point: "
				<< intersection.x << "/" << intersection.y << "/"
				<< intersection.z << std::endl;
			errors++;
		}
		if (!plane.intersectWithLineSegment(Vec3f(0, 0, 0), Vec3f(2, 2, 2), &intersection))
		{
			std::cout << "Intersection expected (3)." << std::endl;
			errors++;
		}
		if (intersection != Vec3f(1, 1, 1))
		{
			std::cout << "Wrong intersection point: "
				<< intersection.x << "/" << intersection.y << "/"
				<< intersection.z << std::endl;
			errors++;
		}
		if (!plane.intersectWithLineSegment(Vec3f(0, 0, 0), Vec3f(-2, -2, -2)))
		{
			std::cout << "No intersection expected (2)." << std::endl;
			errors++;
		}
	}
	std::cout << errors << " errors." << std::endl;
	return errors;
}
