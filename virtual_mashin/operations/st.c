/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:37:29 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:37:33 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    st(t_program *program, t_process *process)
{
    char            param[2];
    unsigned int    val[2];
    int             shift;

    shift = 2;
    param[0] = (char)((*program)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
    param[1] = (char)((*program)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
 	if (param[0] == REG_CODE)
		val[0] = get_reg_value((*program), (*process), &shift);
	else
		return ;
	if (param[1] == REG_CODE)
		val[1] = get_reg_value((*program), (*process), &shift);
	else if (param[1] == IND_CODE)
		val[1] = get_ind_value((*program), (*process), &shift);
	else
		return ;
	if (param[1] == REG_CODE)
	load_value(&(*program), ((*process)->position + (val[1]) % IDX_MOD) %
							MEM_SIZE, val[0]);
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}