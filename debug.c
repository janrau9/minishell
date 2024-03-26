#include "minishell.h"

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

/* prints token array for debugging */
void	token_print(t_token *token)
{
	size_t	i;

	i = 0;
	printf("Printing token array\n");
	while (token[i].type != EOL_TOKEN)
	{
		printf("token typ[%zu]:%d\n", i, token[i].type);
		printf("token len[%zu]:%zu\n", i, token[i].location.len);
		printf("token sta[%zu]:%s\n", i, token[i].location.start);
		i++;
	}
}


/* ~ = $HOME
	~+ = $PWD
	~- = $OLDPWD */
/* char	*ft_expand_tilde(t_exec *exec, char *key)
{
	char	*tmp;

	if (ft_strncmp(key, "~", 1) == 0)
	{
		tmp = key;
		if (ft_strlen(key) == 1)
			key = ft_strdup("HOME=");
		else if (ft_strlen(key) == 2 && key[1] == '+')
			key = ft_strdup("PWD=");
		else if (ft_strlen(key) == 2 && key[1] == '-')
			key = ft_strdup("OLDPWD=");
		free(tmp);
		if (!key)
			ft_error(exec, "malloc error", MALLOC_ERROR);
	}
	return (key);
} */