/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:32:06 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/27 15:27:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ************************************** */
/* * INCLUDES							* */
/* ************************************** */

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

typedef int	t_bool;

enum e_status
{
	eating = 1,
	sleeping = 2,
	thinking = 3,
	dead = 4,
	finished_eating = 5,
	grabbing_fork = 6
};

typedef struct s_rules
{
	int					total_philos;
	int					created_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					max_meals_per_philo;
	int					all_ate_count;
	size_t				start_time;
	t_bool				end;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		last_write_mutex;
}	t_rules;

typedef struct s_philosopher
{
	t_rules				*rules;
	pthread_t			thread;
	t_bool				end;
	int					id;
	enum e_status		status;
	int					meals;
	size_t				last_meal;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
}	t_philosopher;

/* ************************************** */
/* * MACRO								* */
/* ************************************** */

/* Max philosophers */

# define MAX_PHILOSOPHERS 1024

/* t_bool */

# define FALSE 0
# define TRUE 1

/* Int limits */

# define MAX_INT 2147483647
# define MIN_INT -2147483648

/* Colors */

# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define BLUE "\033[0;34m"
# define ORANGE "\033[0;33m"
# define PURPLE "\033[0;35m"
# define YELLOW "\033[1;33m"
# define LIGHT_BLUE "\033[1;34m"
# define LIGHT_PURPLE "\033[1;35m"
# define LIGHT_CYAN "\033[1;36m"
# define LIGHT_GRAY "\033[0;37m"
# define DEFAULT_COLOR "\033[0m"

/* ************************************** */
/* * FUNCTIONS							* */
/* ************************************** */

/* Utils */

t_bool			ft_isdigit(int c);
t_bool			ft_str_is_int(char *arg);

long long int	ft_atolli(const char *nptr);
long double		ft_atold(const char *str);

t_bool			clear_and_free(t_rules *rules, t_philosopher *philosophers);

size_t			get_time(void);

/* Args verification */

t_bool			verify_args(int argc, char **argv);

/* Initialization */

t_bool			initialize(t_rules *rules, t_philosopher **philosophers,
					int argc, char **argv);

/* Life */

t_bool			run_simulation(t_rules *rules, t_philosopher *philosophers);
void			*monitor_routine(void *ptr);
void			*philosopher_routine(void *ptr);

t_bool			try_ending(t_philosopher *philosopher, t_rules *rules);
void			try_thinking(t_philosopher *philosopher, t_rules *rules);
void			try_grabbing_forks(t_philosopher *philosopher, t_rules *rules);
void			try_eating(t_philosopher *philosopher, t_rules *rules);
void			try_sleeping(t_philosopher *philosopher, t_rules *rules);

/* Output */

void			put_usage_indication(void);
t_bool			perror_wrong_nbr_of_args(int nbr_of_given_args);
t_bool			perror_not_a_valid_int(int arg_nbr);
t_bool			perror_int_expected(int arg_nbr);
t_bool			perror_wrong_nbr_of_philosophers(void);
t_bool			perror_not_enough_memory(void);

void			put_philosopher_action(t_philosopher *philo,
					enum e_status action);

#endif
