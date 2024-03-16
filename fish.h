#ifndef UNTITLED3_FISH_H
#define UNTITLED3_FISH_H
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "plankton.h"
#define X_SIZE 48
#define Y_SIZE 211
#define MAX_FISHES 100

typedef struct {
    int x;
    int y;
    int health;
    int bred;
}Fish;

void Make_Fish(Fish fishes[MAX_FISHES], int *num_fishes);

void Remove_Fish(int i, Fish fishes[MAX_FISHES], char field[][Y_SIZE+1]);

void Move_Fish(char field[][Y_SIZE + 1], Fish *f);

void Breed_Fish(int main_fish, Fish *f, Fish fishes[MAX_FISHES], int *num_fishes, char field[][Y_SIZE + 1]);

void Eat_Plankton_Fish(Fish *f, Plankton planktons[MAX_PLANKTON], char field[][Y_SIZE + 1], int *num_planktons);

#endif
