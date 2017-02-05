/*
Copyright (C) 2011, Mathias Gottschlag

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
