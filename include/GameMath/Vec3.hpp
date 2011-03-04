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

#ifndef GAMEMATH_VEC3_HPP_INCLUDED
#define GAMEMATH_VEC3_HPP_INCLUDED

#include "Math.hpp"

#include <cmath>
#include <string>
#include <cstdlib>

namespace math
{
	/**
	 * Class for three-dimensional vectors, used for positions/rotation.
	 */
	template<typename T> class Vec3
	{
		public:
			/**
			 * Constructor.
			 */
			Vec3() : x(0), y(0), z(0)
			{
			}
			/**
			 * Constructor.
			 */
			Vec3(T x, T y, T z) : x(x), y(y), z(z)
			{
			}
			/**
			 * Constructor.
			 */
			template <class T2> Vec3(const Vec3<T2> &v)
				: x(v.x), y(v.y), z(v.z)
			{
			}
			/**
			 * Constructor.
			 */
			Vec3(const char *s)
			{
				set(s);
			}
			/**
			 * Constructor.
			 */
			Vec3(const std::string &s)
			{
				set(s);
			}

			/**
			 * Returns the squared length of the vector. Much less
			 * computationally expensive than getLength(). Good for comparing
			 * vector lengths.
			 */
			float getSquaredLength() const
			{
				return x * x + y * y + z * z;
			}
			/**
			 * Returns the length of the vector.
			 */
			float getLength() const
			{
				return sqrt(getSquaredLength());
			}
			/**
			 * Scales the vector so that it has the length 1.
			 */
			Vec3<T> &normalize()
			{
				*this /= getLength();
				return *this;
			}

			/**
			 * Rotates the vector around the z axis.
			 * @param angle Angle in degrees.
			 */
			void rotateXY(float angle)
			{
				angle = Math::degToRad(angle);
				float s = sin(angle);
				float c = cos(angle);
				*this = Vec3<T>(c * x - s * y, s * x + c * y, z);
			}
			/**
			 * Rotates the vector around the y axis.
			 * @param angle Angle in degrees.
			 */
			void rotateXZ(float angle)
			{
				angle = Math::degToRad(angle);
				float s = sin(angle);
				float c = cos(angle);
				*this = Vec3<T>(-c * x + s * z, y, s * x + c * z);
			}
			/**
			 * Rotates the vector around the x axis.
			 * @param angle Angle in degrees.
			 */
			void rotateYZ(float angle)
			{
				angle = Math::degToRad(angle);
				float s = sin(angle);
				float c = cos(angle);
				*this = Vec3<T>(x, c * y - s * z, s * y + c * z);
			}
			/**
			 * Rotates the vector using the given angles. First z rotation is
			 * applied, then x and then z.
			 */
			void rotate(const Vec3<float> &angles)
			{
				rotateXY(angles.z);
				rotateYZ(angles.x);
				rotateXZ(angles.y);
			}

			/**
			 * Dot product.
			 */
			float dot(const Vec3<T> other) const
			{
				return x * other.x + y * other.y + z * other.z;
			}
			/**
			 * Cross product.
			 */
			Vec3<T> cross(const Vec3<T> other) const
			{
				return Vec3<T>(y * other.z - z * other.y,
				                  z * other.x - x * other.z,
				                  x * other.y - y * other.x);
			}

			/**
			 * Returns the rotation of this vector relative to (0/0/1).
			 */
			Vec3<float> getAngle() const
			{
				Vec3<float> angle;
				angle.y = Math::radToDeg(atan2(x, z));
				angle.x = Math::radToDeg(atan2(sqrt(x * x + z * z), y)) - 90;
				if (angle.y < 0)
					angle.y += 360;
				if (angle.y >= 360)
					angle.y -= 360;
				if (angle.x < 0)
					angle.x += 360;
				if (angle.x >= 360)
					angle.x -= 360;
				return angle;
			}

			/**
			 * Sets the vector to the linear interpolation between a and b.
			 * \param a First vector
			 * \param b Second vector
			 * \param d Interpolation factor. If it is 0, then the vector will
			 * be set to a, if it is 1, the vector will be b.
			 */
			Vec3<T> &interpolate(const Vec3<T> &a,
			                        const Vec3<T> &b,
			                        float d)
			{
				Vec3<T> dv = b - a;
				*this = a + dv * d;
				return *this;
			}
			
			// TODO: sin(), cos() on multiple components?

			/**
			 * Reads the vector from a string in the form "x/y/z".
			 */
			void set(const std::string &s, const std::string &separator = "/")
			{
				unsigned int sepsize = separator.size();
				// TODO: Make the separator configurable?
				size_t separatorpos = s.find(separator);
				size_t separator2pos;
				if (separatorpos != std::string::npos)
					separator2pos = s.find(separator, separatorpos + sepsize);
				if ((separatorpos == std::string::npos)
					|| (separator2pos == std::string::npos))
				{
					x = 0;
					y = 0;
					z = 0;
				}
				else
				{
					x = (T)atof(s.c_str());
					const char *ys = s.c_str() + separatorpos + sepsize;
					y = (T)atof(ys);
					const char *zs = s.c_str() + separator2pos + sepsize;
					z = (T)atof(zs);
				}
			}

			template<typename T2> Vec3<T> operator*(T2 s) const
			{
				return Vec3<T>((T)(x * s), (T)(y * s), (T)(z * s));
			}
			template<typename T2> Vec3<T> &operator*=(T2 s)
			{
				x = x * s;
				y = y * s;
				z = z * s;
				return *this;
			}
			template<typename T2> Vec3<T> operator/(T2 s) const
			{
				return Vec3<T>((T)(x / s), (T)(y / s), (T)(z / s));
			}
			template<typename T2> Vec3<T> &operator/=(T2 s)
			{
				x = x / s;
				y = y / s;
				z = z / s;
				return *this;
			}
			template<typename T2> Vec3<T> operator+(const Vec3<T2> &v) const
			{
				return Vec3<T>((T)(x + v.x), (T)(y + v.y), (T)(z + v.z));
			}
			template<typename T2> Vec3<T> operator-(const Vec3<T2> &v) const
			{
				return Vec3<T>((T)(x - v.x), (T)(y - v.y), (T)(z - v.z));
			}
			template<typename T2> Vec3<T> operator*(const Vec3<T2> &v) const
			{
				return Vec3<T>((T)(x * v.x), (T)(y * v.y), (T)(z * v.z));
			}
			template<typename T2> Vec3<T> &operator=(const Vec3<T2> &v)
			{
				x = (T)v.x;
				y = (T)v.y;
				z = (T)v.z;
				return *this;
			}
			Vec3<T> operator-()
			{
				return Vec3<T>(-x, -y, -z);
			}
			Vec3<T> &operator=(const std::string &s)
			{
				set(s);
				return *this;
			}
			Vec3<T> &operator=(const char *s)
			{
				set(s);
				return *this;
			}
			template<typename T2> Vec3<T> &operator+=(const Vec3<T2> &v)
			{
				x += v.x;
				y += v.y;
				z += v.z;
				return *this;
			}
			template<typename T2> Vec3<T> &operator-=(const Vec3<T2> &v)
			{
				x -= v.x;
				y -= v.y;
				z -= v.z;
				return *this;
			}
			template<typename T2> bool operator==(const Vec3<T2> &v) const
			{
				return x == v.x && y == v.y && z == v.z;
			}
			template<typename T2> bool operator!=(const Vec3<T2> &v) const
			{
				return x != v.x || y != v.y || z != v.z;
			}

			T x;
			T y;
			T z;
	};

	template<typename T> Vec3<T> operator*(T s, const Vec3<T> &v)
	{
		return v * s;
	}

	typedef Vec3<int> Vec3i;
	typedef Vec3<unsigned int> Vec3u;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;
}

#endif
