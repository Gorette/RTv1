/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 14:44:53 by axbal             #+#    #+#             */
/*   Updated: 2018/09/10 11:56:07 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h>

int		solve_cyli(float *sol1, float *sol2, t_data *d, t_vec ray, t_obj *o)
{
	t_dot	q;
	t_vec	p;
	float	delta;

	p = new_vec((float)d->cam->px, (float)d->cam->py, (float)d->cam->pz);
	p = trans_vec(p, o->px, o->py, o->pz);
	p = rot_vec(p, o->rx, o->ry, o->rz);
	ray = rot_vec(ray, o->rx, o->ry, o->rz);
	q.x = pow(ray.x, 2) + pow(ray.y, 2);
	q.y = 2 * p.x * ray.x + 2 * p.y * ray.y;
	q.z = pow(p.x, 2) + pow(p.y, 2) - pow(o->radius, 2);
	delta = pow(q.y, 2) - 4 * q.x * q.z;
	if (delta < 0)
		return (-1);
	else if (delta == 0)
		*sol1 = -q.y / 2 * q.x;
	else if (delta > 0)
	{
		*sol1 = -q.y + sqrt(delta) / 2 * q.x;
		*sol2 = -q.y - sqrt(delta) / 2 * q.x;
	}
	return (1);
}

int		solve_cone(float *sol1, float *sol2, t_data *d, t_vec ray, t_obj *o)
{
	t_dot	q;
	t_vec	p;
	float	delta;

	p = new_vec(d->cam->px, d->cam->py, d->cam->pz);
	p = trans_vec(p, o->px, o->py, o->pz);
	p = rot_vec(p, o->rx, o->ry, o->rz);
	ray = rot_vec(ray, o->rx, o->ry, o->rz);
	q.x = pow(ray.x, 2) + pow(ray.y, 2) - pow(tan(o->angle), 2) * pow(ray.z, 2);
	q.y = 2 * p.x * ray.x + 2 * p.y * ray.y -
	pow(tan(o->angle), 2) * 2 * p.z * ray.z;
	q.z = pow(p.x, 2) + pow(p.y, 2) - pow(tan(o->angle), 2) *
	pow(p.z, 2);
	delta = pow(q.y, 2) - 4 * q.x * q.z;
	if (delta < 0)
		return (-1);
	else if (delta == 0)
		*sol1 = -q.y / 2 * q.x;
	else if (delta > 0)
	{
		*sol1 = -q.y + sqrt(delta) / 2 * q.x;
		*sol2 = -q.y - sqrt(delta) / 2 * q.x;
	}
	return (1);
}

int		solve_plane(float *sol1, t_data *d, t_vec ray, t_obj *p)
{
	float	q;

	if (scalar(p->v, &ray) != 0)
	{
		q = -(p->v->x * p->px + p->v->y * p->py + p->v->z * p->pz);
		*sol1 = (-(p->v->x * d->cam->px) - p->v->y * d->cam->py -
			p->v->z * d->cam->pz - q) / (ray.x * p->v->x + ray.y * p->v->y +
				ray.z * p->v->z);
		if (*sol1 < 0)
			return (-1);
		return (1);
	}
	return (-1);
}

int		solve_sphere(float *sol1, float *sol2, t_data *d, t_vec ray, t_obj *s)
{
	float	a;
	float	b;
	float	c;
	float	delta;

	a = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2);
	b = 2 * (d->cam->px * ray.x + d->cam->py * ray.y + d->cam->pz *
		ray.z - s->px * ray.x - s->py * ray.y - s->pz * ray.z);
	c = 2 * (s->px * d->cam->px + s->py * d->cam->py + s->pz * d->cam->pz) +
		pow(d->cam->px, 2) + pow(d->cam->py, 2) + pow(d->cam->pz, 2)
			+ pow(s->px, 2) + pow(s->py, 2) + pow(s->pz, 2) - pow(s->radius, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (-1);
	if (delta == 0)
		*sol1 = -b / 2 * a;
	else if (delta > 0)
	{
		*sol1 = -b + sqrt(delta) / 2 * a;
		*sol2 = -b - sqrt(delta) / 2 * a;
	}
	return (1);
}
