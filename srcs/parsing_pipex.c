/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:55:29 by rbicanic          #+#    #+#             */
/*   Updated: 2022/02/14 09:48:33 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*empty_cmd(t_list *el)
{
	el->path_error = 1;
	return (ft_strdup(""));
}

char	*check_cmds_path(t_list *el, char **envp)
{
	int		i;
	char	*path_cmd;
	char	**path_env;

	if (el->content[0] == NULL)
		return (empty_cmd(el));
	path_env = find_path_env(envp);
	if (path_env == NULL)
		return (NULL);
	i = -1;
	while (path_env != NULL && path_env[++i])
	{
		path_cmd = ft_strjoin(path_env[i], el->content[0], "/");
		if (path_cmd == NULL)
			return (free_strs(path_env), NULL);
		if (access(path_cmd, F_OK) == 0)
			return (free_strs(path_env), path_cmd);
		free(path_cmd);
	}
	if (ft_strchr(el->content[0], '/') && access(el->content[0], F_OK) == 0)
		return (ft_strdup(el->content[0]));
	el->path_error = 1;
	if (path_env == NULL)
		return (el->content[0]);
	return (free_strs(path_env), ft_strdup(el->content[0]));
}

void	init_el(char **envp, t_pipex *pipex, t_list *el, char **strs)
{
	el->path_error = 0;
	el->path = check_cmds_path(el, envp);
	if (el->path == NULL)
	{
		free_strs(strs);
		free(el);
		ft_error(MALLOC_E, pipex);
	}
}

void	parse_args(int argc, char *argv[], t_pipex *pipex, char **envp)
{
	int		i;
	char	**strs;
	t_list	*el;

	i = 1;
	while (++i < argc - 1)
	{
		strs = ft_split(argv[i], ' ');
		malloc_error((void *) strs, pipex);
		el = ft_lstnew(strs);
		if (el == NULL)
		{
			free_strs(strs);
			malloc_error((void *) el, pipex);
		}
		init_el(envp, pipex, el, strs);
		if (pipex->cmds_list == NULL)
			pipex->cmds_list = el;
		else
			ft_lstadd_back(&pipex->cmds_list, el);
	}
	pipex->actual_cmd = pipex->cmds_list;
	pipex->lst_size = ft_lstsize(pipex->cmds_list);
}
