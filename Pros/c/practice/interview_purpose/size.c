#define SIZEOF(var) ( (char*)(&var+1) - (char*) (&var))
int main()
{
struct s {
int a;
char b;
int c;
};
struct s obj[1];
printf("size of = %ld\n", SIZEOF(obj));
return 0;
}
