#include "RTv1.h"

float	len_vec(t_vec *vec)
{
	return (sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2)));
}

void	norm_vec(t_vec *to_normalize)
{
	float	len;

	len = len_vec(to_normalize);
	if (len != 1)
	{
		len = 1 / len;
		to_normalize->x *= len;
		to_normalize->y *= len;
		to_normalize->z *= len;
	}
}

t_vec	two_point_vector(t_dot p1, t_dot p2)
{
	t_vec	vec;

	vec.x = p2.x - p1.x;
	vec.y = p2.y - p1.y;
	vec.z = p2.z - p1.z;
	return (vec);
}
