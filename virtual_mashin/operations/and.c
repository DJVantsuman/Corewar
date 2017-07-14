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

unsigned int    get_dir_value(t_program *program, t_process *process, int *shift)
{
	int             i;
	unsigned int    val[4];

	i = 0;
	while (i < DIR_SIZE)
	{
		val[i] = (unsigned int)program->map[process->position + (*shift)];
		(*shift)++;
		i++;
	}
	return (val[0] << 24) + (val[1] << 16) + (val[2] << 8) + val[3];
}

unsigned int    get_ind_value(t_program *program, t_process *process, int *shift)
{
	unsigned int    val[4];

	val[0] += program->map[process->position + (*shift)];
	val[1] += program->map[process->position + (*shift) + 1];
	val[2] += program->map[process->position + ((val[0] << 8) + val[1])];
	val[3] += program->map[process->position + ((val[0] << 8) + val[1]) + 1];
	(*shift) += 2;
	return ((val[2] << 8) + val[3]);
}

unsigned int    get_reg_value(t_program *program, t_process *process, int *shift)
{
	unsigned int res;

	res = program->registers[(program->map[process->position + (*shift)]) - 1];
	(*shift)++;
	return res;
}

unsigned int    get_reg_numb(t_program *program, t_process *process, int *shift)
{
	unsigned int res;

	res = (unsigned int)program->map[process->position + (*shift)];
	(*shift)++;
	return res;
}

void    and(t_program **program, t_process **process)
{
	char            param[3];
	unsigned int    val[3];
	int             shift;
	int             i;

	shift = 2;
	i = 0;
	param[0] = (char)((*program)->map[(*process)->position + 1] & 192) >> 6;
	param[1] = (char)((*program)->map[(*process)->position + 1] & 48) >> 4;
	param[2] = (char)((*program)->map[(*process)->position + 1] & 12) >> 2;
	if ((*process)->flag == 1)
	{
		while (i < 2)
		{
			if (param[i] == REG_CODE)
				val[i] = get_reg_value((*program), (*process), &shift);
			else if (param[i] == DIR_CODE)
				val[i] = get_dir_value((*program), (*process), &shift);
			else if (param[i] == IND_CODE)
				val[i] = get_ind_value((*program), (*process), &shift);
			else
				break;
			i++;
		}
		val[2] = get_reg_numb((*program), (*process), &shift);
		if (val[2] <= REG_NUMBER && val[2] > 0 && i == 2)
			(*program)->registers[val[2] - 1] = val[0] & val[1];
		(*program)->carry = (*program)->carry == 0 ? 1 : 0;
		(*process)->flag = 0;
	}
	else
		(*process)->delay = 6;
}