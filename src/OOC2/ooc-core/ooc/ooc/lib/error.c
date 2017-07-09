/*
 *******************************
 * Error (low level) handler implementation
 * -----
 * Object Oriented C programming
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * $Id: error.c,v 1.3 2005/12/01 13:57:20 ldeniau Exp $
 *
 * For more information, please see:
 * http://cern.ch/Laurent.Deniau/html/ooc/ooc.html
 *
 *******************************
 */

#define USING_OOC

#include <ooc/ooc/ooc.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

/*
 * -------------------------
 *  Local implementation
 * -------------------------
 */

static void
display(const char *hdr, const char *fmt, va_list args)
{
  fflush(stdout);
  fprintf(stderr, "OOC-%s: ", hdr);
  vfprintf(stderr, fmt, args);
  
  if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
    fprintf(stderr, " %s", strerror(errno));
  
  putc('\n', stderr);
}

/*
 * -------------------------
 *  Global implementation
 * -------------------------
 */

void
ooc_log(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  display("Log", fmt, args);
  va_end(args);
}

void
ooc_debug(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  display("Debug", fmt, args);
  va_end(args);
}

void
ooc_warning(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  display("Warning", fmt, args);
  va_end(args);
}

void
ooc_error(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  display("Error", fmt, args);
  va_end(args);
}

void
ooc_abort(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  display("Abort", fmt, args);
  va_end(args);

  abort();
}
