#include "filters.h"
#include <stdbool.h>
#include <stdlib.h>

void area_filter(Node* root, int g, int a, int* out_pixels){
    bool cond_g = root->u > g;
    bool cond_a = root->size > a;
    int ng = root->u;
    if (!(cond_a && cond_g)){
        ng = root->parent != NULL ? root->parent->u : 0;
        for (int i = 0; i < root->n_pixels; i++){
            out_pixels[root->pixels[i]] = ng;
        }
    }
    root->u = ng;
    for (int i = 0; i < root->n_sons; i++){
        area_filter(root->sons[i], g, a, out_pixels);
    }
}

void delta_filter(Node* root, float d, int* out_pixels){
    bool cond;
    float delta;
    if (root->parent == NULL) cond = true;
    else{
        delta = (float) (root->parent->size - root->size) /
                 root->parent->size;
        if (!(delta < d)){
            int nu = root->parent->u;
            root->u = nu;
            for (int i = 0; i < root->n_pixels; i++){
                out_pixels[root->pixels[i]] = nu;
            }
        }
    }
    for (int i = 0; i < root->n_sons; i++){
        delta_filter(root->sons[i], d, out_pixels);   
    }
}