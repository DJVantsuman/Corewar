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

unsigned int	get_ind_address(t_data **data, t_process *process, int *shift)
{
	unsigned int val[2];
	val[0] = (unsigned char)((*data)->map[(process->position + *shift) %
										  MEM_SIZE]);
	val[1] = (unsigned char)((*data)->map[(process->position + *shift + 1) %
										  MEM_SIZE]);
	*shift += 2;
	return ((val[0] << 8) + val[1]);
}

void    st(t_data **data, t_process **process)
{
    char            param[2];
    unsigned int    val[2];
    int             shift;

    shift = 2;
    param[0] = (char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
    param[1] = (char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
 	if (param[0] == REG_CODE)
		val[0] = get_reg_value(&(*data), (*process), &shift);
	else
		return ;
	if (param[1] == REG_CODE)
		val[1] = get_reg_value(&(*data), (*process), &shift);
	else if (param[1] == IND_CODE)
		val[1] = get_ind_address (&(*data), (*process), &shift);
	else
		return ;
	load_value(&(*data), &(*process), ((*process)->position + (val[1]) % IDX_MOD) % MEM_SIZE, val[0]);
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}