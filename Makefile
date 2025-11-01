# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 12:08:43 by alexafer          #+#    #+#              #
#    Updated: 2025/10/31 11:11:16 by alexafer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -fPIC
SHARED      := -shared

NASM		:= nasm
NFLAGS		:= -felf64

ifeq ($(shell uname -s),Darwin)
	SHARED := -dynamiclib
endif

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME        := libft_malloc_$(HOSTTYPE).so
SYMLINK     := libft_malloc.so
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a
SRC_DIR		:= srcs
INC_DIR		:= includes
OBJ_DIR		:= .objs

SRCS		:= $(shell find $(SRC_DIR) -type f -name '*.s')

#$(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))
#OBJS		:= $(SRCS:.c=.o)
#SRCS		:=  $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS		:= $(SRCS:%=$(OBJ_DIR)/%.o)

DEPS		:= $(OBJS:.o=.d)


all: $(NAME) $(SYMLINK)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(SHARED) -o $@ $(OBJS) $(LIBFT)

$(SYMLINK): $(NAME)
	ln -sf $(NAME) $(SYMLINK)

-include $(DEPS)

$(OBJ_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(NASM) $(NFLAGS) $< -o $@


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(DEPS)

mclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(SYMLINK)

re: fclean all

Mclean: mclean

.PHONY: all clean fclean mclean re Mclean

