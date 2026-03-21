#ifndef SYSTEM_OPS_H
#define SYSTEM_OPS_H

/* Update and upgrade the system */
int handle_update(void);

/* Clean unused packages and cache */
int handle_clean(void);

/* List files and create index file */
int handle_ls(void);

/* Delete file by index */
int handle_delete(int target);

/* Run in CMD */
int run_system(const char *msg, const char *cmd);
int run_doctor(const char *msg, const char *cmd,const char *package);


#endif