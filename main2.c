// # include <stdlib.h>
// # include <unistd.h>
// # include <stdint.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len])
// 		len++;
// 	return (len);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (!s)
// 		return ;
// 	write (fd, s, ft_strlen(s));
// }

// void	print_error(int error, char* msg)
// {
// 	ft_putstr_fd("Error\n", 2);
// 	if (msg)
// 	  ft_putstr_fd(msg, 1);
// 	  exit(error);
// }

// int	ft_a2i(const char *nptr)
// {
// 	int	sign;
// 	int	res;

// 	sign = 1;
// 	res = 0;
// 	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
// 		nptr++;
// 	if (*nptr == '-' || *nptr == '+')
// 	{
// 		if (*nptr == '-')
// 			sign = -1;
// 		nptr++;
// 	}
// 	while (*nptr >= '0' && *nptr <= '9')
// 	{
// 		res = res * 10 + (*nptr - '0');
// 		nptr++;
// 	}

// 	return (res * sign);
// }

// int main(int argc, char const *argv[])
// {
// 	printf("%d\n", ft_a2i("-4233fc42vsdfsdf-"));
// 	return 0;
// }
