/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:32:18 by rbicanic          #+#    #+#             */
/*   Updated: 2022/02/09 14:25:51 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_write_error(char *error_msg, char *file, int exit_code, t_pipex *pip)
{
	write(2, error_msg, ft_strlen(error_msg));
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
	ft_lstclear(&pip->cmds_list);
	exit(exit_code);
}

void	ft_strerror(int error, t_pipex *pip)
{
	if (error == PATH_CMD)
		ft_write_error("Error: command not found: ", pip->actual_cmd->path,
			127, pip);
	else if (error == PATH_INFILE)
		ft_write_error("Error: no such file or directory: ",
			pip->infile, 2, pip);
	else if (error == RIGHT_INFILE)
		ft_write_error("Error: permission denied: ", pip->infile, 3, pip);
	else if (error == RIGHT_OUTFILE)
		ft_write_error("Error: permission denied: ", pip->outfile, 4, pip);
	else if (error == PATH_ENV)
		ft_write_error("Error: path variable does not exist", "", 5, pip);
}

int	ft_error(int error, t_pipex *pipex)
{
	int	fd_output;

	if (!access(pipex->outfile, F_OK)
		&& access(pipex->outfile, W_OK))
	{
		ft_strerror(RIGHT_OUTFILE, pipex);
		exit(1);
	}
	else if (access(pipex->outfile, F_OK) == -1)
	{
		fd_output = open(pipex->outfile, O_WRONLY | O_CREAT);
		close(fd_output);
	}
	if (error == MALLOC_E || error == FD_E || error == EXEC_E)
	{
		ft_lstclear(&pipex->cmds_list);
		perror("Error");
		exit(6);
	}
	else if (error == PATH_CMD)
		ft_strerror(PATH_CMD, pipex);
	return (0);
}

void	malloc_error(void *ptr, t_pipex *pipex)
{
	if (!ptr)
		ft_error(MALLOC_E, pipex);
}
