/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:55:18 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:55:21 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    lld(t_program **program, t_process **process)
{
	char            param[2];
	unsigned int    val[2];
	int             shift;
	int             i;

	shift = 2;
	i = 0;
	param[0] = (char)((*program)->map[(*process)->position + 1] & 192) >> 6;
	param[1] = (char)((*program)->map[(*process)->position + 1] & 48) >> 4;
	if ((*process)->flag == 1)
	{
		(*process)->flag = 0;
		if (param[0] == DIR_CODE)
		{
			val[0] = get_dir_value((*program), (*process), &shift);
			i += 4;
		}
		else if (param[0] == IND_CODE)
		{
			val[0] = get_ind_value((*program), (*process), &shift);
			i += 2;
		}
		else
			return ;
		if (param[1] == REG_CODE)
		{
			val[1] = get_reg_value((*program), (*process), &shift);
			i += 1;
		}
		else
			return ;
		if (val[1] <= REG_NUMBER && val[1] > 0)
		{
			(*program)->registers[val[1] - 1] = val[0];
			(*program)->carry = (*program)->carry == 0 ? 1 : 0;
			process->position = (process->position + i) % MEM_SIZE;
		}
	}
	else
		(*process)->delay = 10;
}