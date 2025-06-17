#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_data {
    int             nb_philo;
    int            time_to_die;
    int            time_to_eat;
    int            time_to_sleep;
    int             must_eat_count;
}   t_data;

typedef struct s_philo {
    int             id;
    int             meals_eaten;
    int            last_meal;
    pthread_t       thread;
    t_data          *data;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_philo;

int ft_atoi(const char *str);
int parse_args(t_data *data, int argc, char **argv);

#endif