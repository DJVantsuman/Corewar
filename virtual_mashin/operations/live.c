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

void		live(t_data **data, t_process **process, int cycle)
{
	t_player		*pl;
	int    val;
	int 			shift;

	shift = 1;
	val = 0;
	(*process)->live++;
	pl = (*data)->player;
	val = get_dir_value(&(*data), (*process), &shift, 4);
	while (pl)
	{
		if (pl->number == val)
		{
			pl->live++;
			pl->last_live = cycle;

		}
		pl = pl->next;
	}
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}