/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 19:31:47 by itsuman           #+#    #+#             */
/*   Updated: 2017/03/29 20:14:19 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			j = 0;
			if (s1[i] == s2[j])
				while (s2[j])
				{
					if (s2[j] != s1[i + j])
						break ;
					j++;
					if (s2[j] == '\0')
						return ((char *)s1 + i);
				}
			i++;
		}
	}
	return (0);
}
