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
void    create_process(t_process **process, int index, int nbr)
{
    t_process *var;
    t_process *last;

    var = (t_process *)malloc(sizeof(t_process));
    last = (*process);
    var->position = index;
    var->live = 0;
    var->delay = -1;
//    var->flag = 0;
    var->nbr = nbr;

    while(last && last->next)
        last = last->next;
    if (last == NULL)
    {
        var->next = (*process);
	    (*process) = var;
    }
    else
    {
        var->next = NULL;
        last->next = var;
    }
}

/*
** Function "create_map" writes players cod into map(virtual memory) and create
** process for each player.
*/
void    create_map(t_player **player, t_program **program, int amount_player, t_process **process)
{
    int i;
    int n;
    unsigned int j;
    t_player *var;

    var = (*player);
    i = -1;
    while (++i < amount_player)
    {
        if (i == 0)
            n = 0;
        else
            n = (MEM_SIZE / amount_player) * i;
        j = 0;
        create_process(&(*process), n, i);
        while (j < var->header->prog_size)
        {
	        (*program)->map[n] = var->prog_cod[j];
            n++;
            j++;
        }
        var = var->next;
    }
}

/*
** Function "model" create map and give it to the function "start_process".
*/
void    model(t_player **player, int amount_player, t_arg *arg)
{
    t_program   *program;
    t_process   *process;

    program = (t_program *)malloc(sizeof(t_program));
    process = (t_process *)malloc(sizeof(t_process));
    process = NULL;
    create_map(&(*player), &program, amount_player, &process);
    start_process(&(*player), &program, &process, &(*arg));
    free_player(&(*player));
    free_program(&program);
    free_process(&process);
}