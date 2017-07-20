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

void	wprint_status(t_data **data, WINDOW **status, int *cycles)
{
	int i;
	i = 0;
	t_player *tmp;

	tmp = (*data)->player;
	wattron(*status, A_BOLD);
	while (tmp)
	{
		wprintw(*status, "NAME\t");
		wattron(*status, COLOR_PAIR(tmp->id));
		wprintw(*status, "%s\n", tmp->header->prog_name);
		wattroff(*status, COLOR_PAIR(tmp->id));
		wprintw(*status, "LIVE\t%d\n", tmp->live);
		wprintw(*status, "LAST LIVE\t%d\n", tmp->last_live);
		tmp = tmp->next;
	}

	wprintw (*status, "\n\tCYCLES %d\n", cycles[3]);
	wprintw (*status, "\tcarry\t%d\n", (*data)->program->carry);
	wattroff(*status, A_BOLD);
	wrefresh (*status);
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

	i = 0;
	while (i < MEM_SIZE)
	{
		if (is_process(&(*data)->process, i))
		{
			wattron((*map), COLOR_PAIR(10));
			wprintw((*map), "%.2x", (unsigned char)(*data)->program->map[i]);
			wattroff((*map), COLOR_PAIR(10));
			wprintw((*map), " ");
		}
		else
		{
			wattron((*map), COLOR_PAIR((*data)->program->map_v[i]));
			wprintw((*map), "%.2x ", (unsigned char)(*data)->program->map[i]);
			wattroff((*map), COLOR_PAIR((*data)->program->map_v[i]));
		}
		i++;
		if ((i % 64) == 0)
			printw("\n");
	}
	wrefresh(*map);

}

void colors_init()
{
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_RED);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void visualise(t_data **data, int *cycles)
{
	initscr();
	noecho();

	WINDOW *map;
	WINDOW *status;

	map = newwin(64, 192, 1, 2);
	status = newwin(64, 48, 1, 195);

	start_color();
	colors_init();

	wprint_map(&(*data), &map);
	wprint_status (&(*data), &status, cycles);

	refresh();
	wrefresh(status);
	wrefresh(map);
	usleep (10000);
}
