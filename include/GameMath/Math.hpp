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
		
		// TODO: Fast float functions
	};
}

#endif
