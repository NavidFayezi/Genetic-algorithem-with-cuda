#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <windows.h>

#define CHROMOSOME_LENGHT 11
#define POPULATION 10000

int fitness(char* chr) {
    int i = 0;
    int fitness_val = 0;
    char word[] = "HELLO WORLD";
    for (i = 0; i < 11; i++) {
        if (chr[i] == word[i])
            fitness_val += 5;
        else {
            fitness_val -= abs(chr[i] - word[i]);
        }
    }
    return fitness_val;
}


void init_population(char** array) {
    char letters[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0, j = 0;
    for (i = 0; i < (POPULATION + POPULATION / 2); i++) {
        array[i] = (char*)malloc((CHROMOSOME_LENGHT+1) * sizeof(char));
        for (j = 0; j < CHROMOSOME_LENGHT; j++) {
            array[i][j] = letters[(rand() % 27)];
        }
        array[i][j] = '\0';
    }
}

int compare(const void** first, const void** second)
{
    char** f = ((char**)first);
    char** s = ((char**)second);
    int temp = fitness(*s) - fitness(*f);
    return temp;

}

void crossover(char* first,char* second,char* dest) {
    int i;
    for(i = 0 ; i<7 ;i++)
        dest[i] = first[i];
    for (i = 7; i < 11;i++) {
       // if(word[i] == b[i])
            dest[i] = second[i];
    }
}

void mutate(char* chr) {
    
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int i,random;

    for (i = 0; i < CHROMOSOME_LENGHT; i++) {
       random = rand();
        if (rand() % 10 > 7) {
            chr[i] = alphabet[random % 27];
        }
    }
}

int main() {

    int i = 0;
    int counter;
   
    char** population = (char**)malloc(sizeof(char*) * (POPULATION + POPULATION /2));    // *2 -> make space for chromosomes made in crossover function
    double start_time = omp_get_wtime();
    
    
    init_population(population);

   
    qsort(population, POPULATION, sizeof(char*), compare);

    while (fitness(population[0])!=55) {
      
        counter = POPULATION;
        for (i = 0; i < POPULATION-1; i+=2) {

            crossover(population[i], population[i + 1], population[counter]);   // store the crossover results in population[counter]
            counter++;
        }

        for (i = POPULATION ; i < (POPULATION + (POPULATION / 2)); i++) {
            mutate(population[i]);
        }

        qsort(population, (POPULATION + (POPULATION / 2)), sizeof(char*), compare);
       /* for (i = 0; i < POPULATION; i++) {
            printf(population[i]);
            printf("\n %d", fitness_function(population[i]));
            printf("\n");
        }*/

    }
    double time = omp_get_wtime() - start_time;
    printf(population[0]);
    printf("\nexecution time is %f seconds", time);
    free(population);


}