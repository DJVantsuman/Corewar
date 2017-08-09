/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:56:59 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:57:03 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	lldi(t_data **data, t_process **process)
{
	unsigned char	param[3];
	int				val[4];
	int				shift;

	shift = 2;
	param[0] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
	param[1] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
	param[2] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
	if (param[0] == REG_CODE)
		val[0] = get_reg_value(&(*data), (*process), &shift);
	else if (param[0] == DIR_CODE)
		val[0] = get_dir_value(&(*data), (*process), &shift, 2);
	else if (param[0] == IND_CODE)
		val[0] = get_ind_value(&(*data), (*process), &shift, 4);
	if (param[1] == REG_CODE)
		val[1] = get_reg_value(&(*data), (*process), &shift);
	else if (param[1] == DIR_CODE)
		val[1] = get_dir_value(&(*data), (*process), &shift, 2);
	val[2] = get_reg_numb(&(*data), (*process), &shift);
	if ((val[2] <= REG_NUMBER && val[2] > 0) && param[0] > 0 && (param[1] == 1 || param[1] == 2))
	{
		val[3] = get_direct(&(*data), *process, ((val[0] + val[1]) % IDX_MOD)) % MEM_SIZE;
		(*process)->registers[val[2] - 1] = val[3];
	}
	(*process)->carry = val[3] == 0 ? 1 : 0;
	(*process)->position += count_shift(3, (*data)->map[((*process)->position + 1) % MEM_SIZE], 2) % MEM_SIZE;
}
