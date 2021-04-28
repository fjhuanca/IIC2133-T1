#pragma once
#include "max_tree.h"

void area_filter(Node* root, int g, int a, int* out_pixels);
void delta_filter(Node* root, float d, int* out_pixels);