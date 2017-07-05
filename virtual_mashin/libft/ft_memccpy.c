/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 18:37:19 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/12 12:12:40 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *source, int ch, size_t count)
{
	size_t	i;

	i = 0;
	while (count > 0)
	{
		if (((char *)source)[i] == ch)
		{
			((char *)dest)[i] = ((char *)source)[i];
			return ((char *)dest + ++i);
		}
		((char *)dest)[i] = ((char *)source)[i];
		i++;
		count--;
	}
	return (NULL);
}
