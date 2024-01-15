# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rofuente <rofuente@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 10:00:52 by dmonjas-          #+#    #+#              #
#    Updated: 2024/01/15 19:24:23 by rofuente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB	=	ar rcs
RM	=	rm -f

###CASA###
#READLINE_DIR = $(shell brew --prefix readline)
#FLAG	=	-lreadline -lhistory -L $(READLINE_DIR)/lib
###42###
READLINE_DIR = /sgoinfre/students/$(USER)/homebrew/opt/readline
FLAG	=	-lreadline -lhistory -L $(READLINE_DIR)/lib

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I ./inc -I ./libft/inc/ -I $(READLINE_DIR)/include
DEBUG	=	-g3 -fsanitize=address

NAME	=	minishell

BUILT	=	ft_cd.c ft_echo.c ft_export.c ft_exutil.c ft_exutil2.c ft_print.c ft_unset.c
PARSE	=	ft_parse.c ft_parse2.c ft_parse3.c ft_parse4.c ft_parse5.c ft_parse_error.c
PIPE	=	ft_pipe.c ft_pipe_utils.c ft_pipe_utils2.c
SRC	=	ft_minishell.c ft_utils.c ft_error.c ft_lst.c ft_utils2.c ft_signal.c ft_system.c ft_path.c ft_utils3.c

SRC_DIR	=	./src/
P_DIR	=	./parse/
B_DIR	=	./builtins/
PI_DIR	=	./pipe/

OBJ_DIR	=	./obj/
OBJ_FILES	=	$(SRC:.c=.o) $(PARSE:.c=.o) $(BUILT:.c=.o) $(PIPE:.c=.o)
OBJ	=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

##########COLORES##########
DEF_COLOR = \033[0;39m
CUT = \033[K
R = \033[31;1m
G = \033[32;1m
Y = \033[33;1m
B = \033[34;1m
P = \033[35;1m
GR = \033[30;1m
END = \033[0m

##########REGLAS##########
all: $(OBJ_DIR) $(NAME)

$(LIBFT) : $(LIBFT_PATH)
	@make -sC $(LIBFT_PATH)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(B_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
$(OBJ_DIR)%.o:$(P_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
$(OBJ_DIR)%.o:$(PI_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FLAG) -o $(NAME)
	@echo "\n$(G)Basic library compiled!$(DEF_COLOR)-> $@\n"

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_BONUS)
	@make clean -sC libft
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@echo "$(R)All .o files removed$(DEF_COLOR)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@make fclean -sC libft
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@echo "$(R)Library .a file removed$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
