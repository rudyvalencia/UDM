#define free_ptr(ptr) { free(ptr); ptr = 0; }

int vastprintf(TCHAR **strp, const TCHAR *fmt, va_list ap);
int astprintf(TCHAR **strp, const TCHAR *fmt, ...);
