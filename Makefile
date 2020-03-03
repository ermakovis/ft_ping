# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcase <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 11:31:10 by tcase             #+#    #+#              #
#    Updated: 2019/11/12 20:41:21 by tcase            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=ft_ping

CC=			gcc
FLAGS=		#-Wall -Werror -Wextra

SRC_DIR=	./src
OBJ_DIR=	./obj
LIB_DIR=	./lib

SRC_NAME= 	main.c\
			misc.c

SRC= 		$(addprefix $(OBJ_DIR)/, $(SRC_NAME:.c=.o))
OBJ=		$(SRC) $(UTILS)
INC =		-I ./inc -I $(LIB_DIR)/includes

all: $(NAME)

$(NAME) : $(OBJ)
	@make -s -C $(LIB_DIR)
	@$(CC) $(OBJ) -o $(NAME) $(INC) $(LIB_DIR)/libft.a
	@printf "\033[0m\033[35m%-40s\033[1m\033[34m%s\033[0m\n" "Compilation" "Done"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(FLAGS) $(INC) 
	@printf "\033[0m\033[36m%-40s\033[1m\033[34m%s\033[0m\n" "$(notdir $<)" "Done"

clean:
	@rm -f $(OBJ)
	@printf "\033[0m\033[33m%-40s\033[1m\033[34m%s\033[0m\n" "Clean" "Done"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s -C $(LIB_DIR)
	@printf "\033[0m\033[33m%-40s\033[1m\033[34m%s\033[0m\n" "Full Clean" "Done"

test: all
	sudo ./$(NAME) ya.ru

re:	clean all

.PHONY: all, clean, fclean, re
