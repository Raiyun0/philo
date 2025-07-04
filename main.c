/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lakli-no <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:38:30 by lakli-no          #+#    #+#             */
/*   Updated: 2025/06/25 15:38:31 by lakli-no         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	if (verif(data) == 1)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = get_ms();
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	data->someone_died = 0;
	data->start_time = get_ms();
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->philos);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, routine, (void *)&data->philos[i]) != 0)
		{
			printf("Error thread");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("error join");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		printf("error1");
		return (1);
	}
	if (parse_args(&data, ac, av))
	{
		printf("error2");
		return (1);
	}
	if (init_philo(&data) != 0)
	{
		printf("error3");
		return (1);
	}
	if (start_simulation(&data) != 0)
	{
		printf("error4");
		return (1);
	}
	monitor(&data);
	cleanup(&data);
	return (0);
}
