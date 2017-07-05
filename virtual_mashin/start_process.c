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

void    decrease_delay(t_process **process)
{
    t_process *var;

    var = *process;
    while (var)
    {
        if (var->delay > 0)
            var->delay--;
        printf("\nposition = %d", var->position);///////////////////////////////////////////
        var = var->next;
    }
}

void    run_process(t_player **player, t_program *program, t_process **process)
{

}

void    reset_live(t_player **player, t_process **process)
{
    t_player *play;
    t_process *proc;

    play = *player;
    proc = *process;
    while (play)
    {
        play->live = 0;
        play = play->next;
    }
    while (proc)
    {
        proc->live = 0;
        proc = proc->next;
    }
}

int    check_live(t_process **process, t_player **player)
{
    t_process *proc;
    t_player *play;

    proc = *process;
    play = *player;
    while (proc)
    {
        if (proc->live == 0)
            proc->position = -1;
        proc = proc->next;
    }
    while (play)
    {
        if (play->live > 20)
        {
            reset_live(player, process);
            return (1);
        }
        play = play->next;
    }
    return (0);
}

void    start_process(t_player **player, t_program *program, t_process **process, t_arg *arg)
{
    int i;
    int max_check;
    int cycle_to_die;

    max_check = 0;
    cycle_to_die = CYCLE_TO_DIE;
    while (1)
    {
        i = 0;
        while (i < cycle_to_die)
        {
            decrease_delay(process);
            run_process(player, program, process);
            i++;
        }
        if (check_live(process, player))
            cycle_to_die -= CYCLE_DELTA;
        else
            max_check++;
        if (max_check == MAX_CHECKS)
        {
            reset_live(player, process);
            cycle_to_die -= CYCLE_DELTA;
        }
        break;
    }
    //--->>> The next cod only for testing and mast be deleted.
//    int i = 0;
//    while (i <= MEM_SIZE)
//    {
//        printf("%.2x", (unsigned char)program->map[i]);
//        i++;
//    }
//    write(1, "\n", 1);
//
//    t_process   *var;
//    var = *process;
//    while (var)
//    {
//        printf("position = %d\n", var->position);
//        var = var->next;
//    }
//
//    write(1, "\n", 1);
//    printf("dump = %d\n", arg->dump);
//    printf("v = %d\n", arg->v);
//    printf("amount players = %d\n", arg->amount_players);
//    player = NULL;

//<<<---
}