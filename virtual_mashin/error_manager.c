/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 18:17:35 by itsuman           #+#    #+#             */
/*   Updated: 2017/06/02 18:17:37 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    print_error(char *file, int  index)
{
    int i;

    i = -1;
    if (index == 1)
    {
        write(1, "\nERROR! File ", 13);
        while (file[++i])
            ft_putchar(file[i]);
        write(1, " can't be opened.\n", 19);
    }
    else if (index == 7)
    {
        write(1, "\nERROR! Wrong magic number in file ", 35);
        while (file[++i])
            ft_putchar(file[i]);
        write(1, "\n", 1);
    }
    else if (index == 8)
    {
        write(1, "\nERROR! Prog_size can't be bigger then CHAMP_MAX_SIZE "
                "in file ", 62);
        while (file[++i])
            ft_putchar(file[i]);
        write(1, "\n", 1);
    }
    exit(1);
}

void    error_manager(char *file, int  index)
{
    if (index == 0)
        ft_putstr("\nERROR! Wrong arguments.\n");
    else if (index == 1)
        print_error(file, index);
    else if (index == 2)
        ft_putstr("\nERROR! After flag -dump must be amount of cycles.\n");
    else if (index == 3)
        ft_putstr("\nERROR! After players number must be file name.\n");
    else if (index == 4)
        ft_putstr("\nERROR! After flag -n must be players number.\n");
    else if (index == 5)
        ft_putstr("\nERROR! There is must be only one flag -dump.\n");
    else if (index == 6)
        ft_putstr("\nERROR! Number of players mast be from 1 till MAX_PLAYERS.\n");
    else if (index == 7)
        print_error(file, index);
    else if (index == 8)
        print_error(file, index);
    else if (index == 9)
        ft_putstr("\nERROR! There is must be only one flag -v.\n\n");
    exit(1);
}