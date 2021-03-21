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

/*
'str' saves the address of 'list->content' and if it did not save it well, it returns 0.
In while loops, 'i' will be an index of '\n' or at the end of the line.
'ft_strsub(char const *s, unsigned int start, size_t len)' allocates new memory and returns a new string
from '*s' with the size of 'len' starting from 'start'
If there is nothing in 'line', it fails. 
If 'str[i]' element is '\n', that means there are more elements left in 'str'.
Save elements that are left in '*line'.
If 'str[i]' is the end of string, 'ft_strnew' allocates the memory with the size 0.
'str' is no longer needed, so the memory is freed.
The address of 'list->content' saves temp. 
*/

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


/*
This function is used to create a new node list and connect them at the beginning(ft_lstadd).
*/
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

/*
This is the start function. static is used to save the data that's left from the previous calling. 
'fd' is uniquely generated number when the file is opened. 
The memory of 'str' is allocated equivalent to size of BUFFER(1) with the place of NULL terminator.
If the memory is alloated properly, the file descriptor is less than MAX_SIZE(1024), there is text in line string, and it reads a file properly, 
New node list is created in the "fd_check" function.
'ft_strchr(const char *str, int c)' searches for the first occurrence of the character c (an unsigned char) in the string.
While it loops through until it finds '\n' which is new line character and it fails to read a file.
if it fails to read a file, it returns -1.
It adds '\0' null terminator to mark the end of the string.
Then temporary string saves 'list->content'. 
'list->content' is allocated with previous 'list->content' and 'str' combined.
Original 'list->content' that is saved in temporary string is not needed anymore so that we free the memory.
If there is nothing in 'list->content', it returns -1.
Memory for str is freed as it is no longer needed.  
It calls the function 'get_line' with the address of the list.
*/
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
		i = read(fd, str, BUFF_SIZE); // to check if read fails 
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
