#include "philo.h"

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
					printf("%ld %d died\n",
						now - data->start_time,
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

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		print_state(philo, "is eating");
		philo->last_meal = get_ms();
		philo->meals_eaten++;
		smart_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_state(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep);
		print_state(philo, "is thinking");
	}
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

int	start_simulation(t_data *data)
{
	int i;

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