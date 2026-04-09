#include "push_swap.h"

int	main(int argc, char **argv)

{
	t_stack		*a;
	t_stack		*b;

	if (argc < 2)
		return (0);

	a = NULL;
	b = NULL;
	parse_data(argc, argv, &a);
	read_and_execute(&a, &b);

	if (is_sorted(a) && b == NULL)
		write (1, "OK\n", 3);
	else
		write (1, "KO\n", 3);

	free_stack(&a);
	free_stack(&b);
	return (0);
}