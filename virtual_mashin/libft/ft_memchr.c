/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:40:57 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/12 12:10:46 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buffer, int ch, size_t count)
{
	size_t	i;

	i = 0;
	while (count > 0)
	{
		if (((char *)buffer)[i] == (char)ch)
			return ((char *)buffer + i);
		i++;
		count--;
	}
	return (NULL);
}
