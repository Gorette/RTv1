#include "RTv1.h"

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
	angle = fabs(scalar(&normale, &lo));
	c.r += (int)ft_clamp(((obj->color.r / d->lights) * angle), 0, obj->color.r);
	c.g += (int)ft_clamp(((obj->color.g / d->lights) * angle), 0, obj->color.g);
	c.b += (int)ft_clamp(((obj->color.b / d->lights) * angle), 0, obj->color.b);
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
	c.r += (int)ft_clamp(((obj->color.r / d->lights) * angle), 0, obj->color.r);
	c.g += (int)ft_clamp(((obj->color.g / d->lights) * angle), 0, obj->color.g);
	c.b += (int)ft_clamp(((obj->color.b / d->lights) * angle), 0, obj->color.b);
	return (c);
}

t_color	diffuse_cone(t_color c, t_dot inter, t_obj *obj, t_data *d, int l)
{
	t_vec	normale;
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
	lc = two_point_vector(affixe, new_dot(lc.x, lc.y, lc.z));
	norm_vec(&lc);
	angle = fabs(scalar(&normale, &lc));
	c.r += (int)ft_clamp(((obj->color.r / d->lights) * angle), 0, obj->color.r);
	c.g += (int)ft_clamp(((obj->color.g / d->lights) * angle), 0, obj->color.g);
	c.b += (int)ft_clamp(((obj->color.b / d->lights) * angle), 0, obj->color.b);
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
	c.r += (int)ft_clamp(((obj->color.r / d->lights) * angle), 0, obj->color.r);
	c.g += (int)ft_clamp(((obj->color.g / d->lights) * angle), 0, obj->color.g);
	c.b += (int)ft_clamp(((obj->color.b / d->lights) * angle), 0, obj->color.b);
	return (c);
}
