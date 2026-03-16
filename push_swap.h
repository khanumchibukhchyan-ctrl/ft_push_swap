/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:34:27 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/16 19:06:32 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stddef.h>
# include <stdbool.h>

typedef struct s_push_swap_data
{
	t_stack		*a;
	t_stack		*b;
	t_strategy	strategy;
	bool		is_benchmark;
	float		disorder_metric;
}	t_push_swap_data;

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

//List functions
t_stack	*ft_lstnew(int value);
void	ft_lstadd_back(t_stack **lst, t_stack *new);

//Stack operations
void	swap(t_stack **stack, char *msg);
void	rotate(t_stack **stack, char *msg);
void	reverse_rotate(t_stack **stack, char *msg);
void	push(t_stack **stack1, t_stack **stack2, char *msg);

//Main functions
void	init_data(t_push_swap_data *data);
void	sort_stack(t_push_swap_data *data);
float	compute_disorder(t_push_swap_data *data);
void	check_flag(char *argv, t_push_swap_data *data);
void	parse_data(int argc, char **argv, t_push_swap_data *data);

//Parse utiles
char	**split_args(char *args);
char	*join_args(int argc, char **argv);
void	build_stack(char **nums, t_list **stack);

#endif
