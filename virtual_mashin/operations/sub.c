/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:41:12 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:41:20 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void 	operation_sub(t_program *program, t_process *process)
{
	long int 	value;
	int 		k;
	int 		p;

	value = 0;
	p = 0;
	k = process->position;
	if (program->map[k] == 49 && program->map[k + 1] == 53)
	{
		if (is_register(program, get_position(k + 2)) == 1 &&
			is_register(program, get_position(k + 4)) == 1 &&
			is_register(program, get_position(k + 6)) == 1)
		{
			p = get_register(program, process->position + 2);
			value = program->registers[p];
			p = get_register(program, process->position + 4);
			value -= program->registers[p];
			p = get_register(program, process->position + 4) - 1;
			program->registers[p] = (int)value;
			program->carry = (*program)->carry == 0 ? 1 : 0;
		}
	}
}

void    sub(t_program *program, t_process *process)
{
	if (process->flag == 1)
	{
		process->position += 2;
		operation_sub(program, process);
		process->flag = 0;
	}
	else
		process->delay = 10;
}