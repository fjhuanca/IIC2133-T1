#include "filters.h"
#include <stdbool.h>
#include <stdlib.h>

int area_filter(Node* root, int g, int a, int* out_pixels){
    bool cond_g = true;
    bool cond_a = root->n_pixels > a;
    for (int i = 0; i < root->n_pixels; i++){
        if (out_pixels[root->pixels[i]] <= g) {cond_g = false; break;}
    }
    if (!(cond_a && cond_g)){
        int ng = root->parent != NULL ? root->parent->u : 0;
        root->u = ng;
        for (int i = 0; i < root->n_pixels; i++){
            out_pixels[root->pixels[i]] = ng;
        }
    }
    for (int i = 0; i < root->n_sons; i++){
        area_filter(root->sons[i], g, a, out_pixels);
    }
}

// int iter_area_tree(Node* root, int g, int a, int* out_pixels){
// }