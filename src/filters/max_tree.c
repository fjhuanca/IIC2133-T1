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

bool add_neighbour(int coord, int u, int *n_nbs, int *nbs, int *pixels, bool* filled){
    if (coord > -1 && pixels[coord] > u){
        if (!filled[coord]) {
            nbs[*n_nbs] = coord;
            ++*n_nbs;
            filled[coord] = true;
            return true;
        }
    }
    return false;
}

void find_local_neighbours(int coord, int *n_nbs, int *nbs, int u, int width,
                            int height, int* pixels, bool *filled){
    int nl = find_neighbour_l(coord, width, height);
    int nr = find_neighbour_r(coord, width, height);
    int na = find_neighbour_a(coord, width, height);
    int nb = find_neighbour_b(coord, width, height);
    if (add_neighbour(nl, u, n_nbs, nbs, pixels, filled)){
        find_local_neighbours(nl, n_nbs, nbs, u, width, height, pixels, filled);
    }
    if (add_neighbour(nr, u, n_nbs, nbs, pixels, filled)){
        find_local_neighbours(nr,n_nbs, nbs, u, width, height, pixels, filled);
    }
    if (add_neighbour(na, u, n_nbs, nbs, pixels, filled)){
        find_local_neighbours(na, n_nbs, nbs, u, width, height, pixels, filled);
    }
    if (add_neighbour(nb, u, n_nbs, nbs, pixels, filled)){
        find_local_neighbours(nb, n_nbs, nbs, u, width, height, pixels, filled);
    }
}


int find_neighbourhood(int u, int *searched, int searched_size, int width,
                       int height, int *pixels, int *n_nbhs, int **nbhs,
                       int *n_nbs){
                           
    bool* filled = (bool*) calloc(width*height, sizeof(bool));
    for (int i=0; i<searched_size; i++){
        
        if (!filled[*searched] && pixels[*searched] > u){
            
            nbhs[*n_nbhs] = malloc(sizeof(int) * width*height);
            nbhs[*n_nbhs][0] = *searched;
            filled[*searched] = true;
            n_nbs[*n_nbhs]++;
            find_local_neighbours(*searched, &n_nbs[*n_nbhs], nbhs[*n_nbhs], u, width, height, pixels, filled);
            (*n_nbhs)++;
        }
        searched++;
    }
    free(filled);

    return 0;
}

void add_node(int u, int *searched, int searched_size, int *pixels, Node *parent, int width,
             int height){

    
    int* temp = malloc(searched_size*sizeof(int));
    int index = 0;
    for (int j=0; j<searched_size; j++){
        if (pixels[searched[j]] == u){
            temp[index++] = searched[j];
        }
    }
    if (index > 0){
        parent->u = u;
        parent->pixels = malloc(sizeof(int)*index);
        for (int j=0; j<index; j++){
            parent->pixels[j] = temp[j];
        }        
        free(temp);
        parent->n_pixels = index;
        parent->size = searched_size;
        int n_nbhs = 0;
        int** nbhs = malloc(sizeof(int*) * width*height);
        int* n_nbs = calloc(width*height, sizeof(int));
        find_neighbourhood(u, searched, searched_size, width, height, pixels, &n_nbhs, nbhs, n_nbs);

        for (int i=0; i<n_nbhs; i++){
            Node* p = malloc(sizeof(Node));
            p->u = u;
            p->parent = parent;
            p->n_sons = 0;
            p->sons = malloc(sizeof(Node*) * width * height);
            parent->sons[parent->n_sons] = p;
            parent->n_sons ++;
            add_node(u+1, nbhs[i], n_nbs[i], pixels, p, width, height);
        }
        for (int q=0; q<n_nbhs; q++){
            free(nbhs[q]);
        }
        free(nbhs);
        free(n_nbs);
    }
    else if (u < 128 && searched_size > 0){
        free(temp);
        add_node(u+1, searched, searched_size, pixels, parent, width, height);
    }
    else{
        free(temp);
    }
}

void create_tree(int width, int height, int *pixels, Node* root){
    root->u = 0;
    root->parent = NULL;
    root->n_sons = 0;
    root->sons = malloc(sizeof(Node*) * width * height);
    int* searched = malloc(width*height * sizeof(int));
    for (int i=0; i<width*height; i++){
        searched[i] = i;
    }
    add_node(0, searched, width*height, pixels, root, width, height);
    free(searched);
    // print_tree(root);  

}

void print_tree(Node* nodo){
    printf("Nodo: %d - ", nodo->u);
    for (int j=0; j<nodo->n_pixels;j++){
        printf("p%d ", nodo->pixels[j]);
    }
    if (nodo->parent != NULL){
        printf(" parent(%d)\n", nodo->parent->u);
    }
    else printf("\n");
    for (int i=0; i<nodo->n_sons; i++){
        print_tree(nodo->sons[i]);
    }
}

void destroy_tree(Node* nodo){
    for (int i=0; i<nodo->n_sons; i++){
        destroy_tree(nodo->sons[i]);
    }
    free(nodo->pixels);
    free(nodo->sons);
    free(nodo);
}