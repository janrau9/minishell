# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 09:33:34 by jberay            #+#    #+#              #
#    Updated: 2024/03/08 14:17:16 by jberay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRCS = ft_isalpha.c \
	  ft_isalnum.c \
	 ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_memset.c \
	ft_bzero.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line.c \
	ft_lstnew_double.c \
	ft_lstadd_back_double.c \

BONUS_SRC = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c

FT_PRINTF_PATH = ft_printf/

FT_PRINTF_SRC = ft_print_char.c \
		ft_print_nbr.c \
		ft_print_str.c \
		ft_printf.c \
		ft_print_pointer.c

FT_PRINTF_SRCS = $(addprefix $(FT_PRINTF_PATH), $(FT_PRINTF_SRC))

OBJS := $(SRCS:.c=.o)

BONUS_OBJS := $(BONUS_SRC:.c=.o)

FT_PRINTF_OBJS := $(FT_PRINTF_SRCS:.c=.o)

LIBH = libft.h

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

LIBC = ar -rcs

RM = rm -f

%.o: %.c compiling
	@cc $(CFLAGS) -c $< -o $@  -I.

$(NAME): $(OBJS) $(FT_PRINTF_OBJS) 
	@$(LIBC) $(NAME) $(OBJS) $(FT_PRINTF_OBJS)
	@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"	

bonus: .bonus

.bonus: $(BONUS_OBJS)
	@ar -rus $(NAME) $(BONUS_OBJS)
	@touch .bonus

all: $(NAME) compiling

compiling:
	@echo "$(GREEN)Compiling libft...$(DEF_COLOR)"

clean: 
	@$(RM) $(OBJS) $(BONUS_OBJS) $(FT_PRINTF_OBJS) .bonus

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Cleaned!$(DEF_COLOR)"	

re: fclean all

.PHONY: all clean fclean re bonus compiling