/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:59:49 by hyko              #+#    #+#             */
/*   Updated: 2022/02/21 15:03:04 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*return_line;
	int			nl_idx;
	int			pre_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nl_idx = gnl_find_newline(backup);
	if (nl_idx == -1)
	{
		pre_len = ft_strlen(backup);
		backup = gnl_expand_backup(backup, fd);
		if ((int)ft_strlen(backup) == pre_len)
			nl_idx = ft_strlen(backup);
	}
	if (nl_idx != -1)
	{
		return_line = ft_substr(backup, 0, nl_idx + 1);
		backup = gnl_cut_backup(backup, return_line);
		return (return_line);
	}	
	return (get_next_line(fd));
}

int	gnl_find_newline(char *backup)
{
	int	idx;
	int	len;

	if (backup == NULL)
		return (-1);
	idx = 0;
	len = ft_strlen(backup);
	while (idx < len)
	{
		if (backup[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

char	*gnl_read_line(int fd)
{
	char	*read_line;
	int		read_size;

	read_line = (char *)malloc(BUFFER_SIZE + 1);
	if (read_line == NULL)
		return (NULL);
	read_size = read(fd, read_line, BUFFER_SIZE);
	if (read_size == -1)
	{
		free(read_line);
		return (NULL);
	}
	read_line[read_size] = '\0';
	return (read_line);
}

char	*gnl_expand_backup(char *backup, int fd)
{
	char	*new_backup;
	char	*read_line;

	read_line = gnl_read_line(fd);
	if (read_line == NULL)
		return (NULL);
	if (read_line[0] == 0)
	{
		free(read_line);
		return (backup);
	}
	if (backup == NULL)
		return (read_line);
	new_backup = ft_strjoin(backup, read_line);
	free(backup);
	free(read_line);
	return (new_backup);
}

char	*gnl_cut_backup(char *backup, char *return_line)
{
	char	*new_backup;
	int		backup_len;
	int		return_len;

	if (backup == NULL || return_line == NULL)
		return (NULL);
	backup_len = ft_strlen(backup);
	return_len = ft_strlen(return_line);
	if (backup_len == return_len)
	{
		free(backup);
		return (NULL);
	}
	new_backup = ft_substr(backup, return_len, backup_len - return_len);
	free(backup);
	return (new_backup);
}
