/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 17:02:57 by itsuman           #+#    #+#             */
/*   Updated: 2017/06/02 17:03:03 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VM_H_
# define _VM_H_

#include "libft/libft.h"
#include "../op.h"
#include <stdio.h>
#include <fcntl.h>

typedef struct      s_player
{
    int             number;
    char            *file;
    header_t        *header;
    char            *prog_cod;
    int             live;
    int             last_live;
    struct s_player *next;
}                   t_player;

typedef struct       s_process
{
    int              nbr;
    int              position;
    int              live;
    int              delay;
    char             *comand;
    struct s_process *next;
}                    t_process;

typedef struct      s_program
{
    char             map[MEM_SIZE];
    int              registers[REG_NUMBER];
    int              carry;
}                   t_program;

typedef struct      s_arg
{
    int             dump;
    int             v;
    int             nbr;
    int             amount_players;
}                   t_arg;

void    error_manager(char *file, int  index);
void    controller(t_player **player);
void    model(t_player **player, int amount_player, t_arg *arg);
void    start_process(t_player **player, t_program *program, t_process **process, t_arg *arg);
void    free_player(t_player **player);
void    free_program(t_program *program);
void    free_process(t_process **process);

void    live(t_player *player, t_program *program, t_process *process);

unsigned int   bit_rev(unsigned int octet);

int     is_nbr(char *s);
int     check_arg(char **av, int i, int dump, int players);

#endif
