/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:48:57 by pforesti          #+#    #+#             */
/*   Updated: 2022/04/06 10:54:21 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_get(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	time_sum(long time, long tt_thing)
{
	return (time + tt_thing);
}

long	time_diff(long tv_b, long tv_n)
{
	return (tv_n - tv_b);
}

int	wait_time(int n, long start)
{
	long	step;

	while (1)
	{
		usleep(50);
		step = time_get();
		if (step - start >= n)
			break ;
	}
	return (0);
}
