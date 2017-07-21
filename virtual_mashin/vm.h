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
	char 			id;
    unsigned int	number;
    char            *file;
    header_t        *header;
    char            *prog_cod;
    int             live;
    int             last_live;
    struct s_player *next;
}                   t_player;

typedef struct       s_process
{
	char 			 p_id;
	unsigned int 	 p_num;
    unsigned int     position;
    int              live;
	int              carry;
	int              delay;
	unsigned int     registers[REG_NUMBER];
	struct s_process *next;
}                    t_process;

typedef struct 			s_data
{
	struct s_player		*player;
	struct s_process	*process;
	unsigned char       map[MEM_SIZE];
	char             	map_v[MEM_SIZE];
	int             	dump;
	int             	nbr;
	int             	v;
	unsigned int             	amount_players;
	unsigned int		speed;
}						t_data;

void    error_manager(char *file, int  index);
void    controller(t_player **player);
void    model(t_data **data);
void    start_process(t_data **data);
void    run_process(t_data **data, int cycle);
void    reset_live(t_data **data);
void    free_player(t_player **player);
//void    free_program(t_program **program);
void    free_process(t_process **process);

void    live(t_data **data, t_process **process, int cycle);
void    ld(t_data **data, t_process **process);
void    st(t_data **data, t_process **process);
void    add(t_data **data, t_process **process);
void    sub(t_data **data, t_process **process);
void    and(t_data **data, t_process **process);
void    or(t_data **data, t_process **process);
void    xor(t_data **data, t_process **process);
void    zjmp(t_data **data, t_process **process);
void    ldi(t_data **data, t_process **process);
void    sti(t_data **data, t_process **process);
void    ft_fork(t_data **data, t_process **process);
void    lld(t_data **data, t_process **process);
void    lldi(t_data **data, t_process **process);
void    lfork(t_data **data, t_process **process);
void    aff(t_data **data, t_process **process);

unsigned int   bit_rev(unsigned int octet);

int     is_nbr(char *s);
int     check_arg(char **av, int i, int dump, int players);
int     check_live(t_data **data, int index);

void    add_process(t_data **data, t_process **process, unsigned int index);
unsigned int    get_dir_value(t_data **data, t_process *process, int *shift, int dsize);
unsigned int    get_ind_value(t_data **data, t_process *process, int *shift);
unsigned int    get_reg_value(t_data **data, t_process *process, int *shift);
unsigned int    get_reg_numb(t_data **data, t_process *process, int *shift);
unsigned int    get_direct(t_data **data, unsigned int position);
void 	load_value(t_data **data, t_process **process, int pos,
				   unsigned int val);
void	visualise(t_data **data, int cycles);
//void    wprint_map(t_program **program, t_process **process, WINDOW **map);
//void	wprint_status(t_player **player, t_program **program, WINDOW
//**status, int cycles);
//unsigned int    get_dir_value2(t_program *program, t_process *process, int
//*shift);



#endif
