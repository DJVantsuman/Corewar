/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 22:04:07 by itsuman           #+#    #+#             */
/*   Updated: 2017/06/08 22:04:09 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

long int 	get_numb(t_program program, t_process process)
{
	int 		k;
	long int 	p;
	long int 	num;

	num = 0;
	p = 1;
	k = 7;
	while (k >= 0)
	{
		if (program->map[process->position + k] > 47 &&
			program->map[process->position + k] < 58)
			num = num * p + program->map[process->position + k] - 48;
		else if (program->map[process->position + k] > 64 &&
			program->map[process->position + k] < 71)
			num = num * p + program->map[process->position + k] - 55;
		else
			return (0);
		p *= 16;
		k--;
	}
	while (num > 2147483647)
		num -= 2147483647;
	return (2147483647 - num - 1);
}

int 		check_player(t_player pl, long int num)
{
	t_player 	player;

	player = pl;
	while (player)
	{
		if (player->number == (int)num)
			return (1);
	}
	return (0);
}

void		live(t_player **player, t_program *program, t_process *process)
{
	t_player	**pl;
	long int	numb;

	numb = 0;
	if (proc->flag == 1)
	{
		process->live++;
		process->position += 2;
		numb = get_numb(program, process);
		pl = player;
		if (check_player(pl, numb) = 1)
		{
			if (pl->number == numb)
			{
				pl->live++;
				pl->last_live = 1;
				process->position += 8;
			}
			else
				pl->last_live = 0;
		}
	proc->flag = 0;
	}
	else
		proc->delay = 10;
}
