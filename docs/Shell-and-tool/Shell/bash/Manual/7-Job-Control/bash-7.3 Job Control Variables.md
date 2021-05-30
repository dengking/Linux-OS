[TOC]



### [7.3 Job Control Variables](https://www.gnu.org/software/bash/manual/html_node/Job-Control-Variables.html#Job-Control-Variables)

- `auto_resume`

  This variable controls how the shell interacts with the user and job control. If this variable exists then single word simple commands without redirections are treated as candidates for resumption of an existing job. There is no ambiguity allowed; if there is more than one job beginning with the string typed, then the most recently accessed job will be selected. The name of a stopped job, in this context, is the command line used to start it. If this variable is set to the value ‘exact’, the string supplied must match the name of a stopped job exactly; if set to ‘substring’, the string supplied needs to match a substring of the name of a stopped job. The ‘substring’ value provides functionality analogous to the ‘%?’ job ID (see [Job Control Basics](https://www.gnu.org/software/bash/manual/html_node/Job-Control-Basics.html#Job-Control-Basics)). If set to any other value, the supplied string must be a prefix of a stopped job’s name; this provides functionality analogous to the ‘%’ job ID.

