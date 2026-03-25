#ifndef SYSTEM_OPS_H
#define SYSTEM_OPS_H
#define MAX_LEN 300




/* Update and upgrade the system */
int handle_update(void);

/* Clean unused packages and cache */
int handle_clean(void);
int run_info (const char *msg, const char *cmd);
int run_system(const char *msg, const char *cmd);



/* List files and create index file */
/* Delete file by index */
int handle_ls(void);
int handle_delete(int target);


/* Run in CMD */
int handle_doctor_dev(void);
int handle_doctor_web(void);
int run_doctor(const char *msg, const char *cmd,const char *package);
void doctor_init(void);
int doctor_print_summary();


#endif
