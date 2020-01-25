/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 00:26:07 by yelee             #+#    #+#             */
/*   Updated: 2020/01/23 14:28:01 by yelee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			get_line(t_list **list, char **line)
{
	char	*temp;
	char	*str;
	size_t	i;

	i = 0;
	str = (char*)(*list)->content;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_strsub(str, 0, i);
	if (line == NULL)
		return (-1);
	if (str[i] == '\n')
	{
		temp = ft_strsub(str, i + 1, ft_strlen(str) - i);
		if (temp == NULL)
			return (-1);
	}
	else
		temp = ft_strnew(0);
	free(str);
	(*list)->content = temp;
	return (1);
}

static t_list		*fd_check(const int fd, t_list **head)
{
	t_list	*list;

	list = *head;
	while (list)
	{
		if (list->content_size == (size_t)fd)
			return (list);
		list = list->next;
	}
	if (!(list = ft_lstnew("", (size_t)fd)))
		return (NULL);
	ft_lstadd(head, list);
	return (list);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*list;
	ssize_t			i;
	char			*str;
	char			*temp;

	i = 1;
	str = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!str || fd < 0 || fd > MAX_SIZE || !line || read(fd, str, 0) < 0)
		return (-1);
	list = fd_check(fd, &head);
	while (i > 0 && !ft_strchr(list->content, '\n'))
	{
		i = read(fd, str, BUFF_SIZE);
		if (i < 0)
			return (-1);
		str[i] = '\0';
		temp = list->content;
		list->content = ft_strjoin(list->content, str);
		free(temp);
		if (!(list->content))
			return (-1);
	}
	free(str);
	return (get_line(&list, line));
}
