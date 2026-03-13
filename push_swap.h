/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:34:27 by kchibukh          #+#    #+#             */
/*   Updated: 2026/03/13 20:58:32 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include "libft.h"
# include <stdbool.h>

typedef struct s_pushswap_data
{
	t_stack		*a;
	t_stack		*b;
	t_strategy	strategy;
	bool		is_benchmark;
	float		disorder_metric;
}	t_pushswap_data;

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

#endif
