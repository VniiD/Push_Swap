#include "push_swap.h"

int	ft_sqrt(int number)
{
	int	i;

	if (number < 0)
		return (0);
	i = 1;
	while (i * i <= number)
	{
		if (i * i == number || (i + 1) * (i + 1) > number)
			return (i);
		i++;
	}
	return (i);
}