[TOC]



### [7.2 Job Control Builtins](https://www.gnu.org/software/bash/manual/html_node/Job-Control-Builtins.html#Job-Control-Builtins)

​	

- `bg`

  `bg [jobspec …] `Resume each suspended job jobspec in the background, as if it had been started with ‘&’. If jobspec is not supplied, the current job is used. The return status is zero unless it is run when job control is not enabled, or, when run with job control enabled, any jobspec was not found or specifies a job that was started without job control.

- `fg`

  `fg [jobspec] `Resume the job jobspec in the foreground and make it the current job. If jobspec is not supplied, the current job is used. The return status is that of the command placed into the foreground, or non-zero if run when job control is disabled or, when run with job control enabled, jobspec does not specify a valid job or jobspec specifies a job that was started without job control.

- `jobs`

  `jobs [-lnprs] [jobspec] jobs -x command [arguments] `The first form lists the active jobs. The options have the following meanings:`-l`List process IDs in addition to the normal information.`-n`Display information only about jobs that have changed status since the user was last notified of their status.`-p`List only the process ID of the job’s process group leader.`-r`Display only running jobs.`-s`Display only stopped jobs.If jobspec is given, output is restricted to information about that job. If jobspec is not supplied, the status of all jobs is listed.If the -x option is supplied, `jobs` replaces any jobspec found in command or arguments with the corresponding process group ID, and executes command, passing it arguments, returning its exit status.

- `kill`

  `kill [-s sigspec] [-n signum] [-sigspec] jobspec or pid kill -l|-L [exit_status] `Send a signal specified by sigspec or signum to the process named by job specification jobspec or process ID pid. sigspec is either a case-insensitive signal name such as `SIGINT` (with or without the `SIG` prefix) or a signal number; signum is a signal number. If sigspec and signum are not present, `SIGTERM` is used. The -l option lists the signal names. If any arguments are supplied when -l is given, the names of the signals corresponding to the arguments are listed, and the return status is zero. exit_status is a number specifying a signal number or the exit status of a process terminated by a signal. The -L option is equivalent to -l. The return status is zero if at least one signal was successfully sent, or non-zero if an error occurs or an invalid option is encountered.

- `wait`

  `wait [-fn] [jobspec or pid …] `Wait until the child process specified by each process ID pid or job specification jobspec exits and return the exit status of the last command waited for. If a job spec is given, all processes in the job are waited for. If no arguments are given, all currently active child processes are waited for, and the return status is zero. If the -n option is supplied, `wait` waits for any job to terminate and returns its exit status. If the -f option is supplied, and job control is enabled, `wait` forces each pid or jobspec to terminate before returning its status, intead of returning when it changes status. If neither jobspec nor pid specifies an active child process of the shell, the return status is 127.

- `disown`

  `disown [-ar] [-h] [jobspec … | pid … ] `Without options, remove each jobspec from the table of active jobs. If the -h option is given, the job is not removed from the table, but is marked so that `SIGHUP` is not sent to the job if the shell receives a `SIGHUP`. If jobspec is not present, and neither the -a nor the -r option is supplied, the current job is used. If no jobspec is supplied, the -a option means to remove or mark all jobs; the -r option without a jobspec argument restricts operation to running jobs.

- `suspend`

  `suspend [-f] `Suspend the execution of this shell until it receives a `SIGCONT` signal. A login shell cannot be suspended; the -f option can be used to override this and force the suspension.

When job control is not active, the `kill` and `wait` builtins do not accept jobspec arguments. They must be supplied process IDs.