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

unsigned int    get_dir_value(t_data **data, t_process *process, int
*shift, int dsize)
{
	int             i;
	unsigned int    val[4];

	i = 0;
	while (i < dsize)
	{
		val[i] = (unsigned char)((*data)->map[(process->position +
				(*shift)) % MEM_SIZE]);
		(*shift)++;
		i++;
	}
	if (dsize == 4)
		return (val[0] << 24) + (val[1] << 16) + (val[2] << 8) + val[3];
	else
		return ((val[0] << 8) + val[1]);
}

unsigned int    get_ind_value(t_data **data, t_process *process, int *shift)
{
	unsigned int    val[4];

	val[0] = (unsigned char)((*data)->map[(process->position + (*shift)) %
									  MEM_SIZE]);
	val[1] = (unsigned char)((*data)->map[(process->position + (*shift) + 1)
										  % MEM_SIZE]);
	val[2] += (unsigned char)(*data)->map[(process->position + ((val[0] << 8) + val[1])) % MEM_SIZE];
	val[3] += (unsigned char)(*data)->map[(process->position + ((val[0] << 8) + val[1]) + 1) % MEM_SIZE];
	(*shift) += 2;
	return ((val[2] << 8) + val[3]);
}

unsigned int    get_reg_value(t_data **data, t_process *process, int *shift)
{
	unsigned int res;

	res = process->registers[(*data)->map[(process->position + (*shift)) % MEM_SIZE] - 1];
	(*shift)++;
	return res;
}

unsigned int    get_reg_numb(t_data **data, t_process *process, int *shift)
{
	unsigned int res;

	res = (unsigned int)(*data)->map[(process->position + (*shift)) % MEM_SIZE];
	(*shift)++;
	return res;
}

void    and(t_data **data, t_process **process)
{
	char            param[3];
	unsigned int    val[3];
	int             shift;
	int             i;

	shift = 2;
	i = 0;
	param[0] = (char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
	param[1] = (char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
	param[2] = (char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
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
		(*process)->registers[val[2] - 1] = val[0] & val[1];
	(*process)->carry = (*process)->carry == 0 ? 1 : 0;
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}