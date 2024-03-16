#define _CRT_SECURE_NO_WARNINGS
#include "plankton.h"
#include "fish.h"
#include "predator.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <Windows.h>
#include <time.h>

void setcur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Make_Field(char field[X_SIZE][Y_SIZE + 1]) {
    char string[Y_SIZE + 1];
    for (int i = 0; i < X_SIZE; i++) {
        strcpy(string, "");
        if (i == 0 || i == X_SIZE - 1) {
            for (int j = 0; j < Y_SIZE; j++) {
                strcat(string, "#");
            }
        }
        else {
            for (int j = 0; j < Y_SIZE; j++) {
                if (j == 0 || j == Y_SIZE - 1) {
                    strcat(string, "#");
                }
                else {
                    strcat(string, " ");
                }
            }
        }
        strcpy(field[i], string);
    }
}

int main() {
    Plankton planktons[MAX_PLANKTON];
    Fish fishes[MAX_FISHES];
    Predator predators[MAX_PREDATORS];
    int num_planktons = 0;
    int num_fishes = 0;
    int num_predators = 0;
    int step = 1;
    Make_Planktons(planktons, &num_planktons);
    Make_Fish(fishes, &num_fishes);
    Make_Predator(predators, &num_predators);
    char field[X_SIZE][Y_SIZE + 1];
    Make_Field(field);
    srand(time(NULL));
    while(1) {
        system("color 90");
        setcur(0, 0);
        for (int i = 0; i < X_SIZE; i++) {
            puts(field[i]);
        }
        printf("Step: %d Planktons(@): %d Fishes($): %d Predators(%): %d ", step, num_planktons, num_fishes, num_predators);
        step++;
        for (int i = 0; i < num_planktons; i++) {
            if (planktons[i].health == 0) {
                Remove_Plankton(i, planktons, field);
                num_planktons--;
                i--;
                continue;
            }
            Move_Plankton(field, &planktons[i]);
            if (num_planktons < MAX_PLANKTON) {
                Breed_Plankton(&planktons[i], planktons, &num_planktons, field);
            }
        }
        for (int i = 0; i < num_fishes; i++) {
            if (fishes[i].health == 0) {
                Remove_Fish(i, fishes, field);
                num_fishes--;
                i--;
                continue;
            }
            Move_Fish(field, &fishes[i]);
            if (num_fishes < MAX_FISHES) {
                Breed_Fish(i,&fishes[i], fishes, &num_fishes, field);
            }
            if (fishes[i].health < 60) {
                Eat_Plankton_Fish(&fishes[i], planktons, field, &num_planktons);
            }
        }
        for (int i = 0; i < num_predators; i++) {
            if (predators[i].health == 0) {
                Remove_Predator(i, predators, field);
                num_predators--;
                i--;
                continue;
            }
            Move_Predator(field, &predators[i]);
            if (num_predators < MAX_PREDATORS) {
                Breed_Predator(i,&predators[i], predators, &num_predators, field);
            }
            if (predators[i].health < 60) {
                Eat_Fish(&predators[i], fishes, field, &num_fishes);
            }
            else if(predators[i].health < 30) {
                Eat_Plankton_Predator(&predators[i], planktons, field, &num_planktons);
            }
        }
        Sleep(150);
    }
}
