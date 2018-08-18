#include "RTv1.h"

float	ft_atof(const char *str)
{
	int		s;
	int		virgule;
	float	result;
	int		levier;

	s = 0;
	result = 0;
	levier = 1;
	virgule = 0;
	while (str[s] == '\f' || str[s] == '\n' || str[s] == ' '
		|| str[s] == '\t' || str[s] == '\r' || str[s] == '\v')
			s++;
	if (str[s] == '-')
		levier = -1;
	if (str[s] == '-' || str[s] == '+')
		s++;
	while (str[s] >= '0' && str[s] <= '9')
	{
		result = result * 10 + (str[s++] - '0');
		if (str[s] == '.')
			virgule = s++;
	}
	while (virgule != 0 && ft_isdigit(str[++virgule]))
		levier = levier * 10;
	return (result / levier);
}

t_obj	*create_object(t_data *data)
{
	t_obj	*new;

	if (!(new = (t_obj *)malloc(sizeof(t_obj))))
		ft_fail("Error: Could not allocate memory.", data);
	new->pos_c = 0;
	new->type_c = 0;
	new->radius_c = 0;
	new->height_c = 0;
	new->vector_c = 0;
	return (new);
}

