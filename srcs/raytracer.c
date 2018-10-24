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

void	rot_rays(t_data *d)
{
	int		i;
	int		j;

	i = 0;
	while (i < HA)
	{
		j = 0;
		while (j < LA)
		{
			d->rays[i][j] = rot_vec(d->rays[i][j], d->cam->rx, d->cam->ry,
				d->cam->rz);
			j++;
		}
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
	p1 = new_dot(0, 0, 0);
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
	rot_rays(d);
}

int		test_object(t_data *d, t_vec ray, t_obj *obj)
{
	int		ret;

	d->t[0] = -1;
	d->t[1] = -1;
	ret = 0;
	if (ft_strcmp(obj->type, "sphere") == 0)
		ret = solve_sphere(d, ray, obj);
	if (ft_strcmp(obj->type, "plane") == 0)
		ret = solve_plane(d, ray, obj);
	if (ft_strcmp(obj->type, "cylinder") == 0)
		ret = solve_cyli(d, ray, obj);
	if (ft_strcmp(obj->type, "cone") == 0)
		ret = solve_cone(d, ray, obj);
	if (ret == 1 && (d->t[0] >= 0 || d->t[1] >= 0))
		return (1);
	return (0);
}

void	start_raytracing(t_data *d)
{
	int		obj_i;
	int		i;
	int		j;
	float	dm;
	t_obj	*o;
	float	stamp;
	t_color	c;

	i = -1;
	obj_i = 0;
	gen_rays(d);
	while (++i < HA)
	{
		j = -1;
		while (++j < LA)
		{
			dm = -1;
			o = NULL;
			obj_i = -1;
			while (++obj_i <= d->objects - 1)
			{
				if (test_object(d, d->rays[i][j],
					d->obj[obj_i]) > 0)
				{
					stamp = dm;
					if (dm == -1 || (d->t[0] < dm && d->t[0] >= 0) || (d->t[1] < dm && d->t[1] >= 0))
					{
						if (dm == -1)
						{
							if (d->t[0] >= 0)
								dm = d->t[0];
							if (d->t[1] >= 0)
								dm = d->t[0] < d->t[1] ? dm : d->t[1];
						}
						else
						{
							if (d->t[0] >= 0 && d->t[0] < dm)
								dm = d->t[0];
							if (d->t[1] >= 0 && d->t[1] < d->t[0] && d->t[1] < dm)
								dm = d->t[1];
						}
						if (stamp != dm)
							o = d->obj[obj_i];
					}
					if (dm > -1)
					{
						c = secondary_rays(get_hitpoint(d->rays[i][j], dm, d), d, o);
						put_pixel_to_image(new_dot(j, i, 0), d, d->img->str, c);
					}
				}
			}
		}
	}
}
