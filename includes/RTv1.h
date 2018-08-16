/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:05:33 by axbal             #+#    #+#             */
/*   Updated: 2018/08/15 10:54:34 by axbal            ###   ########.fr       */
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

typedef struct		s_cam
{
	float			px;
	float			py;
	float			pz;
	float			vx;
	float			vy;
	float			vz;
}					t_cam;

typedef struct		s_light
{
	float			px;
	float			py;
	float			pz;
}					t_light;

typedef struct		s_obj
{
	char			*type;
	float			px;
	float			py;
	float			pz;
	float			radius;
	float			height;
	float			vx;
	float			vy;
	float			vz;
	int				r;
	int				g;
	int				b;
	struct s_obj	*next;
	int				pos_c;
	int				type_c;
	int				radius_c;
	int				height_c;
	int				vector_c;
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
	t_obj			**obj;
	t_light			*light;
	t_cam			*cam;
	float			s_xmin;
	float			s_ymin;
	float			s_xmax;
	float			s_ymax;
}					t_data;


void	ft_fail(char *str, t_data *data);
int		read_file(t_data *data, char *file);
float	ft_atof(const char *str);
float	*three_values_tab(char *f, int s);
int		read_light(t_data *data, char *file, int select);
char	*word_return(char *str, int select);
int		read_camera(t_data *data, char *file, int select);
int		read_object(t_data *d, char *f, int s);

#endif
