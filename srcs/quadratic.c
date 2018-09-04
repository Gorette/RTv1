#include "RTv1.h"

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
