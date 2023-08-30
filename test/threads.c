/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:24:44 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/30 13:02:02 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void	*func(int n);

pthread_t		philosopher[5];
pthread_mutex_t	chopstick[5];

int	main(void)
{
	int		i;
	int		k;
	void	*msg;

	for(i = 1;i <= 5; i++)
	{
		k = pthread_mutex_init(&chopstick[i], NULL);
		if (k == -1)
		{
			printf("\n Mutex initialization failed");
			exit(1);
		}
	}
	for(i = 1;i <= 5; i++)
	{
		k = pthread_create(&philosopher[i], NULL, (void *)func, (int *)i);
		if (k != 0)
		{
			printf("\n Thread creation error \n");
			exit(1);
		}
	}
	for(i = 1;i <= 5; i++)
	{
		k = pthread_join(philosopher[i], &msg);
		if (k != 0)
		{
			printf("\n Thread join failed \n");
			exit(1);
		}
	}
	for(i = 1;i <= 5; i++)
	{
		k = pthread_mutex_destroy(&chopstick[i]);
		if (k != 0)
		{
			printf("\n Mutex Destroyed \n""");
			exit(1);
		}
	}
	return (0);
}

void	*func(int n)
{
	printf("\nPhilosopher %d is thinking ", n);
	pthread_mutex_lock(&chopstick[n]);
	pthread_mutex_lock(&chopstick[(n + 1) % 5]);
	printf("\nPhilosopher %d is eating ", n);
	sleep(3);
	pthread_mutex_unlock(&chopstick[n]);
	pthread_mutex_unlock(&chopstick[(n + 1) % 5]);
	printf("\nPhilosopher %d Finished eating ", n);
}
// #include <stdio.h>

// #define n 4

// int	compltedPhilo = 0,i;

// struct fork
// {
// 	int	taken;
// }ForkAvil[n];

// struct philosp
// {
// 	int	left;
// 	int	right;
// }Philostatus[n];

// void	goForDinner(int philID)
// { 
// 	//same like threads concept here cases implemented
// 	if(Philostatus[philID].left == 10 && Philostatus[philID].right == 10)
// 		printf("Philosopher %d completed his dinner\n",philID+1);
// 	//if already completed dinner
// 	else if(Philostatus[philID].left == 1 && Philostatus[philID].right == 1)
// 	{
// 		//if just taken two forks
// 		printf("Philosopher %d completed his dinner\n",philID+1);
// 		Philostatus[philID].left = Philostatus[philID].right = 10; //remembering that he completed dinner by assigning value 10
// 		int otherFork = philID-1;
// 		if(otherFork = = -1)
// 			otherFork = (n-1);
// 		ForkAvil[philID].taken = ForkAvil[otherFork].taken = 0; //releasing forks
// 		printf("Philosopher %d released fork %d and fork %d\n",philID+1,philID+1,otherFork+1);
// 		compltedPhilo++;
// 	}
// 	else if (Philostatus[philID].left == 1 && Philostatus[philID].right == 0)
// 	{
// 		//left already taken, trying for right fork
// 		if(philID==(n-1))
// 		{
// 			if(ForkAvil[philID].taken==0)
// 			{ 
// 				//KEY POINT OF THIS PROBLEM, THAT LAST PHILOSOPHER TRYING IN reverse DIRECTION
// 				ForkAvil[philID].taken = Philostatus[philID].right = 1;
// 				printf("Fork %d taken by philosopher %d\n",philID+1,philID+1);
// 			}
// 			else
// 				printf("Philosopher %d is waiting for fork %d\n",philID+1,philID+1);
// 		}
// 		else
// 		{ //except last philosopher case
// 			int dupphilID = philID;
// 			philID-=1;

// 			if(philID== -1)
// 				philID=(n-1);

// 			if(ForkAvil[philID].taken == 0)
// 			{
// 				ForkAvil[philID].taken = Philostatus[dupphilID].right = 1;
// 				printf("Fork %d taken by Philosopher %d\n",philID+1,dupphilID+1);
// 			}
// 			else
// 				printf("Philosopher %d is waiting for Fork %d\n",dupphilID+1,philID+1);
// 		}
// 	}
// 	else if (Philostatus[philID].left==0)
// 	{
// 		//nothing taken yet
// 		if(philID==(n-1))
// 		{
// 			if(ForkAvil[philID-1].taken==0)
// 			{ //KEY POINT OF THIS PROBLEM, THAT LAST PHILOSOPHER TRYING IN reverse DIRECTION
// 				ForkAvil[philID-1].taken = Philostatus[philID].left = 1;
// 				printf("Fork %d taken by philosopher %d\n",philID,philID+1);
// 			}else{
// 				printf("Philosopher %d is waiting for fork %d\n",philID+1,philID);
// 			}
// 		}
// 		else
// 		{
// 			//except last philosopher case
// 			if(ForkAvil[philID].taken == 0)
// 			{
// 				ForkAvil[philID].taken = Philostatus[philID].left = 1;
// 				printf("Fork %d taken by Philosopher %d\n",philID+1,philID+1);
// 			}
// 			else
// 				printf("Philosopher %d is waiting for Fork %d\n",philID+1,philID+1);
// 		}
// 	}
// }
 
// int	main(void)
// {
// 	for(i=0; i<n;  i++)
// 		ForkAvil[i].taken=Philostatus[i].left=Philostatus[i].right=0;
// 	while(compltedPhilo<n)
// 	{
// 		/* Observe here carefully, while loop will run until all philosophers complete dinner
// 		Actually problem of deadlock occur only thy try to take at same time
// 		This for loop will say that they are trying at same time. And remaining status will print by go for dinner function
// 		*/
// 		for(i=0;i<n; i++)
// 			goForDinner(i);
// 		printf("\nTill now num of philosophers completed dinner are %d\n\n",compltedPhilo);
// 	}
// 	return (0);
// }

// void	*func(void *arg)
// {
// 	// detach the current thread
// 	// from the calling thread
// 	pthread_detach(pthread_self());
// 	printf("Inside the thread\n");
// 	// exit the current thread
// 	pthread_exit(NULL);
// }

// void	fun(void)
// {
// 	pthread_t ptid;
// 	// Creating a new thread
// 	pthread_create(&ptid, NULL, &func, NULL);
// 	printf("This line may be printed" " before thread terminates\n");
// 	// The following line terminates
// 	// the thread manually
// 	// pthread_cancel(ptid);
// 	// Compare the two threads created
// 	// while (1)
// 	// {
// 		if(pthread_equal(ptid, pthread_self()))
// 		{
// 			printf("Threads are equal\n");
// 		}
// 		else
// 			printf("Threads are not equal\n");
// 			// Waiting for the created thread to terminate
// 		pthread_join(ptid, NULL);
// 		pthread_exit(NULL);
// 		printf("This line will be printed" " after thread ends\n");
// 	// }
// }

// // Driver code
// int	main(void)
// {
// 	fun();
// 	return (0);
// }
