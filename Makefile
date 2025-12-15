# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gries <gries@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 16:38:39 by craabe            #+#    #+#              #
#    Updated: 2025/12/15 08:58:38 by gries            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = chrispytalk

CC = cc
CFLAGS = -Wextra -Wall -Werror -Iincludes
LDFLAGS = -lreadline
RM = rm -f

INC_DIR = src/
MAIN_DIR = $(INC_DIR)/main/
PAR_DIR = $(INC_DIR)/parser/
EXE_DIR = $(INC_DIR)/executor/
GC_DIR = $(INC_DIR)/gc/
LIBFT_DIR = libft/
OBJ_DIR = obj/

MAIN_FILES = chrispyshell.c env_list_utils.c
PAR_FILES = 0_parser.c 1_lexer.c 2_expander.c 98_lexer_utils.c 99_list_utils.c
EXE_FILES =
GC_FILES =

MAIN_SRC = $(addprefix $(MAIN_DIR), $(MAIN_FILES))
PAR_SRC = $(addprefix $(PAR_DIR), $(PAR_FILES))
EXE_SRC = $(addprefix $(EXE_DIR), $(EXE_FILES))
GC_SRC = $(addprefix $(GC_DIR), $(GC_FILES))

# SRC = $(MAIN_SRC) $(PAR_SRC) $(EXE_SRC) $(GC_SRC)

LIBFT_A = $(LIBFT_DIR)/libft.a

MAIN_OBJ = $(patsubst $(INC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
PAR_OBJ	= $(patsubst $(INC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PAR_SRC))
EXE_OBJ	= $(patsubst $(INC_DIR)/%.c, $(OBJ_DIR)/%.o, $(EXE_SRC))
GC_OBJ	= $(patsubst $(INC_DIR)/%.c, $(OBJ_DIR)/%.o, $(GC_SRC))
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
