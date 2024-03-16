#ifndef UNTITLED3_PLANKTON_H
#define UNTITLED3_PLANKTON_H
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define X_SIZE 48
#define Y_SIZE 211
#define MAX_PLANKTON 100 

typedef struct {
    int x;
    int y;
    int health;
} Plankton;

void Make_Planktons(Plankton planktons[MAX_PLANKTON], int *num_planktons);

void Remove_Plankton(int i, Plankton planktons[MAX_PLANKTON], char field[][Y_SIZE+1]);

void Move_Plankton(char field[][Y_SIZE + 1], Plankton *p);

void Breed_Plankton(Plankton *p, Plankton planktons[MAX_PLANKTON], int *num_planktons, char field[][Y_SIZE + 1]);

#endif
