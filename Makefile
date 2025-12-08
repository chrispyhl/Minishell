# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gries <gries@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 16:38:39 by craabe            #+#    #+#              #
#    Updated: 2025/12/08 15:48:14 by gries            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = chrispytalk

CC = cc
CFLAGS = -Wextra -Wall -Werror -Iincludes
RM = rm -f

INC_DIR = src
PAR_DIR = $(INC_DIR)/parser
EXE_DIR = $(INC_DIR)/executor
GC_DIR = $(INC_DIR)/gc
LIBFT_DIR = libft
OBJ_DIR = obj

PAR_SRC = $(PAR_DIR)/0_parser.c
EXE_SRC =
GC_SRC =

SRC = $(PAR_SRC) $(EXE_SRC) $(GC_SRC)

LIBFT_A = $(LIBFT_DIR)/libft.a

PAR_OBJ	= $(patsubst $(INC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PAR_SRC))
EXE_OBJ	= $(patsubst $(INC_DIR)/%.c, $(OBJ_DIR)/%.o, $(EXE_SRC))
GC_OBJ	= $(patsubst $(INC_DIR)/%.c, $(OBJ_DIR)/%.o, $(GC_SRC))
# patsubst replaces src/ with obj/ for every file in list
# not a wildcard since it takes pre-typed file names from SRC variables
OBJ = $(PAR_OBJ) $(EXE_OBJ) $(GC_OBJ)

all: $(NAME)

pars: $(LIBFT_A) $(PAR_OBJ) $(GC_OBJ)
	@$(CC) $(CFLAGS) $(PAR_OBJ) $(GC_OBJ) $(LIBFT_A) -o pars
	@echo "Built parser."

exec: $(LIBFT_A) $(EXE_OBJ) $(GC_OBJ)
	@$(CC) $(CFLAGS) $(EXE_OBJ) $(GC_OBJ) $(LIBFT_A) -o exec
	@echo "Built executor."

$(NAME): $(LIBFT_A) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -o $(NAME)
	@echo "Built full program."

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
# creates object files in new obj folder on root lvl

clean:
	@$(RM) -r $( OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "Cleaned up object files."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "Cleaned up program."

re: fclean all

.PHONY: all clean fclean re pars exec
