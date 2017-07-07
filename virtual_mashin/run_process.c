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
void    perform_function_continue(t_player **player, t_program *program,
                                 t_process *process, char byte)
{
    if ((unsigned char)byte == 0x09)
        zjmp(player, program, process);
    else if ((unsigned char)byte == 0x0a)
        ldi(player, program, process);
    else if ((unsigned char)byte == 0x0b)
        sti(player, program, process);
    else if ((unsigned char)byte == 0x0c)
        ft_fork(player, program, process);
    else if ((unsigned char)byte == 0x0d)
        lld(player, program, process);
    else if ((unsigned char)byte == 0x0e)
        lldi(player, program, process);
    else if ((unsigned char)byte == 0x0f)
        lfork(player, program, process);
    else if ((unsigned char)byte == 0x10)
        aff(player, program, process);
    else
        process->position++;
}

/*
** Function "perform_function" read byte and choose assembler function for execution.
*/
void    perform_function(t_player **player, t_program *program,
                         t_process *process, char byte)
{
    if ((unsigned char)byte == 0x01)
        live(player, program, process);
    else if ((unsigned char)byte == 0x02)
        ld(player, program, process);
    else if ((unsigned char)byte == 0x03)
        st(player, program, process);
    else if ((unsigned char)byte == 0x04)
        add(player, program, process);
    else if ((unsigned char)byte == 0x05)
        sub(player, program, process);
    else if ((unsigned char)byte == 0x06)
        and(player, program, process);
    else if ((unsigned char)byte == 0x07)
        or(player, program, process);
    else if ((unsigned char)byte == 0x08)
        xor(player, program, process);
    else
        perform_function_continue(player, program, process, byte);
}

/*
** Function "run_process" take each process, read byte from 'map' with an
** index that is equal to the position of the process and pass this byte
** to the function "perform_function".
*/
void    run_process(t_player **player, t_program *program, t_process **process,
                    t_arg *arg)
{
    t_process   *proc;
    char        byte;

    proc = *process;
    while (proc)
    {
        if (proc->live >= 0)
        {
            byte = program->map[proc->position];
            perform_function(player, program, proc, byte);
        }
        proc = proc->next;
    }
}