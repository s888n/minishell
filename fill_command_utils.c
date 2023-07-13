/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:52:32 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/13 11:38:00 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_until_specials(char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '?' && \
			s[i] != '?' && s[i] != '$' && s[i] != '\"' && s[i] != '\'')
		i++;
	return (i);
}

int	letter_count(char *s)
{
	int	len;

	len = 0;
	len = ft_strlen(s);
	if (!len)
		return (1);
	while (*s && ft_isspace(*s))
	{
		s++;
		len--;
	}
	return (len);
}

char	*skip_space(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (letter_count(s) == 0)
		return (s);
	while (s[i] && ft_isspace(s[i]))
		i++;
	str = ft_substr(s, i, ft_strlen(s) - i);
	if (!str)
		return (NULL);
	free(s);
	return (str);
}

void	fill_err(t_cmd *cmd)
{
	cmd->heredoc = 0;
	if (cmd->in)
		free (cmd->in);
	cmd->in = NULL;
	if (cmd->out)
		free (cmd->out);
	cmd->out = NULL;
	cmd->next = NULL;
}

void	free_stuff(char *a, char *b, char *c, char *d)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
}
