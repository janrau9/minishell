/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:28:19 by jberay            #+#    #+#             */
/*   Updated: 2024/03/22 09:56:00 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_exec *exec, char **cmd)
{
	t_command_entry	command_table[8];
	int				i;

	command_table[0] = (t_command_entry){"cd", ft_cd};
	command_table[1] = (t_command_entry){"echo", ft_echo};
	command_table[2] = (t_command_entry){"env", ft_env};
	command_table[3] = (t_command_entry){"export", ft_export};
	command_table[4] = (t_command_entry){"pwd", ft_pwd};
	command_table[5] = (t_command_entry){"unset", ft_unset};
	command_table[6] = (t_command_entry){"exit", ft_exit};
	command_table[7] = (t_command_entry){NULL, NULL};
	i = 0;

	while (command_table[i].name)
	{
		if (!ft_strncmp(cmd[0], command_table[i].name, \
		ft_strlen(command_table[i].name) + 1))
		{
			return (command_table[i].builtin(exec, cmd));
		}
		i++;
	}
	return (-1);
}
