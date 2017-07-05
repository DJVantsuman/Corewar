/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:46:05 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/12 12:54:04 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str(char *s, int n, int l, int f)
{
	int t;

	t = l;
	if (f == 1)
	{
		s[0] = '-';
		while (l > 0)
		{
			s[l] = (n % 10) * -1 + '0';
			n /= 10;
			l--;
		}
	}
	else
		while (--l >= 0)
		{
			s[l] = n % 10 + '0';
			n /= 10;
		}
	s[t + 1] = '\0';
	return (s);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		f;
	int		t;

	i = 1;
	f = 0;
	t = n;
	while (n > 9 || n < -9)
	{
		n /= 10;
		i++;
	}
	if (t < 0)
		f = 1;
	if (f == 1)
		s = (char *)malloc(sizeof(char) * i + 2);
	else
		s = (char *)malloc(sizeof(char) * i + 1);
	if (!s)
		return (0);
	return (str(s, t, i, f));
}
