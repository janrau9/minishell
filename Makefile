# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 11:38:23 by jberay            #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/03/21 13:04:02 by jtu              ###   ########.fr        #
=======
#    Updated: 2024/03/21 10:08:15 by jberay           ###   ########.fr        #
>>>>>>> eb9656baa1037f2c6197550243c81a34eae62428
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;92m

NAME			=	minishell

CC				=	cc
<<<<<<< HEAD
CFLAGS			=	-Wall -Wextra -Werror -g#-fsanitize=address
=======
CFLAGS			=	-Wall -Wextra -Werror
>>>>>>> eb9656baa1037f2c6197550243c81a34eae62428
RM				=	rm -rf
READLINE_HEADER = ~/.brew/opt/readline/include
READLINE_LIB = ~/.brew/opt/readline/lib

SRCS 			=	minishell.c \
					minishell_utils.c \
					heredoc.c \
					heredoc_utils.c \
					char_iter.c \
					tokenizer.c \
					tokenizer_strs.c \
					tokenizer_redir.c \
					tokenizer_utils.c \
					tokenizer_syntax.c \
					parser.c \
					parser_utils.c \
					parser_token.c \
					signals.c \
					builtin.c \
					array_utils.c \
					errors.c \
					frees.c \
					debug.c \
					executor/executor.c \
					executor/redirections.c \
<<<<<<< HEAD
					builtin/builtins.c \
					builtin/ft_cd.c \
					builtin/ft_unset.c \


=======
					buildin/buildins.c \
					debug.c
					
						
>>>>>>> eb9656baa1037f2c6197550243c81a34eae62428
OBJS			=	$(SRCS:%.c=%.o)

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

all:				$(NAME)

$(NAME):			$(LIBFT) $(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -L $(READLINE_LIB) -I$(READLINE_HEADER)  -o $(NAME)
					@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"

%.o:%.c
					@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
					@make -C $(LIBFT_PATH) all

clean:
					@make -C $(LIBFT_PATH) clean
					@$(RM) $(OBJS)

fclean:				clean
					@make -C $(LIBFT_PATH) fclean
					@$(RM) $(NAME)

re:					fclean all

.PHONY:				all bonus clean fclean re libft