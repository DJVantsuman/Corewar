/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:10:16 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/06 19:03:21 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void			*ft_memmove(void *to, const void *from, size_t count)
{
	const char	*s;
	char		*d;

	s = from;
	d = to;
	if (s != to)
	{
		if (s < d)
			while (count--)
				d[count] = s[count];
		if (s > d)
			while (count--)
				*d++ = *s++;
	}
	return (to);
}
