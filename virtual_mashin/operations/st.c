/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:37:29 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:37:33 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

int 	get_index(int a)
{
	int 	p;

	p = a;
	if (p >= MEM_SIZE)
		p -= MEM_SIZE;
	if (p < 0)
		p = MEM_SIZE - 1;
	return (p); 
}

void	save_st(long int value, int p, t_program *program)
{
	long int 	x;
	int 		t;
	int 		val;
	int 		index;

	val = value;
	x = 16;
	t = 7;
	index = 0;
	while (t-- > -1)
	{
		index = get_index(p + t + 1);
		if (val % x < 10)
			program->map[index] = 48 + val % x;
		else
			program->map[index] = 55 + val % x;
		val = val - val % x;
		x *= 16;
	}
}

void	save_st_copy(t_program *program, t_process *process, int p)
{
	//MAKE SURE
	//kak opredelyat adress k T_IND otkuda schityvat i skopirovat eto v mesto po index "P" 
}

void	make_st(t_program *program, t_process *process)
{
	long int 	value;
	int 		reg;
	int 		p;

	value = 0;
	p = 0;
	if (program->map[k + 1] == 53)
	{
		p = get_register(program, process->position + 2);
		value = program->registers[p];
		p = get_register(program, process->position + 6);
		p = process->position - 2 + (p % IDX_MOD);
		save_st(value, p, program);
		process->position += 6;
//pechalka
	}
	else
	{
		p = get_register(program, process->position + 6);
		p = process->position - 2 + (p % IDX_MOD);
		save_st_copy(program, process, p);		
		process->position += 8;
	}
}

void 	operation_st(t_program *program, t_process *process)
{
	int 	k;

	k = process->position;
	if (program->map[k] == 48)
	{
		if (program->map[k + 1] == 53)
		{
			if (is_register(program, get_position(k + 2)) == 1 &&
				is_register(program, get_position(k + 6)) == 1)
				make_st(program, process);
		}
		else if (program->map[k + 1] == 68 || program->map[k + 1] == 100)
		{
			if (is_register(program, k + 2) == 1)
				make_st(program, process);
		}
	}
}

void    st(t_program *program, t_process *process)
{
	if (process->flag == 1)
	{
		process->position += 2;
		operation_st(program, process);
		process->flag = 0;
	}
	else
		process->delay = 5;
}