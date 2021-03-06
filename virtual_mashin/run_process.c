/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 19:10:55 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 19:10:58 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function "perform_function_continue" is only continue of function
** "perform_function".
*/
void    perform_function_continue(t_data **data, t_process **process, int byte)
{
	if ((unsigned char)byte == 0x09)
		zjmp(&(*data), &(*process));
	else if ((unsigned char)byte == 0x0a)
		ldi(&(*data), &(*process));
	else if ((unsigned char)byte == 0x0b)
		sti(&(*data), &(*process));
	else if ((unsigned char)byte == 0x0c)
		ft_fork(&(*data), &(*process));
	else if ((unsigned char)byte == 0x0d)
		lld(&(*data), &(*process));
	else if ((unsigned char)byte == 0x0e)
		lldi(&(*data), &(*process));
	else if ((unsigned char)byte == 0x0f)
		lfork(&(*data), &(*process));
	else if ((unsigned char)byte == 0x10)
		aff(&(*data), &(*process));
	else
		(*process)->position = ((*process)->position + 1) % MEM_SIZE;
}

/*
** Function "perform_function" read byte
** and choose assembler function for execution.
*/
void    perform_function(t_data **data, t_process **process, int byte, int cycle)
{
	if ((*process)->delay > 0)
		return;
//	if (byte > 0 && byte < 17)
//		printf ("P%5d | ", (*process)->numb);
	if ((unsigned char)byte == 0x01)
		live(&(*data), &(*process), cycle);
	else if ((unsigned char)byte == 0x02)
		ld(&(*data), &(*process));
	else if ((unsigned char)byte == 0x03)
		st(&(*data), &(*process));
	else if ((unsigned char)byte == 0x04)
		add(&(*data), &(*process));
	else if ((unsigned char)byte == 0x05)
		sub(&(*data), &(*process));
	else if ((unsigned char)byte == 0x06)
		and(&(*data), &(*process));
	else if ((unsigned char)byte == 0x07)
		or(&(*data), &(*process));
	else if ((unsigned char)byte == 0x08)
		xor(&(*data), &(*process));
	else
		perform_function_continue(&(*data), &(*process), byte);
}


void	set_delay(t_process **process, int byte)
{
	if ((*process)->delay != 0)
		return;
	if (byte == 0x04 || byte == 0x05 || byte == 0x0d)
		(*process)->delay = 10;
	else if (byte == 0x01)
	{
		(*process)->live++;
		(*process)->delay = 10;
		(*process)->f = 1;
	}
	else if (byte == 0x02 || byte == 0x03)
		(*process)->delay = 5;
	else if (byte == 0x06 || byte == 0x07 || byte == 0x08)
		(*process)->delay = 6;
	else if (byte == 0x0a || byte == 0x0b)
		(*process)->delay = 25;
	else if (byte == 0x09)
		(*process)->delay = 20;
	else if (byte == 0x0c)
		(*process)->delay = 800;
	else if (byte == 0x0e)
		(*process)->delay = 50;
	else if (byte == 0x0f)
		(*process)->delay = 1000;
	else if (byte == 0x10)
		(*process)->delay = 2;
//	else
//	{
//		if ((*process)->delay < 0)
//			(*process)->position = ((*process)->position + 1) % MEM_SIZE;
//	}
}

/*
** Function "run_process" take each process, read byte from 'map' with an
** index that is equal to the position of the process and pass this byte
** to the function "perform_function".
*/
void    run_process(t_data **data, int cycle)
{
	t_process	*proc;
	int			byte;

	proc = (*data)->process;
	while (proc)
	{
		byte = (int)(*data)->map[proc->position];
//		if (proc->live >= 0 && proc->delay < 0)
		set_delay(&proc, byte);
		if (proc->delay > 0)
			proc->delay--;
		if (proc->delay == 0 && byte > 0 && byte < 17) {
			perform_function (&(*data), &proc, byte, cycle);
//			if (byte != 0)
//				printf ("\n");
		}
		else if (proc->delay == 0 && proc->f == 1) {
//			proc->position = (proc->position + 5) % MEM_SIZE;
//			proc->f = 0;
//			printf ("P%5d | ", proc->numb);
			live(&(*data), &proc, cycle);
//			printf ("\n");
		}
		else if (proc->delay == 0)
			proc->position += 1;

		proc = proc->next;
	}
}
