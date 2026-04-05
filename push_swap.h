/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:34:27 by kchibukh          #+#    #+#             */
/*   Updated: 2026/04/05 19:33:40 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stddef.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>

typedef enum e_operations
{
	PUSH_A,
	PUSH_B,
	SWAP_A,
	SWAP_B,
	SWAP_BOTH,
	ROTATE_A,
	ROTATE_B,
	ROTATE_BOTH,
	REVERSE_ROTATE_A,
	REVERSE_ROTATE_B,
	REVERSE_ROTATE_BOTH,
	OPERATIONS_COUNT
}	t_operations;

typedef enum e_strategy
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX,
}	t_strategy;

typedef struct s_push_swap_data	t_push_swap_data;

typedef struct s_stack
{
	int					value;
	int					index;
	struct s_stack		*next;
	t_push_swap_data	*data;
}	t_stack;

typedef struct s_push_swap_data
{
	t_stack		*a;
	t_stack		*b;
	t_strategy	strategy;
	bool		is_benchmark;
	float		disorder_metric;
	int			operations_count[OPERATIONS_COUNT];
}	t_push_swap_data;

//List functions
t_stack	*lstnew(int value);
void	lstadd_back(t_stack **lst, t_stack *new);

//Stack operations
void	swap(t_stack **stack, char *msg);
void	rotate(t_stack **stack, char *msg);
void	reverse_rotate(t_stack **stack, char *msg);
void	push(t_stack **stack1, t_stack **stack2, char *msg);

//Sorting utils
void	sort_two(t_stack **a);
int		chunk_size(t_stack *a);
void	sort_three(t_stack **a);
t_stack	*find_minimum(t_stack *stack);
int		size_of_stack(t_stack *stack);
int		find_max_index(t_stack *stack);
int		find_position(t_stack *stack, int index);
void	push_back_sorted(t_stack **b, t_stack **a);
void	bring_to_top(t_stack **a, t_stack *target);
int		count_in_range(t_stack *a, int min, int max);
void	update_chunk(int *min, int *max, int size_of_chunk, int size_of_stack);

//Main functions
void	print_stack(t_stack *stack);
void	init_data(t_push_swap_data *data);
void	sort_stack(t_push_swap_data *data);
void	choose_strategy(t_push_swap_data *data);
void	compute_disorder(t_push_swap_data *data);
void	check_flag(char *argv, t_push_swap_data *data);
void	parse_data(int argc, char **argv, t_push_swap_data *data);

//Parse utils
void	free_string_array(char **arr);
bool	is_num_repeat(int num, t_stack *stack);
int		ft_strcmp(const char *s1, const char *s2);
t_stack	*find_min_number_no_index(t_stack *stack);
void	push_to_stack(char *num, t_push_swap_data *data);
int		ft_atol(const char *nptr, t_push_swap_data *data);

//Error
void	free_stack(t_stack	**stack);
void	free_data(t_push_swap_data *data);
void	print_error(int error, char *msg, t_push_swap_data *data);

//Simple sort
void	sort_simple(t_push_swap_data *data);
void	selection_sort(t_stack	**a, t_stack **b);

//Medium sort
void	sort_medium(t_push_swap_data *data);
void	chunk_sort(t_stack	**a, t_stack **b);

//Complex sort
void	sort_complex(t_push_swap_data *data);
void	radix_sort(t_stack	**a, t_stack **b);

//Benchmark
int		get_operation_type(char *operation);
void	print_benchmark_data(t_push_swap_data *data);
void	print_disorder(t_push_swap_data *data);
void	print_strategy(t_push_swap_data *data);
void	print_total_ops(t_push_swap_data *data);
void	print_operations_line1(t_push_swap_data *data);
void	print_operations_line2(t_push_swap_data *data);
void	print_rotations_line1(t_push_swap_data *data);
void	print_rotations_line2(t_push_swap_data *data);

#endif