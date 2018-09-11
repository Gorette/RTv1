/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 19:11:29 by axbal             #+#    #+#             */
/*   Updated: 2018/09/03 13:04:10 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	put_pixel_to_image(t_dot d, t_data *data, char *img, float di)
{
	if (d.x >= 0 && d.x <= LA && d.y >= 0 && d.y < HA)
	{
		img[((int)d.x * data->img->bpp) + ((int)d.y * data->img->s_l) + 0] = (char)20 + (int)di % 235;
		img[((int)d.x * data->img->bpp) + ((int)d.y * data->img->s_l) + 1] = (char)20 + (int)di % 235 ;
		img[((int)d.x * data->img->bpp) + ((int)d.y * data->img->s_l) + 2] = (char)20 + (int)di % 235;
		img[((int)d.x * data->img->bpp) + ((int)d.y * data->img->s_l) + 3] = (char)0;
	}
}
