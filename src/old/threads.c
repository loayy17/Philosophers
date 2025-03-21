#include "philo.h"

void print_msg(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->data->print_lock);
    if (!is_dead(philo->data))
        printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_lock);
}

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
        pthread_join(data->philo[i].thread, NULL);
}
