/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:38:47 by jberay            #+#    #+#             */
/*   Updated: 2024/03/26 12:16:24 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	togglesignal(t_signal mode)
{
	if (mode == DEFAULT)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (mode == HANDLER)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}

void	togglerawmode(int mode)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	if (mode)
		raw.c_lflag &= ~ECHOCTL;
	else
		raw.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
