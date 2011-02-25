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
using namespace math;

#include <limits>
using namespace std;

// Taken from:
// http://ksvanhorn.com/Articles/ctassert.html

template<bool Expression> struct ctassert
{
	enum { N = 1 - 2 * int(!Expression) };
	static char Test[N];
};
template<bool Expression> char ctassert<Expression>::Test[N];

// Fixed size integers

ctassert<numeric_limits<int8>::digits == 7> inttest1;
ctassert<numeric_limits<uint8>::digits == 8> inttest2;
ctassert<numeric_limits<int16>::digits == 15> inttest3;
ctassert<numeric_limits<uint16>::digits == 16> inttest4;
ctassert<numeric_limits<int32>::digits == 31> inttest5;
ctassert<numeric_limits<uint32>::digits == 32> inttest6;
ctassert<numeric_limits<int64>::digits == 63> inttest7;
ctassert<numeric_limits<uint64>::digits == 64> inttest8;

ctassert<numeric_limits<int8>::is_signed> signtest1;
ctassert<!numeric_limits<uint8>::is_signed> signtest2;
ctassert<numeric_limits<int16>::is_signed> signtest3;
ctassert<!numeric_limits<uint16>::is_signed> signtest4;
ctassert<numeric_limits<int32>::is_signed> signtest5;
ctassert<!numeric_limits<uint32>::is_signed> signtest6;
ctassert<numeric_limits<int64>::is_signed> signtest7;
ctassert<!numeric_limits<uint64>::is_signed> signtest8;

ctassert<sizeof(float32) == 4> floattest1;
ctassert<sizeof(float64) == 8> floattest2;

int main(int argc, char **argv)
{
	return 0;
}
