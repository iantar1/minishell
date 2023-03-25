/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:21:28 by iantar            #+#    #+#             */
/*   Updated: 2023/02/25 20:30:05 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

size_t	ft_strlen(const char *str);
char	*ft_strjoin(char **save_buf, char *buf, int len_buf);
char	*get_next_line(int fd);
int		there_new_line(char *save_buf);
char	*rtn_line(char **save_buf, int index);
char	*rtn_and_clean(char **save_buf);
void	ft_free(char **str);

#endif
