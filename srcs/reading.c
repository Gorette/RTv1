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

int		read_camera(t_data *data, char *file, int select)
{
	t_cam	*new;
	char	*word;
	int		pos;
	int		vector;

	pos = 0;
	vector = 0;
	if (data->cam != NULL)
		ft_fail("Error: Several cameras detected.", data);
	while (file[select] && file[select] != '}')
	{
		word = NULL;
		if (ft_isalpha(file[select]))
			word = word_return(file, select)
		if (word != NULL)
			read_word(word);
		select++;
	}
	if (pos && vector)
		data->cam = new;
	else
		free(new);
	return (select);
}

int		read_new_object(t_data *data, char *ob, char *file, int select)
{
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
			if ((select = read_new_object(data, object, file, select)) > 0)
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
