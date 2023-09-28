#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    if ((slices_amount % width != 0 || slices_amount / width >= height) &&
        (slices_amount % height != 0 || slices_amount / height >= width)) {
        return false;
    }
    return true;
};