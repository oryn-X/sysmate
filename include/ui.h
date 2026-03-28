#ifndef UI_H
#define UI_H

/* ANSI color codes for terminal output */
#define C_RESET         "\033[0m"

/* Basic bright colors */
#define C_BLACK         "\033[1;30m"
#define C_RED           "\033[1;31m"
#define C_GREEN         "\033[1;32m"
#define C_YELLOW        "\033[1;33m"
#define C_BLUE          "\033[1;34m"
#define C_PURPLE        "\033[1;35m"
#define C_CYAN          "\033[1;36m"
#define C_WHITE         "\033[1;37m"

/* Extra nice colors */
#define C_ORANGE        "\033[38;5;208m"
#define C_PINK          "\033[38;5;213m"
#define C_GOLD          "\033[38;5;220m"
#define C_MINT          "\033[38;5;121m"
#define C_SKY           "\033[38;5;117m"
#define C_LAVENDER      "\033[38;5;183m"
#define C_TEAL          "\033[38;5;51m"
#define C_CORAL         "\033[38;5;209m"
#define C_ROSE          "\033[38;5;204m"
#define C_BEIGE         "\033[38;5;230m"

/* Dark / elegant colors */
#define C_DARK_RED      "\033[38;5;124m"
#define C_DARK_GREEN    "\033[38;5;28m"
#define C_DARK_BLUE     "\033[38;5;19m"
#define C_DARK_PURPLE   "\033[38;5;54m"
#define C_DARK_CYAN     "\033[38;5;30m"
#define C_GRAY          "\033[38;5;245m"
#define C_BPURPLE "\033[1;35m"

/* Special nice color */
#define C_INDIGO        "\033[38;5;99m"

/* Shared status kinds */
#define STATUS_OK       0
#define STATUS_ERROR    1
#define STATUS_INFO     2
#define STATUS_PLAIN    3
#define STATUS_WARN     4
#define STATUS_TIP      5



/* Print basic usage instructions */
void print_usage(void);

/* Print current mode (e.g., ls, clean) */
void print_mode(const char *mode);

/* Print message for unknown command */
void print_unknown_command(const char *com);

/* Print status message (success or error) */
void print_status(const char *status, int is_error);

#endif
 