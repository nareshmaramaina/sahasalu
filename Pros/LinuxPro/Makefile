
DIRS= attrib  Designs  fork  ioperm  lib   memalloc  net    proclimit  signals  syscall  timers	\
	clone   exec     io    ipc     libs  multiio   posix  sched      startup  threads


all:    
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done

clean:
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
