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

#ifndef GAMEMATH_MAT4_HPP_INCLUDED
#define GAMEMATH_MAT4_HPP_INCLUDED

#include "Vec4.hpp"
#include "Mat3.hpp"

namespace math
{
	template<typename T> class Mat4
	{
	public:
		Mat4()
		{
		}
		Mat4(const Mat4<T> &other)
		{
			for (unsigned int i = 0; i < 16; i++)
			{
				m[i] = other.m[i];
			}
		}
		Mat4(const Mat3<T> &other)
		{
			Mat4<T> &m = *this;
			m(0, 0) = other(0, 0);
			m(0, 1) = other(0, 1);
			m(0, 2) = other(0, 2);
			m(0, 3) = 0;

			m(1, 0) = other(1, 0);
			m(1, 1) = other(1, 1);
			m(1, 2) = other(1, 2);
			m(1, 3) = 0;

			m(2, 0) = other(2, 0);
			m(2, 1) = other(2, 1);
			m(2, 2) = other(2, 2);
			m(2, 3) = 0;

			m(3, 0) = 0;
			m(3, 1) = 0;
			m(3, 2) = 0;
			m(3, 3) = 1;
		}
		Mat4(float m00, float m01, float m02, float m03,
		     float m10, float m11, float m12, float m13,
		     float m20, float m21, float m22, float m23,
		     float m30, float m31, float m32, float m33)
		{
			Mat4<T> &m = *this;
			m(0, 0) = m00;
			m(0, 1) = m01;
			m(0, 2) = m02;
			m(0, 3) = m03;

			m(1, 0) = m10;
			m(1, 1) = m11;
			m(1, 2) = m12;
			m(1, 3) = m13;

			m(2, 0) = m20;
			m(2, 1) = m21;
			m(2, 2) = m22;
			m(2, 3) = m23;

			m(3, 0) = m30;
			m(3, 1) = m31;
			m(3, 2) = m32;
			m(3, 3) = m33;
		}
		static Mat4<T> TransMat(const Vec3<T> &translation)
		{
			float x = translation.x;
			float y = translation.y;
			float z = translation.z;
			return Mat4<T>(1, 0, 0, x,
			               0, 1, 0, y,
			               0, 0, 1, z,
			               0, 0, 0, 1);
		}
		static Mat4<T> TransMat(T x, T y, T z)
		{
			return TransMat(Vec3f(x, y, z));
		}
		static Mat4<T> ScaleMat(const Vec3<T> &scale)
		{
			float x = scale.x;
			float y = scale.y;
			float z = scale.z;
			return Mat4<T>(x, 0, 0, 0,
			               0, y, 0, 0,
			               0, 0, z, 0,
			               0, 0, 0, 1);
		}
		static Mat4<T> ScaleMat(T x, T y, T z)
		{
			return ScaleMat(Vec3<T>(x, y, z));
		}
		static Mat4<T> Identity()
		{
			return Mat4<T>(1, 0, 0, 0,
			               0, 1, 0, 0,
			               0, 0, 1, 0,
			               0, 0, 0, 1);
		}
		static Mat4<T> PerspectiveFOV(float fov,
		                              float aspectratio,
		                              float znear,
		                              float zfar)
		{
			// TODO: Double accuracy?
			float radians = fov / 180.0f * 3.1415f;
			float t = tan(radians / 2);
			return Perspective(2 * t * znear * aspectratio,
			                   2 * t * znear,
			                   znear,
			                   zfar);
		}
		static Mat4<T> Perspective(float width,
		                           float height,
		                           float znear,
		                           float zfar)
		{
			return Perspective(-width / 2,
			                   width / 2,
			                   -height / 2,
			                   height / 2,
			                   znear,
			                   zfar);
		}
		static Mat4<T> Perspective(float left,
		                           float right,
		                           float bottom,
		                           float top,
		                           float znear,
		                           float zfar)
		{
			float w = right - left;
			float h = top - bottom;
			float r = right;
			float l = left;
			float t = top;
			float b = bottom;
			float n = znear;
			float f = zfar;
			return Mat4<T>(2*n/w, 0,     (r+l)/w,       0,
			               0,     2*n/h, (t+b)/h,       0,
			               0,     0,     -(f+n)/(f-n),  -2*f*n/(f-n),
			               0,     0,     -1,            0);
		}
		static Mat4<T> Ortho(float width,
		                     float height,
		                     float znear,
		                     float zfar)
		{
			return Ortho(-width / 2,
			             width / 2,
			             -height / 2,
			             height / 2,
			             znear,
			             zfar);
		}
		static Mat4<T> Ortho(float left,
		                     float right,
		                     float bottom,
		                     float top,
		                     float znear,
		                     float zfar)
		{
			float w = right - left;
			float h = top - bottom;
			float r = right;
			float l = left;
			float t = top;
			float b = bottom;
			float n = znear;
			float f = zfar;
			return Mat4<T>(2/w, 0,   0,        -(r+l)/w,
			               0,   2/h, 0,        -(t+b)/h,
			               0,   0,   -2/(f-n), -(f+n)/(f-n),
			               0,   0,   0,        1);
		}
		static Mat4<T> EulerRotation(Vec3<T> rotation)
		{
			// TODO: Test this
			// TODO
		}
		static Mat4<T> EulerRotationX(float rotation)
		{
			// TODO: Test this
			float s = sin(rotation);
			float c = cos(rotation);
			return Mat4<T>(1, 0, 0,  0,
			               0, c, -s, 0,
			               0, s, c,  0,
			               0, 0, 0,  1);

		}
		static Mat4<T> EulerRotationY(float rotation)
		{
			// TODO: Test this
			float s = sin(rotation);
			float c = cos(rotation);
			return Mat4<T>(c,  0, s, 0,
			               0,  1, 0, 0,
			               -s, 0, c, 0,
			               0,  0, 0, 1);
		}
		static Mat4<T> EulerRotationZ(float rotation)
		{
			// TODO: Test this
			float s = sin(rotation);
			float c = cos(rotation);
			return Mat4<T>(c, -s, 0, 0,
			               s, c,  0, 0,
			               0, 0,  1, 0,
			               0, 0,  0, 1);
		}

		float determinant() const
		{
			const Mat4<T> &m = *this;
			return (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) -
			       (m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
			       (m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)) +
			       (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) -
			       (m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
			       (m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0));
		}

		Mat4<T> inverse() const
		{
			Mat4<T> out;
			T d = determinant();
			if (d == 0)
				return out;
			d = 1 / d;

			const Mat4<T> &m = *this;
			out(0, 0) = d * (m(1, 1) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) +
			                 m(1, 2) * (m(2, 3) * m(3, 1) - m(2, 1) * m(3, 3)) +
			                 m(1, 3) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)));
			out(0, 1) = d * (m(2, 1) * (m(0, 2) * m(3, 3) - m(0, 3) * m(3, 2)) +
			                 m(2, 2) * (m(0, 3) * m(3, 1) - m(0, 1) * m(3, 3)) +
			                 m(2, 3) * (m(0, 1) * m(3, 2) - m(0, 2) * m(3, 1)));
			out(0, 2) = d * (m(3, 1) * (m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) +
			                 m(3, 2) * (m(0, 3) * m(1, 1) - m(0, 1) * m(1, 3)) +
			                 m(3, 3) * (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)));
			out(0, 3) = d * (m(0, 1) * (m(1, 3) * m(2, 2) - m(1, 2) * m(2, 3)) +
			                 m(0, 2) * (m(1, 1) * m(2, 3) - m(1, 3) * m(2, 1)) +
			                 m(0, 3) * (m(1, 2) * m(2, 1) - m(1, 1) * m(2, 2)));
			out(1, 0) = d * (m(1, 2) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) +
			                 m(1, 3) * (m(2, 2) * m(3, 0) - m(2, 0) * m(3, 2)) +
			                 m(1, 0) * (m(2, 3) * m(3, 2) - m(2, 2) * m(3, 3)));
			out(1, 1) = d * (m(2, 2) * (m(0, 0) * m(3, 3) - m(0, 3) * m(3, 0)) +
			                 m(2, 3) * (m(0, 2) * m(3, 0) - m(0, 0) * m(3, 2)) +
			                 m(2, 0) * (m(0, 3) * m(3, 2) - m(0, 2) * m(3, 3)));
			out(1, 2) = d * (m(3, 2) * (m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) +
			                 m(3, 3) * (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) +
			                 m(3, 0) * (m(0, 3) * m(1, 2) - m(0, 2) * m(1, 3)));
			out(1, 3) = d * (m(0, 2) * (m(1, 3) * m(2, 0) - m(1, 0) * m(2, 3)) +
			                 m(0, 3) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
			                 m(0, 0) * (m(1, 2) * m(2, 3) - m(1, 3) * m(2, 2)));
			out(2, 0) = d * (m(1, 3) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0)) +
			                 m(1, 0) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
			                 m(1, 1) * (m(2, 3) * m(3, 0) - m(2, 0) * m(3, 3)));
			out(2, 1) = d * (m(2, 3) * (m(0, 0) * m(3, 1) - m(0, 1) * m(3, 0)) +
			                 m(2, 0) * (m(0, 1) * m(3, 3) - m(0, 3) * m(3, 1)) +
			                 m(2, 1) * (m(0, 3) * m(3, 0) - m(0, 0) * m(3, 3)));
			out(2, 2) = d * (m(3, 3) * (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) +
			                 m(3, 0) * (m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) +
			                 m(3, 1) * (m(0, 3) * m(1, 0) - m(0, 0) * m(1, 3)));
			out(2, 3) = d * (m(0, 3) * (m(1, 1) * m(2, 0) - m(1, 0) * m(2, 1)) +
			                 m(0, 0) * (m(1, 3) * m(2, 1) - m(1, 1) * m(2, 3)) +
			                 m(0, 1) * (m(1, 0) * m(2, 3) - m(1, 3) * m(2, 0)));
			out(3, 0) = d * (m(1, 0) * (m(2, 2) * m(3, 1) - m(2, 1) * m(3, 2)) +
			                 m(1, 1) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
			                 m(1, 2) * (m(2, 1) * m(3, 0) - m(2, 0) * m(3, 1)));
			out(3, 1) = d * (m(2, 0) * (m(0, 2) * m(3, 1) - m(0, 1) * m(3, 2)) +
			                 m(2, 1) * (m(0, 0) * m(3, 2) - m(0, 2) * m(3, 0)) +
			                 m(2, 2) * (m(0, 1) * m(3, 0) - m(0, 0) * m(3, 1)));
			out(3, 2) = d * (m(3, 0) * (m(0, 2) * m(1, 1) - m(0, 1) * m(1, 2)) +
			                 m(3, 1) * (m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) +
			                 m(3, 2) * (m(0, 1) * m(1, 0) - m(0, 0) * m(1, 1)));
			out(3, 3) = d * (m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
			                 m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
			                 m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)));
			return out;
		}
		Mat4<T> transposed() const
		{
			const Mat4<T> &m = *this;
			Mat4<T> newmat;
			newmat(0, 0) = m(0, 0);
			newmat(1, 0) = m(0, 1);
			newmat(2, 0) = m(0, 2);
			newmat(3, 0) = m(0, 3);

			newmat(0, 1) = m(1, 0);
			newmat(1, 1) = m(1, 1);
			newmat(2, 1) = m(1, 2);
			newmat(3, 1) = m(1, 3);

			newmat(0, 2) = m(2, 0);
			newmat(1, 2) = m(2, 1);
			newmat(2, 2) = m(2, 2);
			newmat(3, 2) = m(2, 3);

			newmat(0, 3) = m(3, 0);
			newmat(1, 3) = m(3, 1);
			newmat(2, 3) = m(3, 2);
			newmat(3, 3) = m(3, 3);
			return newmat;
		}

		Mat4<T> translate(const Vec3<T> &v) const
		{
			// Source:
			// http://lists.freedesktop.org/archives/wayland-devel/2011-February/000618.html
			// TODO: Pass by value instead of reference?
			// TODO: Operate directly on this?
			Mat4<T> out(*this);
			// The translation is just added to the right-most column
			out.m[12] += v.x;
			out.m[13] += v.y;
			out.m[14] += v.z;
			return out;
		}
		
		Mat4<T> scale(const Vec3<T> &v) const
		{
			// Source:
			// http://lists.freedesktop.org/archives/wayland-devel/2011-February/000618.html
			// TODO: Pass by value instead of reference?
			Mat4<T> out(*this);
			// The first three lines are multiplied by the scale
			for (unsigned int i = 0; i < 4; i++)
			{
				out.m[0 + 4 * i] *= v.x;
				out.m[1 + 4 * i] *= v.y;
				out.m[2 + 4 * i] *= v.z;
			}
			return out;
		}

		Vec3<T> transformPoint(const Vec3<T> &point) const
		{
			Vec4<T> transformed = *this * Vec4<T>(point.x, point.y, point.z, 1);
			return Vec3<T>(transformed.x / transformed.w,
			               transformed.y / transformed.w,
			               transformed.z / transformed.w);
		}

		Vec4<T> operator*(const Vec4<T> &v) const
		{
			Vec4<T> out;
			const Mat4<T> &m = *this;
			out.x = v.x * m(0, 0) + v.y * m(0, 1) + v.z * m(0, 2) + v.w * m(0, 3);
			out.y = v.x * m(1, 0) + v.y * m(1, 1) + v.z * m(1, 2) + v.w * m(1, 3);
			out.z = v.x * m(2, 0) + v.y * m(2, 1) + v.z * m(2, 2) + v.w * m(2, 3);
			out.w = v.x * m(3, 0) + v.y * m(3, 1) + v.z * m(3, 2) + v.w * m(3, 3);
			return out;
		}

		Mat4<T> operator*(const Mat4<T> &o) const
		{
			Mat4<T> out;
			const Mat4<T> &m = *this;
			out(0, 0) = m(0, 0) * o(0, 0) + m(0, 1) * o(1, 0) + m(0, 2) * o(2, 0) + m(0, 3) * o(3, 0);
			out(0, 1) = m(0, 0) * o(0, 1) + m(0, 1) * o(1, 1) + m(0, 2) * o(2, 1) + m(0, 3) * o(3, 1);
			out(0, 2) = m(0, 0) * o(0, 2) + m(0, 1) * o(1, 2) + m(0, 2) * o(2, 2) + m(0, 3) * o(3, 2);
			out(0, 3) = m(0, 0) * o(0, 3) + m(0, 1) * o(1, 3) + m(0, 2) * o(2, 3) + m(0, 3) * o(3, 3);

			out(1, 0) = m(1, 0) * o(0, 0) + m(1, 1) * o(1, 0) + m(1, 2) * o(2, 0) + m(1, 3) * o(3, 0);
			out(1, 1) = m(1, 0) * o(0, 1) + m(1, 1) * o(1, 1) + m(1, 2) * o(2, 1) + m(1, 3) * o(3, 1);
			out(1, 2) = m(1, 0) * o(0, 2) + m(1, 1) * o(1, 2) + m(1, 2) * o(2, 2) + m(1, 3) * o(3, 2);
			out(1, 3) = m(1, 0) * o(0, 3) + m(1, 1) * o(1, 3) + m(1, 2) * o(2, 3) + m(1, 3) * o(3, 3);

			out(2, 0) = m(2, 0) * o(0, 0) + m(2, 1) * o(1, 0) + m(2, 2) * o(2, 0) + m(2, 3) * o(3, 0);
			out(2, 1) = m(2, 0) * o(0, 1) + m(2, 1) * o(1, 1) + m(2, 2) * o(2, 1) + m(2, 3) * o(3, 1);
			out(2, 2) = m(2, 0) * o(0, 2) + m(2, 1) * o(1, 2) + m(2, 2) * o(2, 2) + m(2, 3) * o(3, 2);
			out(2, 3) = m(2, 0) * o(0, 3) + m(2, 1) * o(1, 3) + m(2, 2) * o(2, 3) + m(2, 3) * o(3, 3);

			out(3, 0) = m(3, 0) * o(0, 0) + m(3, 1) * o(1, 0) + m(3, 2) * o(2, 0) + m(3, 3) * o(3, 0);
			out(3, 1) = m(3, 0) * o(0, 1) + m(3, 1) * o(1, 1) + m(3, 2) * o(2, 1) + m(3, 3) * o(3, 1);
			out(3, 2) = m(3, 0) * o(0, 2) + m(3, 1) * o(1, 2) + m(3, 2) * o(2, 2) + m(3, 3) * o(3, 2);
			out(3, 3) = m(3, 0) * o(0, 3) + m(3, 1) * o(1, 3) + m(3, 2) * o(2, 3) + m(3, 3) * o(3, 3);

			return out;
		}

		T &operator()(int row, int column)
		{
			return m[row + column * 4];
		}
		const T &operator()(int row, int column) const
		{
			return m[row + column * 4];
		}

		bool operator==(const Mat4<T> &other) const
		{
			for (unsigned int i = 0; i < 16; i++)
			{
				if (m[i] != other.m[i])
					return false;
				// TODO: Floating point comparison
			}
			return true;
		}
		bool operator!=(const Mat4<T> &other) const
		{
			return !(*this == other);
		}

		/**
		 * Matrix data for linear access. The values are stored in a
		 * column-major format, so the first column is at indices 0-3.
		 */
		T m[16];
	};

	typedef Mat4<float> Mat4f;
	typedef Mat4<double> Mat4d;
}

#endif
