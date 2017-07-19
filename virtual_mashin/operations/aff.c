/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 21:00:23 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 21:00:25 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    aff(t_program **program, t_process **process)
{
	char    byte[2];

	byte[0] = (*program)->map[(*process)->position + 1];
	byte[1] = (*program)->map[(*process)->position + 2];
	if (byte[0] == 64)
	{
		if (byte[1] <= REG_NUMBER && byte[1] > 0)
			printf("%c", (*program)->registers[byte[1] - 1] % 256);
	}
	(*process)->position = ((*process)->position + 1) % MEM_SIZE;
}