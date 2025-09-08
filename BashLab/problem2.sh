#!/bin/bash

echo What is your name?
read MY_NAME
echo "Hi, $MY_NAME! How old are you?"
read MY_AGE

if ! [[ "$MY_AGE" =~ ^[0-9]+$ ]]; then
    echo "Contains letters!"
    exit -1
fi

if ((MY_AGE < 0)); then
    echo "Please enter a positive age"
    exit -1
elif ((MY_AGE >= 100)); then
    echo "Nice to meet you, $MY_NAME"
    echo "You're already over 100 years old!"
    exit 0
fi

echo "Nice to meet you, $MY_NAME"
UNTIL_HUNDRED=100
((UNTIL_HUNDRED-=MY_AGE))
echo "You have $UNTIL_HUNDRED years until you turn 100."
