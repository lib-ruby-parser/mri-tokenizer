#undef RUBY_EXPORT
#include "ruby.h"
#include "vm_debug.h"
#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif

#define RUBY_PARSER_PRINT_TOKENS 1
void mri_tokenizer_print_token(void *token);
#include "parse.c"
#include <stdbool.h>

#ifdef yydebug
#undef yydebug
#endif

void mri_tokenizer_print_token(void *token)
{
    enum yytokentype *t = token;
    const char *token_name = yytname[YYTRANSLATE(*t)];

#define map_token(from, to) \
    if (strcmp(token_name, from) == 0) { \
        token_name = to; \
    }

    // keywords
    map_token("\"`def'\"", "kDEF");
    map_token("\"`module'\"", "kMODULE");
    map_token("\"`def'\"", "kDEF");
    map_token("\"`undef'\"", "kUNDEF");
    map_token("\"`begin'\"", "kBEGIN");
    map_token("\"`rescue'\"", "kRESCUE");
    map_token("\"`ensure'\"", "kENSURE");
    map_token("\"`end'\"", "kEND");
    map_token("\"`if'\"", "kIF");
    map_token("\"`unless'\"", "kUNLESS");
    map_token("\"`then'\"", "kTHEN");
    map_token("\"`elsif'\"", "kELSIF");
    map_token("\"`else'\"", "kELSE");
    map_token("\"`case'\"", "kCASE");
    map_token("\"`when'\"", "kWHEN");
    map_token("\"`while'\"", "kWHILE");
    map_token("\"`until'\"", "kUNTIL");
    map_token("\"`for'\"", "kFOR");
    map_token("\"`break'\"", "kBREAK");
    map_token("\"`next'\"", "kNEXT");
    map_token("\"`redo'\"", "kREDO");
    map_token("\"`retry'\"", "kRETRY");
    map_token("\"`in'\"", "kIN");
    map_token("\"`do'\"", "kDO");
    map_token("\"`do'\" for condition", "kDO_COND");
    map_token("\"`do'\" for block", "kDO_BLOCK");
    map_token("\"`do'\" for lambda", "kDO_LAMBDA");
    map_token("\"`return'\"", "kRETURN");
    map_token("\"`yield'\"", "kYIELD");
    map_token("\"`super'\"", "kSUPER");
    map_token("\"`self'\"", "kSELF");
    map_token("\"`nil'\"", "kNIL");
    map_token("\"`true'\"", "kTRUE");
    map_token("\"`false'\"", "kFALSE");
    map_token("\"`and'\"", "kAND");
    map_token("\"`or'\"", "kOR");
    map_token("\"`not'\"", "kNOT");
    map_token("\"`if' modifier\"", "kIF_MOD");
    map_token("\"`unless' modifier\"", "kUNLESS_MOD");
    map_token("\"`while' modifier\"", "kWHILE_MOD");
    map_token("\"`until' modifier\"", "kUNTIL_MOD");
    map_token("\"`rescue' modifier\"", "kRESCUE_MOD");
    map_token("\"`alias'\"", "kALIAS");
    map_token("\"`defined?'\"", "kDEFINED");
    map_token("\"`BEGIN'\"", "klBEGIN");
    map_token("\"`END'\"", "klEND");
    map_token("\"`__LINE__'\"", "k__LINE__");
    map_token("\"`__FILE__'\"", "k__FILE__");
    map_token("\"`__ENCODING__'\"", "k__ENCODING__");

    map_token("\"local variable or method\"", "tIDENTIFIER");
    map_token("\"method\"", "tFID");
    map_token("\"global variable\"", "tGVAR");
    map_token("\"instance variable\"", "tIVAR");
    map_token("\"constant\"", "tCONSTANT");
    map_token("\"class variable\"", "tCVAR");
    map_token("\"label\"", "tLABEL");
    map_token("\"integer literal\"", "tINTEGER");
    map_token("\"float literal\"", "tFLOAT");
    map_token("\"rational literal\"", "tRATIONAL");
    map_token("\"imaginary literal\"", "tIMAGINARY");
    map_token("\"char literal\"", "tCHAR");
    map_token("\"numbered reference\"", "tNTH_REF");
    map_token("\"back reference\"", "tBACK_REF");
    map_token("\"literal content\"", "tSTRING_CONTENT");
    map_token("tREGEXP_END", "tREGEXP_END");

    map_token("'.'", "tDOT");
    map_token("\"backslash\"", "tBACKSLASH");
    map_token("\"escaped space\"", "tSP");
    map_token("\"escaped horizontal tab\"", "tSLASH_T");
    map_token("\"escaped form feed\"", "tSLASH_F");
    map_token("\"escaped carriage return\"", "tSLASH_R");
    map_token("\"escaped vertical tab\"", "tVTAB");
    map_token("\"unary+\"", "tUPLUS");
    map_token("\"unary-\"", "tUMINUS");
    map_token("\"**\"", "tPOW");
    map_token("\"<=>\"", "tCMP");
    map_token("\"==\"", "tEQ");
    map_token("\"===\"", "tEQQ");
    map_token("\"!=\"", "tNEQ");
    map_token("\">=\"", "tGEQ");
    map_token("\"<=\"", "tLEQ");
    map_token("\"&&\"", "tANDOP");
    map_token("\"||\"", "tOROP");
    map_token("\"=~\"", "tMATCH");
    map_token("\"!~\"", "tNMATCH");
    map_token("\"..\"", "tDOT2");
    map_token("\"...\"", "tDOT3");
    map_token("\"(..\"", "tBDOT2");
    map_token("\"(...\"", "tBDOT3");
    map_token("\"[]\"", "tAREF");
    map_token("\"[]=\"", "tASET");
    map_token("\"<<\"", "tLSHFT");
    map_token("\">>\"", "tRSHFT");
    map_token("\"&.\"", "tANDDOT");
    map_token("\"::\"", "tCOLON2");
    map_token("\":: at EXPR_BEG\"", "tCOLON3");
    map_token("\"operator-assignment\"", "tOP_ASGN");
    map_token("\"=>\"", "tASSOC");
    map_token("\"(\"", "tLPAREN");
    map_token("\"( arg\"", "tLPAREN_ARG");
    map_token("\")\"", "tRPAREN");
    map_token("\"[\"", "tLBRACK");
    map_token("\"{\"", "tLBRACE");
    map_token("\"{ arg\"", "tLBRACE_ARG");
    map_token("\"*\"", "tSTAR");
    map_token("\"**arg\"", "tDSTAR");
    map_token("\"&\"", "tAMPER");
    map_token("\"->\"", "tLAMBDA");
    map_token("\"symbol literal\"", "tSYMBEG");
    map_token("\"string literal\"", "tSTRING_BEG");
    map_token("\"backtick literal\"", "tXSTRING_BEG");
    map_token("\"regexp literal\"", "tREGEXP_BEG");
    map_token("\"word list\"", "tWORDS_BEG");
    map_token("\"verbatim word list\"", "tQWORDS_BEG");
    map_token("\"symbol list\"", "tSYMBOLS_BEG");
    map_token("\"verbatim symbol list\"", "tQSYMBOLS_BEG");
    map_token("\"terminator\"", "tSTRING_END");
    map_token("\"'}'\"", "tSTRING_DEND");
    map_token("tSTRING_DBEG", "tSTRING_DBEG");
    map_token("tSTRING_DVAR", "tSTRING_DVAR");
    map_token("tLAMBEG", "tLAMBEG");
    map_token("tLABEL_END", "tLABEL_END");
    // map_token("tLOWEST", "");
    map_token("'='", "tEQL");
    map_token("'?'", "tEH");
    map_token("':'", "tCOLON");
    map_token("'>'", "tGT");
    map_token("'<'", "tLT");
    map_token("'|'", "tPIPE");
    map_token("'^'", "tCARET");
    map_token("'&'", "tAMPER2");
    map_token("'+'", "tPLUS");
    map_token("'-'", "tMINUS");
    map_token("'*'", "tSTAR2");
    map_token("'/'", "tDIVIDE");
    map_token("'%'", "tPERCENT");
    map_token("tUMINUS_NUM", "tUMINUS_NUM");
    map_token("'!'", "tBANG");
    map_token("'~'", "tTILDE");
    // map_token("tLAST_TOKEN", "");
    map_token("'{'", "tLCURLY");
    map_token("'}'", "tRCURLY");
    map_token("'['", "tLBRACK2");
    map_token("','", "tCOMMA");
    map_token("'`'", "tBACK_REF2");
    map_token("'('", "tLPAREN2");
    map_token("')'", "tRPAREN");
    map_token("']'", "tRBRACK");
    map_token("';'", "tSEMI");
    map_token("' '", "tSPACE");
    map_token("'\\n'", "tNL");

    map_token("\"end-of-input\"", "END_OF_INPUT");
    printf("%s\n", token_name);
}

void __parse(const char *filename, const char *src, bool yydebug)
{
    VALUE parser = rb_parser_new();
    rb_parser_set_context(parser, NULL, FALSE);
    rb_parser_set_yydebug(parser, RBOOL(yydebug));
    rb_parser_compile_string(parser, filename, rb_fstring_cstr(src), 0);
}

char *__read_file(const char *filepath)
{
    FILE *f = fopen(filepath, "rb");
    if (!f) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *fcontent = malloc(fsize + 1);
    (void)(fread(fcontent, 1, fsize, f));
    fclose(f);
    fcontent[fsize] = 0;

    return fcontent;
}

int
main(int argc, char **argv)
{
#ifdef HAVE_LOCALE_H
    setlocale(LC_CTYPE, "");
#endif

    ruby_sysinit(&argc, &argv);
    {
    RUBY_INIT_STACK;
    ruby_init();
    if (argc != 2) {
        printf("Usage: mri_tokenizer path/to/file.rb\n");
        return 1;
    }
    char *filepath = argv[1];
    char *code = __read_file(filepath);
    if (!code) {
        printf("Failed to read file '%s', aborting.\n", filepath);
        return 1;
    }
    __parse(filepath, code, false);
    free(code);
    return 0;
    }
}
