/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:37:40 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/13 11:38:07 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_command(t_cmd *command)
{
	command->in = NULL;
	command->out = NULL;
	command->heredoc = 0;
	command->append = 0;
	command->argv = NULL;
	command->next = NULL;
}

t_cmd	*line_to_cmd(char *line)
{
	t_cmd	*command;	

	command = malloc (sizeof (t_cmd));
	if (!command)
		return (NULL);
	init_command (command);
	tokenize (line, command);
	return (command);
}

void	parse(char *line)
{
	t_cmd	*command;

	command = line_to_cmd(line);
	if (!command)
		ft_putstr_fd("malloc failed in parse()\n", STDERR_FILENO);
	else
		execute(command);
	free_cmd(command);
}
