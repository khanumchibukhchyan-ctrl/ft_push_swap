#include "push_swap.h"

void	execute_instruction(char *line, t_stack **a, t_stack **b)
{
	int	op;

	op = get_operation_type(line);
	if (op == PUSH_A)
		pa(a, b);
	else if (op == PUSH_B)
		pb(a, b);
	else if (op == SWAP_A)
		sa(a);
	else if (op == SWAP_B)
		sb(b);
	else if (op == SWAP_BOTH)
		ss(a, b);
	else if (op == ROTATE_A)
		ra(a);
	else if (op == ROTATE_B)
		rb(b);
	else if (op == ROTATE_BOTH)
		rr(a, b);
	else if (op == REVERSE_ROTATE_A)
		rra(a);
	else if (op == REVERSE_ROTATE_B)
		rrb(b);
	else if (op == REVERSE_ROTATE_BOTH)
		rrr(a, b);
}
