/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:05:31 by axbal             #+#    #+#             */
/*   Updated: 2018/11/09 16:11:06 by ceugene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_color	diffuse_sphere(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_vec	normale;
	t_vec	lo;
	t_dot	obj_center;
	t_dot	lc;
	float	angle;

	d->stop = 1;
	lc = new_dot(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	obj_center = new_dot(o->px, o->py, o->pz);
	normale = two_point_vector(obj_center, inter);
	norm_vec(&normale);
	lo = two_point_vector(obj_center, lc);
	norm_vec(&lo);
	angle = fabs(scalar(&normale, &lo));
	c.r += (int)ft_clamp(((o->color.r / d->lights) * angle), 0, o->color.r);
	c.g += (int)ft_clamp(((o->color.g / d->lights) * angle), 0, o->color.g);
	c.b += (int)ft_clamp(((o->color.b / d->lights) * angle), 0, o->color.b);
	if (o->shiny && (angle = compare_vectors(normale, lo)) >= 0 && angle < 0.08)
		return (color_interp(new_color(o->color.r, o->color.g, o->color.b, 0),
			new_color(255, 255, 255, 0), angle * 9));
	d->stop = 0;
	return (c);
}

t_color	diffuse_plane(t_color c, t_dot inter, t_obj *obj, t_data *d)
{
	t_vec	normale;
	t_vec	lo;
	t_dot	lc;
	float	angle;

	d->stop = 1;
	lc = new_dot(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	normale = *(obj->v);
	norm_vec(&normale);
	lo = two_point_vector(lc, inter);
	norm_vec(&lo);
	angle = fabs(scalar(&normale, &lo));
	c.r += (int)ft_clamp(((obj->color.r / d->lights) * angle), 0, obj->color.r);
	c.g += (int)ft_clamp(((obj->color.g / d->lights) * angle), 0, obj->color.g);
	c.b += (int)ft_clamp(((obj->color.b / d->lights) * angle), 0, obj->color.b);
	d->stop = 0;
	return (c);
}

t_color	diffuse_cone(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_vec	normale;
	t_vec	lc;
	t_vec	a_dot;
	t_dot	affixe;
	float	angle;

	d->stop = 1;
	lc = new_vec(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	lc = trans_vec(lc, o->px, o->py, o->pz);
	lc = rot_vec(lc, o->rx, o->ry, 0);
	a_dot = new_vec(inter.x, inter.y, inter.z);
	a_dot = trans_vec(a_dot, o->px, o->py, o->pz);
	a_dot = rot_vec(a_dot, o->rx, o->ry, 0);
	affixe = new_dot(0, 0, a_dot.z);
	normale = two_point_vector(affixe, new_dot(a_dot.x, a_dot.y, a_dot.z));
	norm_vec(&normale);
	lc = two_point_vector(affixe, new_dot(lc.x, lc.y, lc.z));
	norm_vec(&lc);
	angle = fabs(scalar(&normale, &lc));
	c.r += (int)ft_clamp(((o->color.r / d->lights) * angle), 0, o->color.r);
	c.g += (int)ft_clamp(((o->color.g / d->lights) * angle), 0, o->color.g);
	c.b += (int)ft_clamp(((o->color.b / d->lights) * angle), 0, o->color.b);
	if (o->shiny && (angle = compare_vectors(normale, lc)) >= 0 && angle < 0.08)
		return (color_interp(new_color(o->color.r, o->color.g, o->color.b, 0),
			new_color(255, 255, 255, 0), angle * 9));
	d->stop = 0;
	return (c);
}

t_color	diffuse_cylinder(t_color c, t_dot inter, t_obj *o, t_data *d)
{
	t_vec	normale;
	t_vec	lc;
	t_vec	a_dot;
	t_dot	affixe;
	float	angle;

	d->stop = 1;
	lc = new_vec(d->light[d->l]->px, d->light[d->l]->py, d->light[d->l]->pz);
	lc = trans_vec(lc, o->px, o->py, o->pz);
	lc = rot_vec(lc, o->rx, o->ry, 0);
	a_dot = new_vec(inter.x, inter.y, inter.z);
	a_dot = trans_vec(a_dot, o->px, o->py, o->pz);
	a_dot = rot_vec(a_dot, o->rx, o->ry, 0);
	affixe = new_dot(0, 0, a_dot.z);
	normale = two_point_vector(affixe, new_dot(a_dot.x, a_dot.y, a_dot.z));
	norm_vec(&normale);
	lc = two_point_vector(affixe, new_dot(lc.x, lc.y, lc.z));
	norm_vec(&lc);
	angle = fabs(scalar(&normale, &lc));
	c.r += (int)ft_clamp(((o->color.r / d->lights) * angle), 0, o->color.r);
	c.g += (int)ft_clamp(((o->color.g / d->lights) * angle), 0, o->color.g);
	c.b += (int)ft_clamp(((o->color.b / d->lights) * angle), 0, o->color.b);
	if (o->shiny && (angle = compare_vectors(normale, lc)) >= 0 && angle < 0.08)
		return (color_interp(new_color(o->color.r, o->color.g, o->color.b, 0),
			new_color(255, 255, 255, 0), angle * 9));
	d->stop = 0;
	return (c);
}
