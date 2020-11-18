#define DATA "/mydata"
#define SEM  "/datasem"

struct mydata {
	sem_t *sem;
	int a;
	int b;
};
