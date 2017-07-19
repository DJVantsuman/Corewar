/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:48:29 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:48:30 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    zjmp(t_program **program, t_process **process)
{
	unsigned char val[2];

	if ((*program)->carry == 1)
	{
		val[0] += (*program)->map[((*process)->position + 1) % MEM_SIZE];
		val[1] += (*program)->map[((*process)->position + 2) % MEM_SIZE];
		(*process)->position = ((*process)->position + (val[0] << 8) +
				val[1]) % MEM_SIZE;
	}
	else
		(*process)->position += 3 % MEM_SIZE;
}