/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:55:29 by rbicanic          #+#    #+#             */
/*   Updated: 2022/02/12 12:51:47 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char) c)
			return (1);
		s++;
	}
	if (*s == (unsigned char) c)
		return (1);
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_strlen(s) + 1);
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**find_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp("PATH=", envp[i], 5))
			return (ft_split(&envp[i][5], ':'));
		i++;
	}
	return (NULL);
}
