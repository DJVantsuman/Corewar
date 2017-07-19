/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:35:07 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:35:10 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void   ld(t_program **program, t_process **process)
{
	char            par[2];
	unsigned int    val[2];
	int             shift;

	shift = 2;
	par[0] = (char)((*program)->map[(((*process)->position + 1)) % MEM_SIZE] & 192) >> 6;
	par[1] = (char)((*program)->map[(((*process)->position + 1)) % MEM_SIZE] & 48) >> 4;
	if ((*process)->flag == 1)
	{
		(*process)->flag = 0;
		if (par[0] == DIR_CODE)
		{
			val[0] = get_dir_value((*program), (*process), &shift);
			shift += 4;
		}
		else if (par[0] == IND_CODE)
		{
			val[0] = get_ind_value((*program), (*process), &shift);
			shift += 2;
		}
		else
			return ;
		if (par[1] == REG_CODE)
		{
			val[1] = get_reg_value((*program), (*process), &shift);
			shift += 1;
		}
		else
			return ;
		if (val[1] <= REG_NUMBER && val[1] > 0)
		{
			(*program)->registers[val[1] - 1] = val[0] % IDX_MOD;
			(*program)->carry = (*program)->carry == 0 ? 1 : 0;
			(*process)->position = ((*process)->position + shift) % MEM_SIZE;
		}
	}
	else
		(*process)->delay = 5;
}
