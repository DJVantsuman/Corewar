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

void		live(t_player **player, t_program **program, t_process **process)
{
	t_player		*pl;
	unsigned int    val;
	int 			shift;

	shift = 1;
	val = 0;
	(*process)->live++;
	pl = (*player);
	val = get_dir_value((*program), (*process), &shift, 4);
	while (pl)
	{
		if (pl->number == val)
		{
			pl->live++;
			pl->last_live = 1;
			pl = (*player);
			while (pl)
			{
				if (pl->number != val)
					pl->last_live = 0;
				pl = pl->next;
			}
		}
		if (pl != NULL)
			pl = pl->next;
	}
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}