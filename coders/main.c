/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandino <hfandino@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 18:48:24 by hfandino          #+#    #+#             */
/*   Updated: 2026/11/25 23:12:40 by hfandino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>
#include <string.h>

static int	is_valid_number(char *str)
{
	int	i;
	int	number;
	int	digit;

	if (!str || !str[0])
		return (0);
	i = 0;
	number = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit = str[i++] - '0';
		if (number > (INT_MAX - digit) / 10)
			return (0);
		number = number * 10 + digit;
	}
	return (1);
}

static int	arguments_valid(char **argv)
{
	int	j;

	j = 1;
	while (j <= 7)
	{
		if (!is_valid_number(argv[j]))
		{
			printf("Error: arguments must be valid integers\n");
			return (1);
		}
		j++;
	}
	return (0);
}

static int	scheduler_valid(char **argv, t_scheduler *scheduler)
{
	if (strcmp(argv[8], "fifo") == 0)
	{
		*scheduler = FIFO;
		return (0);
	}
	if (strcmp(argv[8], "edf") == 0)
	{
		*scheduler = EDF;
		return (0);
	}
	printf("Error: Scheduler must be 'fifo' or 'edf'\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_scheduler	scheduler;

	if (argc != 9)
	{
		printf("Error: expected 8 arguments\n");
		return (1);
	}
	if (arguments_valid(argv))
		return (1);
	if (scheduler_valid(argv, &scheduler))
		return (1);
	printf("success\n");
	return (0);
}
