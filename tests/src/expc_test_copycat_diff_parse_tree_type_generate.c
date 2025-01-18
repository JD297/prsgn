#include "parse_tree_type.h"

#include <string.h>
#include <unistd.h>

int main(void)
{
    const char *code = "typedef enum ParseTreeType_C {\n"
                       "    PTTC_TRANSLATION_UNIT,\n"
                       "    PTTC_EXTERNAL_DECLARATION,\n"
                       "    PTTC_STORAGE_CLASS_SPECIFIER,\n"
                       "} ParseTreeType_C;\n";

    write(STDOUT_FILENO, code, strlen(code));

    return 0;
}
