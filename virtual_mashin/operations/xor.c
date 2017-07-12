/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:47:07 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:47:10 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    xor(t_program *program, t_process *process)
{
	char            *param;
	unsigned int    val[3];
	int             i;
	int             shift;

	i = 3;
	shift = 1;
	decode_byte(program->map[process->position + 1], &param);
	if (process->flag == 1)
	{
		/*
		 * если 3 параметр == 01 (reg)
		 * и регистр существует
		 */
		if (param[2] == 1)
		{
			while (i--)
				val[i] = get_dir_ind_reg(program, process, param[i], 4, &shift);
			process->position += shift + 1;
			if (val[2] <= REG_NUMBER && val[2] > 0)
				program->registers[val[2] - 1] = val[0] ^ val[1];
			program->carry = program->carry == 0 ? 1 : 0;
		}
		process->flag = 0;
	}
	else
		process->delay = 6;
}