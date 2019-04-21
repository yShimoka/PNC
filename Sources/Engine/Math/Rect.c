#include "Engine/Math/Rect.h"

struct USG_Rect USG_R_intersect(struct USG_Rect a, struct USG_Rect b) {
    return (struct USG_Rect) {};
}

struct USG_Rect USG_R_mul(struct USG_Rect a, struct USG_Vector v) {
    return USG_RECT( 
        a.origin.x * v.x,
        a.origin.y * v.y,
        a.extent.x * v.x,
        a.extent.y * v.y
    );
}