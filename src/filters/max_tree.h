#pragma once
#include <stdbool.h>

struct node;
typedef struct node Node;

struct node{
    int u;
    Node *parent;
    Node **sons;
    int n_sons;
    int n_pixels;
    int *pixels;
    int size;
};

// typedef struct pixel{
//     int coord;
//     int value;
// } Pixel;

int find_neighbour_l(int coord, int width, int height);
int find_neighbour_r(int coord, int width, int height);
int find_neighbour_a(int coord, int width, int height);
int find_neighbour_b(int coord, int width, int height);
bool add_neighbour(int coord, int u, int *n_nbs, int *nbs, int *pixels, bool* filled);
bool find_local_neighbours(int coord, int *n_nbs, int *nbs, int u, int width,
                          int height, int* pixels, bool* filled);
int find_neighbourhood(int u, int *searched, int searched_size, int width,
                       int height, int *pixels, int *n_nbhs, int **nbhs,
                       int *n_nbs);


void add_node(int u, int *searched, int searched_size, int *pixels, Node *parent, int width,
             int height);
void create_tree(int width, int height, int *pixels, Node* root);
void destroy_tree(Node* root);