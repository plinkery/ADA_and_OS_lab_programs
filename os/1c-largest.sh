#!/bin/bash
echo "enter 3 numbers :"
read n1 n2 n3
if [ "$n1" -gt "$n2" ]
then 
	largest=$n1
else
	largest=$n2
fi
if [ "$n3" -gt "$largest" ]
then
	largest=$n3
fi
echo "the largest number is "$largest
