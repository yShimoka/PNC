#include "Engine/Math/Rect.h"

float __fmax(float a, float b) { return a > b ? a : b; }
float __fmin(float a, float b) { return a > b ? b : a; }

struct USG_Rect USG_R_intersect(struct USG_Rect a, struct USG_Rect b) {
    float u, d, l, r;

    u = __fmax(a.origin.y, b.origin.y);
    l = __fmax(a.origin.x, b.origin.x);

    d = __fmin(a.origin.y + a.extent.y, b.origin.y + b.extent.y);
    r = __fmin(a.origin.x + a.extent.x, b.origin.x + b.extent.x);

    if (r > l && d > u) return USG_RECT(l, u, r - l, d - u);
    else return USG_RECT(0, 0, 0, 0);
}

struct USG_Rect USG_R_mul(struct USG_Rect a, struct USG_Vector v) {
    return USG_RECT( 
        a.origin.x * v.x,
        a.origin.y * v.y,
        a.extent.x * v.x,
        a.extent.y * v.y
    );
}

int USG_R_containsPoint(struct USG_Rect rect, struct USG_Vector vect) {
    // Check if the point is in the box.
    if (
        rect.origin.x < vect.x &&
        rect.origin.y < vect.y &&
        (rect.origin.x + rect.extent.x) > vect.x &&
        (rect.origin.y + rect.extent.y) > vect.y
    ) {
        return 1;
    } else {
        return 0;
    }
}