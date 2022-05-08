# 1.9 Signals



Many conditions generate signals. Two terminal keys, called the *interrupt key*—often the DELETE key or Control-C — and the *quit key*—often Control-backslash — are used to interrupt the currently running process. Another way to generate a signal is by calling the kill function. We can call this function from a process to send a signal to another process. Naturally, there are limitations: we have to be the owner of the other process (or the superuser) to be able to send it a signal.

> NOTE:
>
> 1、*interrupt key*—often the DELETE key or Control-C 
>
> 2、*quit key*—often Control-backslash 
>
> 

