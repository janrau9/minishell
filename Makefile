# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 11:38:23 by jberay            #+#    #+#              #
#    Updated: 2024/04/11 12:55:40 by jberay           ###   ########.fr        #
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
					minishell_envp.c \
					minishell_history.c \
					heredoc.c \
					heredoc_utils.c \
					heredoc_tokenizer.c \
					char_iter.c \
					expander.c \
					tokenizer.c \
					tokenizer_strs.c \
					tokenizer_redir.c \
					tokenizer_utils.c \
					tokenizer_syntax.c \
					parser.c \
					parser_utils.c \
					parser_tokenstrs.c \
					parser_tokendollar.c \
					signals.c \
					array_utils.c \
					errors.c \
					frees.c \
					executor/executor.c \
					executor/redirections.c \
					executor/error_exit.c \
					executor/pipes.c \
					executor/check_cmd.c \
					builtin/builtins.c \
					builtin/ft_cd.c \
					builtin/ft_unset.c \
					builtin/ft_export.c \
					builtin/ft_exit.c \


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

.PHONY:				all clean fclean re libft