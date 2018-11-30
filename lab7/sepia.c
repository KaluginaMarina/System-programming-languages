#include "sepia.h"

#include <inttypes.h>
#include <glob.h>

static unsigned char sat( uint64_t x) {
    if (x < 256)
        return (unsigned char)x;
    return 255;
}
static void sepia_one(pixel_t* const pixel ) {
    static const float c[3][3] =  {
            { .393f, .769f, .189f },
            { .349f, .686f, .168f },
            { .272f, .543f, .131f } };
    pixel_t const old = *pixel;
    pixel->r = sat( (uint64_t) (old.r * c[0][0] + old.g * c[0][1] + old.b * c[0][2]));
    pixel->g = sat( (uint64_t)(old.r * c[1][0] + old.g * c[1][1] + old.b  * c[1][2]));
    pixel->b = sat( (uint64_t) (old.r * c[2][0] + old.g * c[2][1] + old.b * c[2][2]));
}
void sepia_c_inplace(image_t* pic) {
    size_t i, j;
    size_t w = pic->width;
    size_t h = pic->height;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            sepia_one(pic->data + i*w + j);
        }
    }
}
