/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:35:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/21 18:29:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers_bonus.h"

t_bool	clear_and_free(t_rules *rules, t_philosopher *philosophers)
{
	int		i;

	if (rules->end_sem)
		sem_close(rules->end_sem);
	if (rules->forks_sem)
		sem_close(rules->forks_sem);
	if (rules->grabbing_forks_sem)
		sem_close(rules->grabbing_forks_sem);
	if (philosophers)
	{
		i = 0;
		while (i < rules->created_philos)
			sem_close(philosophers[i++].last_meal_sem);
		free(philosophers);
	}
	return (TRUE);
}
