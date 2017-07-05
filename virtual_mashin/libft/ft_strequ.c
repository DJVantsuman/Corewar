/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 21:52:57 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/09 16:13:33 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int l1;
	int l2;
	int f;

	f = 1;
	if (s1 && s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		if (l1 != l2)
			return (0);
		else
			while (l1 >= 0)
			{
				if (s1[l1] != s2[l1])
				{
					f = 0;
					break ;
				}
				l1--;
			}
	}
	return (f);
}
