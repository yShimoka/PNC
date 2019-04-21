#ifndef __USAGI_VECTOR_H__
#define __USAGI_VECTOR_H__

#define USG_VECTOR(x, y) (struct USG_Vector) { x, y }

struct USG_Vector {
    float x, y;
};

struct USG_Vector USG_V_add(struct USG_Vector a, struct USG_Vector b);
struct USG_Vector USG_V_sub(struct USG_Vector a, struct USG_Vector b);

struct USG_Vector USG_V_mul(struct USG_Vector a, float v);
struct USG_Vector USG_V_div(struct USG_Vector a, float v);

#endif /* __USAGI_VECTOR_H__ */
