/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakli-no <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:38:41 by lakli-no          #+#    #+#             */
/*   Updated: 2025/06/25 15:38:43 by lakli-no         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t meal_mutex;
}	t_philo;

int		ft_atoi(const char *str);
int		parse_args(t_data *data, int argc, char **argv);
int		init_philo(t_data *data);
int		verif(t_data *data);
int		start_simulation(t_data *data);

void	*routine(void *arg);
void	print_state(t_philo *philo, char *msg);
void	monitor(t_data *data);
void	smart_sleep(long duration);
void	do_routine_cycle(t_philo *philo);
long	get_ms(void);

#endif
