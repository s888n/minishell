/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:18:28 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/13 01:44:24 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_cpy_new_line(char *cmd, char *var_env, char *new, int i)
{
	int		k;
	int		j;
	char	*var;

	k = 0;
	j = 0;
	var = extract_var(cmd, i);
	while (new[j])
		j++;
	while (var_env && var_env[k])
	{
		new[j] = var_env[k];
		j++;
		k++;
	}
	k = i + 1 + ft_strlen(var);
	while (cmd[k])
	{
		new[j] = cmd[k];
		j++;
		k++;
	}
	new[j] = '\0';
	free(var);
	free (cmd);
	return (new);
}

char	*copy_value(char *cmd, char *var_env, char *var, int i)
{
	int		j;
	char	*new;

	j = ft_strlen(cmd) - ft_strlen(var);
	if (var_env)
		j += ft_strlen(var_env);
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i && cmd)
	{
		new[j] = cmd[j];
		j++;
	}
	new[j] = '\0';
	new = ft_cpy_new_line(cmd, var_env, new, i);
	if (!ft_strcmp(var, "?"))
		free (var_env);
	free (var);
	return (new);
}

char	*extract_var(char *s, int index)
{
	int		i;
	int		j;
	int		k;
	char	*var;

	k = index + 1;
	i = var_len (s, index + 1);
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	i += k;
	j = 0;
	while (s[k] && k < i)
	{
		var[j] = s[k];
		j++;
		k++;
	}
	var[j] = '\0';
	return (var);
}

int	closed_sq(char *line, int index)
{
	int	sq;
	int	dq;
	int	i;

	i = 0;
	sq = 0;
	dq = 0;
	while (i < index)
	{
		if (line[i] == '\'' && !(dq % 2))
			sq++;
		if (line[i] == '\"' && !(sq % 2))
			dq++;
		i++;
	}
	if (sq % 2)
		return (0);
	return (1);
}

char	*expand(char *s)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && closed_sq(s, i) \
				&& (valid_var(s[i + 1])))
		{
			var = extract_var(s, i);
			value = get_env_value(var);
			var = copy_value(s, value, var, i);
			if (more_vars(var))
				var = expand(var);
			return (var);
		}
		i++;
	}
	return (s);
}
