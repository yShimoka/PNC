#ifndef __USAGI_TRANSFORM_H__
#define __USAGI_TRANSFORM_H__

#include "Engine/Math/Vector.h"

#define USG_TRANSFORM(x, y, up, right) (struct USG_Transform) { USG_VECTOR(x, y), up, right }
#define USG_DEFAULT_TRANSFORM USG_TRANSFORM(0, 0, 1, 1)

struct USG_Transform {
    struct USG_Vector origin;

    float up, right;
};

struct USG_Vector USG_V_transform(struct USG_Transform t, struct USG_Vector v);
struct USG_Vector USG_V_reverseTransform(struct USG_Transform t, struct USG_Vector v);

#endif /* __USAGI_TRANSFORM_H__ */
