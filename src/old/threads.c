#include "philo.h"

int create_threads(t_data *data)
{
    int i;

    data->start_time = get_time();
    i = -1;
    while (++i < data->n_philos)
    {
        data->philo[i].last_meal = data->start_time;
        if (pthread_create(&data->philo[i].thread, NULL, philo_routine, &data->philo[i]))
            return (1);
    }
    return (0);
}

void join_threads(t_data *data)
{
    int i;

    i = -1;
    while(++i < data->n_philos)
        if (pthread_join(data->philo[i].thread, NULL) != 0)
            return ;   
}
