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

void    add_process(t_data **data, t_process **process, unsigned int index)
{
	t_process *var;
	t_process *last;
	int i;

	i = 0;
	var = (t_process *)malloc(sizeof(t_process));
	last = (*data)->process;
	var->position = index;
	var->live = 0;
	var->delay = -1;
	var->carry = (*process)->carry;
	var->p_id = (*process)->p_id;
	var->p_num = (*process)->p_num;
	while (i < REG_NUMBER)
	{
		var->registers[i] = (*process)->registers[i];
		i++;
	}
	while(last && last->next)
		last = last->next;
	if (last == NULL)
	{
		var->next = (*data)->process;
		(*data)->process = var;
	}
	else
	{
		var->next = NULL;
		last->next = var;
	}
}
void    ft_fork(t_data **data, t_process **process)
{
	unsigned char    byte[2];
	unsigned int     res;

	byte[0] = (unsigned char)(*data)->map[((*process)->position + 1) %
										  MEM_SIZE];
	byte[1] = (unsigned char)(*data)->map[((*process)->position + 2) % MEM_SIZE];
	res = (unsigned int)((byte[0] << 8) + byte[1]);
	add_process(&(*data), &(*process), (unsigned int)(((*process)->position +
	(res % IDX_MOD)) % MEM_SIZE));
	(*process)->position = ((*process)->position + 3) % MEM_SIZE;
}