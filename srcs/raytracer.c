#include "RTv1.h"

int		solve_quadratic(float *sol1, float *sol2, t_data *d)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	r;
	t_vec	ray;

	ray.x = 1;
	ray.y = 2;
	ray.z = 0;
	r = 2;
	*sol1 = -1;
	*sol2 = -1;
	a = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2);
	b = 2 * ray.x * d->cam->px + 2 * ray.y * d->cam->py + 2 * ray.z * d->cam->pz;
	c = pow(d->cam->px, 2) + pow(d->cam->py, 2) + pow(d->cam->pz, 2) - pow(r, 2);
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

void		start_raytracing(t_data *d)
{
	t_vec	*pix;
	float	s1;
	float	s2;

	if (!(pix = (t_vec *)malloc(sizeof(t_vec) * 1)))
		ft_fail("Error: Could not malloc memory.", d);
	// multi-threading while pix->x <= LA
	ft_putnbr(solve_quadratic(&s1, &s2, d));
	free(pix);
}
