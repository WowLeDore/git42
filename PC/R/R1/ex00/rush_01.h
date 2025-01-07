/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_01.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greandre <greandre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:41:04 by greandre          #+#    #+#             */
/*   Updated: 2024/08/25 19:41:22 by greandre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_01_H
# define RUSH_01_H
# define N 4
// takes less than 5 seconds for N <= 6 ; takes ~8 minutes for N == 7
# include <unistd.h>
# include <stdbool.h>

bool	verif_args(int argc, char *argv[]);
bool	verif_grid(int grid[N][N], int x, int y, int conditions[N*N]);
void	convert_conditions(char *argv[], int conditions[N*N]);
int		count_boxes(int line[N], int start, int end);
#endif
