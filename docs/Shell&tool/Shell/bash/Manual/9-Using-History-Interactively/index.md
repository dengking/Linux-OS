# [9 Using History Interactively](https://www.gnu.org/software/bash/manual/html_node/Using-History-Interactively.html)



## [9.3 History Expansion](https://www.gnu.org/software/bash/manual/html_node/History-Interaction.html)



### [9.3.1 Event Designators](https://www.gnu.org/software/bash/manual/html_node/Event-Designators.html)



### [9.3.2 Word Designators](https://www.gnu.org/software/bash/manual/html_node/Word-Designators.html)



## stackoverflow [Echoing the last command run in Bash?](https://stackoverflow.com/questions/6109225/echoing-the-last-command-run-in-bash)



### [A](https://stackoverflow.com/a/9502698)

`!:0` = the name of command executed.

`!:1` = the first parameter of the previous command

`!:4` = the fourth parameter of the previous command

`!:*` = all of the parameters of the previous command

`!^` = the first parameter of the previous command (same as `!:1`)

`!$` = the final parameter of the previous command

`!:-3` = all parameters in range 0-3 (inclusive)

`!:2-5` = all parameters in range 2-5 (inclusive)

`!!` = the previous command line

etc.

So, the simplest answer to the question is, in fact:

```bash
echo !!
```

...alternatively:

```bash
echo "Last command run was ["!:0"] with arguments ["!:*"]"
```

Try it yourself!

```bash
echo this is a test
echo !!
```

In a script, history expansion is turned off by default, you need to enable it with

```bash
set -o history -o histexpand
```