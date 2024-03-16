#include "fish.h" 

void Make_Fish (Fish fishes[MAX_FISHES], int *num_fishes) {
    for (int i = 0; i < 12; i++) {
        if (i == 0 || i == 4) {
            fishes[i].x = X_SIZE - 10;
            if (i == 0) {
                fishes[i].y = 10;
            }
            else {
                fishes[i].y = 20;
            }
        }
        else if (i == 1 || i == 5) {
            fishes[i].x = X_SIZE - 5;
            if (i == 1) {
                fishes[i].y = 10;
            }
            else {
                fishes[i].y = 20;
            }
        }
        else if (i == 2 || i == 6) {
            fishes[i].x = 5;
            if (i == 2) {
                fishes[i].y = Y_SIZE - 10;
            }
            else {
                fishes[i].y = Y_SIZE - 20;
            }
        }
        else if (i == 3 || i == 7){
            fishes[i].x = 10;
            if (i == 3) {
                fishes[i].y = Y_SIZE - 10;
            }
            else {
                fishes[i].y = Y_SIZE - 20;
            }
        }
        else if (i == 8 || i == 10) {
            fishes[i].x = X_SIZE / 2 - 3;
            if (i == 8) {
                fishes[i].y = Y_SIZE / 2 - 5;
            }
            else {
                fishes[i].y = Y_SIZE / 2 + 5;
            }
        }
        else {
            fishes[i].x = X_SIZE / 2 + 3;
            if (i == 9) {
                fishes[i].y = Y_SIZE / 2 - 5;
            }
            else {
                fishes[i].y = Y_SIZE / 2 + 5;
            }
        }
        fishes[i].health = 100;
        fishes[i].bred = 0;
        *num_fishes += 1;
    }
}

