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

int get_player_number(t_player **player)
{
    int         i;
    int         f;
    t_player    *var;

    i = 1;
    while (1)
    {
        f = 0;
        var = *player;
        while(var)
        {
            if (var->number == i)
                f++;
            var = var->next;
        }
        if (f == 0)
            return (i);
        else
            i++;
    }
}

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
        tmp->number = player_number;
        tmp->file = file;
        read(fd, line, sizeof(header_t));
        tmp->header = (header_t *)line;
        tmp->header->prog_size = bit_rev(tmp->header->prog_size);
        tmp->prog_cod = malloc(sizeof(char) * tmp->header->prog_size);
        read(fd, tmp->prog_cod, tmp->header->prog_size);
        close(fd);
        tmp->next = *player;
        *player = tmp;
    }
    else
        error_manager(file, 1);
}

void    reed_arg(t_player **player, t_arg *arg, char **av)
{
    int i;

    i = 0;
    while (av[++i])
    {
        if (ft_strcmp(av[i], "-dump") == 0)
        {
            if (is_nbr(av[++i]))
                arg->dump = ft_atoi(av[i]);
        }
        else if (ft_strcmp(av[i], "-n") == 0)
        {
            arg->nbr = ft_atoi(av[++i]);
            if (av[++i] && ft_strcmp(av[i], "-dump") != 0 &&
                ft_strcmp(av[i], "-n") != 0)
                reed_player(av[i], player, arg->nbr);
        }
        else if (ft_strcmp(av[i], "-v") == 0)
            arg->v = 1;
        else
            reed_player(av[i], player, get_player_number(player));
    }
        controller(player);
}

int main(int ac, char **av)
{
    t_player    *player;
    t_arg       arg;
    int         amount_players;

    if (ac > 1)
    {
        player = NULL;
        amount_players = check_arg(av, 0, 0, 0);
        arg.amount_players = amount_players;
        reed_arg(&player, &arg, av);
        model(&player, amount_players, &arg);
    }
    else
        error_manager(NULL, 0);
//    while (1);
    return (0);
}
