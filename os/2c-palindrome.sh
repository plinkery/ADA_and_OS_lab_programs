#!/bin/bash
echo "enter the string to be checked"
read str
length=${#str}
for((i=length-1;i>=0;i--))
do
	reverse=$reverse${str:$i:1}
done
if [[ $reverse == "$str" ]]
then
	echo "the string is a palindrome"
else
	echo "the string is not a palindrome"
fi
