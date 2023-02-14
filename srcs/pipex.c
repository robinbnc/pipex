/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:11:29 by rbicanic          #+#    #+#             */
/*   Updated: 2022/02/14 09:47:03 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	first_pipe(int fd[2], t_pipex *pipex, char **envp)
{
	int		fd_input;

	if (access(pipex->infile, F_OK) == -1)
		ft_strerror(PATH_INFILE, pipex);
	else if (access(pipex->infile, R_OK) == -1)
		ft_strerror(RIGHT_INFILE, pipex);
	fd_input = open(pipex->infile, O_RDONLY);
	if (fd_input == -1)
		ft_error(PATH_INFILE, pipex);
	dup2(fd_input, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_input);
	if (pipex->actual_cmd->path_error)
		return (ft_error(PATH_CMD, pipex));
	execve(pipex->cmds_list->path, pipex->cmds_list->content, envp);
	return (ft_error(EXEC_E, pipex));
}

int	last_pipe(int fd[2], t_pipex *pipex, char **envp)
{
	int		fd_outfile;

	fd_outfile = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd_outfile == -1)
		ft_error(FD_E, pipex);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
	close(fd[0]);
	close(fd[1]);
	if (pipex->actual_cmd->path_error)
		return (ft_error(PATH_CMD, pipex));
	execve(pipex->actual_cmd->path, pipex->actual_cmd->content, envp);
	return (ft_error(EXEC_E, pipex));
}

int	parent_process(t_pipex *pipex, int fd[2], char **envp, int pid[2])
{
	pipex->actual_cmd = pipex->actual_cmd->next;
	pid[1] = fork();
	if (pid[1] < 0)
		return (2);
	if (pid[1] == 0)
		last_pipe(fd, pipex, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &pipex->exit_status, 0);
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	int		pid[2];
	t_pipex	pipex;

	if (*envp == NULL)
		return (write(2, "Error: Environment Path missing\n", 32), 0);
	if (argc != 5)
		return (write(2, "Error: you must have 4 arguments\n", 33), 1);
	pipex.cmds_list = NULL;
	pipex.arg_nbr = argc;
	pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	parse_args(argc, argv, &pipex, envp);
	ft_error(0, &pipex);
	if (pipe(fd) == -1)
		return (ft_lstclear(&(pipex.cmds_list)), 1);
	pid[0] = fork();
	if (pid[0] < 0)
		return (ft_lstclear(&(pipex.cmds_list)), 2);
	if (pid[0] == 0)
		first_pipe(fd, &pipex, envp);
	else
		parent_process(&pipex, fd, envp, pid);
	return (ft_lstclear(&(pipex.cmds_list)), WEXITSTATUS(pipex.exit_status));
}
