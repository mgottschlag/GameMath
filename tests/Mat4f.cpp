
#include "GameMath.hpp"

#include <iostream>

using namespace math;

int main(int argc, char **argv)
{
	unsigned int errors = 0;
	{
		// Mat4f * Vec4f
		Mat4f m(0, 0, 0, 1,
		        1, 0, 0, 0,
		        0, 1, 0, 0,
		        0, 0, 1, 0);
		Vec4f v(1, 2, 3, 4);
		v = m * v;
		if (v != Vec4f(4, 1, 2, 3))
		{
			std::cout << "Mat4f * Vec4f:" << std::endl;
			std::cout << "(" << v.x << ")   (0 0 0 1)   (1)" << std::endl;
			std::cout << "(" << v.x << ")   (1 0 0 0)   (2)" << std::endl;
			std::cout << "(" << v.z << ") = (0 1 0 0) * (3)" << std::endl;
			std::cout << "(" << v.w << ")   (0 0 1 0)   (4)" << std::endl;
			errors++;
		}
	}
	{
		// Mat4f * Mat4f
		Mat4f m1(1, 2, 3, 4,
		         5, 6, 7, 8,
		         9, 1, 2, 3,
		         4, 5, 6, 7);
		Mat4f m2(3, 1, 4, 2,
		         9, 8, 6, 7,
		         1, 3, 5, 7,
		         2, 4, 6, 8);
		Mat4f result(32, 42, 55, 69,
		             92, 106, 139, 165,
		             44, 35,  70, 63,
		             77, 90, 118, 141);
		if (result != m1 * m2)
		{
			std::cout << "Mat4f * Mat4f" << std::endl;
			errors++;
		}
	}
	{
		// Identity
		Mat4f m = Mat4f::Identity();
		Vec4f v(1, 2, 3, 4);
		Vec4f v2 = m * v;
		if (v2 != v)
		{
			std::cout << "Identity" << std::endl;
			errors++;
		}
	}
	{
		// Determinant
		Mat4f m(1, 2, 3, 4,
		        5, 6, 7, 8,
		        1, 2, 0, 7,
		        9, 1, 3, 1);
		if (m.determinant() != 312)
		{
			std::cout << "determinant(): " << m.determinant()
				<< "(correct: 312)" << std::endl;
			errors++;
		}
	}
	{
		// Transposed
		Mat4f m1(1, 2, 3, 4,
		         5, 6, 7, 8,
		         9, 1, 2, 3,
		         4, 5, 6, 7);
		Mat4f m2(1, 5, 9, 4,
		         2, 6, 1, 5,
		         3, 7, 2, 6,
		         4, 8, 3, 7);
		if (m1.transposed() != m2)
		{
			std::cout << "transposed()" << std::endl;
			errors++;
		}
	}
	{
		// Translation (w = 1)
		Mat4f m = Mat4f::TransMat(Vec3f(1, 2, 3));
		Vec4f v(1, 2, 3, 1);
		Vec4f res = m * v;
		if (res != Vec4f(2, 4, 6, 1))
		{
			std::cout << "Translation (w = 1):" << std::endl;
			std::cout << "(" << res.x << ")   (1)" << std::endl;
			std::cout << "(" << res.y << ")   (2)                 (1)" << std::endl;
			std::cout << "(" << res.z << ") = (3) translated with (2)" << std::endl;
			std::cout << "(" << res.w << ")   (1)                 (3)" << std::endl;
			errors++;
		}
	}
	{
		// Translation (w = 1)
		Mat4f m = Mat4f::TransMat(Vec3f(1, 2, 3));
		Vec4f v(3, 1, 3, 2);
		Vec4f res = m * v;
		if (res != Vec4f(5, 5, 9, 2))
		{
			std::cout << "Translation (w = 1):" << std::endl;
			std::cout << "(" << res.x << ")   (3)" << std::endl;
			std::cout << "(" << res.y << ")   (1)                 (1)" << std::endl;
			std::cout << "(" << res.z << ") = (3) translated with (2)" << std::endl;
			std::cout << "(" << res.w << ")   (2)                 (3)" << std::endl;
			errors++;
		}
	}
	{
		// Scaling
		Mat4f m = Mat4f::ScaleMat(Vec3f(1, 2, 3));
		Vec4f v(3, 1, 3, 2);
		Vec4f res = m * v;
		if (res != Vec4f(3, 2, 9, 2))
		{
			std::cout << "Scaling:" << std::endl;
			std::cout << "(" << res.x << ")   (3)" << std::endl;
			std::cout << "(" << res.y << ")   (1)             (1)" << std::endl;
			std::cout << "(" << res.z << ") = (3) scaled with (2)" << std::endl;
			std::cout << "(" << res.w << ")   (2)             (3)" << std::endl;
			errors++;
		}
	}
	{
		// Inverse
		Mat4f m1(0, 0, 0, 1,
		         2, 0, 1, 0,
		         0, 1, 1, 0,
		         1, 0, 0, 3);
		Mat4f m2(-3, 0, 0, 1,
		         -6, -1, 1, 2,
		         6, 1, 0, -2,
		         1, 0, 0, 0);
		if (m1.inverse() != m2)
		{
			std::cout << "Inverse" << std::endl;
			errors++;
		}
	}
	std::cout << errors << " errors." << std::endl;
	return errors;
}
