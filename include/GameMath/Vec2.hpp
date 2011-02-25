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

#ifndef GAMEMATH_VEC2_HPP_INCLUDED
#define GAMEMATH_VEC2_HPP_INCLUDED

#include "Math.hpp"

#include <cmath>
#include <string>
#include <cstdlib>

namespace math
{
	/**
	 * Class for two-dimensional vectors.
	 */
	template<typename T> class Vec2
	{
		public:
			/**
			 * Constructor.
			 */
			Vec2() : x(0), y(0)
			{
			}
			/**
			 * Constructor.
			 */
			Vec2(T x, T y) : x(x), y(y)
			{
			}
			/**
			 * Constructor.
			 */
			template <class T2> Vec2(const Vec2<T2> &v)
				: x(v.x), y(v.y)
			{
			}
			/**
			 * Constructor.
			 */
			Vec2(const char *s)
			{
				set(s);
			}
			/**
			 * Constructor.
			 */
			Vec2(const std::string &s)
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
				return x * x + y * y;
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
			Vec2<T> &normalize()
			{
				*this /= getLength();
				return *this;
			}

			/**
			 * Rotates the vector.
			 * @param angle Angle in degrees.
			 */
			void rotate(float angle)
			{
				angle = Math::degToRad(angle);
				float s = sin(angle);
				float c = cos(angle);
				*this = Vec2<T>(c * x - s * y, s * x + c * y);
			}

			/**
			 * Dot product.
			 */
			float dot(const Vec2<T> other) const
			{
				return x * other.x + y * other.y;
			}

			/**
			 * Returns the rotation of this vector relative to (1/0).
			 */
			float getAngle() const
			{
				// TODO: Test this
				return Math::radToDeg(atan2(x, y));
			}

			/**
			 * Sets the vector to the linear interpolation between a and b.
			 * \param a First vector
			 * \param b Second vector
			 * \param d Interpolation factor. If it is 0, then the vector will
			 * be set to a, if it is 1, the vector will be b.
			 */
			Vec2<T> &interpolate(const Vec2<T> &a,
			                     const Vec2<T> &b,
			                     float d)
			{
				Vec2<T> dv = b - a;
				*this = a + dv * d;
				return *this;
			}
			
			// TODO: sin(), cos() on multiple components?

			/**
			 * Reads the vector from a string in the form "x/y".
			 */
			void set(const std::string &s, const std::string &separator = "/")
			{
				unsigned int sepsize = separator.size();
				// TODO: Make the separator configurable?
				size_t separatorpos = s.find(separator);
				if (separatorpos == std::string::npos)
				{
					x = 0;
					y = 0;
				}
				else
				{
					x = (T)atof(s.c_str());
					const char *ys = s.c_str() + separatorpos + sepsize;
					y = (T)atof(ys);
				}
			}

			template<typename T2> Vec2<T> operator*(T2 s) const
			{
				return Vec2<T>((T)(x * s), (T)(y * s));
			}
			template<typename T2> Vec2<T> &operator*=(T2 s)
			{
				x = x * s;
				y = y * s;
				return *this;
			}
			template<typename T2> Vec2<T> operator/(T2 s) const
			{
				return Vec2<T>((T)(x / s), (T)(y / s));
			}
			template<typename T2> Vec2<T> &operator/=(T2 s)
			{
				x = x / s;
				y = y / s;
				return *this;
			}
			template<typename T2> Vec2<T> operator+(const Vec2<T2> &v) const
			{
				return Vec2<T>((T)(x + v.x), (T)(y + v.y));
			}
			template<typename T2> Vec2<T> operator-(const Vec2<T2> &v) const
			{
				return Vec2<T>((T)(x - v.x), (T)(y - v.y));
			}
			template<typename T2> Vec2<T> operator*(const Vec2<T2> &v) const
			{
				return Vec2<T>((T)(x * v.x), (T)(y * v.y));
			}
			template<typename T2> Vec2<T> &operator=(const Vec2<T2> &v)
			{
				x = (T)v.x;
				y = (T)v.y;
				return *this;
			}
			Vec2<T> operator-()
			{
				return Vec2<T>(-x, -y);
			}
			Vec2<T> &operator=(const std::string &s)
			{
				set(s);
				return *this;
			}
			Vec2<T> &operator=(const char *s)
			{
				set(s);
				return *this;
			}
			template<typename T2> Vec2<T> &operator+=(const Vec2<T2> &v)
			{
				x += v.x;
				y += v.y;
				return *this;
			}
			template<typename T2> Vec2<T> &operator-=(const Vec2<T2> &v)
			{
				x -= v.x;
				y -= v.y;
				return *this;
			}
			template<typename T2> bool operator==(const Vec2<T2> &v) const
			{
				return x == v.x && y == v.y;
			}
			template<typename T2> bool operator!=(const Vec2<T2> &v) const
			{
				return x != v.x || y != v.y;
			}

			T x;
			T y;
	};

	typedef Vec2<int> Vec2i;
	typedef Vec2<unsigned int> Vec2u;
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;
}

#endif
