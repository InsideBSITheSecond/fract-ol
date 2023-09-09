# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 14:22:16 by llegrand          #+#    #+#              #
#    Updated: 2023/09/09 16:13:13 by llegrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# general:
# make re not working as intended (because make parallelism)
# try fresh runs on osx & lnx

# controls improvements:
# NEED TO MAKE IT SO WE CAN DRAG
# MIDDLE MOUSE CENTER ON MUOSE POS
# KEY REPEAT

# misc:
# smooth iter delimitations
# graph only iter display mode with imaginary locking
# auto zoom
# cool mandelbrot POI using cursor shape
# BUDDAH MODE
# ^ https://www.youtube.com/watch?v=wUlVFYJIUNA&list=PLPn28kZnbmugSaqAS_-pnLxjYte957r27&index=5 v
# NEWTON FRACT
#
# done
# dtoa for debug mode
# iter display modes (line/node/full/none)
# rework colors (gradient provider https://cssgradient.io/)
# fix strformat from libft (leaking)
#
# refused
# dynamic iterations (not precise enough)

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
CCARGS := -Wall -Werror -Wextra -O3

# archive configs
AR := ar
ARARGS := -crs		


# linux-specific compiler args
LNXARGS := -Iincludes -L. -lft -Lmlx_lnx -lmlx_lnx -L/usr/lib -Imlx_lnx -lXext -lX11 -lm -lz -lpthread
#LNXINCL := includes/keycodes_lnx.h

# osx-specific compiler args
OSXARGS := -Iincludes -L. -lft -Lmlx_osx -lmlx_osx -L/usr/lib -Imlx_osx -framework OpenGL -framework AppKit -lm -lz -lpthread
#OSXINCL := includes/keycodes_osx.h

# source files
SRCS := main.c srcs/palette.c srcs/linear_mapping.c srcs/debug.c srcs/color.c srcs/controls.c srcs/coordinates.c srcs/fractal.c srcs/hooks.c srcs/lifecycle.c srcs/render.c srcs/shapes.c srcs/vector_advanced.c srcs/vector_basics.c srcs/worker.c

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

# main program
$(NAME) : libft.a lib$(MLX).a $(SRCS) $(INCLS)
	$(CC) $(SRCS) $(CCARGS) -o $(NAME)

# compile main program and run it
exe : $(NAME)
	./$(NAME) 50

dep : libft.a lib$(MLX).a
	
# libft compilation
libft.a : libft/Makefile
	cd libft && $(MAKE) -j16
	cp libft/libft.a .

# get libft submodule from my github
libft/Makefile :
	git submodule update --init libft

# compile mlx
lib$(MLX).a : $(MLX)/Makefile
	cd $(MLX) && $(MAKE) -j16 CFLAGS+=-w
	cp $(MLX)/libmlx.a ./lib$(MLX).a

# get mlx_osx from intra CDN
mlx_osx/Makefile :
	wget https://cdn.intra.42.fr/document/document/12993/minilibx_opengl.tgz
	tar -Zxvf minilibx_opengl.tgz
	mv minilibx_opengl_20191021 mlx_osx
	rm minilibx_opengl.tgz

# get mlx_lnx submodule from 42Paris github 
mlx_lnx/Makefile :
	git submodule update --init mlx_lnx

# partial clean
clean :
	cd libft && $(MAKE) clean
	cd $(MLX) && $(MAKE) clean

# full clean (mlx dont have an fclean target so we do it ourselves)
fclean : clean
	rm -f $(NAME) libft.a lib$(MLX).a
	cd libft && $(MAKE) fclean
	cd $(MLX) && $(MAKE) clean
	rm -f $(MLX)/libmlx.a

all : $(NAME)

# recompile
re : fclean all

norme :
	norminette srcs libft includes -R CheckDefine

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
















.PHONY : clean fclean all re 
