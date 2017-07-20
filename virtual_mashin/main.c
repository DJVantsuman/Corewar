/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 17:02:42 by itsuman           #+#    #+#             */
/*   Updated: 2017/06/02 17:02:48 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int   bit_rev(unsigned int octet)
{
    unsigned int x[4];

    x[0] = (unsigned int) ((octet & 4278190080) >> 24);
    x[1] = ((octet & 16711680) >> 8);
    x[2] = ((octet & 65280) << 8);
    x[3] = ((octet & 255) << 24);
    return (x[0] + x[1] + x[2] + x[3]);
}

void set_players_number(t_player **player)
{
	char			c;
    unsigned int	i;
    t_player		*var;

	i = 0;
	c = 0;
	var = *player;
	while(var)
	{
		var->id = c;
		var->number = --i;
		var = var->next;
		c += 1;
	}
}

/*
** Function "reed_player" reed one player from the file and store
** it to the struct 'player'.
*/
void    reed_player(char *file, t_player **player, int player_number)
{
    int         fd;
    char        *line;
    t_player    *tmp;

    fd = open(file,O_RDONLY);
    line = malloc(sizeof(header_t));
    tmp = (t_player *)malloc(sizeof(t_player));
    if (fd > 0)
    {
        tmp->number = (unsigned int)player_number;
        tmp->file = file;
        read(fd, line, sizeof(header_t));
        tmp->header = (header_t *)line;
        tmp->header->prog_size = bit_rev(tmp->header->prog_size);
        tmp->prog_cod = malloc(sizeof(char) * tmp->header->prog_size);
        read(fd, tmp->prog_cod, tmp->header->prog_size);
        tmp->live = 0;
        tmp->last_live = 0;
        close(fd);
        tmp->next = *player;
        *player = tmp;
    }
    else
        error_manager(file, 1);
}

/*
** Function "reed_arg" read all argument from command line and store it
** in the structure 'arg'.
** After that this function start reading player and give all players to
** function "controller".
*/
void    reed_arg(t_data **data, char **av)
{
    int i;

    i = 0;
    while (av[++i])
    {
        if (ft_strcmp(av[i], "-dump") == 0)
        {
            if (is_nbr(av[++i]))
			(*data)->dump = ft_atoi(av[i]);
        }
        else if (ft_strcmp(av[i], "-n") == 0)
        {
			(*data)->nbr = ft_atoi(av[++i]);
            if (av[++i] && ft_strcmp(av[i], "-dump") != 0 &&
                ft_strcmp(av[i], "-n") != 0)
                reed_player(av[i], &(*data)->player, (*data)->nbr);
        }
        else if (ft_strcmp(av[i], "-v") == 0)
			(*data)->v = 1;
        else
            reed_player(av[i], &(*data)->player, 0);
    }
}



/*
** Function "main" start program.
** The function "check_arg" is in the file controller.c.
*/
int main(int ac, char **av)
{
    t_data      *data;

    if (ac > 1)
    {
		data = (t_data *)malloc(sizeof(t_data));
        data->player = NULL;
        data->amount_players = check_arg(av, 0, 0, 0);
        reed_arg(&data, av);
		set_players_number(&data->player);
		controller(&data->player);
		model(&data);
    }
    else
        error_manager(NULL, 0);
    return (0);
}
