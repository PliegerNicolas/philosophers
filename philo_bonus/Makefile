# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nplieger <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 09:31:21 by nplieger          #+#    #+#              #
#    Updated: 2023/03/02 10:58:46 by nplieger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=		philo_bonus

#------------------------------------------------#
#   PATHS                                        #
#------------------------------------------------#

SRC_DIR				:=		srcs
OBJ_DIR				:=		objs
INC_DIR				:=		includes

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

DEPS				:=		philosophers_bonus \

SRCS				:=		philosophers \
							output/usage \
							output/errors \
							output/philosopher_action \
							utils/ft_isdigit \
							utils/ft_str_is_int \
							utils/ft_atolli \
							utils/ft_atold \
							utils/ft_itoa \
							utils/ft_strlen \
							utils/ft_strjoin \
							utils/generate_sem_name \
							utils/time \
							utils/semaphores \
							utils/free \
							args_verification/verify_args \
							initialization/initialize \
							life/parent \
							life/childs \
							life/philosopher_routine \
							life/philosopher_actions \

DEPS_H				:=		$(addsuffix .h, $(DEPS))
CC_DEPS_H			:=		$(addsuffix $(DEPS_H), $(INC_DIR)/)

SRCS_C				:=		$(addsuffix .c, $(SRCS))
CC_SRCS_C			:=		$(addsuffix $(SRC_DIR)/, $(SRCS_C))

OBJS				:=		$(SRCS_C:%.c=$(OBJ_DIR)/%.o)

#------------------------------------------------#
#   COMMANDS                                     #
#------------------------------------------------#

CC					:=		gcc
AR					:=		ar -rcs
INCS				:=		-I $(INC_DIR) -lpthread
CFLAGS				:=		-Wall -Wextra -Werror -O3
RM					:=		rm -f

#------------------------------------------------#
#   COLORS			                             #
#------------------------------------------------#

COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#

all:				$(NAME)

$(NAME):			$(OBJS)
	$(AR) $(NAME).a $(OBJS)
	$(CC) $(CFLAGS) $(NAME).a -o ./$(NAME)

$(OBJS):			$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(CC_DEPS_H)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean:				clean
	$(RM) $(NAME).a
	$(RM) $(NAME)

re:					fclean all

.PHONY: all clean fclean re
