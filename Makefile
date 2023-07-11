# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llegrand <llegrand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 14:22:16 by llegrand          #+#    #+#              #
#    Updated: 2023/07/06 19:07:48 by llegrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CCARGS := -Wall -Werror -Wextra

AR := ar
ARARGS := -crs		

SRCS 	= main.c
OBJS := $(SRCS:.c=.o)

NAME := fractol.a

$(NAME) : $(OBJS) libftmlx.a
	$(AR) $(ARARGS) $(NAME) $(OBJS)

build :
	mkdir build

build/libmlx.a : minilibx build
	cd minilibx && $(MAKE)
	cp minilibx/libmlx.a build/

build/libft.a : libft build
	cd libft && $(MAKE)
	cp libft/libft.a build/

libftmlx.a : build/libft.a build/libmlx.a
	cd build && ar -x libft.a && ar -x libmlx.a
	cd build && ar -crs libftmlx.a *.o __.SYMDEF __.SYMDEF\ SORTED
	cd build && rm *.o __.SYMDEF __.SYMDEF\ SORTED
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
