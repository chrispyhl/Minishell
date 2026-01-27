# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craabe <craabe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 16:38:39 by craabe            #+#    #+#              #
#    Updated: 2026/01/27 11:38:23 by craabe           ###   ########.fr        #
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

MAIN_FILES = 0_chrispyshell.c \
			1_env_list_utils.c \
			2_filepath_handler.c \
			3_signal_handler.c \
			4_general_utils.c

PAR_FILES = 0_parser.c \
			1_lexer.c \
			2_expander.c \
			3_cmd_list.c \
			4_handle_token.c \
			5_syntax_validation.c \
			6_lexer_utils.c \
			7_expander_utils.c \
			8_expander_utils_2.c \
			9_cmd_list_utils.c \
			10_file_list_utils.c \
			11_token_list_utils.c

EXE_FILES = 0_executor.c \
			1_single_cmd.c \
			2_piping.c \
			3_redirections.c \
			4_heredoc.c \
			9_0_1_more_utils.c \
			9_0_utils.c \
			9_1_env_conversion.c \
			9_2_1more_env_utils.c \
			9_2env_utils.c \
			9_3_1_redir_utils.c \
			9_3exec_utils.c \
			9_4_2heredoc_utils.c \
			9_4_heredoc_utils.c \
			9_b_utils.c \
			b_handle_builtins.c \
			b_handle_more_builtins.c \
			e_handle_externals.c

GC_FILES = ft_malloc.c \
			gc_itoa.c \
			gc_libft.c \
			gc_split.c \
			gc_utils.c

MAIN_SRC = $(addprefix $(MAIN_DIR), $(MAIN_FILES))
PAR_SRC = $(addprefix $(PAR_DIR), $(PAR_FILES))
EXE_SRC = $(addprefix $(EXE_DIR), $(EXE_FILES))
GC_SRC = $(addprefix $(GC_DIR), $(GC_FILES))

LIBFT_A = $(LIBFT_DIR)/libft.a

MAIN_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
PAR_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(PAR_SRC))
EXE_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(EXE_SRC))
GC_OBJ	= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(GC_SRC))
# patsubst replaces src/ with obj/ for every file in list
# not a wildcard since it takes pre-typed file names from SRC variables
OBJ = $(MAIN_OBJ) $(PAR_OBJ) $(EXE_OBJ) $(GC_OBJ)

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LDFLAGS) -o $(NAME)
	@echo "Get chrispy."

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

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "Cleaned up program."

re: fclean all

.PHONY: all clean fclean re
