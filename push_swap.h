/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:34:27 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/17 21:14:33 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stddef.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}	t_stack;

typedef enum e_strategy
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX,
}	t_strategy;

typedef struct s_push_swap_data
{
	t_stack		*a;
	t_stack		*b;
	t_strategy	strategy;
	bool		is_benchmark;
	float		disorder_metric;
}	t_push_swap_data;

//List functions
t_stack	*lstnew(int value);
void	lstadd_back(t_stack **lst, t_stack *new);

//Stack operations
void	swap(t_stack **stack, char *msg);
void	rotate(t_stack **stack, char *msg);
void	reverse_rotate(t_stack **stack, char *msg);
void	push(t_stack **stack1, t_stack **stack2, char *msg);

//Main functions
void	print_stack(t_stack *stack);
void	init_data(t_push_swap_data *data);
// void	sort_stack(t_push_swap_data *data);
void	compute_disorder(t_push_swap_data *data);
void	check_flag(char *argv, t_push_swap_data *data);
void	parse_data(int argc, char **argv, t_push_swap_data *data);

//Parse utiles
void	free_string_array(char **arr);
int		ft_strcmp(const char *s1, const char *s2);
void	push_to_stack(char *num, t_push_swap_data *data);
int		ft_atol(const char *nptr, t_push_swap_data *data);

//Error
void	free_stack(t_stack	**stack);
void	free_data(t_push_swap_data *data);
void	print_error(int error, char *msg, t_push_swap_data *data);

#endif
