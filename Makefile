# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craabe <craabe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 16:38:39 by craabe            #+#    #+#              #
#    Updated: 2025/12/05 18:04:00 by craabe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = chrispytalk

CC = cc
CFLAGS = -Wextra -Wall -Werror -Iincludes
RM = rm -f

INC_DIR = src
PAR_DIR = $(INC_DIR)/parser
EXE_DIR = $(INC_DIR)/executor
MS_DIR = obj
LIBFT_DIR = libft
GC_DIR = $(INC_DIR)/gc

LIBFT_A = $(LIBFT_DIR)/libft.a
PAR_SRC = $(wildcard $(PAR_DIR)/*.c)
EXE_SRC = $(wildcard $(EXE_DIR)/*.c)
GC_SRC = $(wildcard $(GC_DIR)/*.c)

PAR_OBJ = $(PAR_DIR)/0_parser.c
EXE_OBJ =
GC_OBJ = $(GC_DIR)/ft_malloc.c
# patsubst replaces src/ with obj/ for every file in list
OBJ = $(PAR_OBJ) $(EXE_OBJ) $(GC_OBJ)

HEADER = $(wildcard includes/*.h)

all: $(NAME)

pars: $(LIBFT_A) $(PAR_OBJ) $(GC_OBJ)
	@$(CC) $(PAR_OBJ) $(GC_OBJ) $(LIBFT_A) -o pars
	@echo "Built parser."

exec: $(LIBFT_A) $(EXE_OBJ) $(GC_OBJ)
	@$(CC) $(EXE_OBJ) $(GC_OBJ) $(LIBFT_A) -o exec
	@echo "Built executor."

$(NAME): $(LIBFT_A) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT_A) -o $(NAME)
	@echo "Built full program."

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(MS_DIR)/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
# creates object files in new obj folder on root lvl

clean:
	@$(RM) -r $(MS_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "Cleaned up object files."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "Cleaned up program."

re: fclean all

.PHONY: all clean fclean re pars exec
