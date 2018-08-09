/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:10:49 by axbal             #+#    #+#             */
/*   Updated: 2018/07/24 12:11:57 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		ft_fail(char *str, t_data *data)
{
	ft_putstr_fd(str, 2);
	ft_putchar('\n');
	ft_putstr_fd("State: ", 2);
	ft_putstr_fd("rtv1 is now quitting due to an error.\n", 2);
	if (data)
		exit(0);
	exit(0);
}

void		init_img(t_data *data)
{
	if (!(data->img = (t_img *)malloc(sizeof(t_img) * 1)))
		ft_fail("Error: Could not allocate memory", NULL);
	data->img->width = LA;
	data->img->height = HA;
	if (!(data->img->ptr = mlx_new_image(data->mlx_ptr, LA, HA)))
		ft_fail("Error: cant create image.", NULL);
	if (!(data->img->str = mlx_get_data_addr(data->img->ptr, &data->img->bpp,
		&data->img->s_l, &data->img->endian)))
		ft_fail("Error: cant create image.", NULL);
}

void		init_data(t_data *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		ft_fail("Error: Connection failed.", NULL);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, LA, HA, "rtv1")))
		ft_fail("Error: Unable to create window.", NULL);
	init_img(data);
}

t_data		*new_list(void)
{
	t_data	*new;

	if (!(new = (t_data *)malloc(sizeof(t_data) * 1)))
		ft_fail("Error: Could not allocate memory", NULL);
	new->img = NULL;
	new->obj = NULL;
	return (new);
}

int			main(void)
{
	t_data	*data;

	data = new_list();
	init_data(data);
	ft_putstr("ca fonctionne.\n");
	mlx_loop(data->mlx_ptr);
	return (0);
}
