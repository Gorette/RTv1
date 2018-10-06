#include "RTv1.h"

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

t_color	diffuse_sphere(t_color c, t_dot inter, t_obj *obj, t_data *d, int l)
{
	t_vec	normale;
	t_vec	lo;
	t_dot	obj_center;
	t_dot	light_center;
	float	angle;

	light_center = new_dot(d->light[l]->px, d->light[l]->py, d->light[l]->pz);
	obj_center = new_dot(obj->px, obj->py, obj->pz);
	normale = two_point_vector(obj_center, inter);
	norm_vec(&normale);
	lo = two_point_vector(obj_center, light_center);
	norm_vec(&lo);
	angle = scalar(&normale, &lo);
	c.r = (int)ft_clamp((c.r * angle), 0, obj->color.r);
	c.g = (int)ft_clamp((c.g * angle), 0, obj->color.g);
	c.b = (int)ft_clamp((c.b * angle), 0, obj->color.b);
	return (c);
}

t_color	diffuse_plane(t_color c, t_dot inter, t_obj *obj, t_data *d, int l)
{
	t_vec	normale;
	t_vec	lo;
	t_dot	light_center;
	float	angle;

	light_center = new_dot(d->light[l]->px, d->light[l]->py, d->light[l]->pz);
	normale = *(obj->v);
	norm_vec(&normale);
	lo = two_point_vector(light_center, inter);
	norm_vec(&lo);
	angle = fabs(scalar(&normale, &lo));
	c.r = (int)ft_clamp((c.r * angle), 0, obj->color.r);
	c.g = (int)ft_clamp((c.g * angle), 0, obj->color.g);
	c.b = (int)ft_clamp((c.b * angle), 0, obj->color.b);
	return (c);
}

/*t_color	diffuse_cone(t_color c, t_dot inter, t_obj *obj, t_data *d, int l)
{
	t_vec	normale;
	t_vec	lo;
	t_dot	obj_center;
	t_dot	light_center;
	float	angle;

	light_center = new_dot(d->light[l]->px, d->light[l]->py, d->light[l]->pz);
	obj_center = new_dot(obj->px, obj->py, obj->pz);
	normale = two_point_vector(obj_center, inter);
	norm_vec(&normale);
	lo = two_point_vector(light_center, inter);
	norm_vec(&lo);
	angle = fabs(scalar(&normale, &lo));
	angle = 1 - angle;
	c.r = (int)ft_clamp((c.r * angle), 0, obj->color.r);
	c.g = (int)ft_clamp((c.g * angle), 0, obj->color.g);
	c.b = (int)ft_clamp((c.b * angle), 0, obj->color.b);
	return (c);
}

t_color	diffuse_cylinder(t_color c, t_dot inter, t_obj *obj, t_data *d, int l)
{
	t_vec	normale;
	t_vec	lo;
	t_dot	light_center;
	t_vec	a_dot;
	t_dot	affixe;
	float	angle;

	light_center = new_dot(d->light[l]->px, d->light[l]->py, d->light[l]->pz);
	a_dot = new_vec(inter.x, inter.y, inter.z);
	a_dot = trans_vec(a_dot, obj->px, obj->py, obj->pz);
	a_dot = rot_vec(a_dot, obj->rx, obj->ry, 0);
	a_dot = new_vec(0, 0, a_dot.z);
	a_dot = rot_vec(a_dot, -(obj->rx), -(obj->ry), 0);
	a_dot = trans_vec(a_dot, -(obj->px), -(obj->py), -(obj->pz));
	affixe = new_dot(a_dot.x, a_dot.y, a_dot.z);
	normale = two_point_vector(affixe, inter);
	norm_vec(&normale);
	lo = two_point_vector(inter, light_center);
	norm_vec(&lo);
	angle = fabs(scalar(&normale, &lo));
	c.r = (int)ft_clamp((c.r * angle), 0, obj->color.r);
	c.g = (int)ft_clamp((c.g * angle), 0, obj->color.g);
	c.b = (int)ft_clamp((c.b * angle), 0, obj->color.b);
	return (c);
}*/

t_color	diffuse_cone(t_color c, t_dot inter, t_obj *obj, t_data *d, int l)
{
	t_vec	normale;
	t_vec	lo;
	t_vec	lc;
	t_vec	a_dot;
	t_dot	affixe;
	float	angle;

	lc = new_vec(d->light[l]->px, d->light[l]->py, d->light[l]->pz);
	lc = trans_vec(lc, obj->px, obj->py, obj->pz);
	lc = rot_vec(lc, obj->rx, obj->ry, 0);
	a_dot = new_vec(inter.x, inter.y, inter.z);
	a_dot = trans_vec(a_dot, obj->px, obj->py, obj->pz);
	a_dot = rot_vec(a_dot, obj->rx, obj->ry, 0);
	affixe = new_dot(0, 0, a_dot.z);
	normale = two_point_vector(affixe, new_dot(a_dot.x, a_dot.y, a_dot.z));
	norm_vec(&normale);
	lo = two_point_vector(affixe, new_dot(lc.x, lc.y, lc.z));
	norm_vec(&lo);
	angle = fabs(scalar(&normale, &lo));
	c.r = (int)ft_clamp((c.r * angle), 0, obj->color.r);
	c.g = (int)ft_clamp((c.g * angle), 0, obj->color.g);
	c.b = (int)ft_clamp((c.b * angle), 0, obj->color.b);
	return (c);
}

t_color	diffuse_cylinder(t_color c, t_dot inter, t_obj *obj, t_data *d, int l)
{
	t_vec	normale;
	t_vec	lo;
	t_vec	lc;
	t_vec	a_dot;
	t_dot	affixe;
	float	angle;

	lc = new_vec(d->light[l]->px, d->light[l]->py, d->light[l]->pz);
	lc = trans_vec(lc, obj->px, obj->py, obj->pz);
	lc = rot_vec(lc, obj->rx, obj->ry, 0);
	a_dot = new_vec(inter.x, inter.y, inter.z);
	a_dot = trans_vec(a_dot, obj->px, obj->py, obj->pz);
	a_dot = rot_vec(a_dot, obj->rx, obj->ry, 0);
	affixe = new_dot(0, 0, a_dot.z);
	normale = two_point_vector(affixe, new_dot(a_dot.x, a_dot.y, a_dot.z));
	norm_vec(&normale);
	lo = two_point_vector(affixe, new_dot(lc.x, lc.y, lc.z));
	norm_vec(&lo);
	angle = fabs(scalar(&normale, &lo));
	c.r = (int)ft_clamp((c.r * angle), 0, obj->color.r);
	c.g = (int)ft_clamp((c.g * angle), 0, obj->color.g);
	c.b = (int)ft_clamp((c.b * angle), 0, obj->color.b);
	return (c);
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
	c = new_color(obj->color.r, obj->color.g, obj->color.b, 0);
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
	if (hits != d->lights)
		c = new_color(c.r - c.r / (1 + hits), c.g - c.g / (1 + hits), c.b - c.b / (1 + hits), 0);
	return (c);
}
