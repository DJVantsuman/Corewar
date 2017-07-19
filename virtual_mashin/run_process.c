/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 19:10:55 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 19:10:58 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function "perform_function_continue" is only continue of function
** "perform_function".
*/
void    perform_function_continue(t_program **program,
                                 t_process **process, int byte)
{
    if ((unsigned char)byte == 0x09)
        zjmp(&(*program), &(*process));
    else if ((unsigned char)byte == 0x0a)
	{}
//        ldi(player, program, process);
    else if ((unsigned char)byte == 0x0b)
	{}
//        sti(player, program, process);
    else if ((unsigned char)byte == 0x0c)
        ft_fork(&(*program), &(*process));
    else if ((unsigned char)byte == 0x0d)
        lld(&(*program), &(*process));
    else if ((unsigned char)byte == 0x0e)
	{}
//        lldi(player, program, process);
    else if ((unsigned char)byte == 0x0f)
        lfork(&(*program), &(*process));
    else if ((unsigned char)byte == 0x10)
		aff(&(*program), &(*process));
    else
        (*process)->position++;
}

/*
** Function "perform_function" read byte
** and choose assembler function for execution.
*/
void    perform_function(t_player **player, t_program **program,
                         t_process **process, int byte)
{
    if ((unsigned char)byte == 0x01)
        live(&(*player), &(*program), &(*process));
    else if ((unsigned char)byte == 0x02)
        ld(&(*program), &(*process));
    else if ((unsigned char)byte == 0x03)
	{}
//        st(&(*program), &(*process));
    else if ((unsigned char)byte == 0x04)
	{}
//        add(&(*program), &(*process));
    else if ((unsigned char)byte == 0x05)
	{}
//        sub(player, program, process);
    else if ((unsigned char)byte == 0x06)
        and(&(*program), &(*process));
    else if ((unsigned char)byte == 0x07)
        or(&(*program), &(*process));
    else if ((unsigned char)byte == 0x08)
        xor(&(*program), &(*process));
    else
        perform_function_continue(program, process, byte);
}




/*
** Function "run_process" take each process, read byte from 'map' with an
** index that is equal to the position of the process and pass this byte
** to the function "perform_function".
*/
void    run_process(t_player **player, t_program **program, t_process **process)
{
    t_process   *proc;
    int        byte;

    proc = (*process);
    while (proc)
    {
        if (proc->live >= 0 && proc->delay == 0)
        {
            byte = (int)(*program)->map[proc->position];
	        perform_function(&(*player), &(*program), &proc, byte);
        }
        else if (proc->delay > 0)
        {
            proc->delay--;
            if (proc->delay == 0)
                proc->flag = 1;
        }
        proc = proc->next;
    }
}
