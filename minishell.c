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
	{
		rl_redisplay();
	}
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

void	print_cmd(t_cmd **cmd_ptr)
{
	size_t	i;
	size_t	j;
	t_cmd	*cmd;

	cmd = *cmd_ptr;

	j = 0;
	i = 0;
	while (cmd[j].cmd != NULL)
	{
		printf("\nsimple command[%zu]\n", j);
		i = 0;
		while (cmd[j].cmd[i] != 0)
		{
			printf("cmd[%zu]:%s\n", i, cmd[j].cmd[i]);
			i++;
		}
		printf("cmd[%zu]:%s\n", i, cmd[j].cmd[i]);
		i = 0;
		while (cmd[j].redir[i] != 0)
		{
			printf("redir[%zu]:%s\n", i, cmd[j].redir[i]);
			i++;
		}
		printf("redir[%zu]:%s\n\n", i, cmd[j].redir[i]);
		j++;
	}
}

void	print_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("env[%zu]:%s\n", i, array[i]);
		i++;
	}
}

void	enablerawmode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void	initialize_data(t_data *data)
{
	data->read_line = NULL;
	data->token = NULL;
	data->exec.cmd = NULL;
	data->exec.envp = NULL;
	data->exec.pid = NULL;
	data->exec.cmd_count = 0;
}

void	prep_for_re_promt(t_data *data)
{
	ft_freeall(data);
	initialize_data(data);
	//enablerawmode();
	togglesignal(1);
}

void	make_envp(t_data *data, char **envp)
{
	int	envp_status;

	envp_status = ft_arrdup(&data->exec.envp, envp);
	if (envp_status == MALLOC_ERROR)
		exit (MALLOC_ERROR);
	else if (envp_status == NULL_ERROR)
		data->exec.envp = NULL;
	data->exec.exit_code = 0;
}

/* void prompt(t_data *data)
{
	data->read_line = readline("jjsh-1.0$ ");
	if (!data->read_line || !ft_strncmp(data->read_line, "exit", 5))
	{
		free(data->read_line);
		ft_freearr(&data->exec.envp);
		printf("Exiting minishell\n");
		exit (0);
	}
	if (*data.read_line != '\0')
	{
		add_history(data.read_line);
		data.exec.exit_code = check_command_after_pipe(&data);
		if (data.exec.exit_code == 0)
		{
			parse(&data);
			heredoc(&data);
			//free data
			// check_if_one_cmd(&data.exec);
			//builtin(&data);
			//token_print(data.token);
			print_cmd(&data.exec.cmd);
			//print_array(data.exec.envp);
			// ft_freestruct(&data.exec.cmd);
			
			// executor(&data.exec);
			free(data.token);
			free(data.read_line);
		}
	}
} */

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	
	initialize_data(&data);
	make_envp(&data, envp);
	prep_for_re_promt(&data);
	while (data.exec.exit_code >= 0)
	{
		data.read_line = readline ("jjsh-1.0$ ");
		if (!data.read_line || !ft_strncmp(data.read_line, "exit", 5))
		{
			free(data.read_line);
			ft_freearr(&data.exec.envp);
			printf("Exiting minishell\n");
			exit (0);
		}
		if (*data.read_line != '\0')
		{
			add_history(data.read_line);
			data.exec.exit_code = check_command_after_pipe(&data);
			
			printf("exit code: %d\n", data.exec.exit_code);
			printf("g_exit_code: %d\n", g_in_reprompt);
			if (data.exec.exit_code == 0)
			{
				parse(&data);
				//free token
				heredoc(&data);
				//free data
				// check_if_one_cmd(&data.exec);
				//builtin(&data);
				//token_print(data.token);
				print_cmd(&data.exec.cmd);
				//print_array(data.exec.envp);
				// ft_freestruct(&data.exec.cmd);
				
				// executor(&data.exec);
				free(data.token);
				free(data.read_line);
				g_in_reprompt = 0;
			}
		}
	}
	return (0);
}
