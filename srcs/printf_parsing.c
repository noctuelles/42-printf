/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:36:35 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/12 01:19:09 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_set_flags(char flag, t_printf_info *info)
{
	if (flag == '-')
		info->flags |= LEFT_JUSTIFY;
	else if (flag == '0')
		info->flags |= ZERO_PADDING;
	else if (flag == '#')
		info->flags |= ALTERNATE_FORM;
	else if (flag == ' ')
		info->flags |= SPACE;
	else if (flag == '+')
		info->flags |= SIGN;
}

static const char	*printf_parse_flags(const char *flags, t_printf_info *info)
{
	size_t	i;

	i = 0;
	while (flags[i] != '\0')
	{
		if (printf_is_valid_flag(flags[i]))
			printf_set_flags(flags[i], info);
		else
			break ;
		i++;
	}
	return (&flags[i]);
}

static const char	*printf_parse_width(const char *width, t_printf_info *info)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(width[i]))
		info->width = ft_atoi(&width[i]);
	while (ft_isdigit(width[i]))
		i++;
	return (&width[i]);
}

static const char	*printf_parse_precision(const char *precision
														, t_printf_info *info)
{
	size_t	i;

	i = 0;
	if (precision[i] == '.')
	{
		if (info->flags & ZERO_PADDING)
			info->flags ^= ZERO_PADDING | PRECISION;
		else
			info->flags |= PRECISION;
		i++;
		if (ft_isdigit(precision[i]))
			info->precision = ft_atoi(&precision[i]);
		while (ft_isdigit(precision[i]))
			i++;
	}
	return (&precision[i]);
}

const char	*printf_parse(const char *fmt, va_list ap, t_printf_info *info)
{
	fmt = printf_parse_flags(fmt, info);
	fmt = printf_parse_width(fmt, info);
	fmt = printf_parse_precision(fmt, info);
	if (fmt && ft_strchr(CONVERSION, *fmt))
	{
		info->conv = *fmt;
		if (!printf_conversion(info->conv, ap, info))
			return (NULL);
		if (info->bufs.main[0] == '-')
			info->flags |= NEGATIVE;
		if (info->bufs.main[0] == '0')
			info->flags |= ZERO_VAL;
		if (info->width > 0 && !(info->flags & LEFT_JUSTIFY))
			info->flags |= RIGHT_JUSTIFY;
		printf_update_mlen(info);
	}
	else
		return (NULL);
	return (fmt);
}
