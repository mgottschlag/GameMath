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

#ifndef GAMEMATH_PLATFORM_HPP_INCLUDED
#define GAMEMATH_PLATFORM_HPP_INCLUDED

#if defined(_MSC_VER) || defined(_WINDOWS_) || defined(_WIN32)
	#define GAMEMATH_WINDOWS
#elif defined(unix) || defined(__unix__) || defined(__unix)
	#define GAMEMATH_UNIX
#else
	#error Unsupported platform!
#endif

#if defined(_MSC_VER)
	#define GAMEMATH_MSVC
#else
	#define GAMEMATH_GCC
#endif

#endif
