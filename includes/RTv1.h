/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 12:05:33 by axbal             #+#    #+#             */
/*   Updated: 2018/09/03 13:06:18 by axbal            ###   ########.fr       */
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
# define FOV 90

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_dot
{
	float			x;
	float			y;
	float			z;
}					t_dot;

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
	int				intensity;
}					t_light;

typedef struct		s_obj
{
	char			*type;
	float			px;
	float			py;
	float			pz;
	float			radius;
	float			angle;
	float			vx;
	float			vy;
	float			vz;
	int				r;
	int				g;
	int				b;
	int				rx;
	int				ry;
	int				rz;
	struct s_obj	*next;
	int				pos_c;
	int				type_c;
	int				radius_c;
	int				angle_c;
	int				vector_c;
	int				rotation_c;
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
	t_light			**light;
	t_cam			*cam;
	t_vec			**rays;
	int				lights;
	int				objects;
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
int		get_object_type(char *f, int s, t_obj *obj);
int		get_object_pos(char *f, int s, t_obj *obj);
int		get_object_rad(char *f, int s, t_obj *obj);
int		get_object_angle(char *f, int s, t_obj *obj);
int		get_object_rot(char *f, int s, t_obj *obj);
int		get_object_vec(char *f, int s, t_obj *obj);
t_obj	*create_object(t_data *data);
int		key_release(int key, void *d);
int		ft_increase_file(char **file, char *line);
char	*start_reading(char *str);
int		close_program(t_data *d);
int		refresh_expose(t_data *d);
void	start_raytracing(t_data *d);
t_vec	two_point_vector(t_dot p1, t_dot p2);
void	norm_vec(t_vec *to_normalize);
void	put_pixel_to_image(t_dot d, t_data *data, char *img);

#endif
