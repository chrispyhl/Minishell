/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craabe <craabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:27:04 by craabe            #+#    #+#             */
/*   Updated: 2025/09/17 15:21:23 by craabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

# if defined(_WIN32)
#  define OS 1
# endif

# if defined(_WIN64)
#  undef OS
#  define OS 1
# endif

# if defined(__APPLE__)
#  if defined(__MACH__)
#   undef OS
#   define OS 2
#  endif
# endif

# if defined(__linux__)
#  undef OS
#  define OS 3
# endif

# ifndef OS
#  define OS 0
# endif

int		ft_printf(const char *format, ...);

ssize_t	ft_print_char(int arg);
ssize_t	ft_print_str(char *arg);
ssize_t	ft_print_int(int arg);
ssize_t	ft_print_uns_int(unsigned int arg);

ssize_t	ft_print_pt(void *arg);
ssize_t	ft_print_hex(unsigned int arg, int mode);

int		ft_putnbr_fd_uns(unsigned int n, int fd);

char	*ft_long_hex(unsigned long nbr);
char	*ft_int_hex(unsigned int nbr);

#endif
