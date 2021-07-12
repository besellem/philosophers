# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: besellem <besellem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/25 01:10:15 by besellem          #+#    #+#              #
#    Updated: 2021/07/12 11:09:03 by besellem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	philo_bonus

## Main directories
BUILD_DIR	:=	.build
SRCS_DIR	:=	srcs
INCS		:=	-I incs
SUB_DIR		:=	srcs
OBJ_DIR 	:=	$(BUILD_DIR)/obj
DIRS		:=	$(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))


## Main srcs
SRCS		:=	alive_checks.c \
				dress_the_table.c \
				life_steps.c \
				main.c \
				memory_management.c \
				print_status.c \
				semaphore_utils.c \
				utils.c
# SRCS		:=	$(addprefix srcs/, $(SUB_SRCS))


## Objects
OBJS 		:=	$(SRCS:%.c=$(OBJ_DIR)/%.o)


## Commands
CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -g3 -fsanitize=thread
RM			:=	rm -f


# Colors
CLR_COLOR	:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m


## Compilation
$(NAME):	$(OBJS)
			@echo "Creating $(RED_COLOR)$@ $(CLR_COLOR)..."
			@$(CC) $(CFLAGS) $(INCS) $^ -o $@ -lpthread
			@echo "$(GREEN)Compilation $(YELLOW)of $(RED)$@ $(BLUE)done$(CLR_COLOR)"

all:		$(NAME)

bonus:		all

clean:
			@ echo "Deleting $(CYAN)philo $(CLR_COLOR)objs ..."
			@ $(RM) $(OBJS)
			@ rm -rf $(BUILD_DIR)

fclean:		clean
			@ echo "Deleting $(CYAN)philo $(CLR_COLOR)binary ..."
			@ $(RM) $(NAME)

re:			fclean all

$(BUILD_DIR):
			@ echo "Creating $(RED)$@ $(CLR_COLOR)..."
			@ mkdir $@ $(DIRS)

$(OBJ_DIR)/%.o:$(SRCS_DIR)/%.c ./incs/philo_bonus.h | $(BUILD_DIR)
			@ echo "Compiling $(YELLOW)$< $(CLR_COLOR)..."
			@ $(CC) $(CFLAGS) -c $< -o $@ $(INCS)

.PHONY:		all clean fclean re
