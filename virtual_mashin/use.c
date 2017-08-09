/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 18:29:48 by itsuman           #+#    #+#             */
/*   Updated: 2017/08/09 18:56:02 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	use(void)
{
	ft_putstr("Usage: ./corewar [-d N -s N -v N | -b --stealth]\n");
	ft_putstr("a        : Prints output from \"aff\" (Default is to hide it)\n");
	ft_putstr("#### TEXT OUTPUT MODE #####################################\n");
	ft_putstr("-d N      : Dumps memory after N cycles then exits\n");
	ft_putstr("-s N      : Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_putstr("-v N      : Verbosity levels, can be added together to enable several\n");
	ft_putstr("#### BINARY OUTPUT MODE ###################################\n");
	ft_putstr("-b        : Binary output mode for corewar.42.fr\n");
	ft_putstr("#### NCURSES OUTPUT MODE ##################################\n");
	ft_putstr("-n        : Ncurses output mode\n");
	ft_putstr("###########################################################\n");
}
