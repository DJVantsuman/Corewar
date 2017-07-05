/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 20:31:04 by itsuman           #+#    #+#             */
/*   Updated: 2016/12/07 20:02:00 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char *ret_big;

	ret_big = ft_strstr(big, little);
	if ((ret_big - big) + ft_strlen(little) > len)
		return (0);
	return (ret_big);
}
