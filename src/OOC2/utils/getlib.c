#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>

#define UCHR(c) ((unsigned char)(c))

/*
 * Helper and Error
 */

static void
usage(const char *ext, const char *fmt)
{
  fprintf(stderr,
	  "usage: getlib [-t type] [-f fmt] config1.h config2.h ...\n"
	  "   ex: getlib -t \"%s\" -f \"%s\" ooc/config_ooc.h\n", ext, fmt);
  exit(EXIT_FAILURE);
}

static void
error(const char *fmt, ...)
{
  va_list args;

  fflush(stdout);
  fprintf(stderr, "getlib error: ");
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
    fprintf(stderr, " %s", strerror(errno));
  
  putc('\n', stderr);

  exit(EXIT_FAILURE);
}

/*
 * String and space utilities
 */

static char*
skip_endspc(char *str)
{
  size_t len = strlen(str);

  while (len > 0 && isspace(UCHR(str[len-1])))
    --len;

  str[len] = '\0';

  return str;
}

/*
 * Token and value utilities
 */

static int
get_use(char *buf, char *tok, size_t tok_len)
{
  size_t len = strlen(buf);

  if (len < 4 || strcmp(buf+len-4, "_USE"))
    return -1;

  assert(len-3 < tok_len);

  memcpy(tok, buf, len-3), tok[len-3] = '\0';

  return strtoul(buf+len+1, 0, 10);
}

static char*
get_val(char *buf, char *tok, const char *ext)
{
  size_t len = strlen(tok);

  if (strncmp(buf, tok, len) || strcmp (buf+len, ext))
    return 0;

  return skip_endspc(buf+len+strlen(ext)+1);
}

/*
 * On-fly read functions
 */

static void
skip_c89comment(FILE *fp)
{
  int c, prv_c = 0;

  while ((c = getc(fp)) != EOF && !(c == '/' && prv_c == '*'))
    prv_c = c;
}

static void
skip_c99comment(FILE *fp)
{
  int c;

  while ((c = getc(fp)) != EOF && c != '\n') ;

  ungetc(c, fp);
}

static int
get_chr(FILE *fp)
{
  int c = getc(fp);
  
  if (c == '/') {
    int c = getc(fp);

    switch(c) {
    case '*': skip_c89comment(fp); return ' ';
    case '/': skip_c99comment(fp); return ' ';
    default : ungetc(c, fp);
    }
  }

  return c;
}

static void
skip_spc(FILE *fp)
{
  int c;

  while ((c = get_chr(fp)) != EOF && c != '\n' && isspace(c)) ;

  ungetc(c, fp);
}

static void
get_tok_val(FILE *fp, char *buf, size_t buf_len)
{
  size_t i = strlen(buf)+1;
  int c;

  skip_spc(fp);

  while ((c = get_chr(fp)) != EOF && i < buf_len-1) {
    if (c == '\n') {
      if (buf[i-1] == '\\') /* line continuation */
	skip_spc(fp), c = ' ', --i;
      else {                /* end of #define    */
	ungetc(c, fp);
	break;
      }
    }
    
    buf[i++] = c;
  }

  buf[i] = '\0';
}

static void
get_tok_id(FILE *fp, char *buf, size_t buf_len)
{
  size_t i = 0;
  int c;

  skip_spc(fp);

  while ((c = get_chr(fp)) != EOF && i < buf_len-1) {
    if (!isalnum(c) && c != '_')
      break;

    buf[i++] = c;
  }

  buf[i] = '\0';
  ungetc(c, fp);
}

static int
get_define(FILE *fp)
{
  skip_spc(fp);
  
  return
    getc(fp) == 'd' &&
    getc(fp) == 'e' &&
    getc(fp) == 'f' &&
    getc(fp) == 'i' &&
    getc(fp) == 'n' &&
    getc(fp) == 'e' && isspace(get_chr(fp));
}

static int
get_def(FILE *fp, char *buf, size_t buf_len)
{
  int c, prv_c = 0;

  buf[0] = '\0';

  while ((c = get_chr(fp)) != EOF) {
    if (c == '#' && prv_c == '\n') {
      if (get_define(fp)) {
	get_tok_id (fp, buf, buf_len);
	get_tok_val(fp, buf, buf_len);
	return 1;
      }
      c = 0;
    }
    prv_c = c;
  }

  return 0;
}

/*
 * Main loop
 */

int
main(int argc, char *argv[])
{
  const char *ext = "LIB_DL";
  const char *fmt = "%s ";
  int i = 1;

  if (argc < 2 || !strcmp(argv[i], "-h"))
    usage(ext, fmt);
  
  if (!strcmp(argv[i], "-t"))
    ext = argv[i+1], i += 2;

  if (!strcmp(argv[i], "-f")) 
    fmt = argv[i+1], i += 2;

  for (; i < argc; i++) {
    enum {  line_max_len  = 4095+1,    /*     C99 limitation */
	    token_max_len = 255 +1  }; /* 4 x C99 limitation */

    char buf[ line_max_len] = { 0 };
    char tok[token_max_len] = { 0 };
    FILE *fp = fopen(argv[i], "r");

    if (!fp)
      error("unable to read file %s:", argv[i]);

    while(get_def(fp, buf, sizeof(buf))) {
      int use;
      
      use = get_use(buf, tok, sizeof(tok));

      if      (use  > 0) /* setup token */
	continue;
      else if (use == 0) /* clear token */
	*tok = 0;
      else if (*tok) {   /* check token */
	char *val = get_val(buf, tok, ext);
	
	if (val && *val)
	  printf(fmt, val);
      }
    }
    
    fclose(fp);
  }

  return EXIT_SUCCESS;
}
