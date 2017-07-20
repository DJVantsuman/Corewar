/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 21:05:50 by itsuman           #+#    #+#             */
/*   Updated: 2017/06/06 21:05:56 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    free_player(t_player **player)
{
    t_player *tmp;

    tmp = (*player);
    while (tmp->next)
    {
        tmp = (*player);
        if ((*player)->prog_cod)
            free((*player)->prog_cod);
        free((*player)->header);
        (*player) = (*player)->next;
        free(tmp);
    }
}

//void    free_program(t_program **program)
//{
//    if (*program)
//        free(*program);
//}

void    free_process(t_process **process)
{
    t_process  *var;

        if (process)
        {
            while (*process)
            {
                var = *process;
                *process = (*process)->next;
                free(var);
            }
            free(process);
        }
}

