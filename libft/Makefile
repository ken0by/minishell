LIB = ar rcs
RM = rm -rf

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

NAME = libft.a

INC = ./inc/
SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRC_FILES = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strlen.c ft_tolower.c \
ft_toupper.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_strchr.c ft_strrchr.c ft_strnstr.c \
ft_strncmp.c ft_memchr.c ft_memcmp.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c \
ft_striteri.c ft_itoa.c ft_split.c ft_strjoin_gnl.c ft_strlcat_gnl.c get_next_line.c \
ft_strchr_gnl.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
ft_putnbr_base.c ft_putnbr_base_void.c ft_printf.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

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

all: obj $(NAME)

$(NAME): $(OBJS)
	@$(LIB) $(NAME) $(OBJS)
	@echo "\n$(G)Basic library compiled!$(DEF_CCOLOR)\n"
obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@ 
clean:
	@$(RM) $(OBJS) 
fclean:
	@$(RM) $(NAME) $(OBJ_DIR)
re: clean all

.PHONY: all clean fclean re
