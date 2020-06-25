#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include<stdlib.h>
#include <curand_kernel.h>
#include <ctime>



#define thrdperblc 128
#define POPULATION 10000



__global__ void crossover(char* population) {
    int i, first_start, second_start, first_end, second_end, iterator,endofpopulation;
    int tId = blockIdx.x * thrdperblc + threadIdx.x;
    if (tId <= POPULATION / 2) {
        iterator = 0;
        first_start = tId * 11 * 2;
        first_end = first_start + 7;
        endofpopulation =  (tId / 2 * 11) + POPULATION * 11;
        for (i = first_start; i <first_end ;i++) {
            population[ endofpopulation + iterator] = population[i];
            iterator++;
        }
        second_start = first_start + 18;
        second_end = second_start + 4;
        for (i = second_start; i < second_end ; i++) {
            population[endofpopulation + iterator] = population[i];
            iterator++;
        }
    }
}

__global__ void mutatation(char* population) {
    int i,start,end;
    int tId = blockIdx.x * thrdperblc + threadIdx.x;
    if (tId <= POPULATION / 2) {
        curandState state;
        char letters[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        start = POPULATION * 11 + (tId * 11);
        end = start + 11;
        for (i = start; i < end ; i++) {
            curand_init((unsigned long long)clock() + tId + 1, 0, 0, &state);
            int randnum = (int)( 834 * curand_uniform_double(&state));
            if ((int)randnum % 10 > 7) {
                population[i] = letters[randnum % 27];
            }
        }
    }

}

int fitness(char* chr) {
    int i = 0;
    int fitness_val = 0;
    char word[] = "HELLO WORLD";
    for (i = 0; i < 11; i++) {
        if(chr[i] == word[i])
            fitness_val += 5;
        else {
            fitness_val -= abs(chr[i] - word[i]);
        }
    }
    return fitness_val;
}

int compare(const void* first, const void* second)
{
    char* f = ((char*)first);
    char* s = ((char*)second);
    int temp = fitness(s) - fitness(f);
    return temp;
}

void init_population(char* population) {
    char letters[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for (i = 0; i < POPULATION * 11; i++) {
        population[i] = letters[rand() % 27];
    }

}

int main()
{
    int i;
    float time;
    cudaEvent_t start, stop;
    char* population = (char*)malloc(sizeof(char) * (POPULATION + POPULATION / 2) * 11 );
    char* d_population;
    cudaMalloc(&d_population, sizeof(char) * (POPULATION + POPULATION / 2) * 11 );
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);
    init_population(population);
    qsort(population, POPULATION, sizeof(char) * 11, compare);
    while (fitness(population) != 55) {
        cudaMemcpy(d_population, population, sizeof(char) * 11 * (POPULATION), cudaMemcpyHostToDevice);
        crossover << < POPULATION/ 2 / thrdperblc  + 1, thrdperblc >> > (d_population);
        mutatation << < POPULATION / 2 / thrdperblc + 1, thrdperblc >> > (d_population);
        cudaMemcpy(population, d_population, sizeof(char) * 11 * (POPULATION + POPULATION/2), cudaMemcpyDeviceToHost);
        qsort(population, POPULATION + POPULATION / 2, sizeof(char) * 11, compare);
    }
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time, start, stop);
    for (i = 0; i < 11; i++)
        printf("%c", population[i]);
    printf("\n");
    printf("execution time is : %f miliseconds \n", time);
    cudaFree(d_population);
    free(population);
    return 0;
}
