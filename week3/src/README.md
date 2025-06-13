## References

### gettimeofday

https://www.mm2d.net/main/prog/c/time-04.html

https://armadillo.atmark-techno.com/blog/615/2799

```c
#include <sys/time.h>

/* この構造体が返ってくる */
// 実際の時間: tv_sec + tv_usec / 1000000
struct timeval {
    time_t tv_sec;            /* Seconds.  */
    suseconds_t tv_usec;      /* Microseconds.  */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);
```

### fgets, fputs

https://www.ibm.com/docs/ja/i/7.4.0?topic=functions-fgets-read-string#fgets

https://www.ibm.com/docs/ja/i/7.4.0?topic=functions-fputs-write-string

### fread, fwrite

https://www.ibm.com/docs/ja/i/7.4.0?topic=functions-fread-read-items

https://www.ibm.com/docs/ja/i/7.4.0?topic=functions-fwrite-write-items#fwrite
