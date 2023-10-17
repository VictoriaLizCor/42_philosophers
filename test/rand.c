#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Function to generate a random number within a given interval
long long	generate_rand_num(long long min, long long max)
{
	struct timeval	tv;
	long long		random_num;
	long long		seed;

	gettimeofday(&tv, NULL);
	seed = (long long)tv.tv_sec * 1000000 + (long long)tv.tv_usec;

	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	random_num = 0;
	// random_num = (random_num * -1) + 1;
	random_num = min + (seed % (max - min + 1));
	// while (random_num == 0)
	// {
	// 	random_num = generate_rand_num(min, max);
	// }
	return (random_num);
}

int	*create_integer_array_with_non_repetive_values(int min, int max, int size)
{
	int		*array;
	int		i;
	int		j;
	int		random_num;

	array = (int *)malloc(size * sizeof(int));
	i = 0;
	while (i < size)
	{
		j = 0;
		random_num = generate_rand_num(min, max);
		while (j < i)
		{
			if (array[j] == random_num)
				break ;
			j++;
		}
		if (j == i)
		{
			array[i] = random_num;
			i++;
		}
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

	array = create_integer_array_with_non_repetive_values(1, 5, 5);
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
	for (int i = 0; i < 5; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
	return (0);
}
