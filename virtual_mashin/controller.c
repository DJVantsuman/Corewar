/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 21:03:58 by itsuman           #+#    #+#             */
/*   Updated: 2017/06/02 21:04:01 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function "controller" checks magic and length of cod each players.
*/
void    controller(t_player **player)
{
	t_player    *tmp;

	tmp = *player;
	while (tmp)
	{
		if (bit_rev(tmp->header->magic) != COREWAR_EXEC_MAGIC)
			error_manager(tmp->file, 7);
		if (tmp->header->prog_size > CHAMP_MAX_SIZE)
			error_manager(tmp->file, 8);
		tmp = tmp->next;
	}
}

int     is_nbr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if(s[i] > 47 && s[i] < 58)
			i++;
		else
			return (0);
	}
	return (1);
}

/*
** Function "check_amount_arg" checks amount each arguments.
*/
void    check_amount_arg(int dump, int players, char **av)
{
	int i;
	int v;

	i = 1;
	v = 0;
	if (dump > 1)
		error_manager(NULL, 5);
	if (players < 1 || players > MAX_PLAYERS)
		error_manager(NULL, 6);
	while (av[i])
	{
		if (ft_strcmp(av[i], "-v") == 0)
			v++;
		i++;
	}
	if (v > 1)
		error_manager(NULL, 9);
}

/*
** Function "check_arg" checks amount and correctness of arguments.
*/
int    check_arg(char **av, int i, int dump, int players)
{
	while (av[++i])
		if (ft_strcmp(av[i], "-dump") == 0 && is_nbr(av[i + 1]))
		{
			dump++;
			i++;
		}
		else if (ft_strcmp(av[i], "-dump") == 0)
			error_manager(NULL, 2);
		else if (ft_strcmp(av[i], "-n") == 0 && is_nbr(av[i + 1]))
			if (av[++i + 1] && ft_strcmp(av[i + 1], "-dump") != 0 &&
					ft_strcmp(av[i + 1], "-n") != 0)
			{
				i++;
				players++;
			}
			else
				error_manager(NULL, 3);
		else if (ft_strcmp(av[i], "-n") == 0)
			error_manager(NULL, 4);
		else if (ft_strcmp(av[i], "-v") == 0)
			i = i + 0;
		else
			players++;
	check_amount_arg(dump, players, av);
	return (players);
}
