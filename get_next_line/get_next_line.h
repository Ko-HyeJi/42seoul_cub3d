/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:00:30 by hyko              #+#    #+#             */
/*   Updated: 2022/12/20 15:10:57 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

#define BUFFER_SIZE 42

char	*get_next_line(int fd);
char	*gnl_expand_backup(char *backup, int fd);
char	*gnl_cut_backup(char *backup, char *return_line);
char	*gnl_read_line(int fd);
int		gnl_find_newline(char *read_line);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const	*s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
