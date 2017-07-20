/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:56:59 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:57:03 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    lldi(t_data **data, t_process **process)
{
    char            param[3];
    unsigned int    val[3];
    int             shift;

    shift = 2;
    param[0] = (char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
    param[1] = (char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
    param[2] = (char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
	if (param[0] == REG_CODE)
		val[0] = get_reg_value(&(*data), (*process), &shift);
	else if (param[0] == DIR_CODE)
		val[0] = get_dir_value(&(*data), (*process), &shift, 2);
	else if (param[0] == IND_CODE)
		val[0] = get_ind_value(&(*data), (*process), &shift);
	else
		return ;
	if (param[1] == REG_CODE)
		val[1] = get_reg_value(&(*data), (*process), &shift);
	else if (param[1] == DIR_CODE)
		val[1] = get_dir_value(&(*data), (*process), &shift, 2);
	else
		return ;
	val[2] = get_reg_numb(&(*data), (*process), &shift);
	if (val[2] <= REG_NUMBER && val[2] > 0)
		(*process)->registers[val[2] - 1] = get_direct(&(*data), (val[0] +
				val[1]));
	(*process)->carry = (*process)->carry == 0 ? 1 : 0;
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}
