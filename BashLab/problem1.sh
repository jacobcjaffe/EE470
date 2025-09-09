#!/bin/bash

echo What is your name?
read MY_NAME
echo "Hi, $MY_NAME! How old are you?"
read MY_AGE

# check if the input was an integer number
if ! [[ "$MY_AGE" =~ ^[0-9]+$ ]]; then
    echo "Contains letters or special characters!"
    exit -1
fi

# check that the age is valid or whether the age is already above 100
if ((MY_AGE < 0)); then
    echo "Please enter a positive age"
    exit -1
elif ((MY_AGE >= 100)); then
    echo "Nice to meet you, $MY_NAME"
    echo "You're already over 100 years old!"
    exit 0
fi

# compute the year you will turn 100
echo "Nice to meet you, $MY_NAME"
UNTIL_HUNDRED=100
((UNTIL_HUNDRED-=MY_AGE))
year=$(date +'%Y')
((UNTIL_HUNDRED+=year))
echo "You will turn 100 years old in the year $UNTIL_HUNDRED."
