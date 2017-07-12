/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alldown.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 20:18:52 by itsuman           #+#    #+#             */
/*   Updated: 2016/11/30 20:28:24 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_alldown(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (s[i] >= 65 && s[i] <= 90)
				s[i] += 32;
			i++;
		}
	}
	return (s);
}