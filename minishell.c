/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:41:38 by jberay            #+#    #+#             */
/*   Updated: 2024/03/21 14:46:29 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_exec(t_exec *exec)
{
	exec->read_line = NULL;
	exec->token = NULL;
	exec->cmd = NULL;
	exec->pid = NULL;
	exec->cmd_count = 0;
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

void	prep_for_promt(t_exec *exec)
{
	ft_freeall_n_envp(exec);
	initialize_exec(exec);
	prompt(exec);
}

void	prompt(t_exec *exec)
{
	exec->read_line = readline ("jjsh-1.0$ ");
	if (!exec->read_line || !ft_strncmp(exec->read_line, "exit", 5))
	{
		ft_freearr(&exec->envp);
		printf("Exiting minishell\n");
		exit (0);
	}
	if (*exec->read_line != '\0')
	{
		add_history(exec->read_line);
		exec->exit_code = check_command(exec);
		tokenizer(exec);
		//token_print(exec->token);
		exec->exit_code = check_syntax(exec->token);
		if (exec->exit_code == 0)
		{
			if (parse(exec) == 0)
			{
				//builtin(exec);
				//print_cmd(&exec->cmd);
				//print_array(exec->envp);
				executor(exec);
				g.in_reprompt = 0;
			}
		}
	}
	prep_for_promt(exec);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;

	(void)argc;
	(void)argv;
	(void)envp;

	enablerawmode();
	togglesignal(1);
	initialize_exec(&exec);
	make_envp(&exec, envp);
	prompt(&exec);
	exit (0);
}
