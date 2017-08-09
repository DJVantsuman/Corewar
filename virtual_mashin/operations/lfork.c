/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 20:58:24 by itsuman           #+#    #+#             */
/*   Updated: 2017/07/07 20:58:29 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void	lfork(t_data **data, t_process **process)
{
	unsigned char	byte[2];
	int				res;

	byte[0] = (*data)->map[((*process)->position + 1) % MEM_SIZE];
	byte[1] = (*data)->map[((*process)->position + 2) % MEM_SIZE];
	res = (unsigned int)((byte[0] << 8) + byte[1]);
	add_process(&(*data), &(*process), ((*process)->position + res) % MEM_SIZE);
	(*process)->position = ((*process)->position + 3) % MEM_SIZE;
}
