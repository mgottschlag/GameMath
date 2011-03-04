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

#ifndef GAMEMATH_VEC4_HPP_INCLUDED
#define GAMEMATH_VEC4_HPP_INCLUDED

namespace math
{
	/**
	 * Class for four-dimensional vectors. These are column vectors usually.
	 */
	template<typename T> class Vec4
	{
	public:
		/**
		 * Constructor.
		 */
		Vec4() : x(0), y(0), z(0), w(0)
		{
		}
		/**
		 * Constructor.
		 */
		Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
		{
		}
		/**
		 * Constructor.
		 */
		template <class T2> Vec4(const Vec4<T2> &v)
			: x(v.x), y(v.y), z(v.z), w(v.w)
		{
		}

		/**
		 * Returns the squared length of the vector. Much less
		 * computationally expensive than getLength(). Good for comparing
		 * vector lengths.
		 */
		float getSquaredLength()
		{
			return x * x + y * y + z * z + w * w;
		}
		/**
		 * Returns the length of the vector.
		 */
		float getLength()
		{
			return sqrt(getSquaredLength());
		}

		/**
		 * Dot product.
		 */
		float dot(const Vec4<T> other)
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		template<typename T2> Vec4<T> operator*(T2 s) const
		{
			return Vec4<T>((T)(x * s),
			                  (T)(y * s),
			                  (T)(z * s),
			                  (T)(w * s));
		}
		template<typename T2> Vec4<T> &operator*=(T2 s)
		{
			x = x * s;
			y = y * s;
			z = z * s;
			w = w * s;
			return *this;
		}
		template<typename T2> Vec4<T> operator/(T2 s) const
		{
			return Vec4<T>((T)(x / s),
			                  (T)(y / s),
			                  (T)(z / s),
			                  (T)(w / s));
		}
		template<typename T2> Vec4<T> &operator/=(T2 s)
		{
			x = x / s;
			y = y / s;
			z = z / s;
			w = w / s;
			return *this;
		}
		template<typename T2> Vec4<T> operator+(const Vec4<T2> &v) const
		{
			return Vec4<T>((T)(x + v.x),
			                  (T)(y + v.y),
			                  (T)(z + v.z),
			                  (T)(w + v.w));
		}
		template<typename T2> Vec4<T> operator-(const Vec4<T2> &v) const
		{
			return Vec4<T>((T)(x - v.x),
			                  (T)(y - v.y),
			                  (T)(z - v.z),
			                  (T)(w - v.w));
		}
		template<typename T2> Vec4<T> &operator=(const Vec4<T2> &v)
		{
			x = (T)v.x;
			y = (T)v.y;
			z = (T)v.z;
			w = (T)v.w;
			return *this;
		}
		template<typename T2> Vec4<T> &operator+=(const Vec4<T2> &v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}
		template<typename T2> Vec4<T> &operator-=(const Vec4<T2> &v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}
		template<typename T2> bool operator==(const Vec4<T2> &v) const
		{
			return x == v.x && y == v.y && z == v.z && w == v.w;
		}
		template<typename T2> bool operator!=(const Vec4<T2> &v) const
		{
			return x != v.x || y != v.y || z != v.z || w != v.w;
		}

		T x;
		T y;
		T z;
		T w;
	};

	template<typename T> Vec4<T> operator*(T s, const Vec4<T> &v)
	{
		return v * s;
	}

	typedef Vec4<int> Vec4i;
	typedef Vec4<unsigned int> Vec4u;
	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;
}

#endif
