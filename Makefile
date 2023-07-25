# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 14:22:16 by llegrand          #+#    #+#              #
#    Updated: 2023/07/25 19:51:11 by llegrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# make re not working as intended
# try fresh runs on osx & lnx


# **************************************************************************** #
#                 _       _     _           
#__   ____ _ _ __(_) __ _| |__ | | ___  ___ 
#\ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __|
# \ V / (_| | |  | | (_| | |_) | |  __/\__ \
#  \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/
#                                           
# **************************************************************************** #

# uname
UNAME := $(shell uname)

# compiler configs
CC := gcc
CCARGS := -Wall -Werror -Wextra

# archive configs
AR := ar
ARARGS := -crs		

# linux-specific compiler args
LNXARGS := -Iincludes -L. -lft -Lmlx_lnx -lmlx_lnx -L/usr/lib -Imlx_lnx -lXext -lX11 -lm -lz -lpthread -O3
#LNXINCL := includes/keycodes_lnx.h

# osx-specific compiler args
OSXARGS := -Iincludes -L. -lft -Lmlx_osx -lmlx_osx -L/usr/lib -Imlx_osx -framework OpenGL -framework AppKit -lm -lz -lpthread -O3
#OSXINCL := includes/keycodes_osx.h

# source files
SRCS := main.c srcs/color.c srcs/fractal.c srcs/hooks.c srcs/math.c srcs/render.c srcs/worker.c

# include files
INCLS := includes/colors.h includes/fractol.h

# output name
NAME := fractol.out

# some old bullshit. we keep it there in case we need it again one day.
# the osx_bullshit was used when unpacking the mlx_osx archive to combine it with libft to have a single library.
#MLX = minilibx-linux
#OSX_BULLSHIT = #__.SYMDEF __.SYMDEF\ SORTED

# **************************************************************************** #
#                                 _  __ _           _   _                 
#  ___  ___   ___ _ __   ___  ___(_)/ _(_) ___ __ _| |_(_) ___  _ __  ___ 
# / _ \/ __| / __| '_ \ / _ \/ __| | |_| |/ __/ _` | __| |/ _ \| '_ \/ __|
#| (_) \__ \ \__ \ |_) |  __/ (__| |  _| | (_| (_| | |_| | (_) | | | \__ \
# \___/|___/ |___/ .__/ \___|\___|_|_| |_|\___\__,_|\__|_|\___/|_| |_|___/
#                |_|                                                      

# **************************************************************************** #

ifeq ($(UNAME), Linux)
	CCARGS += $(LNXARGS)
	INCLS += $(LNXINCL)
	MLX := mlx_lnx
endif
ifeq ($(UNAME), Darwin)
	CCARGS += $(OSXARGS)
	INCLS += $(OSXINCL)
	MLX := mlx_osx
endif

# **************************************************************************** #
#                 _    _                             _                 
#  ___ ___   ___ | | _(_)_ __   __ _   _ __ ___  ___(_)_ __   ___  ___ 
# / __/ _ \ / _ \| |/ / | '_ \ / _` | | '__/ _ \/ __| | '_ \ / _ \/ __|
#| (_| (_) | (_) |   <| | | | | (_| | | | |  __/ (__| | |_) |  __/\__ \
# \___\___/ \___/|_|\_\_|_| |_|\__, | |_|  \___|\___|_| .__/ \___||___/
#                              |___/                  |_|              
#
# **************************************************************************** #

$(NAME) : libft.a lib$(MLX).a $(SRCS) $(INCLS)
	$(CC) $(SRCS) $(CCARGS) -o $(NAME)

exe : $(NAME)
	./$(NAME) 50

libft.a : libft/Makefile
	cd libft && $(MAKE)
	cp libft/libft.a .

libft/Makefile :
	git submodule update --init libft

lib$(MLX).a : $(MLX)/Makefile
	cd $(MLX) && $(MAKE)
	cp $(MLX)/libmlx.a ./lib$(MLX).a

$(MLX)/Makefile :
	wget https://cdn.intra.42.fr/document/document/12993/minilibx_opengl.tgz
	tar -Zxvf minilibx_opengl.tgz
	mv minilibx_opengl_20191021 mlx_osx
	rm minilibx_opengl.tgz

clean :
	rm -f $(OBJS) $(BOBJS)
	cd libft && $(MAKE) clean

fclean : clean
	rm -f $(NAME) libft.a lib$(MLX).a
	cd libft && $(MAKE) fclean
	cd $(MLX) && $(MAKE) clean
	rm -f $(MLX)/libmlx.a

all : $(NAME)

re : fclean all

#bonus : $(OBJS) $(BOBJS)
#	$(AR) $(ARARGS) $(NAME) $(OBJS) $(BOBJS)
#
#show :
#	reset
#	@echo $(SRCS)
#	@echo -_-_-_-_-_-_-_-_-_-_-
#	@echo $(OBJS)
#	@echo -_-_-_-_-_-_-_-_-_-_-
#	@echo $(BONUS)
#	@echo -_-_-_-_-_-_-_-_-_-_-
#	@echo $(BOBJS)
#	@echo -_-_-_-_-_-_-_-_-_-_-
#	@echo $(CC) $(CCARGS) -I./ -o $(<:.c=.o)
#	@echo -_-_-_-_-_-_-_-_-_-_-
#	@echo $(AR) $(ARARGS) $(NAME) $(OBJS)
#
#test :
#	gcc ${SRCS} -g -o a.out
#	./a.out ${arg}

.PHONY : clean fclean all re 

# **************************************************************************** #
#     _               _     _ _ _                            _   
# ___| |_ _   _ _ __ (_) __| (_) |_ _   _   _ __   __ _ _ __| |_ 
#/ __| __| | | | '_ \| |/ _` | | __| | | | | '_ \ / _` | '__| __|
#\__ \ |_| |_| | |_) | | (_| | | |_| |_| | | |_) | (_| | |  | |_ 
#|___/\__|\__,_| .__/|_|\__,_|_|\__|\__, | | .__/ \__,_|_|   \__|
#              |_|                  |___/  |_|                   
#
# **************************************************************************** #

spin :
	