#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <omp.h>

int **vertices1;
int **vertices2;
int *adjDeg1;
int *adjDeg2;
int *visited1;
int *visited2;
int **shortestPath1;
int **shortestPath2;
int *saturation1;
int *saturation2;
int *color1;
int *color2;
int *vertexNumber1;
int *vertexNumber2;
int colorMax = 0;

int generateRandomNumber()
{
	int check = rand()%2;
	return check;
}

void printTime(clock_t start, clock_t end)
{
	printf("Time taken: %lf seconds\n", ((double) (end - start)) / CLOCKS_PER_SEC);

}

void memoryAllocate(int number1, int number2)
{
	int numberOfVertices1 = number1;
	int numberOfVertices2 = number2;
	adjDeg1 = (int *)malloc(numberOfVertices1 * sizeof(int));
	adjDeg2 = (int *)malloc(numberOfVertices2 * sizeof(int));
	vertices1 = (int **)malloc(numberOfVertices1*sizeof(int *));
	vertices2 = (int **)malloc(numberOfVertices2*sizeof(int *));
	shortestPath1 = (int **)malloc(numberOfVertices1*sizeof(int *));
	shortestPath2 = (int **)malloc(numberOfVertices2*sizeof(int *));
	visited1 = (int *)malloc(numberOfVertices1*sizeof(int));
	visited2 = (int *)malloc(numberOfVertices2*sizeof(int));
	saturation1 = (int *)malloc(numberOfVertices1*sizeof(int));
	saturation2 = (int *)malloc(numberOfVertices2*sizeof(int));
	color1 = (int *)malloc(numberOfVertices1*sizeof(int));
	vertexNumber1 = (int *)malloc(numberOfVertices1*sizeof(int));
	vertexNumber2 = (int *)malloc(numberOfVertices2*sizeof(int));
	color2 = (int *)malloc(numberOfVertices2*sizeof(int));
	for(int i=0; i<numberOfVertices1; i++)
	{
		vertices1[i] = (int *)malloc(numberOfVertices1 * sizeof(int));
		shortestPath1[i] = (int *)malloc(numberOfVertices1 * sizeof(int));
	}
	for(int i=0; i<numberOfVertices2; i++)
	{
		vertices2[i] = (int *)malloc(numberOfVertices2 * sizeof(int));
		shortestPath2[i] = (int *)malloc(numberOfVertices2 * sizeof(int));
	}

}

void addEdge1(int numberOfVertices1)
{
	int check;
	for(int i=0; i<numberOfVertices1; i++)
	{
		for(int j=i+1; j<numberOfVertices1; j++)
		{
			if(i == j)
			{
				vertices1[i][j] = 0;
			}
			else
			{
				check = generateRandomNumber();
				if(check == 1)
				{
					vertices1[i][j] = 1;
					vertices1[j][i] = 1;
				}
				else
				{
					vertices1[i][j] = 0;
					vertices1[j][i] = 0;
				}
			}
		}
	}
}

void addEdge2(int numberOfVertices2)
{
	int check;
	for(int i=0; i<numberOfVertices2; i++)
	{
		for(int j=0; j<numberOfVertices2; j++)
		{
			if(i == j)
			{
				vertices2[i][j] = 0;
			}
			else
			{
				check = generateRandomNumber();
				if(check == 1)
				{
					vertices2[i][j] = 1;
					vertices2[j][i] = 1;
				}
				else
				{
					vertices2[i][j] = 0;
					vertices2[j][i] = 0;
				}
			}
		}
	}
}

void adjacencyDegree1(int numberOfVertices1)
{

	for(int i=0; i<numberOfVertices1; i++)
	{
		int count = 0;
		for(int j=0; j<numberOfVertices1; j++)
		{
			if(vertices1[i][j] == 1)
			{
				count++;
			}
		}
		adjDeg1[i] = count;
	}
}

void adjacencyDegree2(int numberOfVertices2)
{

	for(int i=0; i<numberOfVertices2; i++)
	{
		int count = 0;
		for(int j=0; j<numberOfVertices2; j++)
		{
			if(vertices2[i][j] == 1)
			{
				count++;
			}
		}
		adjDeg2[i] = count;
	}
}

