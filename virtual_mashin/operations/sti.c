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

void 	load_value(t_data **data, t_process **process, int pos,
				   unsigned int val)
{
	(*data)->map[pos] = (unsigned char)((val & 4278190080) >> 24);
	(*data)->map[pos + 1] = (unsigned char)((val & 16711680) >> 16);
	(*data)->map[pos + 2] = (unsigned char)((val & 65280) >> 8);
	(*data)->map[pos + 3] = (unsigned char)((val & 255));
	(*data)->map_v[pos] = (*process)->p_id;
	(*data)->map_v[pos + 1] = (*process)->p_id;
	(*data)->map_v[pos + 2] = (*process)->p_id;
	(*data)->map_v[pos + 3] = (*process)->p_id;

}

void    sti(t_data **data, t_process **process)
{
	unsigned char   param[3];
    unsigned int    val[3];
    int             shift;

    shift = 2;
    param[0] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
    param[1] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
    param[2] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
	if (param[0] == REG_CODE)
		val[0] = get_reg_value(&(*data), (*process), &shift);
	else
		return ;
	if (param[1] == REG_CODE)
		val[1] = get_reg_value(&(*data), (*process), &shift);
	else if (param[1] == DIR_CODE)
		val[1] = get_dir_value(&(*data), (*process), &shift, 2);
	else if (param[1] == IND_CODE)
		val[1] = get_ind_value(&(*data), (*process), &shift);
	else
		return ;
	if (param[2] == REG_CODE)
		val[2] = get_reg_value(&(*data), (*process), &shift);
	else if (param[2] == DIR_CODE)
		val[2] = get_dir_value(&(*data), (*process), &shift, 2);
	else
		return ;
	load_value(&(*data), &(*process), (short)(((*process)->position + (val[1] +
			val[2])) % MEM_SIZE), val[0]);
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}