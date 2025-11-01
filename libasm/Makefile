# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 16:07:48 by alexafer          #+#    #+#              #
#    Updated: 2025/10/31 15:45:22 by alexafer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NASM = nasm
NASMFLAGS = -f elf64
SRC_DIR = .
INC_DIR = .

SRCC = ft_create_elem.c

SRCS =  ft_write.s \
		ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s \
		ft_read.s \
		ft_strdup.s \


MAIN = main.c

BONUS = ft_list_push_front.s \
		ft_list_size.s \
		ft_list_sort.s \
		ft_atoi_base.s \
		ft_list_remove_if.s

OBJS := $(addprefix $(SRC_DIR)/, $(SRCS:.s=.o))
OBJS += $(addprefix $(SRC_DIR)/, $(SRCC:.c=.o))


BONUS_OBJ = $(addprefix $(SRC_DIR)/, $(BONUS:.s=.o))
BONUS_OBJ += $(addprefix $(SRC_DIR)/, $(SRCC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $^

bonus: $(BONUS_OBJ)
	ar -rcs $(NAME) $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.s
	$(NASM) $(NASMFLAGS) -I./. $< -o $@

compile:
	$(CC) $(CFLAGS) -I./. $(MAIN) $(NAME)
	#@./a.out

clean:
	rm -f $(OBJS) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)
	#rm -r a.out

re: fclean all

.PHONY: all clean fclean re bonus

