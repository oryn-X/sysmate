#ifndef UI_H
#define UI_H
#define C_RESET "\033[0m"
#define C_CYAN "\033[1;36m"
#define C_GREEN "\033[1;32m"
#define C_YELLOW "\033[1;33m"
#define C_WHITE "\033[1;37m"
#define C_RED "\033[38;5;196m"
#define C_BPURPLE "\033[1;35m"

void print_usage(void);
void print_mode(const char *mode);
void print_unknown_command(const char *com);
void print_status(const char *status, int is_erorr);


#endif
