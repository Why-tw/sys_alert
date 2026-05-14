#include "include/util.h"
#include <ctype.h>

int only_number(const char *s) {
    if (s[0] == '\0') return 0;
    for (int i = 0; s[i]; i ++) {
        if ((!isdigit((unsigned char)s[i]))) return 0;
    }
    return 1;
}
