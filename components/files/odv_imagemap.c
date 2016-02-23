#include "odv_imagemap.h"

struct ODVImageMap *odv_imagemap_new(struct ODVFile *file)
{
    struct ODVImage *img = NULL;
    struct ODVImageMap *imgmap = NULL;

    img = odv_image_parse(file);
    if (img == NULL) {
        return NULL;
    }
    imgmap = calloc(1, sizeof (struct ODVImageMap));
    if (imgmap == NULL) {
        fprintf(stderr, "[-] odv_imagemap_new - calloc failed\n");
        odv_image_clean(img);
        return NULL;
    }
    imgmap->images = NULL;
    imgmap->image_count = 0;
    odv_imagemap_add(imgmap, img);
    return imgmap;
}

int odv_imagemap_radd(struct ODVImageMap *imgmap, struct ODVFile *file)
{
    struct ODVImage *img = NULL;

    img = odv_image_parse(file);
    if (img == NULL) {
        return 0;
    }
    if (odv_imagemap_add(imgmap, img) == 0) {
        free(img);
        return 0;
    }
    return 1;
}

int odv_imagemap_add(struct ODVImageMap *imgmap, struct ODVImage *img)
{
    imgmap->images = realloc(imgmap->images, (imgmap->image_count + 1) * sizeof (struct ODVImage*));
    if (imgmap->images == NULL) {
        fprintf(stderr, "[-] odv_imagemap_add - realloc failed\n");
        return 0;
    }
    imgmap->images[imgmap->image_count] = img;
    imgmap->image_count += 1;
    return 1;
}

void odv_imagemap_info(const struct ODVImageMap *imgmap)
{
    unsigned int i;

    if (imgmap == NULL)
        return;
    printf("[- ODV IMAGEMAP information -]\n");
    printf("image_count : 0x%08X\n", imgmap->image_count);
    for (i = 0; i < imgmap->image_count; i++) {
        odv_image_info(imgmap->images[i]);
    }
    printf("[-------------------------]\n");
}

void odv_imagemap_clean(struct ODVImageMap *imgmap)
{
    unsigned int i;

    if (imgmap == NULL)
        return;
    if (imgmap->images != NULL) {
        for (i = 0; i < imgmap->image_count; i++) {
            odv_image_clean(imgmap->images[i]);
        }
        free(imgmap->images);
    }
    free(imgmap);
}