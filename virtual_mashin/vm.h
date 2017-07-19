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
#include <ncurses.h>

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
	int              flag;
    char             *comand;
    struct s_process *next;
}                    t_process;

typedef struct      s_program
{
    char             map[MEM_SIZE];
    unsigned int     registers[REG_NUMBER];
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
void    start_process(t_player **player, t_program **program, t_process **process, t_arg *arg);
void    run_process(t_player **player, t_program **program, t_process **process);
void    reset_live(t_player **player, t_process **process);
void    free_player(t_player **player);
void    free_program(t_program **program);
void    free_process(t_process **process);

void    live(t_player **player, t_program **program, t_process **process);
void    ld(t_program **program, t_process **process);
void    st(t_program **program, t_process **process);
void    add(t_program **program, t_process **process);
void    sub(t_player **player, t_program *program, t_process *process);
void    and(t_program **program, t_process **process);
void    or(t_program **program, t_process **process);
void    xor(t_program **program, t_process **process);
void    zjmp(t_program **program, t_process **process);
void    ldi(t_player **player, t_program *program, t_process *process);
void    sti(t_player **player, t_program *program, t_process *process);
void    ft_fork(t_program **program, t_process **process);
void    lld(t_program **program, t_process **process);
void    lldi(t_player **player, t_program *program, t_process *process);
void    lfork(t_program **program, t_process **process);
void    aff(t_program **program, t_process **process);

unsigned int   bit_rev(unsigned int octet);

int     is_nbr(char *s);
int     check_arg(char **av, int i, int dump, int players);
int     check_live(t_process **process, t_player **player, int index);

void    add_process(t_process **process, int index);
unsigned int    get_dir_value(t_program *program, t_process *process, int *shift);
unsigned int    get_ind_value(t_program *program, t_process *process, int *shift);
unsigned int    get_reg_value(t_program *program, t_process *process, int *shift);
unsigned int    get_reg_numb(t_program *program, t_process *process, int *shift);

void	visualise(t_player **player, t_program **program, t_process **process,
				  int cycles);
void    wprint_map(t_program **program, t_process **process, WINDOW **map);
void	wprint_status(t_player **player, t_program **program, WINDOW
**status, int cycles);


#endif
