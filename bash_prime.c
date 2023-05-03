#!/bin/bash

echo "Enter the limit: "
read limit

echo "Prime numbers up to $limit are: "
for (( i=2; i<=$limit; i++ ))
do
    # Assume the number is prime to start
    is_prime=true
    
    # Check if the number is divisible by any integer from 2 to i-1
    for (( j=2; j<i; j++ ))
    do
        if [ $((i%j)) -eq 0 ]
        then
            # If it's divisible by any number other than 1 and itself, it's not prime
            is_prime=false
            break
        fi
    done
    
    # If the number is prime, print it
    if [ $is_prime == true ]
    then
        echo $i
    fi
done
