#define LOGGING
#ifdef LOGGING
#define LOG(...) fprintf(stderr, __VA_ARGS__);
#else
#define LOG(...) 
#endif
