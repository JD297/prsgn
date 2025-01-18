#include "parse_tree_type.h"

int main(void)
{
    const char *bnf = "<translation-unit> ::= {<external-declaration>}*\n"
                      "<external-declaration> ::= <function-definition>\n"
                      "                         | <declaration>\n"
                      "<storage-class-specifier> ::= int\n"
                      "                            | char\n";

    parse_tree_type_generate(bnf, "C");

    return 0;
}
