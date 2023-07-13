/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:55:26 by aoutifra          #+#    #+#             */
/*   Updated: 2023/07/13 11:45:08 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getcmd(char **cmd, char *path)
{
	char	*command;
	char	**pathsplited;
	int		i;

	command = *cmd;
	i = 0;
	if (*cmd && ft_strrchr(*cmd, '/'))
		return ;
	pathsplited = ft_split(path, ':');
	while (pathsplited[i])
	{
		path = ft_strjoin(pathsplited[i], "/");
		*cmd = ft_strjoin(path, command);
		free(path);
		if (!access(*cmd, X_OK))
		{
			free(command);
			free_2d_arr(pathsplited);
			return ;
		}
		free(*cmd);
		i++;
	}
	*cmd = command;
	free_2d_arr(pathsplited);
}

void	close_fd(int fd[2])
{
	close(fd[1]);
	close(fd[0]);
}

void	check_fd(t_cmd *cmd, int fd[2])
{
	int	in;
	int	out;

	if (cmd->heredoc)
	{
		write(fd[1], cmd->in, ft_strlen(cmd->in));
		dup2(fd[0], 0);
		return ;
	}
	if (cmd->in)
	{
		in = open(cmd->in, O_RDONLY, 0664);
		dup2(in, STDIN_FILENO);
	}
	if (cmd->out)
	{
		if (cmd->append)
			out = open(cmd->out, O_CREAT | O_RDWR | O_APPEND, 0664);
		else
			out = open(cmd->out, O_CREAT | O_TRUNC, 0664);
		dup2(out, STDOUT_FILENO);
	}
	return ;
}

void	ft_error(char *cmd, char *err)
{
	if (cmd && errno != 13)
	{
		printf("minishell %s: command not found\n", err);
		exit(127);
	}
	else if (errno == 13)
	{
		printf("minishell %s: Permission denied \n", err);
		exit(126);
	}
	else
		printf("minishell %s: %s \n", err, (char *)(strerror(errno)));
		exit(errno);
}

void	execute(t_cmd *cmd)
{
	int		pipefd[2];
	int		pid;
	char	*err;
	int		status = 0;

	err = 0;

	if (cmd && !cmd->next && is_builtin(*cmd->argv))
	{
		exec_builtin(cmd);
		update_last_cmd(ft_strdup(cmd->argv[0]));
		return;
	}
	while (cmd && *cmd->argv)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_chiled(pipefd, cmd, err);
		dup2(pipefd[0], STDIN_FILENO);
		close_fd(pipefd);
		check_exit_status(cmd);
		cmd = cmd->next;
	}	
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 2)
			g_vars->status = WEXITSTATUS(status);
		if (WIFEXITED(status) == 0)
			g_vars->status = 130;
	}
	dup2(g_vars->in, STDIN_FILENO);
	dup2(g_vars->out, STDOUT_FILENO);
}
