#ifndef RND_UTILS_H_INCLUDED
#define RND_UTILS_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

  /* This function takes m unique values from range 0..n
     and writes them to array dest.
     Please note that written values are sorted
     in descending order */
  void take_m_out_of_n(int m, int n, int *dest);

#ifdef __cplusplus
}
#endif

#endif
