#pragma once
#include <stdbool.h>

struct node;
typedef struct node Node;

struct node{
    int u;
    Node* sons;
};

// typedef struct pixel{
//     int coord;
//     int value;
// } Pixel;

int find_neighbour_l(int coord, int width, int height);
int find_neighbour_r(int coord, int width, int height);
int find_neighbour_a(int coord, int width, int height);
int find_neighbour_b(int coord, int width, int height);
bool add_neighbour(int coord, int u, int *n_nbs, int *nbs, int *pixels);
bool find_local_neighbours(int coord, int *n_nbs, int *nbs, int u, int width,
                          int height, int* pixels);
bool find_in_neighbourhoods(int coord, int n_nbhs, int *n_nbs, int **neighbourhoods);
int find_neighbourhood(int width, int height, int *pixels);