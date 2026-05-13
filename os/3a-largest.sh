#!/bin/bash
echo "enter the size of the array "
read n
declare -a arr
echo "enter the elements of the array "
for (( i=0;i<n;i++ ))
do
	read arr[i]
done
max=${arr[0]}
for (( i=1;i<n;i++ ))
do
	if (( $max < ${arr[$i]} ))
	then
		max=${arr[$i]}
	fi
done
echo "the largest of the given numbers is $max"
