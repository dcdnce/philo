# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 11:09:43 by pforesti          #+#    #+#              #
#    Updated: 2022/04/07 10:17:49 by pforesti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BG_RD	= \033[48;2;237;66;69m
BG_GR	= \033[48;2;0;194;60m
BG_BL	= \033[48;2;88;101;242m
FG_WH	= \033[38;2;255;255;255m
FG_BK	= \033[38;2;0;0;0m
BOLD	= \033[1m
NOCOL	= \033[0m

###############################################################################
###############################################################################

SRCS = srcs/lists.c \
		srcs/main.c \
		srcs/utils.c \
		srcs/routine.c \
		srcs/display.c \
		srcs/init.c \
		srcs/time.c \

OBJS = $(SRCS:%.c=%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

INCLUDES = -Iincludes/

NAME = philo

%.o	:	%.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

###############################################################################
###############################################################################

$(NAME):	$(OBJS)
		@$(CC) -o $(NAME) $^
		@echo "$(BG_GR)$(FG_WH) $(NAME) done $(NOCOL)"

all:	$(NAME)

clean:
		@rm -f $(OBJS)
		@echo "$(BG_RD)$(FG_WH) $(NAME) clean $(NOCOL)"

fclean:	clean
		@rm -f $(NAME)
		@echo "$(BG_RD)$(FG_WH) $(NAME) fclean $(NOCOL)"

re: fclean all

.PHONY:	all clean fclean all

