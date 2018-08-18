#include "RTv1.h"

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
