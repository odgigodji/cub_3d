/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:09:55 by namerei           #+#    #+#             */
/*   Updated: 2020/11/18 22:29:05 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int a)
{
	if (a == '\n' || a == '\v' || a == '\r'\
	|| a == '\t' || a == '\f' || a == ' ')
		return (1);
	return (0);
}
