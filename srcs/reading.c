#include "RTv1.h"

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

int		search_pos_cam(t_cam *cam, char *f, int s)
{
	int		x;
	int		y;
	int		z;
	int		result;
	int		levier;

	levier = 0;
	while (f[s] && f[s] != ')')
	{
		if ((ft_isdigit(f[s]) && ((f[s - 1] == ','
			|| f[s - 1] == ' ' || f[s - 1] == ')') || f[s - 1] == '+'))
				|| (f[s] == '-' && f[s + 1] && ft_isdigit(f[s + 1])))
		{
			result = atoi(f + s);
			if (levier == 0)
				x = result;
			else if (levier == 1)
				y = result;
			else if (levier == 2)
				z = result;
			levier++;
		}
		s++;
	}
	if (!(f[s]) || levier != 2 || f[s] != ')')
		return (-1);
	cam->px = x;
	cam->py = y;
	cam->pz = z;
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
	if (data->cam != NULL)
		ft_fail("Error: Several cameras detected.", data);
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
//			else
//				dir = search_dir(data, new, file, select);
			free(word);
		}
		select++;
	}
	if (pos == 1)
		ft_putstr("camera pos OK\n");
	if (pos == 1 && dir == 1)
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
				ft_putstr(object);
				ft_putchar('\n');
			}
			free(object);
		}
		select++;
	}
	free(file);
	return (1);
}
