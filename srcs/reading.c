#include "RTv1.h"
#include <stdio.h>

char	*word_return(char *str, int select)
{
	char	*word;
	int		select2;

	select2 = select;
	while (str[select2] && ft_isalpha(str[select2]))
		select2++;
	if (!(str[select2]))
		return (NULL);
	if (!(word = ft_strnew(select2 - select + 1)))
		ft_fail("Error: Cant allocate memory.", NULL);
	select2 = 0;
	while (str[select] && ft_isalpha(str[select]))
	{
		word[select2] = str[select];
		select++;
		select2++;
	}
	word[select2] = '\0';
	return (word);
}

float	*three_values_tab(char *f, int s)
{
	float	*tab;
	int		levier;
	float	result;

	levier = 0;
	if (!(tab = (float *)malloc(sizeof(float) * 5)))
		ft_fail("Error: Could not allocate memory.", NULL);
	while (f[s] && f[s] != ')')
	{
		if ((ft_isdigit(f[s]) && ((f[s - 1] == ','
			|| f[s - 1] == ' ' || f[s - 1] == '(') || f[s - 1] == '+'))
				|| (f[s] == '-' && f[s + 1] && ft_isdigit(f[s + 1])))
		{
			result = ft_atof(f + s);
			if (levier < 3)
				tab[levier] = result;
			levier++;
		}
		s++;
	}
	tab[3] = levier;
	tab[4] = s;
	return (tab);
}

int		search_pos_cam(t_cam *cam, char *f, int s)
{
	float	*tab;

	tab = three_values_tab(f, s);
	s = (int)tab[4];
	printf("tab3 : %f\n", tab[3]);
	if (!(f[s]) || (int)tab[3] != 3 || f[s] != ')')
	{
		free(tab);
		return (-1);
	}
	cam->px = tab[0];
	cam->py = tab[1];
	cam->pz = tab[2];
	free(tab);
	printf("x = %f, y = %f, z = %f\n", cam->px, cam->py, cam->pz);
	return (1);
}

int		search_dir_cam(t_cam *cam, char *f, int s)
{
	float	*tab;

	tab = three_values_tab(f, s);
	s = (int)tab[4];
	printf("tab3 : %f\n", tab[3]);
	if (!(f[s]) || (int)tab[3] != 3 || f[s] != ')')
	{
		free(tab);
		return (-1);
	}
	cam->vx = tab[0];
	cam->vy = tab[1];
	cam->vz = tab[2];
	free(tab);
	return (1);
}

int		read_camera(t_data *data, char *file, int select)
{
	t_cam	*new;
	char	*word;
	int		pos;
	int		dir;

	pos = 0;
	dir = 0;
	if (!(new = (t_cam *)malloc(sizeof(t_cam) * 1)))
		ft_fail("Error: Could not allocate memory.", data);
	while (file[select] && file[select] != '}')
	{
		word = NULL;
		if (ft_isalpha(file[select]))
			word = word_return(file, select);
		if (word != NULL)
		{
			select += ft_strlen(word);
			if (!(ft_strcmp(word, "pos")))
				pos = search_pos_cam(new, file, select);
			else
				dir = search_dir_cam(new, file, select);
			free(word);
		}
		select++;
	}
	if (pos > 0 && dir > 0 && data->cam != NULL)
		ft_fail("Error: Several valid cameras detected.", data);
	if (pos > 0 && dir > 0)
		data->cam = new;
	else
		free(new);
	return (select);
}

int		read_new_object(t_data *data, char *ob, char *file, int select)
{
	if (!(file[select]) || !(file[select + 1]))
		return (0);
	if (ft_strcmp(ob, "object") == 0)
		return (1);
	else if (ft_strcmp(ob, "light") == 0)
		return (2);
	else if (ft_strcmp(ob, "camera") == 0)
		return (read_camera(data, file, select));
	return (0);
}

int		read_file(t_data *data, char *file)
{
	int		select;
	char	*object;

	if (!data)
		return (-1);
	select = 0;
	while (file[select])
	{
		object = NULL;
		if (ft_isalpha(file[select]))
			object = word_return(file, select);
		if (object != NULL)
		{
			select += ft_strlen(object);
			if ((read_new_object(data, object, file, select)) > 0)
			{
			}
			free(object);
		}
		select++;
	}
	free(file);
	return (1);
}
