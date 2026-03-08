/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:29:19 by kchibukh          #+#    #+#             */
/*   Updated: 2026/02/09 17:20:12 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	k;

	p = (unsigned char *)s;
	k = (unsigned char)c;
	while (n--)
	{
		if (*p == k)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
