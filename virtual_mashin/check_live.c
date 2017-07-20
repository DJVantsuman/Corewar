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
** Function "print_champ" print which player is won
*/
void    print_champ(t_player **player)
{
    t_player    *play;

    play = *player;
    while (play)
    {
        if (play->last_live == 1)
        {
            printf("\nPlayer %d (%s) won.\n", play->number, play->header->prog_name);
            exit(1);
        }
        play = play->next;
    }
    printf("\nPlayer %d (%s) won.\n", (*player)->number, (*player)->header->prog_name);
    exit(1);
}

/*
** Function "check_process_live" checks for the existence of live processes
** and if they do not return 1 otherwise 0.
*/
int     check_process_live(t_process **process)
{
    t_process *proc;
    int       f;

    proc = *process;
    f = 0;
    while (proc)
    {
        if (proc->live > 0)
            f++;
        proc = proc->next;
    }
    if (f == 0)
        return (1);
    else
        return (0);
}

/*
** Function "reset_live" sets the value for the variable live for all processes
** and players to 0.
*/
void    reset_live(t_data **data)
{
    t_player *play;
    t_process *proc;

    proc = (*data)->process;
    play = (*data)->player;
    while (play)
    {
        play->live = 0;
        play = play->next;
    }
    while (proc)
    {
        if (proc->live > 0)
            proc->live = 0;
        proc = proc->next;
    }
}

/*
** Function "check_live" check how many times each process said "live" and
** if live=0 delete this process (sets the value of 'position' = -1).
** If all processes is died or variable index <= CYCLE_DELTA this function
** print champion and stop program.
** Also this function check how many times each player said 'live' and
** if any player said 'live' => then NBR_LIVE times function return 1,
** otherwise return 0;
*/
int    check_live(t_data **data, int index)
{
    t_process *proc;
    t_player *play;

    proc = (*data)->process;
    play = (*data)->player;
    while (proc)
    {
        if (proc->live == 0)
            proc->live = -1;
        proc = proc->next;
    }
    if (check_process_live(&(*data)->process) || index <= CYCLE_DELTA)
        print_champ(&(*data)->player);
    while (play)
    {
        if (play->live >= NBR_LIVE)
        {
            reset_live(&(*data));
            return (1);
        }
        play = play->next;
    }
    return (0);
}