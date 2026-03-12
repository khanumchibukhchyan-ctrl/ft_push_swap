/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:34:27 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/12 21:35:37 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include "libft.h"

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

void	parse_args(int argc, char **argv);
void	sort_stack(t_stack *a, t_stack *b, t_strategy stategy);
void	init_stack(t_stack **a, t_stack **b, int argc, char **argv);
void	push(t_stack **stack1, t_stack **stack2, char *msg);
void	swap(t_stack **stack, char *msg);
void	rotate(t_stack **stack, char *msg);
void	reverse_rotate(t_stack **stack, char *msg);


#endif
