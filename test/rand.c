#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Function to generate a random number within a given interval
long long generateRandomNumber(long long min, long long max)
{
	struct timeval tv;
	long long randomNumber;

	gettimeofday(&tv, NULL);

	// Use the current time in microseconds as the seed
	long long seed = (long long)tv.tv_sec * 1000000 + (long long)tv.tv_usec;

	// Use the Xorshift algorithm to generate a random number
	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	randomNumber =  min + (seed % (max - min + 1));
	if (randomNumber < 1)
	{
		randomNumber = (randomNumber * -1) + 1;
	}
	// Return the random number within the specified interval
	return (randomNumber);
}

int main()
{
	int min = 10;
	int max = 50;

	long long randomNumber = generateRandomNumber(1, 6);
	printf("Random number within interval [%d, %d]: %lld\n", min, max, randomNumber);

	return 0;
}