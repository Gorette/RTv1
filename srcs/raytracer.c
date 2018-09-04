#include "RTv1.h"

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
			p2 = new_dot(j - LA / 2, -i + HA / 2, LA / (2 * (tan(FOV / 2))));
			d->rays[i][j] = two_point_vector(p1, p2);
			norm_vec(&(d->rays[i][j]));
			j++;
		}
		i++;
	}
}

int			test_object(float *s1, float *s2, t_data *d, t_vec ray, t_obj *obj)
{
	int		ret;

	*s1 = -1;
	*s2 = -1;
	ret = 0;
	if (ft_strcmp(obj->type, "sphere") == 0)
		ret = solve_sphere(s1, s2, d, ray, obj);
	if (ft_strcmp(obj->type, "plane") == 0)
		ret = solve_plane(s1, d, ray, obj);
	if (ret == 1 && (*s1 >= 0 || *s2 >= 0))
		return (1);
	return (0);
}

void		start_raytracing(t_data *d)
{
	float	sol1;
	float	sol2;
	int		obj_i;
	int		i;
	int		j;

	i = -1;
	obj_i = 0;
	gen_rays(d);
	while (++i < HA)
	{
		j = -1;
		while (++j < LA)
		{
			obj_i = -1;
			while (++obj_i <= d->objects - 1)
			{
				if (test_object(&sol1, &sol2, d, d->rays[i][j],
					d->obj[obj_i]) > 0)
					put_pixel_to_image(new_dot(j, i, 0), d, d->img->str);
			}
		}
	}
}
