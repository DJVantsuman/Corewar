/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:39:41 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:39:44 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void 	operation_add(t_program *program, t_process *process)
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
			p = get_register(program, process->position + 2);
			value = program->registers[p];
			p = get_register(program, process->position + 4);
			value += program->registers[p];
			if (value > 2147483647)

	}
}

void    add(t_program *program, t_process *process)
{
	if (process->flag == 1)
	{
		process->position += 2;
		operation_add(program, process);
		process->flag = 0;
	}
	else
		process->delay = 10;

}