/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:27:40 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/12 02:21:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	printf_is_valid_flag(char c)
{
	if (ft_strchr(FLAGS, c))
		return (TRUE);
	return (FALSE);
}

/*
 *	NOT USED
 */

t_bool	printf_check_coherence(t_printf_info *info)
{
	if (info->conv == 'c' && (info->flags & c_ERRMASK))
		return (FALSE);
	else if (info->conv == 's' && (info->flags & s_ERRMASK))
		return (FALSE);
	else if (info->conv == 'd' && (info->flags & d_ERRMASK))
		return (FALSE);
	else if (info->conv == 'i' && (info->flags & i_ERRMASK))
		return (FALSE);
	else if (info->conv == 'u' && (info->flags & u_ERRMASK))
		return (FALSE);
	else if (info->conv == 'x' && (info->flags & x_ERRMASK))
		return (FALSE);
	else if (info->conv == 'X' && (info->flags & X_ERRMASK))
		return (FALSE);
	else
		return (TRUE);
}

void	printf_flush_info(t_printf_info *info)
{
	info->bufs.right = NULL;
	info->bufs.main = NULL;
	info->bufs.m_len = 0;
	info->bufs.left = NULL;
	info->conv = 0;
	info->prcs_add = 0;
	info->pad_add = 0;
	info->flags = NO_FLAGS;
	info->width = 0;
	info->precision = 0;
}

void	printf_update_mlen(t_printf_info *info)
{
	info->bufs.m_len = ft_strlen(info->bufs.main);
}
