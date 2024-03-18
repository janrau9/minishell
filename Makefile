# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 11:38:23 by jberay            #+#    #+#              #
#    Updated: 2024/03/18 11:16:41 by jtu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;92m

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g
RM				=	rm -rf
READLINE_HEADER = ~/.brew/opt/readline/include
READLINE_LIB = ~/.brew/opt/readline/lib

SRCS 			=	minishell.c \
					minishell_utils.c \
					heredoc.c \
					char_iter.c \
					tokenizer.c \
					tokenizer_strs.c \
					tokenizer_redir.c \
					tokenizer_utils.c \
					tokenizer_syntax.c \
					parser.c \
					parser_utils.c \
					parser_token.c \
					builtin.c \
					array_utils.c \
					errors.c \
					frees.c \
					executor/executor.c \
					executor/redirections.c \
					buildin/buildins.c \
					buildin/ft_cd.c \
					buildin/ft_unset.c \



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