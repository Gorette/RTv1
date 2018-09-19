#include "RTv1.h"

float	ft_clamp(float to_clamp, float min, float max)
{
	if (to_clamp > max)
		return (max);
	if (to_clamp < min)
		return (min);
	return (to_clamp);
}
