#include <stdio.h>

typedef long word_t;

word_t src[8], dst[8];

/* $begin absrev */
/*
 * absrev - copy src to dst in reverse, returning the sum of the absolute
 * value of numbers contained in src array.
 */
word_t absrev(word_t *src, word_t *dst, word_t len)
{
    word_t *dst_rev = dst + len - 1;
    word_t sum = 0;
    word_t val;
    word_t absval;

    while (len > 0) {
        val = *src++;
        *dst_rev-- = val;
        absval = val > 0 ? val : -val;
        sum += absval;
        len--;
    }

    return sum;
}
/* $end absrev */

int main()
{
    word_t i, count;

    for (i = 0; i < 8; i++)
        src[i] = (i + 1) * (i % 2 ? -1 : 1);
    count = absrev(src, dst, 8);
    printf ("sum=%ld\n", count);
    for (i = 0; i < 8; i++)
        printf("%ld ", dst[i]);
    putchar('\n');
    return 0;
}


