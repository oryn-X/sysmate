#ifndef UI_H
#define UI_H

/* ANSI color codes for terminal output */
#define C_RESET   "\033[0m"
#define C_CYAN    "\033[1;36m"
#define C_GREEN   "\033[1;32m"
#define C_YELLOW  "\033[1;33m"
#define C_WHITE   "\033[1;37m"
#define C_RED     "\033[38;5;196m"
#define C_BPURPLE "\033[1;35m"

/* Print basic usage instructions */
void print_usage(void);

/* Print current mode (e.g., ls, clean) */
void print_mode(const char *mode);

/* Print message for unknown command */
void print_unknown_command(const char *com);

/* Print status message (success or error) */
void print_status(const char *status, int is_error);

#endif