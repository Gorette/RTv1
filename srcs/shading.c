#include "RTv1.h"

t_color	secondary_rays(t_dot inter, t_data *d, t_obj *obj)
{
	t_dot	ld;
	t_vec	lo;
	float	dist;
	int		i;
	int		j;
	float	s1;
	float	s2;
	t_color	c;

	j = -1;
	c = new_color(obj->color.r, obj->color.g, obj->color.b, 0);
	while (++j < d->lights)
	{
		ld = new_dot(d->light[j]->px, d->light[j]->py, d->light[j]->pz);
		lo = two_point_vector(ld, inter);
		test_light(&s1, &s2, d->light[j], lo, obj);
		if ((s2 == -1  && s1 != -1) || ((int)inter.x == (int)(ld.x + lo.x * s1)
			&& (int)inter.y == (int)(ld.y + lo.y * s1)
				&& (int)inter.z == (int)(ld.z + lo.z * s1)))
			dist = s1;
		else
			dist = s2;
		i = -1;
		while (++i <= d->objects - 1)
		{
			if (test_light(&s1, &s2, d->light[j], lo, d->obj[i]) != 0)
			{
				if ((s1 < dist && s1 > 0) || (s2 < dist && s2 > 0))
				{
					c = new_color(c.r - c.r / (1 + d->lights), c.g - c.g / (1 + d->lights), c.b - c.b / (1 + d->lights), 0);
					break;
				}
			}
		}
	}
	return (c);
}