void initializeShortest1(int numberOfVertices1)
{
	for(int i=0; i<numberOfVertices1; i++)
	{
		for(int j=0; j<numberOfVertices1; j++)
		{
			shortestPath1[i][j] = vertices1[i][j];
		}
	}
}

void initializeShortest2(int numberOfVertices2)
{
	for(int i=0; i<numberOfVertices2; i++)
	{
		for(int j=0; j<numberOfVertices2; j++)
		{
			shortestPath2[i][j] = vertices2[i][j];
		}
	}
}


void markShortestPath1(int numberOfVertices1, int i, int j, int k)
{
	for(i=0; i<numberOfVertices1; i++)
	{
		for(j=0; j<numberOfVertices1; j++)
		{
			if((i != j) && (shortestPath1[i][j] == 0))
			{
				for(k=0; j<numberOfVertices1; k++)
				{
					if((shortestPath1[k][j] != 0) && (shortestPath1[i][k] != 0))
					{
							shortestPath1[i][j] = shortestPath1[i][k] + 1;
							break;
					}

				}
			}

		}
	}
}

void markShortestPath2(int numberOfVertices2, int i, int j, int k)
{
	for(i=0; i<numberOfVertices2; i++)
	{
		for(j=0; j<numberOfVertices2; j++)
		{
			if((i != j) && (shortestPath2[i][j] == 0))
			{
				for(k=0; j<numberOfVertices2; k++)
				{
					if((shortestPath2[k][j] != 0) && (shortestPath2[i][k] != 0))
					{
							shortestPath2[i][j] = shortestPath2[i][k] + 1;
							break;
					}

				}
			}

		}
	}
}

void updateShortestPath(int numberOfVertices1, int numberOfVertices2)
{
	int i,j,k;
	initializeShortest1(numberOfVertices1);
	initializeShortest2(numberOfVertices2);
	/*for(i=0; i<numberOfVertices1; i++)
	{
		markShortestPath1(numberOfVertices1,i,j,k);
	}
	for(i=0; i<numberOfVertices2; i++)
	{
		markShortestPath2(numberOfVertices2,i,j,k);
	} */


}

void initializeSaturation(int numberOfVertices1, int numberOfVertices2)
{
	for(int i=0; i<numberOfVertices1; i++)
	{
		saturation1[i] = 1;
		color1[i] = 0;
		vertexNumber1[i] = i;
	}

	for(int i=0; i<numberOfVertices2; i++)
	{
		saturation2[i] = 1;
		color2[i] = 0;
		vertexNumber2[i] = i;
	}
}

int maxAdjDeg1(int numberOfVertices1)
{
	int max = 0;
	int vertexIndex = 0;
	for(int i=0; i<numberOfVertices1; i++)
	{
		if(max < adjDeg1[i])
		{
			max = adjDeg1[i];
			vertexIndex = i;
		}
	}
	return vertexIndex;
}

int maxAdjDeg2(int numberOfVertices2)
{
	int max = 0;
	int vertexIndex = 0;
	for(int i=0; i<numberOfVertices2; i++)
	{
		if(max < adjDeg2[i])
		{
			max = adjDeg2[i];
			vertexIndex = i;
		}
	}
	return vertexIndex;
}


int saturationDegree1(int numberOfVertices1)
{
	int maxSatDeg = -1, vertexIndex = -1; int x;
	int size = -1;
	int adjDegMax = -1;
	int count =0;
	for(int i=0; i<numberOfVertices1; i++)
	{
		if(color1[i] == 0)
		{
			x = adjDeg1[i];
			if(x == 0)
			{
				size = 0;
			}
			int colorCheck[numberOfVertices1];
			for(int j=0; j<numberOfVertices1; j++)
			{
				if(vertices1[i][j] == 1)
				{
					colorCheck[j] = color1[j];
				}
			}
			for(int j=0; j<numberOfVertices1; j++)
			{
				for(int k=0; k<numberOfVertices1; k++)
				{
					if(colorCheck[j] == k)
					{
						count++;
						break;
					}

				}
			}	
			size = count;
			if(maxSatDeg < size)
			{
				maxSatDeg = size;
				vertexIndex = i;
				adjDegMax = x;
				}
			if((maxSatDeg == size) && (x > adjDegMax))
			{
				adjDegMax = x;
				maxSatDeg = size;
				vertexIndex = i;
			}
		}
	}
	return vertexIndex;
}

