/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:33:56 by kchibukh          #+#    #+#             */
/*   Updated: 2026/02/09 20:33:29 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
	{
		len = 1;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*new;
	int		i;

	nb = n;
	i = get_len(n);
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	new[i] = '\0';
	if (nb == 0)
	{
		new[0] = '0';
	}
	if (nb < 0)
	{
		nb = -nb;
		new[0] = '-';
	}
	while (nb > 0)
	{
		new[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	return (new);
}
