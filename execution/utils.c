/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:12:29 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/13 11:07:26 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

t_env	*create_env_oi(char **env)
{
	t_env	*head;
	t_env	*fetch;
	int		i;

	i = 0;
	if (!env || !*env)
		return (NULL);
	head = new_line_oi(env[i++]);
	if (!head)
		return (NULL);
	fetch = head;
	while (env[i])
	{
		head->next = new_line_oi(env[i++]);
		head = head->next;
	}
	head = fetch;
	return (head);
}	

char	*oi_strjoin(char *str, char *cmd)
{
	int		len1;
	int		len2;
	char	*path;
	int		i;
	int		j;

	if (!str || !cmd)
		return (0);
	i = -1;
	j = 0;
	len1 = oi_strlen(str);
	len2 = oi_strlen(cmd);
	path = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!path)
		return (0);
	while (str[++i])
		path[i] = str[i];
	path[i++] = '/';
	while (cmd[j])
		path[i++] = cmd[j++];
	path[i] = '\0';
	return (path);
}

char	*oi_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == 0)
		return ((char *)s + i);
	return (0);
}

char	*oi_strtrim(char const *s1, char const *set)
{
	size_t	len;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && oi_strchr(set, s1[i]))
		i++;
	s1 = s1 + i;
	len = oi_strlen((char *)s1);
	while (len && oi_strchr(set, s1[len]))
		len--;
	return (oi_substr(s1, 0, (len + 1)));
}

char	*classic_ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	y;

	if (!s1 || !s2)
		return (NULL);
	s1_len = oi_strlen((char *)s1);
	s2_len = oi_strlen((char *)s2);
	ptr = (char *)malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (0);
	i = 0;
	y = 0;
	while (i < s1_len)
		ptr[y++] = s1[i++];
	i = 0;
	while (i < s2_len)
		ptr[y++] = s2[i++];
	ptr[y] = 0;
	return (ptr);
}
