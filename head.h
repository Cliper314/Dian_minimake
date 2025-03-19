int parse_command_line(int argc, char *argv[], int *verbose_mode, char *target);
void preprocess_and_parse_makefile(const char *filename, int verbose_mode);
void print_help();
void syntax_check(const char *line, int line_number,int *in_rule);
