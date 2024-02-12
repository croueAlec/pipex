/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:13:01 by acroue            #+#    #+#             */
/*   Updated: 2024/02/12 18:27:23 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

size_t	ft_dprintf(int fd, const char *format, ...);
void	fd_print_nbr(long n, int fd);
int		fd_put_signed(int n, int fd);
int		fd_put_unsigned(unsigned int n, int fd);
int		fd_hex_min(long long arg, int fd);
int		fd_hex_zero(long long arg, char c, int fd);
int		fd_put_hex(char *str, int len, int is_address, int fd);
int		fd_putnbr_base(unsigned long long n, char *base, int is_adr, int fd);
int		fd_putchar(char c, int fd);
int		fd_putstr(char *s, int fd);

#endif
