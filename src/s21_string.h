
#include <stdarg.h>
#include <stdlib.h>

#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

typedef unsigned long s21_size_t;
#define S21_NULL ((void *)0)

#define SPECIFIER '%'
#define SPECIFICATORS "cdefginopsuxEGX%%"
#define FLOATSPEC "efgEG"
#define FLAGS "+- #0"
#define LENGTH "hlL"
#define DIGITS "0123456789"
#define DIGITS_N_STAR "*0123456789"
#define WHITE_SPACES " \n\t\v\f\r"
#define DIGIT_LEN 22  // "18446744073709551615".len + 1
#define FLEN 1079     // 3 + DBL_MANT_DIG - DBL_MIN_EXP

#define TRUE 1
#define FALSE 0

#define MANY 3000

#if defined(__APPLE__) && defined(__MACH__)
#define IS_APPLE 1
#define S21_ERROR_COUNT 107
static const char s21_error_array[S21_ERROR_COUNT][100] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full"};
#else
#define IS_APPLE 0
#define S21_ERROR_COUNT 134
static const char s21_error_array[S21_ERROR_COUNT][100] = {
    "No error information",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "I/O error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child process",
    "Resource temporarily unavailable",
    "Out of memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "No file descriptors available",
    "Not a tty",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Invalid seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Domain error",
    "Result not representable",
    "Resource deadlock would occur",
    "Filename too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Symbolic link loop",
    "No error information",
    "No message of desired type",
    "Identifier removed",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Device not a stream",
    "No data available",
    "Device timeout",
    "Out of streams resources",
    "No error information",
    "No error information",
    "No error information",
    "Link has been severed",
    "No error information",
    "No error information",
    "No error information",
    "Protocol error",
    "Multihop attempted",
    "No error information",
    "Bad message",
    "Value too large for data type",
    "No error information",
    "File descriptor in bad state",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Illegal byte sequence",
    "No error information",
    "No error information",
    "No error information",
    "Not a socket",
    "Destination address required",
    "Message too large",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address in use",
    "Address not available",
    "Network is down",
    "Network unreachable",
    "Connection reset by network",
    "Connection aborted",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is connected",
    "Socket not connected",
    "Cannot send after socket shutdown",
    "No error information",
    "Operation timed out",
    "Connection refused",
    "Host is down",
    "Host is unreachable",
    "Operation already in progress",
    "Operation in progress",
    "Stale file handle",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Remote I/O error",
    "Quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "No error information",
    "No error information",
    "No error information",
    "No error information",
    "Previous owner died",
    "State not recoverable",
    "No error information",
    "No error information",
};
#endif

typedef struct flags {
  unsigned short minus;
  unsigned short plus;
  unsigned short space;
  unsigned short sharp;
  unsigned short zero;
} flags;

typedef struct specifier_options {
  flags flag;
  int width;
  int precision;
  char len;

  char *start;
  char *finish;
} specifier_options;

// --------------------- printf + helpers ----------------------------
int s21_sprintf(char *, const char *, ...);

void s21_parse_format(char *, const char *);
void s21_reset_options(specifier_options *opts);
void s21_apply_default(specifier_options *opts);
void s21_set_flag(char, specifier_options *);
void s21_read_p_options(const char *, specifier_options *, va_list);

s21_size_t s21_build_fragment(char *, specifier_options *, va_list, int);
void s21_put_char(char *, char);
s21_size_t s21_put_nchar(char **, char, s21_size_t);

void s21_ins_pref(char **, s21_size_t *, s21_size_t, short);
s21_size_t s21_insert_sign(char **, s21_size_t, flags *, s21_size_t *);

s21_size_t s21_precission_correction(char **, s21_size_t, specifier_options *,
                                     s21_size_t *);
void s21_strnput(char **, char *, s21_size_t, s21_size_t *);

s21_size_t s21_append_digit(long long, char *, specifier_options *);
s21_size_t s21_append_o_digit(unsigned long, char *, specifier_options *);
s21_size_t s21_append_x_digit(long long, char *, specifier_options *, short);
s21_size_t s21_append_u_digit(unsigned long, char *, specifier_options *);
s21_size_t s21_append_char(char, char *, specifier_options *);
s21_size_t s21_append_str(char *, char *, specifier_options *);
s21_size_t s21_append_float(double, char *, specifier_options *, short);
s21_size_t s21_append_ptr(void *, char *, specifier_options *);
s21_size_t s21_append_science(double, char *, specifier_options *, short);
int s21_science_rank(double *, specifier_options *);
s21_size_t s21_append_g(double, char *, specifier_options *);
// -------------------------------------------------------------------

// ----------------------------- base ------------------------------
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
char *s21_strtok_r(char *str, const char *delim, char **save_ptr);
// -------------------------------------------------------------------

// ----------------------------- sscanf ------------------------------
int s21_sscanf(const char *str, const char *format, ...);

void s21_read_s_options(const char *, specifier_options *);
short s21_scan_is_legal(specifier_options *);
short s21_scan_d(char **, specifier_options *, void *, short);
short s21_scan_u(char **, specifier_options *, void *, short);
short s21_scan_s(char **, specifier_options *, void *);
short s21_scan_float(char **, specifier_options *, void *);
short s21_scan_double(char **, specifier_options *, void *);
short s21_scan_long_double(char **, specifier_options *, void *);

short s21_eq_or_whitespaces(char **, char **);
// -------------------------------------------------------------------

// ---------------------------- bonus --------------------------------
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
// -------------------------------------------------------------------

// ---------------------------- utils --------------------------------
int s21_max(int, int);
int s21_min(int, int);
short s21_isnan(double);
short s21_isnormal(double);
short s21_isinf(double);
double s21_fabs(double);
short s21_is_white_space(char *);
size_t s21_positive_diff(int, int);
int s21_atoi(char *, s21_size_t);
s21_size_t s21_itoa(long long, char *);
s21_size_t s21_u_itoa(unsigned long, char *, int, short);
char *s21_ftoa(double, char *, specifier_options *);
void s21_reverse(char *, int, int);
double s21_round(double);
// -------------------------------------------------------------------

#endif  // SRC_S21_STRING_H_
