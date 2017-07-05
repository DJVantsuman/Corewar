/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 17:37:19 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/05 20:28:12 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(const char *s)
{
	int		i;
	int		l;

	i = 0;
	l = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	l--;
	while (s[l] == ' ' || s[l] == '\t' || s[l] == '\n')
		l--;
	if (s[i] == '\0')
		return (0);
	else
		return (++l - i);
}

char		*ft_strtrim(char const *s)
{
	char	*cop;
	int		l;
	int		i;
	int		t;

	i = 0;
	t = 0;
	cop = NULL;
	if (s)
	{
		l = ft_strlen(s) - 1;
		cop = (char *)malloc(sizeof(char) * len(s) + 1);
		if (!cop)
			return (0);
		while (s[i] <= 32)
			i++;
		while (s[l] <= 32)
			l--;
		while (i <= l)
			cop[t++] = s[i++];
		cop[t] = '\0';
	}
	return (cop);
}
