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
void    print_map(t_program *program)
{
    int i;

    i = 0;
    printf("PRINT MAP\n");
    while (i <= MEM_SIZE)
    {
        printf("%.2x", (unsigned char)program->map[i]);/////////////////////////////////////
        i++;
    }
    exit(1);
}

/*
** Function "decrease_delay" decrease process delay by one.
*/
/*void    decrease_delay(t_process **process)
{
    t_process *var;

    var = *process;
    while (var)
    {
        if (var->delay > 0)
            var->delay--;
        else 
            var->flag = 1;
        var = var->next;
    }
}*/

/*
** Function 'start_process' start CYCLE_TO_DIE and after each CYCLE_TO_DIE
** check how many times each process and players said 'live'.
** index[0] - it is simple iterrator for cycle CYCLE_TO_DIE.
** index[1] - it is a variable for check MAX_CHECKS.
** index[2] - it is a variable which is equal to variable CYCLE_TO_DIE.
*/
void    start_process(t_player **player, t_program *program, t_process **process, t_arg *arg)
{
    int index[3];

    index[1] = 0;
    index[2] = CYCLE_TO_DIE;
    while (1)
    {
        index[0] = 1;
        while (index[0] <= index[2])
        {
      //      decrease_delay(process);
            run_process(player, program, process);
            if (arg->dump > 0 && arg->dump == index[0])
                print_map(program);
            index[0]++;
        }
        check_live(process, player, index[2]) ? index[2] -= CYCLE_DELTA : index[1]++;
        if (index[1] == MAX_CHECKS)
        {
            reset_live(player, process);
            index[2] -= CYCLE_DELTA;
        }
    }
}