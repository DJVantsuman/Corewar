/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:53:40 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:53:42 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    add_process(t_process **process, int index)
{
	t_process *var;
	t_process *last;

	var = (t_process *)malloc(sizeof(t_process));
	last = *process;
	var->position = index;
	var->live = 0;
	var->delay = 0;
	var->flag = 0;

	while(last && last->next)
		last = last->next;
	if (last == NULL)
	{
		var->next = *process;
		*process = var;
	}
	else
	{
		var->next = NULL;
		last->next = var;
	}
}
void    ft_fork(t_program *program, t_process *process)
{
	char    byte[2];
	int     res;

	byte[0] = program->map[process->position + 1];
	byte[1] = program->map[process->position + 2];
	res = (byte[0] << 8) + byte[1];
	if (process->flag == 1)
	{
		add_process(&process, process->position + (res % IDX_MOD));
		process->flag = 0;
	}
	else
		process->delay = 5;
}