
#ifndef SJRAND_H__
#define SJRAND_H__

inline void *sj_srand(unsigned long long seed)
{
  unsigned long long *a;
  a = (unsigned long long *)malloc(sizeof *a);
  *a = seed;
  return (void *)a;
}

inline double sj_rand(void *handle)
{
  unsigned long long *a = (unsigned long long *)handle, b;
  *a = *a * 7212336353ULL + 8963315421273233617ULL;
  b = *a & 0x3fffffffffffffffULL | 0x3ff0000000000000ULL;
  return *(double *)(&b) - 1.0;
}

inline void sj_drand(void *handle)
{
  free(handle);
}

#endif

