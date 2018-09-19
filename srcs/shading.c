#include "RTv1.h"

t_color	secondary_rays(t_dot inter, t_data *d, t_obj *obj)
{
	t_dot	ld;
	t_vec	lo;
	float	dist;
	int		i;
	float	s1;
	float	s2;

	ld = new_dot(d->light[0]->px, d->light[0]->py, d->light[0]->pz);
	lo = two_point_vector(ld, inter);
	test_light(&s1, &s2, d->light[0], lo, obj);
	if ((s2 == -1  && s1 != -1) || ((int)inter.x == (int)(ld.x + lo.x * s1) && (int)inter.y == (int)(ld.y + lo.y * s1)
		&& (int)inter.z == (int)(ld.z + lo.z * s1)))
		dist = s1;
	else
		dist = s2;
	i = -1;
	while (++i <= d->objects - 1)
	{
		if (test_light(&s1, &s2, d->light[0], lo, d->obj[i]) != 0)
		{
			if ((s1 < dist && s1 > 0) || (s2 < dist && s2 > 0))
				return (new_color(obj->color.r / 2, obj->color.g / 2, obj->color.b / 2, 0));
		}
	}
	return (obj->color);
}
