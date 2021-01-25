#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "ray.h"

// Axis-aligned bounding box class

class aabb
{
public:
	aabb() {}
	aabb(const point3& a, const point3& b)
	{
		minimum = a;
		maximum = b;
	}

	point3 min() const { return minimum; }
	point3 max() const { return maximum; }

	point3 minimum;
	point3 maximum;

	bool hit(const ray& r, double t_min, double t_max) const {
		for (int i = 0; i < 3; i++)
		{
			auto invD = 1.0f / r.direction()[i];
			auto t0 = (min()[i] - r.origin()[i]) * invD;
			auto t1 = (max()[i] - r.origin()[i]) * invD;

			if (invD < 0.0f)
			{
				std::swap(t0, t1);
			}
			
			t_min = std::max(t0, t_min);
			t_max = std::min(t1, t_max);

			if (t_max <= t_min)
			{
				return false;
			}
		}

		return true;
	}
};

aabb surrounding_box(aabb box0, aabb box1) {
	point3 small(fmin(box0.min().x(), box1.min().x()),
		fmin(box0.min().y(), box1.min().y()),
		fmin(box0.min().z(), box1.min().z()));

	point3 big(fmax(box0.max().x(), box1.max().x()),
		fmax(box0.max().y(), box1.max().y()),
		fmax(box0.max().z(), box1.max().z()));

	return aabb(small, big);
}
#endif