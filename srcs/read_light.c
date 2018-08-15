/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 10:27:47 by axbal             #+#    #+#             */
/*   Updated: 2018/08/15 10:54:41 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		get_light_pos(char *file, int select, t_light *light)
{
	float	*tab;

	tab = three_values_tab(file, select);
	select = tab[4];
	if (tab[3] != 3 || file[select] != ')')
	{
		free(tab);
		return (-1);
	}
	light->px = tab[0];
	light->py = tab[1];
	light->pz = tab[2];
	free(tab);
	return (select);
}

int		read_light(t_data *data, char *file, int select)
{
	t_light		*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		ft_fail("Error: Could not allocate memory.", data);
	while (file[select] && file[select] != '}')
	{
		if (ft_strncmp(file + select, "pos(", 4) == 0)
		{
			if ((select = get_light_pos(file, select, light)) == -1)
				break ;
		}
		select++;
	}
	if (select != -1)
		data->light = light;
	else
		free(light);
	return (select);
}
