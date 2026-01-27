# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craabe <craabe@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/18 10:25:33 by craabe            #+#    #+#              #
#    Updated: 2026/01/27 11:45:04 by craabe           ###   ########.fr        #
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

LIBFT_FILES =	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_lstadd_back_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstmap_bonus.c \
				ft_lstnew_bonus.c \
				ft_lstsize_bonus.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c
SRC_LIBFT = $(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES))

FT_PRINTF_FILES = ft_printf.c \
				hex_print.c \
				hex_utils.c \
				std_print.c \
				std_utils.c
SRC_FT_PRINTF = $(addprefix $(FT_PRINTF_DIR)/, $(FT_PRINTF_FILES))

GNL_FILES =		get_next_line_bonus.c
SRC_GNL = $(addprefix $(GNL_DIR)/, $(GNL_FILES))

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
