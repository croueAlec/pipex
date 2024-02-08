/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:36:10 by acroue            #+#    #+#             */
/*   Updated: 2024/02/08 19:48:16 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] && strncmp("PATH", env[i], 4))
		i++;
	if (!env[i])
		return (NULL);
	return (&env[i][5]);
}

static int	check_path_env(char *path, char *command)
{
	char	*tmp;

	tmp = ft_strdup(path);
	tmp = ft_sep_join(tmp, command, "/");
	if (!tmp || access(tmp, X_OK))
		return (free(tmp), 0);
	return (free(tmp), 1);
}

static char	*find_cmd(char **envp, char **argv)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	envp = ft_split(find_path(envp), ':');
	while (envp && envp[i])
	{
		if (check_path_env(envp[i], argv[0]) && tmp == NULL)
			tmp = ft_strdup(envp[i]);
		free(envp[i]);
		i++;
	}
	return (free(envp), ft_sep_join(tmp, argv[0], "/"));
}

static int	is_directory(char *str)
{
	if (!ft_memcmp("/", str, 1))
		return (1);
	if (!ft_memcmp("./", str, 2))
		return (1);
	if (!ft_memcmp("../", str, 3))
		return (1);
	return (0);
}

char	*check_input(char **argv, char **envp)
{
	if (is_directory(argv[0]))
		return (ft_strdup(argv[0]));
	else if (ft_strchr(argv[0], '/'))
		return (ft_strjoin("./", argv[0]));
	else
		return (find_cmd(envp, argv));
}
