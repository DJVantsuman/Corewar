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

void	add_process(t_data **data, t_process **process, int index)
{
	t_process	*var;
	int			i;

	i = 0;
	var = (t_process *)malloc(sizeof(t_process));
	var->numb = (*data)->procnumb++;
	var->position = index;
	var->live = 0;
	var->delay = 0;
	var->carry = (*process)->carry;
	var->p_id = (*process)->p_id;
	var->p_num = (*process)->p_num;
	while (i < REG_NUMBER)
	{
		var->registers[i] = (*process)->registers[i];
		i++;
	}
	var->next = (*data)->process;
	(*data)->process = var;
}

void	ft_fork(t_data **data, t_process **process)
{
	unsigned char	byte[2];
	int				res;

	byte[0] = (*data)->map[((*process)->position + 1) % MEM_SIZE];
	byte[1] = (*data)->map[((*process)->position + 2) % MEM_SIZE];
	res = (short)((byte[0] << 8) + byte[1]);
	add_process(&(*data), &(*process), (((*process)->position
		+ (res % IDX_MOD)) % MEM_SIZE));
	(*process)->position = ((*process)->position + 3) % MEM_SIZE;
}
