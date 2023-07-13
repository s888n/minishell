/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:48:29 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/07 10:44:10 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*head;

	while (env)
	{
		head = env;
		env = env->next;
		free(head->var);
		free(head->value);
		free(head);
	}
}

void	cmd_error(t_cmd *command)
{
	init_command(command);
	command->argv = malloc(1);
	command->argv = NULL;
}

void	free_two(char ***del, char **line, char **joined)
{
	char	*line_nl;
	int		i;

	line_nl = NULL;
	i = 0;
	i = xpnd (*del);
	while (**del)
	{
		*line = readline("\033[1;35m>\033[0m ");
		if (!*line)
			break ;
		if (i && **line)
			*line = expand(*line);
		line_nl = ft_strjoin(*line, "\n");
		if (!ft_strcmp(*line, **del))
			return (free(*line), free(line_nl));
		if (**del)
			*joined = store_line(*joined, line_nl);
		free (*line);
		free (line_nl);
	}
}