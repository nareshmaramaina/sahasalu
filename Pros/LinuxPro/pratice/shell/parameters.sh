#unset foo
foo=$(ls)
echo ${#foo} #gives the lenth of parameter

#!/bin/sh
unset foo
echo ${foo:-bar}
foo=fud
echo ${foo:-bar}
foo=/usr/bin/X11/startx
echo " 1 $foo " 
echo ${foo#*/}
echo " 2 $foo " 
echo ${foo##*/}
echo " 3 $foo " 
bar=/usr/local/etc/local/networks/local/finally
echo " 4 $bar " 
echo ${bar%local*}
echo ${bar%%local*}
exit 0
