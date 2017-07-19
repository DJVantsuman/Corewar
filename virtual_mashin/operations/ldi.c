/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:50:20 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:50:22 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

unsigned int    get_dir_value2(t_program *program, t_process *process, int *shift)
{
    int             i;
    unsigned int    val[2];

    i = 0;
    while (i < 2)
    {
        val[i] = (unsigned int)program->map[process->position + (*shift)];
        (*shift)++;
        i++;
    }
    return (val[0] << 8) + val[1];
}

unsigned int    get_direct(t_program *program, unsigned int position)
{
    int             i;
    unsigned int    val[4];
    unsigned int    pos;

    i = 0;
    pos = position;
    while (i < DIR_SIZE)
    {
        val[i] = (unsigned int)program->map[pos];
        pos++;
        i++;
    }
    return (val[0] << 24) + (val[1] << 16) + (val[2] << 8) + val[3];
}

void    ldi(t_program **program, t_process **process)
{
    char            param[3];
    unsigned int    val[3];
    int             shift;

    shift = 2;
    param[0] = (char)((*program)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
    param[1] = (char)((*program)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
    param[2] = (char)((*program)->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
    if ((*process)->flag == 1)
    {
        if (param[0] == REG_CODE)
        {
            val[0] = get_reg_value((*program), (*process), &shift);
            shift += 1;
        }
        else if (param[0] == DIR_CODE)
        {
            val[0] = get_dir_value2((*program), (*process), &shift);
            shift += 2;
        }
        else if (param[0] == IND_CODE)
        {
            val[0] = get_ind_value((*program), (*process), &shift);
            shift += 2;
        }
        else
            return ;
        if (param[1] == REG_CODE)
        {
            val[1] = get_reg_value((*program), (*process), &shift);
            shift += 1;
        }
        else if (param[1] == DIR_CODE)
        {
            val[1] = get_dir_value2((*program), (*process), &shift);
            shift += 2;
        }
        else
            return ;
        val[2] = get_reg_numb((*program), (*process), &shift);
        if (val[2] <= REG_NUMBER && val[2] > 0)
            (*program)->registers[val[2] - 1] = get_direct(*program, (val[0] + val[1]) % MEM_SIZE);
        (*program)->carry = (*program)->carry == 0 ? 1 : 0;
        (*process)->flag = 0;
    }
    else
        (*process)->delay = 25;
}