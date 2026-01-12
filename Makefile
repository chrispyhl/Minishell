# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpohl <cpohl@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 16:38:39 by craabe            #+#    #+#              #
#    Updated: 2026/01/12 16:38:42 by cpohl            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wextra -Wall -Werror -I includes
LDFLAGS = -lreadline
RM = rm -f

SRC_DIR = src/
MAIN_DIR = $(SRC_DIR)/main/
PAR_DIR = $(SRC_DIR)/parser/
EXE_DIR = $(SRC_DIR)/executor/
GC_DIR = $(SRC_DIR)/gc/
LIBFT_DIR = libft/
OBJ_DIR = obj/

# REMOVE WILDCARDS !!!
# REMOVE WILDCARDS !!!
# REMOVE WILDCARDS !!!
MAIN_FILES = $(notdir $(wildcard $(MAIN_DIR)*.c))
PAR_FILES  = $(notdir $(wildcard $(PAR_DIR)*.c))
EXE_FILES  = $(notdir $(wildcard $(EXE_DIR)*.c))
GC_FILES   = $(notdir $(wildcard $(GC_DIR)*.c))
# REMOVE WILDCARDS !!!
# REMOVE WILDCARDS !!!
# REMOVE WILDCARDS !!!

MAIN_SRC = $(addprefix $(MAIN_DIR), $(MAIN_FILES))
PAR_SRC = $(addprefix $(PAR_DIR), $(PAR_FILES))
EXE_SRC = $(addprefix $(EXE_DIR), $(EXE_FILES))
GC_SRC = $(addprefix $(GC_DIR), $(GC_FILES))

# SRC = $(MAIN_SRC) $(PAR_SRC) $(EXE_SRC) $(GC_SRC)

LIBFT_A = $(LIBFT_DIR)/libft.a

MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
PAR_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PAR_SRC))
EXE_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(EXE_SRC))
GC_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(GC_SRC))
# patsubst replaces src/ with obj/ for every file in list
# not a wildcard since it takes pre-typed file names from SRC variables
OBJ = $(MAIN_OBJ) $(PAR_OBJ) $(EXE_OBJ) $(GC_OBJ)

all: $(NAME)

# to be removed for final submission
pars: $(LIBFT_A) $(PAR_OBJ) $(GC_OBJ)
	@$(CC) $(CFLAGS) $(PAR_OBJ) $(GC_OBJ) $(LIBFT_A) -o pars
	@echo "Built parser."

# to be removed for final submission
exec: $(LIBFT_A) $(EXE_OBJ) $(GC_OBJ)
	@$(CC) $(CFLAGS) $(EXE_OBJ) $(GC_OBJ) $(LIBFT_A) -o exec
	@echo "Built executor."

$(NAME): $(LIBFT_A) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "Built full program."

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
# creates object files in new obj folder on root lvl

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "Cleaned up object files."

# explicit mention of pars and exec can be remoed later
fclean: clean
	@$(RM) $(NAME) pars exec
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "Cleaned up program."

re: fclean all

.PHONY: all clean fclean re pars exec
