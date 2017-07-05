/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 22:37:15 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/12 12:00:26 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;

	i = 0;
	d = NULL;
	if (s)
	{
		d = (char *)malloc(sizeof(char) * len + 1);
		if (d)
		{
			while (s[start] != '\0' && len > 0)
			{
				d[i] = s[start];
				i++;
				start++;
				len--;
			}
			d[i] = '\0';
		}
	}
	return (d);
}
