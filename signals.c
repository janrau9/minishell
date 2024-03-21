/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:38:47 by jberay            #+#    #+#             */
/*   Updated: 2024/03/21 10:50:22 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (ft_strncmp(rl_prompt, "> ", 3) == 0)
		{
			g.in_reprompt = 1;
			printf("\n");
			close (STDIN_FILENO);
		}
		if (g.in_reprompt == 0)
			printf("\n");
		if (g.in_heredoc == 1)
			return ;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
		rl_redisplay();
}

void	togglesignal(int mode)
{
	if (mode == 1)
	{
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}

}

void	enablerawmode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}