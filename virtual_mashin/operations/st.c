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

int     count_shift(int numb, unsigned char byte, int dir)
{
	unsigned char cbyte[3];
	int     shift;
	int     i;

	i = 0;
	shift = 2;

	cbyte[0] = (unsigned char)(byte & 192) >> 6;
	cbyte[1] = (unsigned char)(byte & 48) >> 4;
	cbyte[2] = (unsigned char)(byte & 12) >> 2;
	while (i < numb)
	{
		if (cbyte[i] == REG_CODE)
			shift += 1;
		else if (cbyte[i] == IND_CODE)
			shift += 2;
		else if (cbyte[i] == DIR_CODE)
		{
			if (dir == 2)
				shift += 2;
			else
				shift += 4;
		}
		i++;
	}
	return (shift);
}

int	get_ind_address(t_data **data, t_process *process, int *shift)
{
	int val[2];
	val[0] = ((*data)->map[(process->position + *shift) % MEM_SIZE]);
	val[1] = ((*data)->map[(process->position + *shift + 1) % MEM_SIZE]);
	*shift += 2;
//	printf (" %d", (short)((val[0] << 8) + val[1]));
	return (short)((val[0] << 8) + val[1]);
}

void    st(t_data **data, t_process **process)
{
	unsigned char   param[2];
	int    val[3];
	int             shift;
//	int 	reg;

	shift = 2;
	param[0] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 192) >> 6;
	param[1] = (unsigned char)((*data)->map[((*process)->position + 1) % MEM_SIZE] & 48) >> 4;
//	printf ("st");
	if (param[0] == REG_CODE) {
		val[0] = get_reg_numb(&(*data), (*process), &shift);
//		shift--;
//		val[0] = get_reg_value (&(*data), (*process), &shift);
	}
	if (param[1] == REG_CODE)
		val[1] = get_reg_numb(&(*data), (*process), &shift);
	else if (param[1] == IND_CODE)
		val[1] = (short)get_ind_address(&(*data), (*process), &shift);
	val[2] = (*process)->position + (val[1] % IDX_MOD);

//	(*process)->position += count_shift (2, (*data)->map[((*process)->position + 1) % MEM_SIZE], 2) % MEM_SIZE;

	if (param[0] == REG_CODE && (val[0] > 0 && val[0] <= REG_NUMBER) && param[1] == IND_CODE)
	{
		load_value(&(*data), &(*process), val[2], (*process)->registers[val[0] - 1]);
		(*process)->position += 5;
	}
	else if ( param[0] == REG_CODE && (val[0] > 0 && val[0] <= REG_NUMBER) &&
			  param[1] == REG_CODE && (val[1] > 0 && val[1] <= REG_NUMBER) )
	{
		(*process)->registers[val[1] - 1] = (*process)->registers[val[0] - 1];
		(*process)->position += 4;
	}
	else
	{
		(*process)->position += 5;
	}
}

