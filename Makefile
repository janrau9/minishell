# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 11:38:23 by jberay            #+#    #+#              #
#    Updated: 2024/03/08 09:06:02 by jberay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;92m

NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -L/home/linuxbrew/.linuxbrew/opt/readline/lib -I/home/linuxbrew/.linuxbrew/opt/readline/include -I./includes -I./libft/includes -g
RM				=	rm -rf

SRCS 			=	minishell.c \
					char_iter.c \
					tokenizer.c \
					tokenizer_utils.c \
					tokenizer_utils2.c \
					parser.c \
					parser_utils.c \
					token_iter.c \
						
OBJS			=	$(SRCS:%.c=%.o)

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

all:				$(NAME)

$(NAME):			$(LIBFT) $(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME) 
					@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"
					
%.o:%.c
					@$(CC) $(CFLAGS) -c $< -o $@		
							
$(LIBFT):
					@make -C $(LIBFT_PATH) all bonus

clean:
					@make -C $(LIBFT_PATH) clean
					@$(RM) $(OBJS)

fclean:				clean
					@make -C $(LIBFT_PATH) fclean
					@$(RM) $(NAME)
					
re:					fclean all

.PHONY:				all bonus clean fclean re libft