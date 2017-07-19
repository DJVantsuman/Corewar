/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:52:14 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:52:17 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void 	load_value(t_program **program, unsigned int pos, unsigned int val)
{
	(*program)->map[pos] = (val & 4278190080) >> 24;
	(*program)->map[pos + 1] = (val & 16711680) >> 16;
	(*program)->map[pos + 2] = (val & 65280) >> 8;
	(*program)->map[pos + 3] = (val & 255);
}

void    sti(t_program **program, t_process **process)
{
    char            param[3];
    unsigned int    val[3];
    int             shift;

    shift = 2;
    param[0] = (char)((*program)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
    param[1] = (char)((*program)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
    param[2] = (char)((*program)->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
	if (param[0] == REG_CODE)
	{
//		val[0] = get_reg_numb((*program), (*process), &shift);
//		if (val[0] > REG_NUMBER)
//			return ;
		val[0] = get_reg_value((*program), (*process), &shift);
	}
	if (param[1] == REG_CODE)
		val[1] = get_reg_value((*program), (*process), &shift);
	else if (param[1] == DIR_CODE)
		val[1] = get_dir_value((*program), (*process), &shift, 2);
	else if (param[1] == IND_CODE)
		val[1] = get_ind_value((*program), (*process), &shift);
	else
		return ;
	if (param[2] == REG_CODE)
		val[2] = get_reg_value((*program), (*process), &shift);
	else if (param[2] == DIR_CODE)
		val[2] = get_dir_value((*program), (*process), &shift, 2);
	else
		return ;
	load_value(&(*program), ((*process)->position +(val[1] + val[2])) %
							MEM_SIZE, val[0]);
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}