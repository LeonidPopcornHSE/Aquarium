#include "plankton.h"

void Make_Planktons(Plankton planktons[MAX_PLANKTON], int *num_planktons) {
    for(int i = 0; i < 4; i++) {
        if (i == 0 || i == 2) {
            planktons[i].x = X_SIZE / 4;
        }
        else { 
            planktons[i].x = X_SIZE - (X_SIZE / 4);
        }
        if (i == 0 || i == 1) {
            planktons[i].y = Y_SIZE / 4;
        }
        else {
            planktons[i].y = Y_SIZE - (Y_SIZE / 4);
        }
        planktons[i].health = 30;
        *num_planktons += 1;
    }
}

void Remove_Plankton(int i, Plankton planktons[MAX_PLANKTON], char field[][Y_SIZE+1]) {
    field[planktons[i].x][planktons[i].y] = ' ';
    for (int j = i; j < MAX_PLANKTON - 1; j++) {
        planktons[j].x = planktons[j+1].x;
        planktons[j].y = planktons[j+1].y;
        planktons[j].health = planktons[j+1].health;
    }
}

void Move_Plankton(char field[][Y_SIZE + 1], Plankton *p) {
    field[p->x][p->y] = ' ';
    int rand_x = rand() * 1.0 / RAND_MAX * 3 + 1;
    int rand_y = rand() * 1.0 / RAND_MAX * 3 + 1;
    switch (rand_x) {
        case 1: if ((p->x < (X_SIZE - 2)) && (field[p->x + 1][p->y] != '@') && (field[p->x + 1][p->y] != '$') && (field[p->x + 1][p->y] != '%') && (field[p->x + 1][p->y] != '#')) { p->x += 1; } break;
        case 2: if ((p->x > 1) && (field[p->x - 1][p->y] != '@') && (field[p->x - 1][p->y] != '$') && (field[p->x - 1][p->y] != '%') && (field[p->x - 1][p->y] != '#')) { p->x -= 1; } break;
        default: break;
    }
    switch (rand_y) {
        case 1: if ((p->y < (Y_SIZE - 3)) && (field[p->x][p->y + 2] != '@') && (field[p->x][p->y + 2] != '$') && (field[p->x][p->y + 2] != '%') && (field[p->x][p->y + 2] != '#') && (field[p->x][p->y + 1] != '#')) { p->y += 2; } break;
        case 2: if ((p->y > 2) && (field[p->x][p->y - 2] != '@') && (field[p->x][p->y - 2] != '$') && (field[p->x][p->y - 2] != '%') && (field[p->x][p->y - 2] != '#') && (field[p->x][p->y - 1] != '#')) { p->y -= 2; } break;
        default: break;
    }
    field[p->x][p->y] = '@';
    p->health--;
}

void Breed_Plankton(Plankton *p, Plankton planktons[MAX_PLANKTON], int *num_planktons, char field[][Y_SIZE + 1]) {
    int flag = 0;
    if (p->health == 10 || p->health == 20) {
        for (int i = p->x - 1; i < p->x + 2; i++) {
            for (int j = p->y - 1; j < p->y + 2; j++) {
                if (field[i][j] == ' ') {
                    Plankton new_plankton;
                    new_plankton.x = i;
                    new_plankton.y = j;
                    new_plankton.health = 30;
                    planktons[*num_planktons] = new_plankton;
                    *num_planktons += 1;
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) {
                break;
            }
        }
    }
}