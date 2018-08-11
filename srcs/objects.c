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
