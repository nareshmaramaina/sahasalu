#!/bin/sh
#This program will run untill matched argmuent
while [ "$1" != "uu" ]; do
echo $1
shift # this is simply print all given argments
done
exit 0
