/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:51:18 by hameur            #+#    #+#             */
/*   Updated: 2023/01/01 01:12:15 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H

# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFFER_SIZE 1000

int		ft_strchr_nl(char *s);
char	*get_next_line(int fd);
char	*new_line(char *str);
char	*rst_ln(char *s);
char	*read_fd(int fd, char *str);

#endif
