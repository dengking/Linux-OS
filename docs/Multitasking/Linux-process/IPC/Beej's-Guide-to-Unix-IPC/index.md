# [Beej's Guide to Unix IPC](http://beej.us/guide/bgipc/html/multi/index.html)

\1. [Intro](http://beej.us/guide/bgipc/html/multi/intro.html)

1.1. [Audience](http://beej.us/guide/bgipc/html/multi/intro.html#audience)

1.2. [Platform and Compiler](http://beej.us/guide/bgipc/html/multi/intro.html#platform)

1.3. [Official Homepage](http://beej.us/guide/bgipc/html/multi/intro.html#homepage)

1.4. [Email Policy](http://beej.us/guide/bgipc/html/multi/intro.html#emailpolicy)

1.5. [Mirroring](http://beej.us/guide/bgipc/html/multi/intro.html#mirroring)

1.6. [Note for Translators](http://beej.us/guide/bgipc/html/multi/intro.html#xlate)

1.7. [Copyright and Distribution](http://beej.us/guide/bgipc/html/multi/intro.html#copyright)



\2. [A **`fork()`** Primer](http://beej.us/guide/bgipc/html/multi/fork.html)

2.1. ["Seek ye the Gorge of Eternal Peril"](http://beej.us/guide/bgipc/html/multi/fork.html#forkperil)

2.2. ["I'm mentally prepared! Give me *The Button*!"](http://beej.us/guide/bgipc/html/multi/fork.html#forkbutton)

2.3. [Summary](http://beej.us/guide/bgipc/html/multi/fork.html#forksum)



\3. [Signals](http://beej.us/guide/bgipc/html/multi/signals.html)

3.1. [Catching Signals for Fun and Profit!](http://beej.us/guide/bgipc/html/multi/signals.html#catchsig)

3.2. [The Handler is not Omnipotent](http://beej.us/guide/bgipc/html/multi/signals.html#handlerok)

3.3. [What about **`signal()`**](http://beej.us/guide/bgipc/html/multi/signals.html#signalwrong)

3.4. [Some signals to make you popular](http://beej.us/guide/bgipc/html/multi/signals.html#signalpop)

3.5. [What I have Glossed Over](http://beej.us/guide/bgipc/html/multi/signals.html#siggloss)



\4. [Pipes](http://beej.us/guide/bgipc/html/multi/pipes.html)

4.1. ["These pipes are clean!"](http://beej.us/guide/bgipc/html/multi/pipes.html#pipesclean)

4.2. [**`fork()`** and **`pipe()`**—you have the power!](http://beej.us/guide/bgipc/html/multi/pipes.html#pipefork)

4.3. [The search for Pipe as we know it](http://beej.us/guide/bgipc/html/multi/pipes.html#pipequest)

4.4. [Summary](http://beej.us/guide/bgipc/html/multi/pipes.html#pipesum)



\5. [FIFOs](http://beej.us/guide/bgipc/html/multi/fifos.html)

5.1. [A New FIFO is Born](http://beej.us/guide/bgipc/html/multi/fifos.html#fifonew)

5.2. [Producers and Consumers](http://beej.us/guide/bgipc/html/multi/fifos.html#fifopc)

5.3. [`O_NDELAY`! I'm UNSTOPPABLE!](http://beej.us/guide/bgipc/html/multi/fifos.html#fifondelay)

5.4. [Concluding Notes](http://beej.us/guide/bgipc/html/multi/fifos.html#fifoconc)



\6. [File Locking](http://beej.us/guide/bgipc/html/multi/flocking.html)

6.1. [Setting a lock](http://beej.us/guide/bgipc/html/multi/flocking.html#flockset)

6.2. [Clearing a lock](http://beej.us/guide/bgipc/html/multi/flocking.html#flockclear)

6.3. [A demo program](http://beej.us/guide/bgipc/html/multi/flocking.html#flockdemo)

6.4. [Summary](http://beej.us/guide/bgipc/html/multi/flocking.html#flocksum)



\7. [Message Queues](http://beej.us/guide/bgipc/html/multi/mq.html)

7.1. [Where's my queue?](http://beej.us/guide/bgipc/html/multi/mq.html#mqwhere)

7.2. ["Are you the Key Master?"](http://beej.us/guide/bgipc/html/multi/mq.html#mqftok)

7.3. [Sending to the queue](http://beej.us/guide/bgipc/html/multi/mq.html#mqsend)

7.4. [Receiving from the queue](http://beej.us/guide/bgipc/html/multi/mq.html#mqrece)

7.5. [Destroying a message queue](http://beej.us/guide/bgipc/html/multi/mq.html#mqdest)

7.6. [Sample programs, anyone?](http://beej.us/guide/bgipc/html/multi/mq.html#mqsamp)

7.7. [Summary](http://beej.us/guide/bgipc/html/multi/mq.html#mqsum)



\8. [Semaphores](http://beej.us/guide/bgipc/html/multi/semaphores.html)

8.1. [Grabbing some semaphores](http://beej.us/guide/bgipc/html/multi/semaphores.html#semgrab)

8.2. [Controlling your semaphores with **`semctl()`**](http://beej.us/guide/bgipc/html/multi/semaphores.html#semctl)

8.3. [`semop()`: Atomic power!](http://beej.us/guide/bgipc/html/multi/semaphores.html#semop)

8.4. [Destroying a semaphore](http://beej.us/guide/bgipc/html/multi/semaphores.html#semdest)

8.5. [Sample programs](http://beej.us/guide/bgipc/html/multi/semaphores.html#semsamp)

8.6. [Summary](http://beej.us/guide/bgipc/html/multi/semaphores.html#semsum)



\9. [Shared Memory Segments](http://beej.us/guide/bgipc/html/multi/shm.html)

9.1. [Creating the segment and connecting](http://beej.us/guide/bgipc/html/multi/shm.html#shmcreat)

9.2. [Attach me—getting a pointer to the segment](http://beej.us/guide/bgipc/html/multi/shm.html#shmat)

9.3. [Reading and Writing](http://beej.us/guide/bgipc/html/multi/shm.html#shmrw)

9.4. [Detaching from and deleting segments](http://beej.us/guide/bgipc/html/multi/shm.html#shmdet)

9.5. [Concurrency](http://beej.us/guide/bgipc/html/multi/shm.html#shmcon)

9.6. [Sample code](http://beej.us/guide/bgipc/html/multi/shm.html#shmsam)



\10. [Memory Mapped Files](http://beej.us/guide/bgipc/html/multi/mmap.html)

10.1. [Mapmaker](http://beej.us/guide/bgipc/html/multi/mmap.html#mmmaker)

10.2. [Unmapping the file](http://beej.us/guide/bgipc/html/multi/mmap.html#mmunmap)

10.3. [Concurrency, again?!](http://beej.us/guide/bgipc/html/multi/mmap.html#mmconcur)

10.4. [A simple sample](http://beej.us/guide/bgipc/html/multi/mmap.html#mmsamp)

10.5. [Summary](http://beej.us/guide/bgipc/html/multi/mmap.html#mmsum)



\11. [Unix Sockets](http://beej.us/guide/bgipc/html/multi/unixsock.html)

11.1. [Overview](http://beej.us/guide/bgipc/html/multi/unixsock.html#unixsockover)

11.2. [What to do to be a Server](http://beej.us/guide/bgipc/html/multi/unixsock.html#unixsockserv)

11.3. [What to do to be a client](http://beej.us/guide/bgipc/html/multi/unixsock.html#sockclient)

11.4. [`socketpair()`—quick full-duplex pipes](http://beej.us/guide/bgipc/html/multi/unixsock.html#socketpair)



\12. [More IPC Resources](http://beej.us/guide/bgipc/html/multi/references.html)

12.1. [Books](http://beej.us/guide/bgipc/html/multi/references.html#refbooks)

12.2. [Other online documentation](http://beej.us/guide/bgipc/html/multi/references.html#onlineref)

12.3. [Linux man pages](http://beej.us/guide/bgipc/html/multi/references.html#manpages)