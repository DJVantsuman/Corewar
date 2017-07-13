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

void    or(t_program *program, t_process *process)
{
	char            param[3];
	unsigned int    val[3];
	int             shift;
	int             i;

	shift = 2;
	i = 0;
	param[0] = (char)(program->map[process->position + 1] & 192) >> 6;
	param[1] = (char)(program->map[process->position + 1] & 48) >> 4;
	param[2] = (char)(program->map[process->position + 1] & 12) >> 2;
	if (process->flag == 1)
	{
		while (i < 2)
		{
			if (param[i] == REG_CODE)
				val[i] = get_reg_value(program, process, &shift);
			else if (param[i] == DIR_CODE)
				val[i] = get_dir_value(program, process, &shift);
			else if (param[i] == IND_CODE)
				val[i] = get_ind_value(program, process, &shift);
			else
				break;
			i++;
		}
		val[2] = get_reg_numb(program, process, &shift);
		if (val[2] <= REG_NUMBER && val[2] > 0 && i == 2)
			program->registers[val[2] - 1] = val[0] | val[1];
		program->carry = program->carry == 0 ? 1 : 0;
		process->flag = 0;
	}
	else
		process->delay = 6;
}