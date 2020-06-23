#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHROMOSOME_LENGHT 11
#define POPULATION 10000

int fitness_function(char* chromosome) {

    int i = 0;
    int fitness = 0;
    char word[] = "HELLO WORLD";

    for (i = 0; i < CHROMOSOME_LENGHT; i++) {

        fitness -= abs(chromosome[i] - word[i]);
    }

    return fitness;
}

void init_population(char** a) {

    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int i = 0, j = 0;

    for (i = 0; i < POPULATION*2 ; i++) {
        a[i] = (char*)malloc((CHROMOSOME_LENGHT+1) * sizeof(char));
        for (j = 0; j < CHROMOSOME_LENGHT; j++) {
            a[i][j] = alphabet[(rand() % 27)];
        }
        a[i][j] = '\0';
    }
}

int comp(const void** elem1, const void** elem2)
{
    char** f = ((char**)elem1);
    char** s = ((char**)elem2);
    int temp = fitness_function(*s) - fitness_function(*f);
    return temp;

}

void crossover(char* a,char* b,char* dest) {
   
    char word[] = "HELLO WORLD";
    int i;
    for(i = 0 ; i<6 ;i++)
        dest[i] = a[i];
    for (i = 6; i < 11;i++) {
       // if(word[i] == b[i])
            dest[i] = b[i];
    }
}

void mutate(char* chromosome) {
    
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    int i,random;

    for (i = 0; i < CHROMOSOME_LENGHT; i++) {
       random = rand();
        if (rand() % 10 > 6) {
            chromosome[i] = alphabet[random % 27];
        }
    }
}

int main() {

    char word[] = "Hello world";
    int i = 0;
    int counter;
   
    char** population = (char**)malloc(sizeof(char*) * POPULATION  * 2);    // *2 -> make space for chromosomes made in crossover function
    init_population(population);

   
    qsort(population, POPULATION, sizeof(char*), comp);

    while (fitness_function(population[0])) {
      
        counter = POPULATION;
        for (i = 0; i < POPULATION-1; i+=2) {

            crossover(population[i], population[i + 1], population[counter]);   // store the crossover results in population[counter]
            counter++;
        }

        for (i = POPULATION ; i < (POPULATION + (POPULATION / 2)); i++) {
            mutate(population[i]);
        }

        qsort(population, (POPULATION + (POPULATION / 2)), sizeof(char*), comp);
       /* for (i = 0; i < POPULATION; i++) {
            printf(population[i]);
            printf("\n %d", fitness_function(population[i]));
            printf("\n");
        }*/

    }
        
    printf(population[0]);
    free(population);


}