/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:43:35 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/17 12:28:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

sem_t	*sem_open_new(char const *name, int val)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, PERM_READ_WRITE, val));
}
