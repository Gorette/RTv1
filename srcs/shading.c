#include "RTv1.h"
#include <stdio.h>

float	find_right_distance(t_data *d, t_dot inter, t_dot light, t_vec vec)
{
	float	dist;
	float	sum1;
	float	sum2;

	sum1 = fabs(inter.x - (light.x + (vec.x * d->t[0])))
	+ fabs(inter.y - (light.y + (vec.y * d->t[0])))
	+ fabs(inter.z - (light.z + (vec.z * d->t[0])));
	sum2 = fabs(inter.x - (light.x + (vec.x * d->t[1])))
	+ fabs(inter.y - (light.y + (vec.y * d->t[1])))
	+ fabs(inter.z - (light.z + (vec.z * d->t[1])));
	dist = sum1 < sum2 ? d->t[0] : d->t[1];
	return (dist);
}

t_color	secondary_rays(t_dot inter, t_data *d, t_obj *obj)
{
	t_dot	ld;
	t_vec	lo;
	float	dist;
	int		i;
	t_color	c;

	d->l = -1;
	c = d->lights > 0 ? new_color(0, 0, 0, 0) :
	new_color(obj->color.r, obj->color.g, obj->color.b, 0);
	while (++(d->l) < d->lights)
	{
		d->stop = 0;
		ld = new_dot(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
		lo = two_point_vector(ld, inter);
		test_light(d, d->light[d->l], lo, obj);
		dist = find_right_distance(d, inter, ld, lo);
		i = -1;
		while (++i < d->objects)
		{
			if (test_light(d, d->light[d->l], lo, d->obj[i]) == 1)
			{
				if ((d->t[0] > 0 && d->t[0] < dist) || (d->t[1] > 0 &&
					d->t[1] < dist))
					break;
			}
			{
				if (ft_strcmp(obj->type, "sphere") == 0 && i == d->objects - 1)
					c = diffuse_sphere(c, inter, obj, d);
				if (!ft_strcmp(obj->type, "plane") && i == d->objects - 1)
					c = diffuse_plane(c, inter, obj, d);
				if (!ft_strcmp(obj->type, "cone") && i == d->objects - 1)
					c = diffuse_cone(c, inter, obj, d);
				if (!ft_strcmp(obj->type, "cylinder") && i == d->objects - 1)
					c = diffuse_cylinder(c, inter, obj, d);
			}
			if (d->stop != 0)
				break;
		}
	}
	return (c);
}
