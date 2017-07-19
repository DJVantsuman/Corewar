/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodiono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 17:10:14 by arodiono          #+#    #+#             */
/*   Updated: 2017/07/18 17:10:16 by arodiono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	wprint_status(t_player **player, t_program **program, WINDOW
**status, int cycles)
{
	int i;
	i = 0;
	t_player *tmp;

	tmp = *player;
	while (tmp)
	{
		wprintw (*status, "\tname %s\n\tlive %d\n\tlast live %d\n\n",
				 tmp->header->prog_name,
				 tmp->live,
				 tmp->last_live);
		tmp = tmp->next;
	}
	while (i < REG_NUMBER)
	{
		wprintw (*status, "\tr%d\t%u\n", i + 1, (*program)->registers[i]);
		i++;
	}
	wprintw (*status, "\n\tcycle %d", cycles);
	wrefresh (*status);

}

int 	is_process(t_process **process, int i)
{
	t_process *tmp;

	tmp = *process;
	while (tmp)
	{
		if (tmp->position == i)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void    wprint_map(t_program **program, t_process **process, WINDOW **map)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{

		if (is_process(&(*process), i))
		{
			wattron((*map), COLOR_PAIR(2));
			wprintw((*map), "%.2x", (unsigned char)(*program)->map[i]);
			wattroff((*map), COLOR_PAIR(2));
			wprintw((*map), " ");
		}
		else
			wprintw((*map), "%.2x ", (unsigned char)(*program)->map[i]);
		i++;
		if ((i % 64) == 0)
			printw("\n");
	}
	wrefresh(*map);

}

void visualise(t_player **player, t_program **program, t_process **process, int cycles)
{
	initscr();
	noecho();

	WINDOW *map;
	WINDOW *top;
	WINDOW *status;

	top = newwin(6, 192,1, 1);
	map = newwin(64, 192, 7,1);
	status = newwin(64, 48, 7, 194);

	start_color();

	init_pair( 1, COLOR_WHITE,   COLOR_BLACK);
	init_pair( 2, COLOR_BLACK,    COLOR_WHITE);


	wbkgd(status, COLOR_PAIR(1));
	wbkgd(map, COLOR_PAIR(1));
	wbkgd(top, COLOR_PAIR(1));

	wprint_map(&(*program), &(*process), &map);
	wprint_status (&(*player), &(*program), &status, cycles);
	wprintw(top, "corewar");

	refresh();
	wrefresh(status);
	wrefresh(map);
	wrefresh(top);
	usleep (10000);
}
