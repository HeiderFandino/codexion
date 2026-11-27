/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfandino <hfandino@student.42barcelona.co> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 18:01:44 by hfandino          #+#    #+#             */
/*   Updated: 2026/11/27 18:12:42 by hfandino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc != 9)
	{
		printf("Error: expected 8 arguments\n");
		return (1);
	}
	if (arguments_valid(argv))
		return (1);
	init_config(argv, &sim);
	if (scheduler_valid(argv, &sim.scheduler))
		return (1);
	if (init_resources(&sim))
	{
		printf("Error: memory allocation failed\n");
		return (1);
	}
	printf("success\n");
	free(sim.coders);
	free(sim.dongles);
	return (0);
}

