# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gries <gries@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 10:25:33 by craabe            #+#    #+#              #
#    Updated: 2025/10/30 10:50:04 by gries            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Werror -Wall -Wextra

INC_DIR = src
LIBFT_DIR = $(INC_DIR)/libft_basic
FT_PRINTF_DIR = $(INC_DIR)/ft_printf
GNL_DIR = $(INC_DIR)/get_next_line
# which directories to look for

CPPFLAGS = -I$(INC_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR)
# where to find headers

AR = ar
# archiver: manages static libraries (.a files)
ARFLAGS = rcs
# r = replace, c = create, i = index
# support $(AR), helps with archiving
RAN = ranlib
# supports linker, ensures that lib index is up-to-date
# this Makefile has no linking, but $(RAN) supports external linking later

RM = rm -f

SRC_LIBFT = $(wildcard $(LIBFT_DIR)/*.c)
SRC_FT_PRINTF = $(wildcard $(FT_PRINTF_DIR)/*.c)
SRC_GNL = $(wildcard $(GNL_DIR)/*.c)
# wildcard makes *.c work, otherwise make would look for literal file "*.c"

SRC = $(SRC_LIBFT) $(SRC_FT_PRINTF) $(SRC_GNL)
# adds the source together

OBJ := $(SRC:.c=.o)
# turn all .c files into o files

HEADER = $(INC_DIR)/libft.h

all: $(NAME)
# "make all" is the same as "make" in ths case, as all is the first command
# all depends on $(NAME) -> checks if $(NAME) exists and is up-to-date
# if it doesn't exist or if some .o files have been updated in the meantime -> creates
# creates .a file using this logic vvv

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $@ $^
	@$(RAN) $@
# $@ = target name, here: libft.a
# $^ = target prerequisite, here $(OBJ)

%.o: %.c $(HEADER)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

dist: all
	@$(RM) $(OBJ)
# custom command to make a clean rebuild and remove those\
# annoying .o files afterwards

.PHONY: all clean fclean re dist
