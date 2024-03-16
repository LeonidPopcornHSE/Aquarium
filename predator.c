#include "predator.h"

void Make_Predator(Predator predators[MAX_PREDATORS], int *num_predators) {
    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 4) {
            predators[i].x = 15;
            if (i == 0) {
                predators[i].y = 10;
            }
            else {
                predators[i].y = 20;
            } 
        }
        else if (i == 1 || i == 5) {
            predators[i].x = 10;
            if (i == 1) {
                predators[i].y = 10;
            }
            else {
                predators[i].y = 20;
            }
        }
        else if (i == 2 || i == 6) {
            predators[i].x = X_SIZE - 10;
            if (i == 2) {
                predators[i].y = Y_SIZE - 10;
            }
            else {
                predators[i].y = Y_SIZE - 20;
            }
        }
        else {
            predators[i].x = X_SIZE - 15;
            if (i == 3) {
                predators[i].y = Y_SIZE - 10;
            }
            else {
                predators[i].y = Y_SIZE - 20;
            }
        }
        predators[i].health = 100;
        predators[i].bred = 0;
        *num_predators += 1;
    }
}

void Breed_Predator(int main_predator, Predator *p, Predator predators[MAX_PREDATORS], int *num_predators, char field[][Y_SIZE + 1]) {
    int x_distance, y_distance, flag = 0;
    for (int i = 0; i < *num_predators; i++) {
        if (i == main_predator) { continue; }
        x_distance = p->x - predators[i].x;
        y_distance = p->y - predators[i].y;
        if (abs(x_distance) < 2 && abs(y_distance) < 3) {
            if (p->bred == 0 && predators[i].bred == 0) {
                for (int j = p->x - 1; j < p->x + 2; j++) {
                    for (int k = p->y - 1; k < p->y + 2; k++) {
                        if (field[j][k] == ' ') {
                            Predator new_predator;
                            new_predator.x = j;
                            new_predator.y = k;
                            new_predator.health = 100;
                            new_predator.bred = 0;
                            predators[*num_predators] = new_predator;
                            *num_predators += 1;
                            p->bred = 1;
                            predators[i].bred = 1;
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 1) {
                        break;
                    }
                }
            }
            break;
        }
    }
}

void Eat_Fish(Predator *p, Fish fishes[MAX_FISHES], char field[][Y_SIZE + 1], int *num_fishes) {
    int x_distance, y_distance;
    for (int i = 0; i < *num_fishes; i++) {
        x_distance = p->x - fishes[i].x;
        y_distance = p->y - fishes[i].y;
        if (abs(x_distance) < 2 && abs(y_distance) < 3) {
            Remove_Fish(i, fishes, field);
            *num_fishes -= 1;
            p->health += 60;
            p->bred = 0;
            break;
        }
    }
}

void Eat_Plankton_Predator(Predator *p, Plankton planktons[MAX_PLANKTON], char field[][Y_SIZE + 1], int *num_planktons) {
    int x_distance, y_distance;
    for (int i = 0; i < *num_planktons; i++) {
        x_distance = p->x - planktons[i].x;
        y_distance = p->y - planktons[i].y;
        if (abs(x_distance) < 2 && abs(y_distance) < 3) {
            Remove_Plankton(i, planktons, field);
            *num_planktons -= 1;
            p->health += 40;
            p->bred = 0;
            break;
        }
    }
}

void Remove_Predator(int i, Predator predators[MAX_PREDATORS], char field[][Y_SIZE+1]) {
    field[predators[i].x][predators[i].y] = ' ';
    for (int j = i; j < MAX_PREDATORS - 1; j++) {
        predators[j].x = predators[j+1].x;
        predators[j].y = predators[j+1].y;
        predators[j].health = predators[j+1].health;
        predators[j].bred = predators[j+1].bred;
    }
}

void Move_Predator(char field[][Y_SIZE + 1], Predator *p) {
    field[p->x][p->y] = ' ';
    int best_variant = 100;
    int x_best_variant, y_best_variant, distance;
    int x_distant_up, x_distant_down, y_distant_left, y_distant_right;
    x_distant_up = p->x % X_SIZE - 2;
    if (x_distant_up > 10) { x_distant_up = 10; }
    x_distant_down = X_SIZE - 2 - (p->x % X_SIZE - 2);
    if (x_distant_down > 10) { x_distant_down = 10; }
    y_distant_left = p->y % (Y_SIZE - 2);
    if (y_distant_left > 20) { y_distant_left = 20; }
    y_distant_right = (Y_SIZE - 2) - (p->y % (Y_SIZE - 2));
    if (y_distant_right > 20) { y_distant_right = 20; }
    if ((p->health > 30) && (p->bred == 0)) {
        for (int i = p->x - x_distant_up; i < p->x + x_distant_down; i++) {
            for (int j = p->y - y_distant_left; j < p->y + y_distant_right; j++) {
                if (field[i][j] == '%') {
                    distance = sqrt(pow(i - p->x, 2) + pow(j - p->y, 2));
                    if (best_variant > distance) {
                        best_variant = distance;
                        x_best_variant = i;
                        y_best_variant = j;
                    }
                }
            }
        }
    }
    else if (p->health < 60) {
        for (int i = p->x - x_distant_up; i < p->x + x_distant_down; i++) {
            for (int j = p->y - y_distant_left; j < p->y + y_distant_right; j++) {
                if (field[i][j] == '$') {
                    distance = sqrt(pow(i - p->x, 2) + pow(j - p->y, 2));
                    if (best_variant > distance) {
                        best_variant = distance;
                        x_best_variant = i;
                        y_best_variant = j;
                    }
                }
            }
        }
    }
    else if (p->health < 50) {
        for (int i = p->x - x_distant_up; i < p->x + x_distant_down; i++) {
            for (int j = p->y - y_distant_left; j < p->y + y_distant_right; j++) {
                if (field[i][j] == '@') {
                    distance = sqrt(pow(i - p->x, 2) + pow(j - p->y, 2));
                    if (best_variant > distance) {
                        best_variant = distance;
                        x_best_variant = i;
                        y_best_variant = j;
                    }
                }
            }
        }
    }
    if (best_variant == 100) {
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
    }
    else {
        if ((p->x > x_best_variant) && (field[p->x - 1][p->y] != '@') && (field[p->x - 1][p->y] != '$') && (field[p->x - 1][p->y] != '%') && (field[p->x - 1][p->y] != '#')) { p->x--; }
        else if ((field[p->x + 1][p->y] != '@') && (field[p->x + 1][p->y] != '$') && (field[p->x + 1][p->y] != '%') && (field[p->x + 1][p->y] != '#')) { p->x++; }
        if ((p->y > y_best_variant) && (field[p->x][p->y - 2] != '@') && (field[p->x][p->y - 2] != '$') && (field[p->x][p->y - 2] != '%') && (field[p->x][p->y - 2] != '#') && (field[p->x][p->y - 1] != '#')) { p->y -= 2; }
        else if ((field[p->x][p->y + 2] != '@') && (field[p->x][p->y + 2] != '$') && (field[p->x][p->y + 2] != '%') && (field[p->x][p->y + 2] != '#') && (field[p->x][p->y + 1] != '#')) { p->y += 2; }
    }
    field[p->x][p->y] = '%';
    p->health--;
}
