
#include "push_swap.h"

int	ft_atol(const char *nptr, t_push_swap_data *data)
{
	int	sign;
	long	res;

	sign = 1;
	res = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + (*nptr - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			print_error(1, "Integer overflow\n", data);
		nptr++;
	}
	if (*nptr != '\0')
		print_error(1, "Is not number\n", data);
	return (res * sign);
}
