/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 18:07:08 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/05 20:24:44 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(char const *s, char c)
{
	int		l;

	l = 0;
	while (s[l] != c && s[l])
		l++;
	return (l);
}

static int	nam(char const *s, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (s[0] != c)
		n++;
	while (s[i] != '\0')
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
			n++;
		i++;
	}
	return (n);
}

static void	split(char const *s, char **a, char c)
{
	int		i;
	int		t;
	int		l;

	i = 0;
	t = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			l = len(s + i, c);
			a[t] = (char *)malloc(sizeof(char) * l + 1);
			l = 0;
			while (s[i] != c && s[i] != '\0')
				a[t][l++] = s[i++];
			a[t++][l] = '\0';
		}
		else
			i++;
	}
	a[t] = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	char	**a;
	int		i;
	int		t;

	i = 0;
	t = 0;
	if (s)
	{
		a = (char **)malloc(sizeof(char*) * nam(s, c) + 1);
		if (!a)
			return (NULL);
		split(s, a, c);
		return (a);
	}
	else
		return (NULL);
}
