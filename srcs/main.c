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
	if (!(new->mlx_ptr = mlx_init()))
		ft_fail("Error: Connection failed.", NULL);
	if (!(new->win_ptr = mlx_new_window(new->mlx_ptr, LA, HA, "rtv1")))
		ft_fail("Error: Unable to create window.", NULL);
	new->img = init_img(new);
	return (new);
}

int		ft_increase_file(char **file, char *line)
{
	char	*copy;

	if (*file == NULL)
	{
		if (!(*file = ft_strdup(line)))
			return (-1);
		free(line);
		return (1);
	}
	if (!(copy = ft_strdup(*file)))
		return (-1);
	free(*file);
	if (!(*file = ft_strnew(ft_strlen(copy) + ft_strlen(line))))
		return (-1);
	ft_strcpy(*file, copy);
	free(copy);
	ft_strcat(*file, line);
	free(line);
	return (1);
}

char		*start_reading(char *str)
{
	int		fd;
	int		ret;
	char	*file;
	char	*line;

	file = NULL;
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: No file '", 2);
		ft_putstr_fd(str, 2);
		ft_fail("' found.", NULL);
	}
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_increase_file(&file, line) == -1)
			ft_fail("Error: An error occurred.", NULL);
	}
	close(fd);
	if (ret < -1 || ft_strlen(file) >= (163840))
		ft_fail("Error: File is too big or is a directory.", NULL);
	if (ft_strlen(file) == 0)
		ft_fail("Error: File is empty.", NULL);
	return (file);
}

void		let_mlx_loop(t_data *data)
{
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
	ft_putstr("ca fonctionne.\n");
	let_mlx_loop(data);
	return (0);
}
