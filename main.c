#include "philo.h"

int main(int ac, char **av)
{
    t_data data;

    if (ac != 5 && ac!=6)
    {
        printf("error1");
        return(1);
    }
    if (parse_args(&data, ac, av))
    {
        printf("error2");
        return(1);
    }

    printf("Parsed OK: %d philosophers\n", data.nb_philo);
    printf("Time to die: %d ms\n", data.time_to_die);
    printf("Time to eat: %d ms\n", data.time_to_eat);
    printf("Time to sleep: %d ms\n", data.time_to_sleep);
    if (data.must_eat_count != -1)
        printf("Each philosopher must eat %d times\n", data.must_eat_count);
    else
        printf("No meal count limit\n");

    return (0);
}