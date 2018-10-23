/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 16:11:56 by axbal             #+#    #+#             */
/*   Updated: 2018/10/23 16:11:58 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

float	len_vec(t_vec *vec)
{
	return (sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2)));
}

void	norm_vec(t_vec *to_normalize)
{
	float	len;

	len = len_vec(to_normalize);
	if (len != 1)
	{
		len = 1 / len;
		to_normalize->x *= len;
		to_normalize->y *= len;
		to_normalize->z *= len;
	}
}

t_vec	two_point_vector(t_dot p1, t_dot p2)
{
	t_vec	vec;

	vec.x = p2.x - p1.x;
	vec.y = p2.y - p1.y;
	vec.z = p2.z - p1.z;
	norm_vec(&vec);
	return (vec);
}

t_dot	get_hitpoint(t_vec vector, float d, t_data *data)
{
	t_dot	dot;

	dot.x = data->cam->px + vector.x * d;
	dot.y = data->cam->py + vector.y * d;
	dot.z = data->cam->pz + vector.z * d;
	return (dot);
}

float	scalar(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}
