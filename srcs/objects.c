/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:56:25 by axbal             #+#    #+#             */
/*   Updated: 2018/08/17 13:40:40 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h>

void	add_obj(t_data *data, t_obj *obj)
{
	t_obj	**tmp;
	int		i;

	i = 0;
	if (!(tmp = (t_obj **)malloc(sizeof(t_obj *) * (data->objects + 1))))
		ft_fail("Error: Could not allocate memory.", data);
	while (i < data->objects)
	{
		tmp[i] = data->obj[i];
		i++;
	}
	tmp[i] = obj;
	if (data->objects > 0)
		free(data->obj);
	data->obj = tmp;
	data->objects++;
	printf("L'objet de type %s a bien ete ajoute.\n", obj->type);
}

int		expected_result(t_obj *obj)
{
	if (obj->type_c == 0)
		return (0);
	if (!(ft_strcmp(obj->type, "sphere")))
	{
		if (obj->pos_c != 1 || obj->radius_c != 1)
			return (0);
		return (1);
	}
	if (!(ft_strcmp(obj->type, "cylinder") || !(ft_strcmp(obj->type, "cone"))))
	{
		if (obj->pos_c != 1 || obj->radius_c != 1 || obj->height_c != 1
			|| obj->vector_c != 1)
			return (0);
		return (1);
	}
	if (!(ft_strcmp(obj->type, "plane")))
	{
		if (obj->pos_c != 1 || obj->vector_c != 1)
			return (0);
		return (1);
	}
	return (-2);
}

int		get_object_type(char *f, int s, t_obj *obj)
{
	char	*type;

	s += 5;
	type = word_return(f, s);
	if (type != NULL && (ft_strcmp(type, "sphere") == 0
		|| ft_strcmp(type, "cylinder") == 0 || ft_strcmp(type, "cone") == 0
			|| ft_strcmp(type, "plane") == 0))
	{
		if (obj->type_c == 0)
			obj->type = type;
		else
			free(type);
		obj->type_c += 1;
	}
	return (0);
}

int		get_object_pos(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 3)
	{
		free(tab);
		return (0);
	}
	obj->px = tab[0];
	obj->py = tab[1];
	obj->pz = tab[2];
	free(tab);
	obj->pos_c += 1;
	return (1);
}

int		get_object_rad(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 1)
	{
		free(tab);
		return (0);
	}
	obj->radius = tab[0];
	obj->radius_c += 1;
	free(tab);
	return (1);
}

int		get_object_height(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 1)
	{
		free(tab);
		return (0);
	}
	obj->height = tab[0];
	obj->height_c += 1;
	free(tab);
	return (1);
}

int		get_object_vec(char *f, int s, t_obj *obj)
{
	float	*tab;

	tab = three_values_tab(f, s);
	if (!(f[(int)tab[4]]) || tab[3] != 3)
	{
		free(tab);
		return (0);
	}
	obj->vx = tab[0];
	obj->vy = tab[1];
	obj->vz = tab[2];
	free(tab);
	obj->vector_c += 1;
	return (1);
}

int		compare_string_to_values(char *f, int s, t_obj *new)
{
	if (ft_strncmp(f + s, "type(", 5) == 0)
		return (get_object_type(f, s, new));
	else if (ft_strncmp(f + s, "pos(", 4) == 0)
		return (get_object_pos(f, s, new));
	else if (ft_strncmp(f + s, "radius(", 7) == 0)
		return (get_object_rad(f, s, new));
	else if (ft_strncmp(f + s, "height(", 7) == 0)
		return (get_object_height(f, s, new));
	else if (ft_strncmp(f + s, "vector(", 7) == 0)
		return (get_object_vec(f, s, new));
//	else if (ft_strncmp(f + s, "color(", 6) == 0)
	return (0);
}

int		read_object_var(char *f, int s, t_obj *new)
{
	new->type = NULL;
	while (f[s] && (f[s] != '}'))
	{
		if (ft_isalpha(f[s]))
			compare_string_to_values(f, s, new);
		s++;
	}
	if (f[s] != '}' || !(expected_result(new)))
		return (-1);
	printf("object %s is perfect!\n", new->type);
	return (1);
}

t_obj	*create_object(t_data *data)
{
	t_obj	*new;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		ft_fail("Error: Could not allocate memory.", data);
	new->pos_c = 0;
	new->type_c = 0;
	new->radius_c = 0;
	new->height_c = 0;
	new->vector_c = 0;
	return (new);
}

int		read_object(t_data *d, char *f, int s)
{
	t_obj	*new;
	int		result;

	new = create_object(d);
	new->type = NULL;
	result = read_object_var(f, s, new);
	if (new->type == NULL || result != 1)
	{
		free(new);
		return (0);
	}
	add_obj(d, new);
	return (1);
}
