#include "RTv1.h"

float	ft_clamp(float to_clamp, float min, float max)
{
	if (to_clamp > max)
		return (max);
	if (to_clamp < min)
		return (min);
	return (to_clamp);
}

float	two_point_dist(t_dot p1, t_dot p2)
{
	float	dist;

	dist = pow(p2.x - p1.x, 2) + pow(p2.y - p2.y, 2) + pow(p2.z - p2.z, 2);
	return (dist);
}

float	degree_to_radian(float degree)
{
	return (degree * M_PI / 180.0);
}
