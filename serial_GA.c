#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHROMOSOME_LENGHT 11
#define POPULATION 500

int fitness_function(char chromosome[]) {

    int i = 0;
    int fitness = 0;
    char word[] = "Hello world";

    for (i = 0; i < CHROMOSOME_LENGHT; i++) {

        fitness -= abs(chromosome[i] - word[i]);
    }

    return fitness;
}

void init_population(char** a) {

    int i = 0, j = 0;
    for (i = 0; i < POPULATION; i++) {
        a[i] = (char*)malloc((CHROMOSOME_LENGHT+1) * sizeof(char));
        for (j = 0; j < CHROMOSOME_LENGHT; j++) {
            a[i][j] = (char)(65 + (rand() % 26));
        }
        a[i][j] = '\0';
    }
}

int main() {
    int i = 0;
    char** population = (char**)malloc(sizeof(char*) * POPULATION);
    init_population(population);
    for (i = 0; i < POPULATION; i++) {
        printf(population[i]);
        printf("\n");
    }
    int myint = fitness_function((char*)"Hezmo world");
    printf("%c", (char)65);
}