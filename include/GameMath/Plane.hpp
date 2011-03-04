/*
Copyright (C) 2010, Mathias Gottschlag

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

#ifndef _CORERENDER_MATH_PLANE_HPP_INCLUDED_
#define _CORERENDER_MATH_PLANE_HPP_INCLUDED_

#include <GameMath.hpp>

namespace math
{
	/**
	 * Class which represents an infinite plane in 3d space.
	 * 
	 * @note The normal vector of the plane is not normalized, if you depend on
	 * this behaviour, you have to do this manually.
	 */
	class Plane
	{
		public:
			/**
			 * Constructor.
			 */
			Plane()
				: normal(0, 1, 0), d(0)
			{
			}
			/**
			 * Constructor.
			 *
			 * @param normal Normal vector.
			 * @param d Offset of the plane.
			 */
			Plane(const Vec3f &normal, float d)
				: normal(normal), d(d)
			{
			}
			/**
			 * Constructor.
			 *
			 * @param a Normal vector (x).
			 * @param b Normal vector (y).
			 * @param c Normal vector (z).
			 * @param d Offset of the plane.
			 */
			Plane(float a, float b, float c, float d)
				: normal(a, b, c), d(d)
			{
			}
			/**
			 * Creates a plane which contains the three points.
			 *
			 * The normal vector of the plane then is (p2 - p1).cross(p3 - p1).
			 *
			 * @param p1 First point.
			 * @param p2 Second point.
			 * @param p3 Third point.
			 */
			Plane(const Vec3f &p1, const Vec3f &p2, const Vec3f &p3)
			{
				Vec3f v1 = p2 - p1;
				Vec3f v2 = p3 - p1;
				normal = v1.cross(v2);
				d = p1.dot(normal);
			}

			/**
			 * Sets the length of the normal vector to 1 and scales d
			 * accordingly.
			 */
			void normalize()
			{
				float length = normal.getLength();
				d /= length;
				normal /= length;
			}

			/**
			 * Returns the distance of the point relative to the plane. The unit
			 * of the returned value is the length of the normal vector of the
			 * plane, so use this with a vector with the length 1 to get the
			 * "real" distance. You can use this with a different vector length
			 * to find out on which side of the plane the point is.
			 *
			 * @param point Point to compute the distance to.
			 * @return Distance of the point to the plane.
			 */
			float getDistance(const Vec3f &point)
			{
				float d2 = point.dot(normal);
				return d2 - d;
			}

			/**
			 * Returns the whether the plane and a line intersect and computes the
			 * intersection point.
			 *
			 * Note that this uses an infinite plane and an infinite line, so if
			 * you only want results within a certain area, you should use
			 * intersectWithLineSegment().
			 * 
			 * @param lineoffset Point on the line.
			 * @param linedirection Direction of the line.
			 * @param intersection If not 0, the result is written into this vector.
			 * @return True if the plane and the line intersect.
			 */
			bool intersectWithLine(Vec3f lineoffset,
								Vec3f linedirection,
								Vec3f *intersection = 0)
			{
				float ndotd = normal.dot(linedirection);
				if (ndotd == 0)
				{
					// The line is parallel with the plane, so we either have
					// infinitely many intersections or no intersection
					if (getDistance(lineoffset) == 0)
					{
						if (intersection)
							*intersection = lineoffset;
						return true;
					}
					else
						return false;
				}
				else
				{
					// We have exactly one intersection point as the line and the
					// plane are not parallel
					if (intersection)
					{
						float ndotv = normal.dot(lineoffset);
						float s = (d - ndotv) / ndotd;
						*intersection = lineoffset + s * linedirection;
					}
					return true;
				}
			}

			/**
			 * Returns whether the plane and a line segment intersect and
			 * computes the intersection point.
			 * 
			 * @param point1 Start of the line segment.
			 * @param point2 End of the line segment.
			 * @param intersection If not 0, the result is written into this vector.
			 * @return True if the plane and the line intersect.
			 */
			bool intersectWithLineSegment(Vec3f point1,
										Vec3f point2,
										Vec3f *intersection = 0)
			{
				float ndotd = normal.dot(point2 - point1);
				if (ndotd == 0)
				{
					// The line is parallel with the plane, so we either have
					// infinitely many intersections or no intersection
					if (getDistance(point1) == 0)
					{
						if (intersection)
							*intersection = point1;
						return true;
					}
					else
						return false;
				}
				else
				{
					// We have at most one intersection point as the line and the
					// plane are not parallel
					if (intersection)
					{
						float ndotv = normal.dot(point1);
						float s = (d - ndotv) / ndotd;
						// Check whether the intersection point is in the segment
						if (s > 1.0f)
							return false;
						if (s < 0.0f)
							return false;
						*intersection = (1.0f - s) * point1 + s * point2;
					}
					return true;
				}
			}

			/**
			 * Normal vector of the plane.
			 */
			Vec3f normal;
			/**
			 * Offset of the plane. All points with p.dot(normal)=d are in the
			 * plane.
			 */
			float d;
		};
}

#endif
