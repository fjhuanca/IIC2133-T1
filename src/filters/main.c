#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../imagelib/image.h"
#include "max_tree.h"
#include "filters.h"


#include <sys/resource.h>

int main(int argc, char** argv){

    const rlim_t kStackSize = 24 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0){
        if (rl.rlim_cur < kStackSize){
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0){
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    // Revisamos los argumentos
    if(argc < 4) {
        printf("Modo de uso: %s <input.png> <output.png> <command> [args]\n", argv[0]);
        return 1;
    }

    // Cargamos la imagen original desde el archivo
    Image* image = img_png_read_from_file(argv[1]);

    /* ------------- POR IMPLEMENTAR -------------- */
    /* Aqui debes crear el MaxTree de la imagen.    */

    Node* root = malloc(sizeof(Node));
    create_tree(image->width, image->height, image->pixels, root);

    // Creamos una nueva imagen de igual tamaño, para el output
    Image* new_img = calloc(1, sizeof(Image));
    *new_img = (Image) {
        .height = image->height,
        .width = image->width,
        .pixel_count = image->pixel_count,
        .pixels = calloc(image->pixel_count, sizeof(int))
    };
    for (int i=0; i<new_img->pixel_count; i++){
        new_img->pixels[i] = image->pixels[i];
    }
    // Filtramos el arbol y lo guardamos en la imagen, segun el filtro que corresponda
    if (! strcmp("delta", argv[3])){
        // Filtro DELTA
        float max_delta = atof(argv[4]);

        /* ------------- POR IMPLEMENTAR -------------- */
        /* Aqui debes implementar el filtro delta y     */
        delta_filter(root, max_delta, new_img->pixels);
        /* guardar la imagen filtrada en new_img.       */

    }
    else if (! strcmp("area", argv[3])){
        
        // Filtro AREA-COLOR
        int min_area = atoi(argv[4]);
        int threshold = atoi(argv[5]);

        /* ------------- POR IMPLEMENTAR -------------- */
        /* Aqui debes implementar el filtro de area y   */
        area_filter(root, threshold, min_area, new_img->pixels);
        /* guardar la imagen filtrada en new_img.       */
        
    }

    // Exportamos la nueva imagen
    printf("Guardando imagen en %s\n", argv[2]);
    img_png_write_to_file(new_img, argv[2]);
    printf("Listo!\n");

    // Liberamos los recursos
    destroy_tree(root);
    img_png_destroy(image);
    img_png_destroy(new_img);

    // Terminamos exitosamente
    return 0;
}