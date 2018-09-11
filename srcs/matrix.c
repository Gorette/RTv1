/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 13:33:37 by axbal             #+#    #+#             */
/*   Updated: 2018/09/10 12:01:20 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vec	rot_x(t_vec ray, float teta)
{
	float	y;
	float	z;

	y = cos(teta) * ray.y - sin(teta) * ray.z;
	z = sin(teta) * ray.y + cos(teta) * ray.z;
	ray.y = y;
	ray.z = z;
	return (ray);
}

t_vec	rot_y(t_vec ray, float teta)
{
	float	x;
	float	z;

	x = cos(teta) * ray.x + sin(teta) * ray.z;
	z = -sin(teta) * ray.x + cos(teta) * ray.z;
	ray.x = x;
	ray.z = z;
	return (ray);
}

t_vec	rot_vec(t_vec ray, float rx, float ry)
{
	ray = rot_x(ray, degree_to_radian(rx));
	ray = rot_y(ray, degree_to_radian(ry));
	return (ray);
}

t_vec	trans_vec(t_vec vec, float tx, float ty, float tz)
{
	vec.x -= tx;
	vec.y -= ty;
	vec.z -= tz;
	return (vec);
}
