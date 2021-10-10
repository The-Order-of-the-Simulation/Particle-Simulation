# C/C++ Vector Math

This series of C/C++ headers contain structs and

Some of these functions could be merged and made smaller, but they are deliberately written so that the compiler (e.g. GCC with `-Ofast`) can better auto-vectorize them. I (@Zi7ar21) have done some research on vectorization and discovered `immintrin.h` and how to use it, but not all processors support the same vectorization options. Besides, I think the compiler can more efficiently optimize this for vectors with lengths that aren't exponents of 2.

A lot of these functions are also not inlined, because i have found that it can cause issues with certain compiler settings (once again, e.g. GCC with `-Ofast`). I have tested inlined vs. not inlined performance in another project and it didn't make a noticable difference.
