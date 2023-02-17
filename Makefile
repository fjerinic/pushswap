# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 16:18:42 by fjerinic          #+#    #+#              #
#    Updated: 2023/02/17 16:25:07 by fjerinic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/ 

# place all source files here
SRC = 	$(SRC_DIR)form_stack.c \
		$(SRC_DIR)input.c \
		$(SRC_DIR)input2.c \
		$(SRC_DIR)main.c \
		$(SRC_DIR)move1.c \
		$(SRC_DIR)move2.c \
		$(SRC_DIR)push.c \
		$(SRC_DIR)rotate1.c \
		$(SRC_DIR)rotate2.c \
		$(SRC_DIR)sorting1.c \
		$(SRC_DIR)sorting2.c \
		$(SRC_DIR)utils1.c

# takes all named source files and converts them to .o files in the /obj directory
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# define compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -I $(INC_DIR)

# prevents rules from being considered as files
.PHONY: all clean fclean re

all: $(NAME)

# creates subdirectory /obj
$(OBJ_DIR):
	@mkdir $@

# makes sure to make a /obj dir before compiling .o files
$(OBJ): | $(OBJ_DIR)

# compiles .c files into .o files and puts them in the /obj folder
$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

# compiles all object files and builds executable file 'pipex'
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@


# removes all object files and the /obj directory and cleans libft
clean:
	rm -f $(OBJ)
	rmdir $(OBJ_DIR)

# calls 'clean' and removes the executable
fclean: clean
	$(MAKE) fclean -C
	rm -f $(NAME)

# re-makes the whole compilation from scratch
re: fclean all