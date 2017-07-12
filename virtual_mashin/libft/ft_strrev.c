/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 20:29:01 by itsuman           #+#    #+#             */
/*   Updated: 2016/11/30 21:21:49 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrev(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (s[i] >= 65 && s[i] <= 90)
				s[i] = 90 - (s[i] - 65);
			if (s[i] >= 97 && s[i] <= 122)
				s[i] = 122 - (s[i] - 97);
			i++;
		}
	}
	return (s);
}