#include "Engine/Math/Transform.h"

struct USG_Vector USG_V_transform(struct USG_Transform t, struct USG_Vector v) {
    struct USG_Vector out;

    out = USG_V_sub(out, t.origin);
    out.x /= t.right;
    out.y /= t.up;

    return out;
}

struct USG_Vector USG_V_reverseTransform(struct USG_Transform t, struct USG_Vector v) {
    struct USG_Vector out = v;

    out.x *= t.right;
    out.y *= t.up;
    out = USG_V_add(out, t.origin);

    return out;
}


