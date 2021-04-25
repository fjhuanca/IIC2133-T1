#include <stdlib.h>
#include <stdbool.h>
#include "max_tree.h"
#include <stdio.h>

int find_neighbour_l(int coord, int width, int height){
    if ((coord - 1) / width == coord / width) return coord - 1;
    else return -1;
}

int find_neighbour_r(int coord, int width, int height){
    if ((coord + 1) / width == coord / width) return coord + 1;
    else return -1;
}

int find_neighbour_a(int coord, int width, int height){
    if ((coord - width) >= 0) return coord - width;
    else return -1;
}
    
int find_neighbour_b(int coord, int width, int height){
    if ((coord + width) < height*width) return coord + width;
    else return -1;
}

bool add_neighbour(int coord, int u, int *n_nbs, int *nbs, int *pixels){
    if (coord > -1 && pixels[coord] == u){
        bool finded = false;
        for (int i = 0; i<*n_nbs; i++){
            if (nbs[i] == coord) {
                finded = true;
                break;
            }
        }
        if (!finded) {
            nbs[*n_nbs] = coord;
            ++*n_nbs;
            return true;
        }
    }
    return false;
}

bool find_local_neighbours(int coord, int *n_nbs, int *nbs, int u, int width,
                            int height, int* pixels){
    int nl = find_neighbour_l(coord, width, height);
    int nr = find_neighbour_r(coord, width, height);
    int na = find_neighbour_a(coord, width, height);
    int nb = find_neighbour_b(coord, width, height);
    bool added = false;
    if (add_neighbour(nl, u, n_nbs, nbs, pixels)){
        find_local_neighbours(nl, n_nbs, nbs, u, width, height, pixels);
        added = true;
    }
    if (add_neighbour(nr, u, n_nbs, nbs, pixels)){
        find_local_neighbours(nr,n_nbs, nbs, u, width, height, pixels);
        added = true;
    }
    if (add_neighbour(na, u, n_nbs, nbs, pixels)){
        find_local_neighbours(na, n_nbs, nbs, u, width, height, pixels);
        added = true;
    }
    if (add_neighbour(nb, u, n_nbs, nbs, pixels)){
        find_local_neighbours(nb, n_nbs, nbs, u, width, height, pixels);
        added = true;
    }
    return added;
}

bool find_in_neighbourhoods(int coord, int n_nbhs, int *n_nbs, int **neighbourhoods){
    for (int i=0; i<n_nbhs; i++){
        for (int j=0; j<n_nbs[i]; j++){
            if(neighbourhoods[i][j] == coord) return true;
        }
    }
    return false;
}

int find_neighbourhood(int width, int height, int *pixels){
    int n_nbhs = 0;
    int** nbhs = malloc(sizeof(int*) * width*height);
    int* n_nbs = calloc(width*height, sizeof(int));
    for (int i=0; i<width*height; i++){
        if (!find_in_neighbourhoods(i, n_nbhs, n_nbs, nbhs)){
            nbhs[n_nbhs] = malloc(sizeof(int) * width*height);
            if (find_local_neighbours(i, &n_nbs[n_nbhs], nbhs[n_nbhs], 0, width, height, pixels)){
                ++n_nbhs;
            }
        }
    }
    for (int i=0; i<n_nbhs; i++){
        for(int j=0; j<n_nbs[i]; j++){
            printf("Vecindario %d: vecino %d\n", i, nbhs[i][j]);
        }
    }
    return 0;
}