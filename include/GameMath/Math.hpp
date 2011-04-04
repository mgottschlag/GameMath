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

#ifndef GAMEMATH_MATH_HPP_INCLUDED
#define GAMEMATH_MATH_HPP_INCLUDED

#include "Types.hpp"

#define MATH_PI 3.14159265358979323846

namespace math
{
	class Math
	{
	public:
		static float degToRad(float degrees)
		{
			return degrees * ((float)MATH_PI / 180.0f);
		}
		static float radToDeg(float radians)
		{
			return radians * (180.0f / (float)MATH_PI);
		}
		static double degToRad(double degrees)
		{
			return degrees * (MATH_PI / 180.0);
		}
		static double radToDeg(double radians)
		{
			return radians * (180.0 / MATH_PI);
		}

		/**
		 * Performs a fast float-to-int conversion (bankers round).
		 */
		static int ftoi(const float val)
		{
			union
			{
				int64 i;
				double d;
			} conversion;

			static const double xs_doublemagic = (6755399441055744.0); // 2^52 * 1.5
			conversion.d = val + xs_doublemagic;
			// Cast to grab the bottom bits
			return (int)conversion.i;
		}

		/**
		 * Fast function to check whether an integer is a power of two or null.
		 * 
		 * This function is slightly faster than isPowerOfTwo().
		 */
		static bool isPowerOfTwoOrNull(unsigned int n)
		{
			// http://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
			return (n & (n - 1)) == 0;
		}

		/**
		 * Fast function to check whether an integer is a power of two.
		 */
		static bool isPowerOfTwo(unsigned int n)
		{
			// http://graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
			return n && !(n & (n - 1));
		}

		/**
		 * Fast function to calculate the logarithm of an integer if the integer
		 * is a power of two.
		 * 
		 * This function is slightly faster than log2().
		 */
		static unsigned int log2FromPowerOfTwo(unsigned int n)
		{
			// http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogDeBruijn
			static const int MultiplyDeBruijnBitPosition2[32] =
			{
				0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
				31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
			};
			return MultiplyDeBruijnBitPosition2[(uint32_t)(n * 0x077CB531U) >> 27];
		}

		/**
		 * Returns the smallest power of two which is larger than an integer.
		 */
		static unsigned int nextPowerOfTwo(unsigned int n)
		{
			// http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
			n--;
			n |= n >> 1;
			n |= n >> 2;
			n |= n >> 4;
			n |= n >> 8;
			n |= n >> 16;
			n++;
			return n;
		}

		/**
		 * Fast function to calculate the logarithm of an integer.
		 */
		static unsigned int log2(unsigned int n)
		{
			// http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogDeBruijn
			static const int MultiplyDeBruijnBitPosition[32] = 
			{
				0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
				8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
			};
			// First round down to one less than a power of 2 
			n |= n >> 1; 
			n |= n >> 2;
			n |= n >> 4;
			n |= n >> 8;
			n |= n >> 16;
			return MultiplyDeBruijnBitPosition[(uint32_t)(n * 0x07C4ACDDU) >> 27];
		}

		// TODO: Fast trigonometric functions
	};
}

#endif
