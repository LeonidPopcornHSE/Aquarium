#ifndef UNTITLED3_PREDATOR_H
#define UNTITLED3_PREDATOR_H
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "plankton.h"
#include "fish.h"
#define X_SIZE 48
#define Y_SIZE 211
#define MAX_PREDATORS 100 

typedef struct {
    int x;
    int y;
    int health;
    int bred;
}Predator;

void Make_Predator(Predator predators[MAX_PREDATORS], int *num_predators);

void Remove_Predator(int i, Predator predators[MAX_PREDATORS], char field[][Y_SIZE+1]);

void Move_Predator(char field[][Y_SIZE + 1], Predator *p);

void Breed_Predator(int main_predator, Predator *p, Predator predators[MAX_PREDATORS], int *num_predators, char field[][Y_SIZE + 1]);

void Eat_Fish(Predator *p, Fish fishes[MAX_FISHES], char field[][Y_SIZE + 1], int *num_fishes);

void Eat_Plankton_Predator(Predator *p, Plankton planktons[MAX_PLANKTON], char field[][Y_SIZE + 1], int *num_planktons);

#endif
