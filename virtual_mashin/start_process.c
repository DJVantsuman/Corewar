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
void    print_map(char *map)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        printf("%.2x", (unsigned char)map[i]);/////////////////////////////////////
        i++;
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
    index[3] = 0;

    while (1)
    {
        index[0] = 0;
        while (index[0] < index[2])
        {
            run_process(&(*data));
			if((*data)->v == 1)
				visualise (&(*data), (int *)index);
			if ((*data)->dump > 0 && (*data)->dump == index[0])
                print_map((*data)->program->map);
            index[0]++;
        }
        check_live(&(*data), index[2]) ? index[2] -= CYCLE_DELTA : index[1]++;
        if (index[1] == MAX_CHECKS)
        {
            reset_live(&(*data));
            index[2] -= CYCLE_DELTA;
        }
        index[3]++;
    }
}