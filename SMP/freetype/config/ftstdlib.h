/***************************************************************************/
/*                                                                         */
/*  ftstdlib.h                                                             */
/*                                                                         */
/*    ANSI-specific library and header configuration file (specification   */
/*    only) for win32.                                                     */
/*                                                                         */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/

#ifndef FTSTDLIB_WIN32_H_
#define FTSTDLIB_WIN32_H_

#include "../../../include/freetype/config/ftstdlib.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#undef ft_fopen
#define ft_fopen ft_fopen_win32

__inline FILE * ft_fopen_win32( const char *fname, const char *mode )
{
  FILE* f = NULL;
  errno_t result = 0;
  WCHAR wlpFName[MAX_PATH];
  WCHAR wlpMode[100];
  if (MultiByteToWideChar(CP_UTF8, 0, fname, -1, wlpFName, MAX_PATH) == 0) {
    return NULL;
  }
  if (MultiByteToWideChar(CP_UTF8, 0, mode, -1, wlpMode, 100) == 0) {
    return NULL;
  }

  if (wlpFName && wlpMode)
    result = _wfopen_s(&f, wlpFName, wlpMode);

  if (result == 0)
    return f;

  return NULL;
}

#if defined(WINAPI_FAMILY_PARTITION) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
# undef ft_getenv
# define ft_getenv(x)  NULL
#endif

#endif /* FTSTDLIB_WIN32_H_ */


/* END */
