#include "RTv1.h"

int		solve_quadratic(float *sol1, float *sol2, t_data *d, t_vec ray, t_obj *s)
{
	float	a;
	float	b;
	float	c;
	float	delta;

	*sol1 = -1;
	*sol2 = -1;
	a = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2);
	b = 2 * (d->cam->px * ray.x + d->cam->py * ray.y + d->cam->pz * ray.z - s->px * ray.x - s->py * ray.y - s->pz * ray.z);
	c = 2 * (s->px * d->cam->px + s->py * d->cam->py + s->pz * d->cam->pz) + pow(d->cam->px, 2) + pow(d->cam->py, 2) + pow(d->cam->pz, 2) + pow(s->px, 2) + pow(s->py, 2) + pow(s->pz, 2) - pow(s->radius, 2);
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

void	malloc_rays(t_data *d)
{
	int		i;

	i = 0;
	if (!(d->rays = (t_vec **)malloc(sizeof(t_vec *) * HA)))
		ft_fail("Error: could not allocate memory.", d);
	while (i < HA)
	{
		if (!(d->rays[i] = (t_vec *)malloc(sizeof(t_vec) * LA)))
			ft_fail("Error: could not allocate memory.", d);
		i++;
	}
}

t_dot	new_dot(float x, float y, float z)
{
	t_dot	d;

	d.x = x;
	d.y = y;
	d.z = z;
	return (d);
}

void	gen_rays(t_data *d)
{
	int		i;
	int		j;
	t_dot	p1;
	t_dot	p2;

	i = 0;
	p1 = new_dot(d->cam->px, d->cam->py, d->cam->pz);
	malloc_rays(d);
	while (i < HA)
	{
		j = 0;
		while (j < LA)
		{
			p2 = new_dot(j - LA / 2, i - HA / 2, LA / (2 * (tan(FOV / 2))));
			d->rays[i][j] = two_point_vector(p1, p2);
			norm_vec(&(d->rays[i][j]));
			j++;
		}
		i++;
	}
}

void		start_raytracing(t_data *d)
{
	float	sol1;
	float	sol2;
	int		ret;
	int		i;
	int		j;

	i = 0;
	gen_rays(d);
	while (i < HA)
	{
		j = 0;
		while (j < LA)
		{
			ret = solve_quadratic(&sol1, &sol2, d, d->rays[i][j], d->obj[0]);
			if (ret == 1)
				put_pixel_to_image(new_dot(j, i, 0), d, d->img->str);
			j++;
		}
		i++;
	}
}
