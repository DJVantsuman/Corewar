/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cycle_to_die.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 17:52:28 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/06 17:52:31 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
 ** Function "reset_live" sets the value for the variable live for all processes
 ** and players to 0.
 */
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

/*
 ** Function "check_live" check how many times each process said "live" and
 ** if live=0 delete this process (sets the value of 'position' = -1).
 ** Also this function check how many times each player said 'live' and
 ** if any player said 'live' => then NBR_LIVE times function return 1,
 ** otherwise return 0;
 */
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
        if (play->live > NBR_LIVE)
        {
            reset_live(player, process);
            return (1);
        }
        play = play->next;
    }
    return (0);
}

/*
 ** Function 'check_cycle_to_die' check how many times each process
 ** and players said 'live'. Return index[2].
 ** index[0] - it is simple iterrator for cycle CYCLE_TO_DIE.
 ** index[1] - it is a variable for check MAX_CHECKS.
 ** index[2] - it is a variable which is equal to variable CYCLE_TO_DIE.
 */
int    check_cycle_to_die(t_player **player, t_process **process, int index[3])
{
    if (check_live(process, player))
        index[2] -= CYCLE_DELTA;
    else
        index[1]++;
    if (index[1] == MAX_CHECKS)
    {
        reset_live(player, process);
        index[2] -= CYCLE_DELTA;
    }
    return (index[2]);
}