void Breed_Fish(int main_fish, Fish *f, Fish fishes[MAX_FISHES], int *num_fishes, char field[][Y_SIZE + 1]) {
    int x_distance, y_distance, flag = 0;
    for (int i = 0; i < *num_fishes; i++) {
        if (i == main_fish) { continue; }
        x_distance = f->x - fishes[i].x;
        y_distance = f->y - fishes[i].y;
        if (abs(x_distance) < 2 && abs(y_distance) < 3) {
            if (f->bred < 1 && fishes[i].bred < 1) {
                for (int j = f->x - 1; j < f->x + 2; j++) {
                    for (int k = f->y - 1; k < f->y + 2; k++) {
                        if (field[j][k] == ' ') {
                            Fish new_fish;
                            new_fish.x = j;
                            new_fish.y = k;
                            new_fish.health = 100;
                            new_fish.bred = 0;
                            fishes[*num_fishes] = new_fish;
                            *num_fishes += 1;
                            f->bred += 1;
                            fishes[i].bred += 1;
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

void Eat_Plankton_Fish(Fish *f, Plankton planktons[MAX_PLANKTON], char field[][Y_SIZE + 1], int *num_planktons) {
    int x_distance, y_distance;
    for (int i = 0; i < *num_planktons; i++) {
        x_distance = f->x - planktons[i].x;
        y_distance = f->y - planktons[i].y;
        if (abs(x_distance) < 2 && abs(y_distance) < 3) {
            Remove_Plankton(i, planktons, field);
            *num_planktons -= 1;
            f->health += 60;
            f->bred = 0;
            break;
        }
    }
}

void Remove_Fish(int i, Fish fishes[MAX_FISHES], char field[][Y_SIZE+1]) {
    field[fishes[i].x][fishes[i].y] = ' ';
    for (int j = i; j < MAX_FISHES - 1; j++) {
        fishes[j].x = fishes[j+1].x;
        fishes[j].y = fishes[j+1].y;
        fishes[j].health = fishes[j+1].health;
        fishes[j].bred = fishes[j+1].bred;
    }
}

void Move_Fish(char field[][Y_SIZE + 1], Fish *f) {
    field[f->x][f->y] = ' ';
    int best_variant = 100;
    int x_best_variant, y_best_variant, distance;
    int x_distant_up, x_distant_down, y_distant_left, y_distant_right;
    x_distant_up = f->x % (X_SIZE - 2);
    if (x_distant_up > 15) { x_distant_up = 15; }
    x_distant_down = (X_SIZE - 2) - (f->x % (X_SIZE - 2));
    if (x_distant_down > 15) { x_distant_down = 15; }
    y_distant_left = f->y % (Y_SIZE - 2);
    if (y_distant_left > 30) { y_distant_left = 30; }
    y_distant_right = (Y_SIZE - 2) - (f->y % (Y_SIZE - 2));
    if (y_distant_right > 30) { y_distant_right = 30; }
    if ((f->health > 30) && (f->bred < 1)) {
        for (int i = f->x - x_distant_up; i < f->x + x_distant_down; i++) {
            for (int j = f->y - y_distant_left; j < f->y + y_distant_right; j++) {
                if (field[i][j] == '$') {
                    distance = sqrt(pow(i - f->x, 2) + pow(j - f->y, 2));
                    if (best_variant > distance) {
                        best_variant = distance;
                        x_best_variant = i;
                        y_best_variant = j;
                    }
                }
            }
        }
    }
    else if ((f->health < 60)) {
        for (int i = f->x - x_distant_up; i < f->x + x_distant_down; i++) {
            for (int j = f->y - y_distant_left; j < f->y + y_distant_right; j++) {
                if (field[i][j] == '@') {
                    distance = sqrt(pow(i - f->x, 2) + pow(j - f->y, 2));
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
            case 1: if ((f->x < (X_SIZE - 2)) && (field[f->x + 1][f->y] != '@') && (field[f->x + 1][f->y] != '$') && (field[f->x + 1][f->y] != '%') && (field[f->x + 1][f->y] != '#')) { f->x += 1; } break;
            case 2: if ((f->x > 1) && (field[f->x - 1][f->y] != '@') && (field[f->x - 1][f->y] != '$') && (field[f->x - 1][f->y] != '%') && (field[f->x - 1][f->y] != '#')) { f->x -= 1; } break;
            default: break;
        }
        switch (rand_y) {
            case 1: if ((f->y < (Y_SIZE - 3)) && (field[f->x][f->y + 2] != '@') && (field[f->x][f->y + 2] != '$') && (field[f->x][f->y + 2] != '%') && (field[f->x][f->y + 2] != '#') && (field[f->x][f->y + 1] != '#')) { f->y += 2; } break;
            case 2: if ((f->y > 2) && (field[f->x][f->y - 2] != '@') && (field[f->x][f->y - 2] != '$') && (field[f->x][f->y - 2] != '%') && (field[f->x][f->y - 2] != '#') && (field[f->x][f->y - 1] != '#')) { f->y -= 2; } break;
            default: break;
        }
    }
    else {
        if ((f->x > x_best_variant) && (field[f->x - 1][f->y] != '@') && (field[f->x - 1][f->y] != '$') && (field[f->x - 1][f->y] != '%') && (field[f->x - 1][f->y] != '#')) { f->x--; }
        else if ((field[f->x + 1][f->y] != '@') && (field[f->x + 1][f->y] != '$') && (field[f->x + 1][f->y] != '%') && (field[f->x + 1][f->y] != '#')) { f->x++; }
        if ((f->y > y_best_variant) && (field[f->x][f->y - 2] != '@') && (field[f->x][f->y - 2] != '$') && (field[f->x][f->y - 2] != '%') && (field[f->x][f->y - 2] != '#') && (field[f->x][f->y - 1] != '#')) { f->y -= 2; }
        else if ((field[f->x][f->y + 2] != '@') && (field[f->x][f->y + 2] != '$') && (field[f->x][f->y + 2] != '%') && (field[f->x][f->y + 2] != '#') && (field[f->x][f->y + 1] != '#')) { f->y += 2; }
    }
    field[f->x][f->y] = '$';
    f->health--;
}
