/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 20:23:30 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/04 20:23:34 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function 'print_map' print map to the standart output wen user established
** flag -dump.
*/
void    print_map(unsigned char *map)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if ((i % 64) == 0)
			printf("0x%.4x : ", i);
		printf("%.2x ", map[i]);/////////////////////////////////////
		i++;
		if ((i % 64) == 0)
			printf("\n");
	}
	exit(1);
}

/*
** Function 'start_process' start CYCLE_TO_DIE and after each CYCLE_TO_DIE
** check how many times each process and players said 'live'.
** index[0] - it is simple iterrator for cycle CYCLE_TO_DIE.
** index[1] - it is a variable for check MAX_CHECKS.
** index[2] - it is a variable which is equal to variable CYCLE_TO_DIE.
*/
void    start_process(t_data **data)
{
	int index[4];

	index[1] = 0;
	index[2] = CYCLE_TO_DIE;
	index[3] = 1;

	while (1)
	{
		index[0] = 0;
		while (index[0] < index[2])
		{
//			printf ("It is now cycle %d\n", index[3]);
			run_process(&(*data), index[3]);
			if((*data)->v == 1)
				visualise (&(*data), index);
			if ((*data)->dump > 0 && (*data)->dump == index[3])
				print_map((*data)->map);
			index[0]++;
			index[3]++;
		}
		if (check_live(&(*data), &index[1], index[2]))
		{
			index[2] -= CYCLE_DELTA;
			index[1] = 0;
//			printf ("Cycle to die is now %d\n", index[2]);
		}
		else
			index[1]++;
		if (index[1] == MAX_CHECKS)
		{
			reset_live(&(*data));
			index[2] -= CYCLE_DELTA;
//			printf ("Cycle to die is now %d\n", index[2]);
			index[1] = 0;
		}
	}
}
