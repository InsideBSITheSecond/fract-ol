# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: insidebsi <insidebsi@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 14:22:16 by llegrand          #+#    #+#              #
#    Updated: 2023/07/19 17:33:11 by insidebsi        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CCARGS := #-Wall -Werror -Wextra
LXARGS = -lX11 -lXxf86vm -lXext 

AR := ar
ARARGS := -crs		

MLX = minilibx-linux
OSX_BULLSHIT = #__.SYMDEF __.SYMDEF\ SORTED

SRCS := srcs/main.c srcs/color.c srcs/fractal.c srcs/math.c
INCLS := includes/colors.h includes/fractol.h
NAME := fractol.out

$(NAME) : libft.a $(SRCS) $(INCLS)
	$(CC) $(SRCS) $(CCARGS) -Iincludes -L. -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -O3 -o $(NAME)

exe : $(NAME)
	./$(NAME) 50

build :
	mkdir build

build/libmlx.a : minilibx build
	cd $(MLX) && $(MAKE)
	cp $(MLX)/libmlx.a build/

libft.a : libft build
	cd libft && $(MAKE)
	cp libft/libft.a .

libftmlx.a : build/libft.a build/libmlx.a
	cd build && ar -x libft.a && ar -x libmlx.a
	cd build && ar -crs libftmlx.a *.o $(OSX_BULLSHIT)
	cd build && rm *.o $(OSX_BULLSHIT)
	cp build/libftmlx.a .
	
%.o : %.c
	$(CC) $(CCARGS) -I ./includes -c $< -o ${<:.c=.o}

clean :
	rm -f $(OBJS) $(BOBJS)
	cd libft && $(MAKE) clean

fclean : clean
	rm -f $(NAME) libftmlx.a
	rm -rf build
	cd libft && $(MAKE) fclean

all : $(NAME)

re :	fclean all

bonus : $(OBJS) $(BOBJS)
	$(AR) $(ARARGS) $(NAME) $(OBJS) $(BOBJS)

show :
	reset
	@echo $(SRCS)
	@echo -_-_-_-_-_-_-_-_-_-_-
	@echo $(OBJS)
	@echo -_-_-_-_-_-_-_-_-_-_-
	@echo $(BONUS)
	@echo -_-_-_-_-_-_-_-_-_-_-
	@echo $(BOBJS)
	@echo -_-_-_-_-_-_-_-_-_-_-
	@echo $(CC) $(CCARGS) -I./ -o $(<:.c=.o)
	@echo -_-_-_-_-_-_-_-_-_-_-
	@echo $(AR) $(ARARGS) $(NAME) $(OBJS)

test :
	gcc ${SRCS} -g -o a.out
	./a.out ${arg}

.PHONY : clean fclean all re 
