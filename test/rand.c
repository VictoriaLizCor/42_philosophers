#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long long	generate_rand_num(long long min, long long max)
{
	struct timeval	tv;
	long long		seed;
	long long		random_num;

	gettimeofday(&tv, NULL);
	seed = (long long)tv.tv_sec * 1000000 + (long long)tv.tv_usec;
	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	return (min + (seed % (max - min + 1)));
}

// Function to generate a random number within a given interval
long long	rand_pos(long long min, long long max)
{
	long long		random_num;

	random_num = 0;
	while (1)
	{
		random_num = generate_rand_num(min, max);
		if (random_num > 0)
			break ;
	}
	return (random_num);
}

int	val_exist(long long num, int arr[], int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		if (arr[i] == num)
			return (1);
		i++;
	}
	return (0);
}

int	*random_non_repetive_values(int min, int max, int size)
{
	int		*array;
	int		i;
	int		j;
	int		tmp;
	int		random_num;

	array = (int *)calloc(size, sizeof(int));
	i = 0;
	random_num = 0;
	while (i < size)
	{
		while (val_exist(random_num, array, i))
		{
			while (1)
			{
				random_num = generate_rand_num(min, max);
				if (random_num > 0)
					break ;
			}
		}
		array[i] = random_num;
		i++;
	}
	return (array);
}

int	main(void)
{
	int			min;
	int			max;
	int			i;
	long long	random_number;
	int			*array;

	array = random_non_repetive_values(1, 5, 5);
	min = 10;
	max = 50;
	i = 0;
	// printf("Random number within interval [%d, %d]: %lld\n", min, max, random_number);
	// while (i++ < 100)
	// {
	// 	random_number = generate_rand_num(1, 10);
	// 	printf("Random number within interval[%d] [%d, %d]: %lld\n", 
	// 	i, min, max, random_number);
	// 	// 	printf("i = %d %% 4=> %d\n", i, i % 4);
	// }
	printf("\n--> [");
	for (int i = 0; i < 5; i++) {
		printf("%d ", array[i]);
	}
	printf("]\n");
	free(array);
	return (0);
}
