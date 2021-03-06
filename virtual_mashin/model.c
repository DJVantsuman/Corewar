/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 21:07:12 by itsuman           #+#    #+#             */
/*   Updated: 2017/06/02 21:07:19 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function "create_process" create one process and add it to the end of
** list 'process'.
*/
void    create_process(t_data **data, int index, int p_num, unsigned char p_id)
{
	int			i;
	t_process	*var;
	t_process	*last;

	i = 1;
	var = (t_process *)malloc(sizeof(t_process));
	last = (*data)->process;
	var->numb = (*data)->procnumb++;
	var->p_num = p_num;
	var->p_id = p_id;
	var->position = index;
	var->live = 0;
	var->carry = 0;
	var->delay = 0;
	var->registers[0] = p_num;
	while (i < REG_NUMBER)
		var->registers[i++] = 0;
	var->next = (*data)->process;
	(*data)->process = var;
	// while(last && last->next)
	// 	last = last->next;
	// if (last == NULL)
	// {
	// 	var->next = (*data)->process;
	// 	(*data)->process = var;
	// }
	// else
	// {
	// 	var->next = NULL;
	// 	last->next = var;
	// }
}

/*
** Function "create_map" writes players cod into map(virtual memory) and create
** process for each player.
*/
void    create_map(t_data **data)
{
	int				i;
	int				n;
	unsigned int	j;
	t_player		*var;

	var = (*data)->player;
	i = 0;
	while (i < (*data)->amount_players)
	{
		if (i == 0)
			n = 0;
		else
			n = (MEM_SIZE / (*data)->amount_players) * i;
		j = 0;
		create_process(&(*data), n, var->number, var->id);
		while (j < var->header->prog_size)
		{
			(*data)->map[n] = var->prog_cod[j];
			(*data)->map_v[n] = var->id;
			n++;
			j++;
		}
		var = var->next;
		i++;
	}
}

/*
** Function "model" create map and give it to the function "start_process".
*/
void    model(t_data **data)
{
	(*data)->process = (t_process *)malloc(sizeof(t_process));
	(*data)->process = NULL;
	(*data)->speed = 20000;
	(*data)->procnumb = 1;
	create_map(&(*data));
	start_process(&(*data));
	free_player(&(*data)->player);
	free_process(&(*data)->process);
}
