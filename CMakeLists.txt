cmake_minimum_required(VERSION 3.6)
project(corewar)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    op.h
        virtual_mashin/libft/libft.h
        virtual_mashin/main.c
        virtual_mashin/error_manager.c
        virtual_mashin/controller.c
        virtual_mashin/model.c
        virtual_mashin/libft/ft_memdel.c
        virtual_mashin/libft/ft_itoa.c
        virtual_mashin/libft/ft_atoi.c
        virtual_mashin/libft/ft_putnbr.c
        virtual_mashin/libft/ft_strcmp.c
        virtual_mashin/free_memory.c
        virtual_mashin/operations/live.c virtual_mashin/start_process.c)

add_executable(corewar ${SOURCE_FILES}
        virtual_mashin/main.c
        virtual_mashin/libft/ft_putstr.c
        virtual_mashin/libft/ft_putchar.c
        virtual_mashin/error_manager.c
        virtual_mashin/controller.c
        virtual_mashin/model.c
        virtual_mashin/libft/ft_memdel.c
        virtual_mashin/libft/ft_itoa.c
        virtual_mashin/libft/ft_atoi.c
        virtual_mashin/libft/ft_putnbr.c
        virtual_mashin/libft/ft_strcmp.c
        virtual_mashin/free_memory.c
        virtual_mashin/operations/live.c virtual_mashin/start_process.c)