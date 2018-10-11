#include "RTv1.h"
#include <stdio.h>

float	find_right_distance(float s1, float s2, t_dot inter, t_dot light, t_vec vec)
{
	float	dist;
	float	sum1;
	float	sum2;

	sum1 = fabs(inter.x - (light.x + (vec.x * s1)))
	+ fabs(inter.y - (light.y + (vec.y * s1)))
	+ fabs(inter.z - (light.z + (vec.z * s1)));
	sum2 = fabs(inter.x - (light.x + (vec.x * s2)))
	+ fabs(inter.y - (light.y + (vec.y * s2)))
	+ fabs(inter.z - (light.z + (vec.z * s2)));
	dist = sum1 < sum2 ? s1 : s2;
	return (dist);
}

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
	int		hits;

	j = -1;
	c = d->lights > 0 ? new_color(0, 0, 0, 0) :
		new_color(obj->color.r, obj->color.g, obj->color.b, 0);
	hits = d->lights;
	while (++j < d->lights)
	{
		ld = new_dot(d->light[j]->px, d->light[j]->py, d->light[j]->pz);
		lo = two_point_vector(ld, inter);
		test_light(&s1, &s2, d->light[j], lo, obj);
		dist = find_right_distance(s1, s2, inter, ld, lo);
		i = -1;
		while (++i <= d->objects - 1)
		{
			if (test_light(&s1, &s2, d->light[j], lo, d->obj[i]) != 0)
			{
				if ((s1 < dist && s1 > 0) || (s2 < dist && s2 > 0))
				{
					hits--;
					break;
				}
			}
			if (ft_strcmp(obj->type, "sphere") == 0 && i == d->objects - 1)
				c = diffuse_sphere(c, inter, obj, d, j);
			if (ft_strcmp(obj->type, "plane") == 0 && i == d->objects - 1)
				c = diffuse_plane(c, inter, obj, d, j);
			if (ft_strcmp(obj->type, "cone") == 0 && i == d->objects - 1)
				c = diffuse_cone(c, inter, obj, d, j);
			if (ft_strcmp(obj->type, "cylinder") == 0 && i == d->objects - 1)
				c = diffuse_cylinder(c, inter, obj, d, j);
		}
	}
	return (c);
}
