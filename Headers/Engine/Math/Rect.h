#ifndef __USAGI_RECT_H__
#define __USAGI_RECT_H__

#include "Engine/Math/Vector.h"

#define USG_R_SDL(Rect) (SDL_Rect) { Rect.origin.x, Rect.origin.y, Rect.extent.x, Rect.extent.y }
#define USG_RECT(x, y, w, h) (struct USG_Rect) { USG_VECTOR(x, y), USG_VECTOR(w, h) }
#define USG_RECT_V(ori, ext) (struct USG_Rect) { ori, ext }
#define USG_RECT_UNIT USG_RECT(0, 0, 1, 1)

struct USG_Rect {
    struct USG_Vector origin, extent;
};

struct USG_Rect USG_R_intersect(struct USG_Rect a, struct USG_Rect b);
struct USG_Rect USG_R_mul(struct USG_Rect a, struct USG_Vector v);

int USG_R_containsPoint(struct USG_Rect rect, struct USG_Vector vect);

#endif /* __USAGI_RECT_H__ */
