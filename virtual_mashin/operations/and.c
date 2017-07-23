/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:43:26 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:43:28 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int    get_dir_value(t_data **data, t_process *process, int *shift, int dsize)
{
	int    i;
	int    val[4];

	i = 0;
	while (i < dsize)
	{
		val[i] = ((*data)->map[(process->position + (*shift)) % MEM_SIZE]);
		(*shift)++;
		i++;
	}
	if (dsize == 4)
		return (val[0] << 24) + (val[1] << 16) + (val[2] << 8) + val[3];
	else
		return ((val[0] << 8) + val[1]);
}

int    get_ind_value(t_data **data, t_process *process, int *shift, int size)
{
	int    val[6];
	int i;

	i = 0;
	val[0] = ((*data)->map[(process->position + (*shift)) % MEM_SIZE]);
	val[1] = ((*data)->map[(process->position + (*shift) + 1) % MEM_SIZE]);

	while (i < size)
	{
		val[i + 2] = (*data)->map[(process->position + ((val[0] << 8) +
				val[1]) + i) % MEM_SIZE];
		i++;
	}
//	val[2] = (*data)->map[(process->position + ((val[0] << 8) + val[1])) %
//						  MEM_SIZE];
//	val[3] = (*data)->map[(process->position + ((val[0] << 8) + val[1]) + 1)
//						  % MEM_SIZE];
//	val[4] = (*data)->map[(process->position + ((val[0] << 8) + val[1]) + 2)
//						  % MEM_SIZE];
//	val[5] = (*data)->map[(process->position + ((val[0] << 8) + val[1]) + 3)
//						  % MEM_SIZE];
	(*shift) += 2;
	if (size == 4)
		return ((val[2] << 24) + (val[3] << 16) + (val[4] << 8) + val[5]);
	else
		return  ((val[2] << 8) + val[3]);
}

int    get_reg_value(t_data **data, t_process *process, int *shift)
{
	int res;

	res = process->registers[(*data)->map[(process->position + (*shift)) % MEM_SIZE] - 1];
	(*shift)++;
	return res;
}

int    get_reg_numb(t_data **data, t_process *process, int *shift)
{
	int res;

	res = (*data)->map[(process->position + (*shift)) % MEM_SIZE];
	(*shift)++;
	return res;
}

void    and(t_data **data, t_process **process)
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
			val[i] = get_ind_value(&(*data), (*process), &shift, 4);
		i++;
	}
	val[2] = get_reg_numb(&(*data), (*process), &shift);
	if (val[2] <= REG_NUMBER && val[2] > 0 && param[0] > 0 && param[1] > 0 && param[2] == 1)
	{
		(*process)->registers[val[2] - 1] = (val[0] & val[1]);
	}
	(*process)->carry = (val[0] & val[1]) == 0 ? 1 : 0;
	(*process)->position += count_shift (3, (*data)->map[((*process)->position + 1) % MEM_SIZE], 4) % MEM_SIZE;
}