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
	data->img->bpp /= 8;
}

void		init_data(t_data *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		ft_fail("Error: Connection failed.", NULL);
	if (!(data->win_ptr = mlx_new_window(data->mlx_ptr, LA, HA, "rtv1")))
		ft_fail("Error: Unable to create window.", NULL);
	init_img(data);
}

t_data		*new_data(void)
{
	t_data	*new;

	if (!(new = (t_data *)malloc(sizeof(t_data) * 1)))
		ft_fail("Error: Could not allocate memory", NULL);
	new->img = NULL;
	new->obj = NULL;
	return (new);
}

int		ft_increase_file(char **file, char *line)
{
	char	*copy;

	if (*file == NULL)
	{
		if (!(*file = ft_strnew(ft_strlen(line))))
			return (-1);
		return (1);
	}
	if (!(copy = ft_strdup(*file)))
		return (-1);
	free(*file);
	if (!(*file = ft_strnew(ft_strlen(copy) + ft_strlen(line))))
		return (-1);
	ft_strncpy(*file, copy, ft_strlen(copy));
	ft_strcat(*file, line);
	free(copy);
	return (1);
}

void		start_reading(t_data *data, char *str)
{
	int		fd;
	char	*file;
	char	*line;
	int		ret;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: No file '", 2);
		ft_putstr_fd(str, 2);
		ft_fail("' found.", data);
	}
	file = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_increase_file(&file, line) == -1)
			ft_fail("Error: An error occurred.", data);
	}
	if (ft_strlen(file) == 0)
		ft_fail("Error: File is empty.", data);
	if (ret == -1 || ft_strlen(file) > (2048 * 80))
		ft_fail("Error: File is too big or is a directory.", data);
}

int			main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 2)
		ft_fail("Usage: rtv1 input_file", NULL);
	data = new_data();
	init_data(data);
	start_reading(data, argv[1]);
	ft_putstr("ca fonctionne.\n");
	mlx_loop(data->mlx_ptr);
	return (0);
}
