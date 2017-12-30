#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "compute.h"

/*******************************************************
  IL EST FORMELLEMENT INTERDIT DE CHANGER LE PROTOTYPE
  DES FONCTIONS
 *******************************************************/


/*---------------------------------------
Proto:


But:

Entrees:
--->le tableau des valeurs des pixels de l'image d'origine
(les lignes sont mises les unes � la suite des autres)
--->le nombre de lignes de l'image,
--->le nombre de colonnes de l'image,
--->le tableau des valeurs des pixels de l'image resultat
(les lignes sont mises les unes � la suite des autres)


Sortie:

Rem:

Voir aussi:

---------------------------------------*/
void ComputeImage(guchar *img_orig,
        guint nb_lines,
        guint nb_cols,
        guchar *img_res)
{
    int img_size, i;
    int channel_i, nb_channels=3; /* on travaille sur des images couleurs*/

    printf("Img: l:%d c:%d\n", nb_lines, nb_cols);

    img_size = nb_cols * nb_lines;
    for (i = 0; i < img_size * nb_channels; i = i + nb_channels)
        for (channel_i = 0; channel_i < nb_channels; channel_i++)
            img_res[i + channel_i] = get_pixel_radiometry(img_orig, i);
    guchar radiometry_img[img_size][RAD_VECT_SIZE];
    compute_radiometry(radiometry_img, img_res, nb_cols, nb_lines, RAD_VECT_SIZE);
    for (int i = 0; i < RAD_VECT_SIZE; i++)
        printf("%d\n", radiometry_img[0][i]);
}

int compare_guchar(const void *a, const void *b) {
    return (*(guchar*)b - *(guchar*)a);
}

void compute_radiometry(guchar (*radiometry_img)[RAD_VECT_SIZE], guchar *img, int nb_cols, int nb_lines, int rad_vect_size)
{
    int img_size = nb_cols * nb_lines;
    int rad_idx = 0;
    for (int j = 0; j < nb_cols; j++)
    {
        for (int i = 0; i < nb_cols; i++)
        {
            radiometry_img[i + j * nb_cols][0] = img[i + j * nb_cols];
            rad_idx = 1;
            if ((i + 1) + j * nb_cols < img_size)
            {
                radiometry_img[i + j * nb_cols][rad_idx] = img[(i + 1) + j * nb_cols];
                rad_idx++;
            }
            if ((i - 1) + j * nb_cols > 0)
            {
                radiometry_img[i + j * nb_cols][rad_idx] = img[(i - 1) + j * nb_cols];
                rad_idx++;
            }
            if (i + (j + 1) * nb_cols < img_size)
            {
                radiometry_img[i + j * nb_cols][rad_idx] = img[i + (j + 1) * nb_cols];
                rad_idx++;
            }
            if (i + (j - 1) * nb_cols > 0)
            {
                radiometry_img[i + j * nb_cols][rad_idx] = img[i + (j - 1) * nb_cols];
                rad_idx++;
            }
            while (rad_idx < rad_vect_size)
            {
                radiometry_img[i + j * nb_cols][rad_idx] = 0;
                rad_idx++;
            }
            qsort(&radiometry_img[i + j * nb_cols], rad_vect_size, sizeof (guchar), compare_guchar);
        }
    }
}

guchar get_pixel(guchar *img, enum neighbor_loc loc, int curr_loc)
{
    return 0;
}

guchar get_pixel_radiometry(guchar *img, int curr_loc)
{
    guchar mean_pix = (unsigned char)
        ((
          *(img + curr_loc) +
          *(img + curr_loc + 1) +
          *(img + curr_loc + 2)) / 3);

    return mean_pix;
}
