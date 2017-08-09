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

void	load_value(t_data **data, t_process **process, int pos, int val)
{
	if (pos < 0)
		pos += MEM_SIZE;
	pos %= MEM_SIZE;
	(*data)->map[pos] = (unsigned char)((val & 4278190080) >> 24);
	(*data)->map[(pos + 1) % MEM_SIZE] = (unsigned char)((val & 16711680) >> 16);
	(*data)->map[(pos + 2) % MEM_SIZE] = (unsigned char)((val & 65280) >> 8);
	(*data)->map[(pos + 3) % MEM_SIZE] = (unsigned char)((val & 255));
	(*data)->map_v[pos] = (*process)->p_id;
	(*data)->map_v[(pos + 1) % MEM_SIZE] = (*process)->p_id;
	(*data)->map_v[(pos + 2) % MEM_SIZE] = (*process)->p_id;
	(*data)->map_v[(pos + 3) % MEM_SIZE] = (*process)->p_id;
}

void	sti(t_data **data, t_process **process)
{
	unsigned char	param[3];
	int				val[4];
	int				shift;

	shift = 2;
	param[0] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
	param[1] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
	param[2] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
	if (param[0] == REG_CODE)
		val[0] = get_reg_value(&(*data), (*process), &shift);
	if (param[1] == REG_CODE)
		val[1] = get_reg_value(&(*data), (*process), &shift);
	else if (param[1] == DIR_CODE)
		val[1] = get_dir_value(&(*data), (*process), &shift, 2);
	else if (param[1] == IND_CODE)
		val[1] = get_ind_value(&(*data), (*process), &shift, 4);
	if (param[2] == REG_CODE)
		val[2] = get_reg_value(&(*data), (*process), &shift);
	else if (param[2] == DIR_CODE)
		val[2] = get_dir_value(&(*data), (*process), &shift, 2);
	val[3] = ((*process)->position + ((val[1] + val[2]))) % MEM_SIZE;
	(*process)->position += count_shift(3, (*data)->map[((*process)->position + 1) % MEM_SIZE], 2) % MEM_SIZE;
	if (param[0] == 1 && param[1] > 0 && (param[2] == 1 || param[2] == 2))
		load_value(&(*data), &(*process), val[3], val[0]);
}
