PAT=attrib/

all: aligned destructor inline noreturn nonnull posix_memaling unused_result 			\
        cleanup deprecated section demo

aligned: aligned.c
	@gcc -w aligned.c -o aligned && echo "  CC $(PAT)aligned.c"
demo: demo.c
	@gcc -w demo.c -o demo && echo "  CC $(PAT)demo.c"
destructor: destructor.c
	@gcc -w destructor.c -o destructor && echo "  CC $(PAT)destructor.c"
inline: inline.c
	@gcc -w inline.c -o inline && echo "  CC $(PAT)inline.c"
nonnull:nonnull.c
	@gcc -w nonnull.c -o nonnull && echo "  CC $(PAT)nonnull.c"
posix_memaling:posix_memaling.c
	@gcc -w posix_memaling.c -o posix_memaling && echo "  CC $(PAT)posix_memaling.c"
unused_result:unused_result.c
	@gcc -w unused_result.c -o unused_result && echo "  CC $(PAT)unused_result.c"
cleanup: cleanup.c
	@gcc -w cleanup.c -o cleanup && echo "  CC $(PAT)cleanup.c"
deprecated: deprecated.c
	@gcc -w deprecated.c -o deprecated && echo "  CC $(PAT)deprecated.c"
noreturn:noreturn.c
	@gcc -w noreturn.c -o noreturn && echo "  CC $(PAT)noreturn.c"
section:section.c
	@gcc -w section.c -o section && echo "  CC $(PAT)section.c"
	 

clean : 
	@rm -rf *.o aligned demo destructor inline noreturn nonnull a.out posix_memaling unused_result \
	cleanup deprecated section .*.swp
	@echo "	$(PAT)	cleaned"
