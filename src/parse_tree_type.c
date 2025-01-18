#include "parse_tree_type.h"

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PTT_START_FORMAT "typedef enum ParseTreeType_%s {\n"
#define PTT_START_VALUE_FORMAT "    PTT%s_"
#define PTT_END_VALUE_FORMAT ",\n"
#define PTT_END_FORMAT "} ParseTreeType_%s;\n"

void parse_tree_type_generate(const char *src, const char *lang)
{
    const char *non_terminal_symbol_begin_pattern = "^<[^>]+>";
    
    regex_t regex;
    
    regcomp(&regex, non_terminal_symbol_begin_pattern, REG_EXTENDED);

    printf(PTT_START_FORMAT, lang);

    for (const char *p_src = src; p_src != NULL && *p_src != '\0'; p_src = strstr(p_src, "\n") + 1) {
        regmatch_t match;
        
        if (regexec(&regex, p_src, 1, &match, 0) == 0) {
            printf(PTT_START_VALUE_FORMAT, lang);
        
            for (regoff_t i = 1; i < match.rm_eo - 1; i++) {
                char c = p_src[i];
                
                if (c == '-') {
                    printf("_");
                } else {
                    printf("%c", toupper((unsigned char)c));
                }
            }

            printf(PTT_END_VALUE_FORMAT);
        }
    }

    regfree(&regex);
    
    printf(PTT_END_FORMAT, lang);
}
