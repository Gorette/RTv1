/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:10:49 by axbal             #+#    #+#             */
/*   Updated: 2018/08/17 13:19:14 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		ft_fail(char *str, t_data *data)
{
	ft_putstr_fd(str, 2);
	ft_putchar('\n');
	if (data)
		exit(0);
	exit(0);
}

t_img		*init_img(t_data *data)
{
	t_img		*img;

	if (!(img = (t_img *)malloc(sizeof(t_img) * 1)))
		ft_fail("Error: Could not allocate memory", NULL);
	img->width = LA;
	img->height = HA;
	if (!(img->ptr = mlx_new_image(data->mlx_ptr, LA, HA)))
		ft_fail("Error: cant create image.", NULL);
	if (!(img->str = mlx_get_data_addr(img->ptr, &img->bpp,
		&img->s_l, &img->endian)))
		ft_fail("Error: cant create image.", NULL);
	img->bpp /= 8;
	return (img);
}

t_data		*new_data(void)
{
	t_data	*new;

	if (!(new = (t_data *)malloc(sizeof(t_data) * 1)))
		ft_fail("Error: Could not allocate memory", NULL);
	new->img = NULL;
	new->obj = NULL;
	new->cam = NULL;
	new->light = NULL;
	new->lights = 0;
	new->objects = 0;
	if (!(new->mlx_ptr = mlx_init()))
		ft_fail("Error: Connection failed.", NULL);
	if (!(new->win_ptr = mlx_new_window(new->mlx_ptr, LA, HA, "rtv1")))
		ft_fail("Error: Unable to create window.", NULL);
	new->img = init_img(new);
	return (new);
}

void		let_mlx_loop(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 1L << 17, &close_program, data);
//	mlx_hook(data->win_ptr, 2, 1L << 0, &key_pressed, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, &key_release, data);
	mlx_loop_hook(data->mlx_ptr, &refresh_expose, data);
	mlx_loop(data->mlx_ptr);
}

int			main(int argc, char **argv)
{
	t_data	*data;
	char	*file;

	file = NULL;
	if (argc < 2)
		ft_fail("Usage: rtv1 input_file", NULL);
	data = new_data();
	file = start_reading(argv[1]);
	read_file(data, file);
	ft_putstr("ca fonctionne.\n");
	start_raytracing(data);
	let_mlx_loop(data);
	return (0);
}
