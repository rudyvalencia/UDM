#include "stdafx.h"

int vastprintf(TCHAR **strp, const TCHAR *fmt, va_list ap)
{
	int r = -1, size = _vsctprintf(fmt, ap);

	if ((size >= 0) && (size < INT_MAX))
	{
		*strp = (TCHAR *)calloc(size + 1, sizeof(TCHAR)); //+1 for null
		if (*strp)
		{
			r = _vsntprintf_s(*strp, size + 1, size + 1, fmt, ap);  //+1 for null
			if ((r < 0) || (r > size))
			{
				free_ptr(*strp);
				r = -1;
			}
		}
	}
	else { *strp = 0; }

	return(r);
}

int astprintf(TCHAR **strp, const TCHAR *fmt, ...)
{
	int r;
	va_list ap;
	va_start(ap, fmt);
	r = vastprintf(strp, fmt, ap);
	va_end(ap);
	return(r);
}
