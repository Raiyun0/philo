/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakli-no <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:38:05 by lakli-no          #+#    #+#             */
/*   Updated: 2025/06/25 15:38:07 by lakli-no         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
void	monitor(t_data *data)
{
	int		i;
	long	now;

	while (!data->someone_died)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			now = get_ms();
			if (now - data->philos[i].last_meal >= data->time_to_die)
			{
				pthread_mutex_lock(&data->print_mutex);
				if (!data->someone_died)
				{
					data->someone_died = 1;
					printf("%ld %d died\n", now - data->start_time,
						data->philos[i].id);
				}
				pthread_mutex_unlock(&data->print_mutex);
				return ;
			}
			i++;
		}
		usleep(100);
	}
}
*/

static int	check_death(t_philo *philo, long now)
{
	long	last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (now - last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (!philo->data->someone_died)
		{
			philo->data->someone_died = 1;
			printf("%ld %d died\n", now - philo->data->start_time, philo->id);
		}
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}

void	monitor(t_data *data)
{
	int		i;
	long	now;

	while (!data->someone_died)
	{
		i = 0;
		now = get_ms();
		while (i < data->nb_philo)
			if (check_death(&data->philos[i++], now))
				return ;
		usleep(100);
	}
}

void	do_routine_cycle(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	philo->last_meal = get_ms();
	philo->meals_eaten++;
	/*smart_sleep(philo->data->time_to_eat);*/smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_state(philo, "is sleeping");
	/*smart_sleep(philo->data->time_to_sleep);*/smart_sleep(philo->data->time_to_eat, philo->data);
	print_state(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		/*smart_sleep(philo->data->time_to_die);*/smart_sleep(philo->data->time_to_eat, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (!philo->data->someone_died)
		do_routine_cycle(philo);
	return (NULL);
}

void	print_state(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_died)
	{
		timestamp = get_ms() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}


