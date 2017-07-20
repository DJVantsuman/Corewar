/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:41:12 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:41:20 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void    sub(t_data **data)
{
	char            param[3];
	unsigned int    val[3];
	int             shift;
	int 			pos;

	shift = 2;
	pos = 2;
	param[0] = (char)((*data)->program->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
	param[1] = (char)((*data)->program->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
	param[2] = (char)((*data)->program->map[((*process)->position + 1) % MEM_SIZE] & 12) >> 2;
	if (param[0] == REG_CODE && param[1] == REG_CODE && param[2] == REG_CODE)
	{
		val[0] = get_reg_numb((*data)->program, (*process), &shift);
		val[1] = get_reg_numb((*data)->program, (*process), &shift);
		val[2] = get_reg_numb((*data)->program, (*process), &shift);
		if (val[0] <= 16 && val[0] > 0 && val[1] <= 16 && val[1] > 0 && val[2] <= 16 && val[2] > 0)
		{
			val[0] = get_reg_value((*data)->program, (*process), &pos);
			val[1] = get_reg_value((*data)->program, (*process), &pos);
			(*process)->registers[val[2] - 1] = val[0] - val[1];
		}
	}
	(*process)->position = ((*process)->position + shift) % MEM_SIZE;
}