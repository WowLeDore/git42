/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   big.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: uanglade <uanglade@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/08/31 15:03:26 by uanglade		  #+#	#+#			 */
/*   Updated: 2024/09/01 01:07:34 by uanglade		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "ft_main.h"

char	**ft_split_nbr2(char **nbrs, int *i, int *j, char *nbr)
{
	nbrs[*j] = malloc(sizeof(char) * 4);
	if (nbrs[*j] == NULL)
	{
		free(nbrs);
		return (NULL);
	}
	nbrs[*j][0] = '0';
	if (*i == 1)
		nbrs[*j][1] = '0';
	else
		nbrs[*j][1] = nbr[0];
	nbrs[*j][2] = nbr[*i - 1];
	nbrs[*j][3] = '\0';
	*j += 1;
	return ((char **)"");
}

char	**ft_split_nbr(char *nbr)
{
	int		i;
	int		j;
	char	**nbrs;

	nbrs = (char **)malloc(sizeof(char *) * 18);
	if (nbrs == NULL)
		return (NULL);
	i = ft_strlen(nbr);
	j = 0;
	while (i > 2)
	{
		nbrs[j] = ft_strndup(nbr + i - 3, 4);
		if (nbrs[j++] == NULL)
		{
			free(nbrs);
			return (NULL);
		}
		i -= 3;
	}
	if (i > 0 && ft_split_nbr2(nbrs, &i, &j, nbr) == NULL)
		return (NULL);
	nbrs[j] = 0;
	return (nbrs);
}

bool	ft_verif_nbr(char	*nbr)
{
	while (*nbr)
	{
		if (*nbr < '0' || *nbr > '9')
		{
			ft_putstr("Error\n");
			return (false);
		}
		nbr++;
	}
	return (true);
}

char	**main2(int argc, char **argv, char *file)
{
	char			**nbrs;

	nbrs = ft_split_nbr(argv[argc - 1]);
	if (file == NULL)
	{
		if (nbrs != NULL)
			free(nbrs);
		return (0);
	}
	if (nbrs == NULL)
	{
		if (file != NULL)
			free(file);
		return (0);
	}
	return (nbrs);
}

int	main(int argc, char **argv)
{
	struct s_number	*dict;
	char			*file;
	char			**nbrs;

	if (!ft_verif_nbr(argv[argc - 1]))
		return (0);
	if (argc == 2)
		file = get_file("numbers.dict");
	else if (argc == 3)
		file = get_file(argv[1]);
	else
		return (0);
	nbrs = main2(argc, argv, file);
	if (!nbrs)
		return (0);
	if (!ft_verif_dict(file))
		return (0);
	dict = ft_parse_file(file);
	free(file);
	if (dict == NULL)
		return (0);
	ft_print_whole_nb(nbrs, dict);
	free(nbrs);
	free(dict);
	return (0);
}
