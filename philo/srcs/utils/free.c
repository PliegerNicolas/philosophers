/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:35:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/17 19:29:13 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* Free memory outside of structures. */
t_bool	free_threads_and_philos(pthread_t *threads, t_philosopher *philosophers)
{
	if (threads)
		free(threads);
	if (philosophers)
		free(philosophers);
	return (TRUE);
}

/* Free all memory. */
t_bool	free_all(pthread_t *threads, t_philosopher *philosophers,
	int malloced_forks)
{
	int		i;

	if (!philosophers || !malloced_forks)
		return (TRUE);
	pthread_mutex_destroy(&philosophers[0].rules->end_mutex);
	i = 0;
	while (i < malloced_forks)
	{
		pthread_mutex_destroy(&philosophers[i].last_meal_mutex);
		if (philosophers[i].left_fork_mutex)
		{
			pthread_mutex_destroy(philosophers[i].left_fork_mutex);
			free(philosophers[i].left_fork_mutex);
		}
		i++;
	}
	return (free_threads_and_philos(threads, philosophers));
}
