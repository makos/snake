#ifndef UTILS_H
#define UTILS_H
typedef struct Vec Vec_t;

int is_eq(Vec_t dir, Vec_t other);
Vec_t random_vec(int maxy, int maxx);
Vec_t reverse_dir(Vec_t dir);

#endif //UTILS_H