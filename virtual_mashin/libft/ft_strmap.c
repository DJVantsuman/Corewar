/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 20:33:51 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/05 20:18:14 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		l;
	char	*s2;

	l = 0;
	i = 0;
	s2 = NULL;
	if (s)
	{
		while (s[l] != '\0')
			l++;
		s2 = (char *)malloc(l + 1);
		if (!s2)
			return (NULL);
		while (s[i] != '\0')
		{
			s2[i] = f(s[i]);
			i++;
		}
		s2[i] = '\0';
	}
	return (s2);
}
