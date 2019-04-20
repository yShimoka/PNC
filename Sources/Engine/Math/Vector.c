#include "Engine/Math/Vector.h"

struct USG_Vector USG_V_add(struct USG_Vector a, struct USG_Vector b) {
    return (struct USG_Vector) {a.x + b.x, a.y + b.y};
}

struct USG_Vector USG_V_sub(struct USG_Vector a, struct USG_Vector b) {
    return (struct USG_Vector) {a.x - b.x, a.y - b.y};
}

struct USG_Vector USG_V_mul(struct USG_Vector a, float v) {
    return (struct USG_Vector) {a.x * v, a.y * v};
}

struct USG_Vector USG_V_div(struct USG_Vector a, float v) {
    return (struct USG_Vector) {a.x / v, a.y / v};
}