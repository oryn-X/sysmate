#ifndef COMMANDS_H
#define COMMANDS_H

/* Parse user input and execute the correct command */
int execute_command(int argc, char *argv[]);

#endif

/*    int re = run_doctor("gcc       -> C compiler", "which gcc > /dev/null 2>&1");
 
   if (re == 1)
   {
    missing++;
   }else if (re == 0)
   {
    ok++;
    total++;
   } */