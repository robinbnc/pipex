/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:09:57 by rbicanic          #+#    #+#             */
/*   Updated: 2022/02/12 12:53:04 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

enum {
	MALLOC_E = 1,
	FD_E,
	EXEC_E,
	PATH_CMD,
	PATH_INFILE,
	RIGHT_INFILE,
	RIGHT_OUTFILE,
	PATH_ENV
};

typedef struct s_list
{
	int				path_error;
	char			**content;
	char			*path;
	struct s_list	*next;
}				t_list;

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		arg_nbr;
	int		lst_size;
	int		exit_status;
	t_list	*cmds_list;
	t_list	*actual_cmd;
}				t_pipex;

char	**ft_split(char const *s, char c);
char	*ft_strcat(char *dest, char *src);
int		ft_strlen(const char *s);
t_list	*ft_lstnew(char **content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst);
int		ft_lstsize(t_list *lst);
t_pipex	*send_data(void);
t_list	*ft_lstlast(t_list *lst);
void	parse_args(int argc, char *argv[], t_pipex *pipex, char **envp);
int		ft_error(int error, t_pipex *pipex);
void	free_strs(char **strs);
char	*ft_strjoin(char *s1, char *s2, char *sep);
char	*ft_strdup(char *s);
void	ft_strerror(int error, t_pipex *pipex);
int		ft_strchr(char *s, int c);
void	malloc_error(void *ptr, t_pipex *pipex);
char	**find_path_env(char **envp);

#endif