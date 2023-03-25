gcc -fPIC -c fun.c 
gcc -shared -o libnaresh.so fun.o
mv libnaresh.so /usr/lib 
