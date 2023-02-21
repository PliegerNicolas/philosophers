/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:47:16 by nicolas           #+#    #+#             */
/*   Updated: 2023/02/18 03:11:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

/* Give default values to a given philosopher and distribut fork pointers. */
static t_bool	populate_philosopher(t_philosopher *philos,
	t_rules *rules, int i)
{
	philos[i].rules = rules;
	philos[i].id = i + 1;
	philos[i].status = sleeping;
	philos[i].meals = 0;
	philos[i].last_meal = 0;
	pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
	philos[i].left_fork_mutex = malloc(sizeof(*philos[i].left_fork_mutex));
	if (!philos[i].left_fork_mutex)
		return (FALSE);
	pthread_mutex_init(philos[i].left_fork_mutex, NULL);
	if (i > 0)
		philos[i - 1].right_fork_mutex = philos[i].left_fork_mutex;
	if (rules->total_philos > 1 && i == rules->total_philos - 1)
		philos[i].right_fork_mutex
			= philos[i - rules->total_philos + 1].left_fork_mutex;
	return (TRUE);
}

/* Produce a thread per philosopher. */
static int	create_threads(pthread_t *threads, t_philosopher *philosophers,
	t_rules *rules)
{
	int		i;

	i = 0;
	rules->start_time = get_time();
	while (i < rules->total_philos)
	{
		if (pthread_create(&threads[i], NULL, &routine,
				(void *)&philosophers[i]) != 0)
		{
			rules->end = TRUE;
			return (i);
		}
		usleep(1);
		i++;
	}
	return (i);
}

/* Wait for each thread to finish working before */
/* continuing main thread. */
static t_bool	join_threads(pthread_t *threads, int created_threads)
{
	int		i;

	if (!threads)
		return (TRUE);
	i = 0;
	while (i < created_threads)
	{
		if (pthread_join(threads[i++], NULL) != 0)
			return (FALSE);
	}
	return (TRUE);
}

/* Malloc threads and philosophers. */
static t_bool	malloc_var(t_rules *rules, pthread_t **threads,
	t_philosopher **philosophers)
{
	*threads = malloc(rules->total_philos * sizeof(**threads));
	if (!*threads)
		return (!free_threads_and_philos(*threads, *philosophers));
	*philosophers = malloc(rules->total_philos * sizeof(**philosophers));
	if (!*threads)
		return (!free_threads_and_philos(*threads, *philosophers));
	return (TRUE);
}

/* Initialize variables (threads && philosophers) */
/* and initialize rules and threads. */
t_bool	initialize_philosophers(t_rules *rules)
{
	pthread_t		*threads;
	t_philosopher	*philosophers;
	int				i;
	int				created_threads;

	threads = NULL;
	philosophers = NULL;
	if (!malloc_var(rules, &threads, &philosophers))
		return (FALSE);
	i = 0;
	while (i < rules->total_philos)
	{
		if (!populate_philosopher(philosophers, rules, i))
			return (free_all(threads, philosophers, i));
		i++;
	}
	created_threads = create_threads(threads, philosophers, rules);
	rules->start_time = get_time();
	if (!join_threads(threads, created_threads))
		return (free_all(threads, philosophers, rules->total_philos));
	free_all(threads, philosophers, rules->total_philos);
	return (TRUE);
}