int saturationDegree2(int numberOfVertices2)
{
	int maxSatDeg = -1, vertexIndex = -1; int x;
	int size = -1;
	int adjDegMax = -1;
	int count =0;
	for(int i=0; i<numberOfVertices2; i++)
	{
		if(color2[i] == 0)
		{
			x = adjDeg2[i];
			if(x == 0)
			{
				size = 0;
			}
			int colorCheck[numberOfVertices2];
			for(int j=0; j<numberOfVertices2; j++)
			{
				if(vertices2[i][j] == 1)
				{
					colorCheck[j] = color2[j];
				}
			}
			for(int j=0; j<numberOfVertices2; j++)
			{
				for(int k=0; k<numberOfVertices2; k++)
				{
					if(colorCheck[j] == k)
					{
						count++;
						break;
					}

				}
			}	
			size = count;
			if(maxSatDeg < size)
			{
				maxSatDeg = size;
				vertexIndex = i;
				adjDegMax = x;
				}
			if((maxSatDeg == size) && (x > adjDegMax))
			{
				adjDegMax = x;
				maxSatDeg = size;
				vertexIndex = i;
			}
		}
	}
	return vertexIndex;
}


void addColorToVertex1(int vertexToBeColored, int numberOfVertices1)
{

	int flag = 0;
	int checkColor[numberOfVertices1];
	for(int j=0; j<numberOfVertices1; j++)
	{
		if(vertices1[vertexToBeColored][j] == 1)
		{
			checkColor[j] = color1[j];
		}
	}
	for(int j=0; j<=numberOfVertices1; j++)
	{
		for(int i=1; i<=numberOfVertices1; i++)
		{
			if(checkColor[j] == i)
			{
				continue;
			}
			else
			{
				color1[vertexToBeColored] = i;
				if (colorMax < i)
				{
					colorMax = i;
					flag = 1;
					break;
				}

			}	
		}
		if(flag == 1)
			break;	
	}
	
}

void addColorToVertex2(int vertexToBeColored, int numberOfVertices2)
{

	int flag = 0;
	int checkColor[numberOfVertices2];
	for(int j=0; j<numberOfVertices2; j++)
	{
		if(vertices2[vertexToBeColored][j] == 1)
		{
			checkColor[j] = color2[j];
		}
	}
	for(int j=0; j<=numberOfVertices2; j++)
	{
		for(int i=1; i<=numberOfVertices2; i++)
		{
			if(checkColor[j] == i)
			{
				continue;
			}
			else
			{
				color2[vertexToBeColored] = i;
				if (colorMax < i)
				{
					colorMax = i;
					flag = 1;
					break;
				}

			}	
		}
		if(flag == 1)
			break;	
	}
	
}

void colorVertex1(int numberOfVertices1)
{

	int first;
	first = maxAdjDeg1(numberOfVertices1);
	color1[first] =1;
	int vertexToBeColored;
	vertexToBeColored = saturationDegree1(numberOfVertices1);

	while(vertexToBeColored != -1)
	{
		addColorToVertex1(vertexToBeColored,numberOfVertices1); // calls a function to add color to the other vertices
		vertexToBeColored = saturationDegree1(numberOfVertices1);
	}

}

void colorVertex2(int numberOfVertices2)
{

	int first;
	first = maxAdjDeg2(numberOfVertices2);
	color1[first] =1;
	int vertexToBeColored;
	vertexToBeColored = saturationDegree2(numberOfVertices2);

	while(vertexToBeColored != -1)
	{
		addColorToVertex2(vertexToBeColored,numberOfVertices2); // calls a function to add color to the other vertices
		vertexToBeColored = saturationDegree2(numberOfVertices2);
	}

}


