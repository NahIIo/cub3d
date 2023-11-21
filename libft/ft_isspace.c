/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:59:54 by jchauvet          #+#    #+#             */
/*   Updated: 2023/11/21 09:59:56 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION :
	The function ft_isspace checks whether c is a space character or not.

	RETURN VALUE:
	Non-zero if c is a space, zero if not.
*/
int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (c);
	return (0);
}
