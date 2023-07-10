/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:25:05 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 18:25:50 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_var(char c)
{
	if (c && !ft_isspace(c) && c != '\'' && c != '\"')
		return (1);
	return (0);
}

/*counts the lenght of the word after '$' */
int	var_len(char *s, int i)
{
	while (s[i] && valid_var(s[i]) && s[i] != '$')
		i++;
	return (i);
}

int	ft_strlen_var(char *str, int j)
{
	int	i;

	i = 1;
	j++;
	while (str[j] && valid_var(str[j]) && str[j] != '$')
	{
		i++;
		j++;
	}
	return (i);
}

/*checks if there is '$' in s ,so we run expand() again*/
int	more_vars(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if ((size_t)i < ft_strlen(s))
		return (1);
	return (0);
}

int	non_space_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			count++;
		i++;
	}
	return (count);
}
