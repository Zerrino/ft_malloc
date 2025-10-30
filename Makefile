# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zerrino <zerrino@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 12:08:43 by alexafer          #+#    #+#              #
#    Updated: 2025/10/30 21:06:50 by zerrino          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -fPIC
SHARED      := -shared

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
LIBASM_DIR	:= libasm
SRC_DIR		:= srcs
INC_DIR		:= includes
OBJ_DIR		:= .objs

SRCS        := \
    	malloc.c \
    	free.c \
    	realloc.c \
    	show_alloc_mem.c \
		wrappers.c \

#$(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))
OBJS		:= $(SRCS:.c=.o)
SRCS		:=  $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS		:= $(addprefix $(OBJ_DIR)/, $(OBJS))

DEPS		:= $(OBJS:.o=.d)


all: $(NAME) $(SYMLINK)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(SHARED) -o $@ $(OBJS) $(LIBFT)

$(SYMLINK): $(NAME)
	ln -sf $(NAME) $(SYMLINK)

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c -I./$(INC_DIR) $< -o $@


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

