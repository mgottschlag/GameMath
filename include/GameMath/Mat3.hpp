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

#ifndef GAMEMATH_MAT3_HPP_INCLUDED
#define GAMEMATH_MAT3_HPP_INCLUDED

#include "Vec3.hpp"

namespace math
{
	template<typename T> class Mat3
	{
	public:
		Mat3<T>()
		{
		}
		Mat3<T>(const Mat3<T> &other)
		{
			for (unsigned int i = 0; i < 9; i++)
			{
				m[i] = other.m[i];
			}
		}
		Mat3<T>(float m00, float m01, float m02,
		        float m10, float m11, float m12,
		        float m20, float m21, float m22)
		{
			Mat3<T> &m = *this;
			m(0, 0) = m00;
			m(0, 1) = m01;
			m(0, 2) = m02;

			m(1, 0) = m10;
			m(1, 1) = m11;
			m(1, 2) = m12;

			m(2, 0) = m20;
			m(2, 1) = m21;
			m(2, 2) = m22;
		}
		static Mat3<T> Identity()
		{
			return Mat3<T>(1, 0, 0,
			               0, 1, 0,
			               0, 0, 1);
		}

		Mat3 operator*(const Mat3 &o) const
		{
			const Mat3<T> &m = *this;
			return Mat3<T>(m(0, 0) * o(0, 0) + m(1, 0) * o(0, 1) + m(2, 0) * o(0, 2),
			               m(0, 1) * o(0, 0) + m(1, 1) * o(0, 1) + m(2, 1) * o(0, 2),
			               m(0, 2) * o(0, 0) + m(1, 2) * o(0, 1) + m(2, 2) * o(0, 2),

			               m(0, 0) * o(1, 0) + m(1, 0) * o(1, 1) + m(2, 0) * o(1, 2),
			               m(0, 1) * o(1, 0) + m(1, 1) * o(1, 1) + m(2, 1) * o(1, 2),
			               m(0, 2) * o(1, 0) + m(1, 2) * o(1, 1) + m(2, 2) * o(1, 2),

			               m(0, 0) * o(2, 0) + m(1, 0) * o(2, 1) + m(2, 0) * o(2, 2),
			               m(0, 1) * o(2, 0) + m(1, 1) * o(2, 1) + m(2, 1) * o(2, 2),
			               m(0, 2) * o(2, 0) + m(1, 2) * o(2, 1) + m(2, 2) * o(2, 2));
		}

		T &operator()(int row, int column)
		{
			return m[row + column * 3];
		}
		const T &operator()(int row, int column) const
		{
			return m[row + column * 3];
		}

		/**
		 * Matrix data for linear access. The values are stored in a
		 * row-major format, so the first row is at indices 0-2.
		 */
		T m[9];
	};

	typedef Mat3<float> Mat3f;
	typedef Mat3<double> Mat3d;
}

#endif
