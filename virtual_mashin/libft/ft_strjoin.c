/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 23:09:11 by itsuman           #+#    #+#             */
/*   Updated: 2017/02/08 20:21:56 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	l;
	char	*s;

	i = 0;
	l = 0;
	s = NULL;
	if (s1 && s2)
	{
		l = (ft_strlen((char *)s1) + ft_strlen((char *)s2));
		s = (char *)malloc(l + 1);
		if (s)
		{
			i = -1;
			l = -1;
			while (s1[++i])
				s[i] = s1[i];
			while (s2[++l])
				s[i++] = s2[l];
			s[i] = '\0';
		}
	}
	return (s);
}
