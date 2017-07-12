/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:35:07 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:35:10 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int 	get_position(int s)
{
	if (s >= MEM_SIZE)
		s -= MEM_SIZE;
	return (s);
}

int 	get_register(t_program *program, int k)
{
	int 	z;

	z = 0;
	if (program->map[k + 1] > 47 && program->map[k + 1] < 58)
		z = z + program->map[k + 1] - 48;
	else if (program->map[k + 1] > 64 && program->map[k + 1] < 71)
		z = z + program->map[k + 1] - 55;
	else
		return (0);
	if (program->map[k] > 47 && program->map[k] < 58)
		z = z + 16 * (program->map[k] - 48);
	else if (program->map[k] > 64 && program->map[k] < 71)
		z = z + 16 * (program->map[k] - 55);
	else
		return (0);
	return (z);
}

int 	is_register(t_program *program, int p)
{
	int 	z;

	z = get_register(program, p);
	if (z > 0 && z <= REG_NUMBER)
		return (1);
	else
		return (0);
}

long int 	get_dir4(t_program *program, t_process *process)
{
	long int 	val;
	int 		z;
	int 		k;

	z = 1;
	k = 10;
	val = 0;
	while (--k > 1)
	{
		if (program->map[process->position + k] > 47 &&
			program->map[process->position + k] < 58)
			val = val + z * (program->map[k] - 48);
		else
			val = val + z * (program->map[k] - 55);
		z *= 16;
	}
//	4294967295
//	2147483648
	while (val > 2147483647)
		val -= 2147483648;
	return (2147483647 - val);
}

long int 	get_indir(t_program *program, t_process *process)
{
	long int 	val;
	int 		z;
	int 		k;

	z = 1;
	k = 6;
	val = 0;
	//change indirect
	while (--k > 1)
	{
		if (program->map[process->position + k] > 47 &&
			program->map[process->position + k] < 58)
			val = val + z * (program->map[k] - 48);
		else
			val = val + z * (program->map[k] - 55);
		z *= 16;
	}
	return (2147483647 - val);
}

void	make_ld(t_program *program, t_process *process)
{
	long int 	value;
	int 		reg;
	int 		p;

	value = 0;
	p = 0;
	if (program->map[k + 1] == 57)
	{
		value = get_dir4(program, process);
		p = get_register(program, process->position + 10);
		program->registers[p - 1] = value;
	}
	else
	{
		//indirect
		value = get_indir(program, process);
		p = get_register(program, process->position + 6);
		program->registers[p - 1] = value;
	}
	if (program->carry == 0)
		program->carry = 1;
	else
		program->carry = 0;
}

void 	operation_ld(t_program *program, t_process *process)
{
	int 	k;

	k = process->position;
	if (program->map[k] == 48)
	{
		if (program->map[k + 1] == 57)
		{
			if (is_register(program, get_position(k + 10)) == 1)
				make_ld(program, process);
		}
		else if (program->map[k + 1] == 68 || program->map[k + 1] == 100)
		{
			if (is_register(program, k + 6) == 1)
				make_ld(program, process);
		}
	}
}

void    ld(t_program *program, t_process *process)
{
	if (process->flag == 1)
	{
		process->position += 2;
		operation_ld(program, process);
		process->flag = 0;
	}
	else
		process->delay = 5;
}

