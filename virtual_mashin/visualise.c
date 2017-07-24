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

//void	wprint_champ(t_player **player)
//{
//	t_player    *play;
//
//	play = *player;
//	while (play)
//	{
//		if (play->last_live == 1)
//		{
//			refresh ();
//			wprintw(stdscr, "\nPlayer %d (%s) won.\n", play->number, play->header->prog_name);
//			refresh ();
//		}
//		play = play->next;
//	}
//	refresh ();
//	wprintw(stdscr, "\nPlayer %d (%s) won.\n", (*player)->number, (*player)->header->prog_name);
//	refresh ();
//
////	endwin();
////	exit(1);
//
//}

int		process_count(t_process *process)
{
	int i;
	t_process *tmp;

	i = 0;
	tmp = process;
	while (tmp)
	{
		if (tmp->live >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	wprint_status(t_data **data, WINDOW **status, int *cycles)
{
	t_player *tmp;
	float sp;

	sp = 1 / ((float)(*data)->speed / (float)1000000);
	tmp = (*data)->player;
	wattron(*status, A_BOLD);
	wprintw (*status, "CYCLES/SECOND\t%.1f\n", sp);
	wprintw (*status, "CYCLE\t\t%d\n\n", cycles[3]);
	wprintw (*status, "CYCLE_TO_DIE\t%d\n", cycles[2]);
	wprintw (*status, "CYCLE_DELTA\t%d\n", CYCLE_DELTA);
	wprintw (*status, "NBR_LIVE\t%d\n", NBR_LIVE);
	wprintw (*status, "MAX_CHECKS\t%d\n", cycles[1]);
	wprintw (*status, "\nPROCESSES\t%d\n", process_count((*data)->process));
	while (tmp)
	{
		wprintw(*status, "\nPLAYER %i\t", tmp->number);
		wattron(*status, COLOR_PAIR(tmp->id));
		wprintw(*status, "%s\n", tmp->header->prog_name);
		wattroff(*status, COLOR_PAIR(tmp->id));
		wprintw(*status, "  LIVE\t\t%d\n", tmp->live);
		wprintw(*status, "  LAST LIVE\t%d\n", tmp->last_live);
		tmp = tmp->next;
	}
	wattroff(*status, A_BOLD);
}

char 	is_process(t_process **process, int i)
{
	t_process *tmp;

	tmp = *process;
	while (tmp)
	{
		if (tmp->position == i && tmp->live >= 0)
			return (tmp->p_id);
		tmp = tmp->next;
	}
	return (0);
}

void    wprint_map(t_data **data, WINDOW **map)
{
	int i;
	int color;
	char p_id;

	i = 0;
	while (i < MEM_SIZE)
	{
		if ((i % 64) == 0)
			wprintw((*map), "0x%.4x : ", i);
		color = (*data)->map_v[i] == 0 ? 10 : (*data)->map_v[i];
		if ((p_id = is_process(&(*data)->process, i)))
		{
			wattron((*map), COLOR_PAIR(p_id + 4));
			wprintw((*map), "%.2x", (*data)->map[i]);
			wattroff((*map), COLOR_PAIR(p_id + 4));
			wprintw((*map), " ");
		}
		else
		{
			wattron((*map), COLOR_PAIR(color));
			wprintw((*map), "%.2x ", (*data)->map[i]);
			wattroff((*map), COLOR_PAIR(color));
		}
		i++;
//		if ((i % 64) == 0)
//			printw("\n");
	}
	wrefresh(*map);

}

void colors_init()
{
	init_color(COLOR_WHITE, 700, 700, 700);

	init_pair(14, COLOR_BLACK, COLOR_WHITE);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);

	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);

	init_pair(0, COLOR_WHITE, COLOR_BLACK);
//	init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void visualise(t_data **data, int *cycles)
{
	int key;

	initscr();
	noecho();
	nodelay(stdscr, TRUE);

	WINDOW *map;
	WINDOW *status;

	map = newwin(64, 201, 1, 2);
	status = newwin(64, 48, 1, 205);

	start_color();
	colors_init();

	wprint_map(&(*data), &map);
	wprint_status (&(*data), &status, cycles);

	refresh();
	wrefresh(status);
	wrefresh(map);
	key = getch();
	if (key == 27)
	{
		endwin();
		exit(1);
	}
	else if (key == 32)
	{
		while(1)
		{
			key = getch();
			if(key == 32)
				break;
		}
	}
	else if (key == 'e')
	{
		if ((*data)->speed > 0)
			(*data)->speed -= 1000;
	}
	else if (key == 'w')
	{
		if ((*data)->speed < 4294967295)
			(*data)->speed += 1000;
	}
	usleep ((*data)->speed);
}
