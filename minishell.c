/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:41:38 by jberay            #+#    #+#             */
/*   Updated: 2024/03/15 15:04:34 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	g_in_reprompt;

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (ft_strncmp(rl_prompt, "> ", 3) == 0)
		{
			g_in_reprompt = 1;
			printf("\n");
			close (STDIN_FILENO);
		} 
		if (g_in_reprompt == 0)
			printf("\n");
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

void	initialize_exec(t_exec *exec)
{
	exec->read_line = NULL;
	exec->token = NULL;
	exec->cmd = NULL;
	exec->pid = NULL;
	exec->cmd_count = 0;
}

void	prep_for_next_promt(t_exec *exec)
{
	ft_freeall_n_envp(exec);
	initialize_exec(exec);
	enablerawmode();
	togglesignal(1);
}

void	make_envp(t_exec *exec, char **envp)
{
	int	envp_status;

	
	envp_status = ft_arrdup(&exec->envp, envp);
	if (envp_status == MALLOC_ERROR)
		exit (MALLOC_ERROR);
	else if (envp_status == NULL_ERROR)
		exec->envp = NULL;
	exec->exit_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;

	(void)argc;
	(void)argv;
	(void)envp;
	
	initialize_exec(&exec);
	make_envp(&exec, envp);
	prep_for_next_promt(&exec);
	while (exec.exit_code >= 0)
	{
		exec.read_line = readline ("jjsh-1.0$ ");
		if (!exec.read_line || !ft_strncmp(exec.read_line, "exit", 5))
		{
			ft_freearr(&exec.envp);
			printf("Exiting minishell\n");
			exit (0);
		}
		if (*exec.read_line != '\0')
		{
			add_history(exec.read_line);
			exec.exit_code = check_command_after_pipe(&exec);
			if (exec.exit_code == 0)
			{
				parse(&exec);
				//free token
				//free data
				//print_array(exec.envp);
				builtin(&exec);
				print_cmd(&exec.cmd);
				// ft_freestruct(&exec.cmd);
				executor(&exec);
				free(exec.token);
				free(exec.read_line);
				g_in_reprompt = 0;
			}
		}
	}
	return (0);
}
