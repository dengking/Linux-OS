

## stackoverflow [Does the Thundering Herd Problem exist on Linux anymore?](https://stackoverflow.com/questions/2213779/does-the-thundering-herd-problem-exist-on-linux-anymore)



### A

For years, most unix/linux kernels serialize response to accept(2)s, in other words, only one thread is waken up if more than one are blocking on accept(2) against a single open file descriptor.

OTOH, many (if not all) kernels still have the thundering herd problem in the select-accept pattern as you describe.

I have written a simple script ( https://gist.github.com/kazuho/10436253 ) to verify the existence of the problem, and found out that the problem exists on linux 2.6.32 and Darwin 12.5.0 (OS X 10.8.5).



