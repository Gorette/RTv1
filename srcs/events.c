#include "RTv1.h"

int		close_program(t_data *d)
{
	if (d)
	// free ce qu il y a a free
		exit(0);
	exit(0);
}

int		key_release(int key, void *d)
{
	if (key == 53 || key == 12)
		close_program(d);
	return (1);
}
