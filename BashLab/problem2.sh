#!/bin/bash

score=0
# Question 1
echo What is the capital of South Korea?
read ans
# making the answer case agnostic
ans="${ans,,}"
if [[ "$ans" == "seoul" ]]; then 
    echo "Correct!"
    ((score+=1))
else
    echo "Wrong! The correct answer is 'Seoul'"
fi 

# Question 2
echo What is the next Leonardo DiCaprio movie?
read ans
ans="${ans,,}"
if [[ "$ans" == "one battle after another" ]]; then 
    echo "Correct!"
    ((score+=1))
else
    echo "Wrong! The correct answer is 'One Battle After Another'"
fi 

# Question 3
echo Who is Rohnert Park named after?
read ans
ans="${ans,,}"
if [[ "$ans" == "waldo rohnert" ]]; then 
    echo "Correct!"
    ((score+=1))
else
    echo "Wrong! The correct answer is 'Waldo Rohnert'"
fi 

d=$(date)
echo "Thank you for taking the quiz on $d"
echo "Your score is $score out of 3 questions."
