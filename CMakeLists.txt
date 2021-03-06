cmake_minimum_required(VERSION 3.7)
project(corewar)

set(CMAKE_CXX_STANDARD 11)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set(SOURCE_FILES
        virtual_mashin/libft/ft_alldown.c
        virtual_mashin/libft/ft_allup.c
        virtual_mashin/libft/ft_atoi.c
        virtual_mashin/libft/ft_bzero.c
        virtual_mashin/libft/ft_isalnum.c
        virtual_mashin/libft/ft_isalpha.c
        virtual_mashin/libft/ft_isascii.c
        virtual_mashin/libft/ft_isblank.c
        virtual_mashin/libft/ft_isdigit.c
        virtual_mashin/libft/ft_isprint.c
        virtual_mashin/libft/ft_itoa.c
        virtual_mashin/libft/ft_lstadd.c
        virtual_mashin/libft/ft_lstdel.c
        virtual_mashin/libft/ft_lstdelone.c
        virtual_mashin/libft/ft_lstiter.c
        virtual_mashin/libft/ft_lstmap.c
        virtual_mashin/libft/ft_lstnew.c
        virtual_mashin/libft/ft_memalloc.c
        virtual_mashin/libft/ft_memccpy.c
        virtual_mashin/libft/ft_memchr.c
        virtual_mashin/libft/ft_memcmp.c
        virtual_mashin/libft/ft_memcpy.c
        virtual_mashin/libft/ft_memdel.c
        virtual_mashin/libft/ft_memmove.c
        virtual_mashin/libft/ft_memset.c
        virtual_mashin/libft/ft_putchar.c
        virtual_mashin/libft/ft_putchar_fd.c
        virtual_mashin/libft/ft_putendl.c
        virtual_mashin/libft/ft_putendl_fd.c
        virtual_mashin/libft/ft_putnbr.c
        virtual_mashin/libft/ft_putnbr_fd.c
        virtual_mashin/libft/ft_putstr.c
        virtual_mashin/libft/ft_putstr_fd.c
        virtual_mashin/libft/ft_strcat.c
        virtual_mashin/libft/ft_strchr.c
        virtual_mashin/libft/ft_strclr.c
        virtual_mashin/libft/ft_strcmp.c
        virtual_mashin/libft/ft_strcpy.c
        virtual_mashin/libft/ft_strdel.c
        virtual_mashin/libft/ft_strdup.c
        virtual_mashin/libft/ft_strequ.c
        virtual_mashin/libft/ft_striter.c
        virtual_mashin/libft/ft_striteri.c
        virtual_mashin/libft/ft_strjoin.c
        virtual_mashin/libft/ft_strlcat.c
        virtual_mashin/libft/ft_strlen.c
        virtual_mashin/libft/ft_strmap.c
        virtual_mashin/libft/ft_strmapi.c
        virtual_mashin/libft/ft_strncat.c
        virtual_mashin/libft/ft_strncmp.c
        virtual_mashin/libft/ft_strncpy.c
        virtual_mashin/libft/ft_strnequ.c
        virtual_mashin/libft/ft_strnew.c
        virtual_mashin/libft/ft_strnstr.c
        virtual_mashin/libft/ft_strrchr.c
        virtual_mashin/libft/ft_strrev.c
        virtual_mashin/libft/ft_strsplit.c
        virtual_mashin/libft/ft_strstr.c
        virtual_mashin/libft/ft_strsub.c
        virtual_mashin/libft/ft_strtrim.c
        virtual_mashin/libft/ft_strworldup.c
        virtual_mashin/libft/ft_tolower.c
        virtual_mashin/libft/ft_toupper.c
        virtual_mashin/libft/libft.h
        virtual_mashin/operations/add.c
        virtual_mashin/operations/aff.c
        virtual_mashin/operations/and.c
        virtual_mashin/operations/ft_fork.c
        virtual_mashin/operations/ld.c
        virtual_mashin/operations/ldi.c
        virtual_mashin/operations/lfork.c
        virtual_mashin/operations/live.c
        virtual_mashin/operations/lld.c
        virtual_mashin/operations/lldi.c
        virtual_mashin/operations/or.c
        virtual_mashin/operations/st.c
        virtual_mashin/operations/sti.c
        virtual_mashin/operations/sub.c
        virtual_mashin/operations/xor.c
        virtual_mashin/operations/zjmp.c
        virtual_mashin/check_live.c
        virtual_mashin/controller.c
        virtual_mashin/error_manager.c
        virtual_mashin/free_memory.c
        virtual_mashin/main.c
        virtual_mashin/model.c
        virtual_mashin/run_process.c
        virtual_mashin/start_process.c
        virtual_mashin/visualise.c
        virtual_mashin/vm.h
        op.h)

add_executable(corewar ${SOURCE_FILES})
target_link_libraries(corewar ${CURSES_LIBRARIES})
