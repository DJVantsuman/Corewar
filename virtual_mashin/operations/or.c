/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:45:39 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:45:42 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    or(t_data **data, t_process **process)
{
	unsigned char   param[3];
	int    val[3];
	int             shift;
	int             i;

	shift = 2;
	i = 0;
	param[0] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
	param[1] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
	param[2] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
	while (i < 2)
	{
		if (param[i] == REG_CODE)
			val[i] = get_reg_value(&(*data), (*process), &shift);
		else if (param[i] == DIR_CODE)
			val[i] = get_dir_value(&(*data), (*process), &shift, 4);
		else if (param[i] == IND_CODE)
			val[i] = get_ind_value(&(*data), (*process), &shift);
		else
			break;
		i++;
	}
	val[2] = get_reg_numb(&(*data), (*process), &shift);
	if (val[2] <= REG_NUMBER && val[2] > 0 && i == 2)
		(*process)->registers[val[2] - 1] = val[0] | val[1];
	(*process)->carry = (*process)->carry == 0 ? 1 : 0;
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}