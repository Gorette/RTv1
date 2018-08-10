/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:05:33 by axbal             #+#    #+#             */
/*   Updated: 2018/07/24 12:33:50 by axbal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <pthread.h>
# include <fcntl.h>

# define LA 896
# define HA 504

typedef struct		s_obj
{
	char			*type;
	float			x;
	float			y;
	float			z;
	int				id;
	float			rayon;
	float			height;
	float			width;
}					t_obj;

typedef struct		s_img
{
	void			*ptr;
	char			*str;
	int				width;
	int				height;
	int				bpp;
	int				s_l;
	int				endian;
}					t_img;

typedef struct		s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			*img;
	t_obj			*obj;
	float			s_xmin;
	float			s_ymin;
	float			s_xmax;
	float			s_ymax;
}					t_data;

#endif
