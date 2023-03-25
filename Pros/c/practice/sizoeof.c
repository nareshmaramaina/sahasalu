#define SIZEOF(var) ( (char*)(&var+1) - (char*) (&var))
int main()
{
double  val;
printf("size of = %d\n", SIZEOF(val));return 0;
}
