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

//int     get_index_position(int pc, unsigned int val)
//{
//	int     p;
//
//	p = val;
//	if (p < 0)
//	{
//		while (p < 0)
//			p += IDX_MOD;
//		p -= IDX_MOD;
//	}
//	else
//		p %= IDX_MOD;
//	p += pc;
//	if (p < 0)
//		p += MEM_SIZE;
//	else
//		p %= MEM_SIZE;
//	return (p);
//}

int	get_ind_address(t_data **data, t_process *process, int *shift)
{
	int val[2];
	val[0] = ((*data)->map[(process->position + *shift) % MEM_SIZE]);
	val[1] = ((*data)->map[(process->position + *shift + 1) % MEM_SIZE]);
	*shift += 2;
	return ((val[0] << 8) + val[1]);
}

void    st(t_data **data, t_process **process)
{
	unsigned char   param[2];
    int    val[3];
    int             shift;

    shift = 2;
    param[0] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
    param[1] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
 	if (param[0] == REG_CODE)
		val[0] = get_reg_value(&(*data), (*process), &shift);
	else
		return ;
	if (param[1] == REG_CODE)
		val[1] = get_reg_value(&(*data), (*process), &shift);
	else if (param[1] == IND_CODE)
		val[1] = (short)get_ind_address(&(*data), (*process), &shift);
	else
		return ;
	val[2] = (*process)->position + (val[1] % IDX_MOD);
	if (val[2] < 0)
		val[2] += MEM_SIZE;
	load_value(&(*data), &(*process), val[2], val[0]);
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}