void initializeVisited(int numberOfVertices1, int numberOfVertices2)
{
	for(int i=0; i<numberOfVertices1; i++)
	{
		visited1[i] = 0;
	}
	for(int i=0; i<numberOfVertices2; i++)
	{
		visited2[i] = 0;
	}
}


void printGraph1(int numberOfVertices1)
{
	printf("\n");
	for(int i=0; i<numberOfVertices1; i++)
	{
		for(int j=0; j<numberOfVertices1; j++)
		{
			printf("%d\t",vertices1[i][j]);
		}
		printf("\n");
	}
}

void printGraph2(int numberOfVertices2)
{
	printf("\n");
	for(int i=0; i<numberOfVertices2; i++)
	{
		for(int j=0; j<numberOfVertices2; j++)
		{
			printf("%d\t",vertices2[i][j]);
		}
		printf("\n");
	}
}

void printColor(int numberOfVertices1, int numberOfVertices2)
{
	printf("\n");
	for(int i=0; i<numberOfVertices1; i++)
	{
		printf("%d\t",color1[i]);
	}

	printf("\n");
	for(int i=0; i<numberOfVertices2; i++)
	{
		printf("%d\t",color2[i]);
	}
}

void generateGraph(int numberOfVertices1, int numberOfVertices2)
{
	addEdge1(numberOfVertices1);
	addEdge2(numberOfVertices2);
	adjacencyDegree1(numberOfVertices1);
	adjacencyDegree2(numberOfVertices2);
	initializeVisited(numberOfVertices1,numberOfVertices2);
	updateShortestPath(numberOfVertices1,numberOfVertices2);
	initializeSaturation(numberOfVertices1,numberOfVertices2);
	colorVertex1(numberOfVertices1);
	colorVertex2(numberOfVertices2);
	//printColor(numberOfVertices1, numberOfVertices2);
	//printGraph1(numberOfVertices1);
	//printGraph2(numberOfVertices2);
}


// do permutation to check all combinations
int checkIsomorphism(int numberOfVertices1, int numberOfVertices2, int numberThreads)
{
	int numberOfThreads = numberThreads;
	//numberOfThreads = omp_get_num_threads(); 
	//printf("\n number of Threads %d ", numberOfThreads);
	//scanf("%d",&numberOfThreads); 
      	omp_set_num_threads(numberOfThreads);
	#pragma omp parallel
	for(int i=0; i<numberOfVertices1; i++)
	{
		int checkDeg = adjDeg1[i];
		int count = 0;

		for(int j=0; j<numberOfVertices2; j++)
		{
			if((adjDeg2[j] == checkDeg) && (visited2[j] == 0))
			{
				for(int k=0; k<numberOfVertices2; k++)
				{
					if(vertices1[i][k] == vertices2[j][k])
					{
						count++;
					}
	
				}
			}

			if(count == numberOfVertices2)
			{
				visited2[j] = 1;
			}
		}


	}

	for(int i=0; i<numberOfVertices2; i++)
	{
		if(visited2[i] == 0)
		{
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[])
{

	int numberThreads;
	if(argc != 2)
	{
		printf(" \n Enter number of threads to be used in command line argument ");
		exit(1);
	}

	numberThreads=atoi(argv[1]);
	if(numberThreads<1)
	{
		printf(" \n Number of threads specified should be more than 1 ");
		exit(1);
	}

	int number1 = 2000,number2 = 2000;
	int check;
	clock_t startTime,endTime;
	/*printf("\nEnter number of vertices for graph 1\n");
	scanf("%d",&number1);
	printf("\nEnter number of vertices for graph 2\n");
	scanf("%d",&number2); */


	memoryAllocate(number1,number2);
	startTime = clock();
	generateGraph(number1,number2);
	check = checkIsomorphism(number1,number2,numberThreads);
	if(check == 0)
	{
		printf("\n Not IsoMorphic \n ");
	}
	else
		printf("\n IsoMorphic \n");
	
	endTime = clock();
	printTime(startTime,endTime);
	return 0;
}


