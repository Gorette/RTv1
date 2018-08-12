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

//void	read_new_object(t_data *data, char *file, int select, char *ob)
//{
//}

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
			ft_putstr(object);
			ft_putchar('\n');
//			read_new_object(data, file, select, object);
			free(object);
		}
		select++;
	}
	free(file);
	return (1);
}
