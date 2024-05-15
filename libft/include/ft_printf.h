/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:06:22 by jdemers           #+#    #+#             */
/*   Updated: 2024/02/09 14:54:52 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	print_char(char c, int fd);
int	print_string(char *str, int fd);
int	print_ptr(void *ptr, int fd);
int	print_int(int n, int fd);
int	print_hex(unsigned long n, char type, int fd);
int	print_unsigned_int(unsigned int n, int fd);

#endif
