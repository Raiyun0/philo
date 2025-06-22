#include "philo.h"

long get_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

void	smart_sleep(long duration)
{
	long	start;

	start = get_ms();
	while ((get_ms() - start) < duration)
		usleep(100);
}

int ft_atoi(const char *str)
{
    long res = 0;
    int i = 0;

    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        if (res > INT_MAX)
            return (-1);
        i++;
    }
    if (str[i] != '\0')
        return (-1);
    return ((int)res);
}

int parse_args(t_data *data, int argc, char **argv)
{
    data->nb_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);

    if (data->nb_philo <= 0 || data->nb_philo > 200 ||
        data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
        return (1);

    if (argc == 6)
    {
        data->must_eat_count = ft_atoi(argv[5]);
        if (data->must_eat_count <= 0)
            return (1);
    }
    else
        data->must_eat_count = -1;
    return (0);
}