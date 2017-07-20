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

void	wprint_status(t_data **data, WINDOW **status, int cycles)
{
	t_player *tmp;

	tmp = (*data)->player;
	wattron(*status, A_BOLD);
	while (tmp)
	{
		wprintw(*status, "PLAYER %i\t", tmp->number);
		wattron(*status, COLOR_PAIR(tmp->id));
		wprintw(*status, "%s\n", tmp->header->prog_name);
		wattroff(*status, COLOR_PAIR(tmp->id));
		wprintw(*status, "LIVE\t%d\n", tmp->live);
		wprintw(*status, "LAST LIVE\t%d\n\n", tmp->last_live);
		tmp = tmp->next;
	}
	wprintw (*status, "\n\tCYCLES %d\n", cycles);
	wattroff(*status, A_BOLD);
}

int 	is_process(t_process **process, unsigned int i)
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

void    wprint_map(t_data **data, WINDOW **map)
{
	unsigned int i;
	int color;

	i = 0;
	while (i < MEM_SIZE)
	{
		color = (*data)->map_v[i] == 0 ? 10 : (*data)->map_v[i];
		if (is_process(&(*data)->process, i))
		{
			wattron((*map), COLOR_PAIR(color + 4));
			wprintw((*map), "%.2x", (unsigned char)(*data)->map[i]);
			wattroff((*map), COLOR_PAIR(color + 4));
			wprintw((*map), " ");
		}
		else
		{
			wattron((*map), COLOR_PAIR(color));
			wprintw((*map), "%.2x ", (unsigned char)(*data)->map[i]);
			wattroff((*map), COLOR_PAIR(color));
		}
		i++;
		if ((i % 64) == 0)
			printw("\n");
	}
	wrefresh(*map);

}

void colors_init()
{
	init_pair(14, COLOR_BLACK, COLOR_WHITE);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

	init_pair(5, COLOR_BLACK, COLOR_RED);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);

//	init_pair(9, COLOR_WHITE, COLOR_BLACK);
//	init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void visualise(t_data **data, int cycles)
{
	initscr();
	noecho();

	WINDOW *map;
	WINDOW *status;

	map = newwin(64, 192, 1, 2);
	status = newwin(64, 48, 1, 200);

	start_color();
	colors_init();

	wprint_map(&(*data), &map);
	wprint_status (&(*data), &status, cycles);

	refresh();
	wrefresh(status);
	wrefresh(map);
	usleep (10000);
}
