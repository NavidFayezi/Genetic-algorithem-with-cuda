#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHROMOSOME_LENGHT 11


int fitness_function(char chromosome[]){
    
    int i = 0 ;
    int fitness = 0 ;
    char word[] = "Hello world";

    for (i = 0 ; i < CHROMOSOME_LENGHT ; i++){

        fitness -= abs(chromosome[i]-word[i]);
    }

    return fitness ;
}

int main(){
    int myint = fitness_function("Hezmo world");
    printf("%d", myint) ; 
}