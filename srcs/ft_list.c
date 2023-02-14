/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:25:36 by rbicanic          #+#    #+#             */
/*   Updated: 2022/01/29 16:13:36 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_list	*ft_lstnew(char **content)
{
	t_list	*newlst;

	newlst = malloc(sizeof(t_list));
	if (newlst == NULL)
		return (NULL);
	newlst->content = content;
	newlst->next = NULL;
	return (newlst);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = ft_lstlast(*alst);
	if (tmp == NULL)
		*alst = new;
	else
		tmp->next = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free_strs((*lst)->content);
		if ((*lst)->path)
			free((*lst)->path);
		free(*lst);
		*lst = tmp;
	}
}

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*tmp;

	len = 1;
	tmp = lst;
	if (tmp == NULL)
		return (0);
	while (tmp->next != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
