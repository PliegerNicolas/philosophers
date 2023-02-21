/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_sem_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:23:44 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/17 13:35:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

char	*generate_sem_name(char *prefix, int philosopher_id)
{
	char	*str;
	char	*id;

	id = ft_itoa(philosopher_id);
	if (!id)
		return (NULL);
	str = ft_strjoin(prefix, id);
	free(id);
	if (!str)
		return (NULL);
	return (str);
}
