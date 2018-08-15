/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:56:25 by axbal             #+#    #+#             */
/*   Updated: 2018/08/11 22:05:02 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	add_obj(t_data *data, t_obj *obj)
{
	t_obj	**list;
	t_obj	*current;
	t_obj	*next;

	list = data->obj;
	current = *list;
	next = current->next;
	while (next)
	{
		current = next;
		next = current->next;
	}
	if (!current)
		*list = obj;
	else
		current->next = obj;
}

int		determine_object_type(char *f, int s, t_obj *new)
{
//	while (f[s] && (f[s] != '}' || f[s] != '('))
	return (1);
}

int		expected_result(char *type)
{
	if (!type)
		return (-2);
	if (!(ft_strcmp(type, "sphere")))
		return (4);
	if (!(ft_strcmp(type, "cylinder") || !(ft_strcmp(type, "cone"))))
		return (5);
	if (!(ft_strcmp(type, "plane")))
		return (3);
	return (-2);
}

char	*compare_string_to_values(char *f, int s)
{
}

int		read_object_var(char *f, int s, t_obj *new)
{
	int		result;
	char	*word;

	result = 0;
	new->type = NULL;
	while (f[s] && (f[s] != '}'))
	{
		word = NULL;
		s++;
		if ((word = compare_string_to_values(f, s)) != NULL)
		{
			result += 1;
		}
	}
	if (f[s] != '}' || result != expected_result(new->type))
		return (-1);
	return (1);
}

int		read_object(t_data *d, char *f, int s)
{
	t_obj	*new;
	int		result;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		ft_fail("Error: Could not allocate memory.", d);
	new->type = NULL;
	result = determine_object_type(f, s, new);
	if (new->type == NULL || result != 1)
	{
		free(new);
		return (0);
	}
	add_obj(d, new);
	return (1);
}
