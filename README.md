# CSCI3302-TeachRobots
Teach Robots is a group project for CSCI3302-Robotics. The purpose of this group is to apply some robotics
methods to our Arduino Sparki robot. We utilized modified inverse kinematics code that was used in our labs.
openCV was used to analize video stream to identify objects.


## Team
Roy De Jesus

Nic Williams

Zijun Xi

## Repo
This repo only has three files:

main.py - This file contains the menu code, Nic's language processing code,

robotSideController.c - This file is the modified C code from our lab. pySerial was added by Zijun.

IKcode.c - This was the team's original inverse kinematics code created for our lab.

## Responsibility
Roy De Jesus:

My responsibilities included developing openCV code. This included connecting the video stream to the program,
detecting the objects, and filtering through colors. I also created the simple menu and compiled all the code into
one file.
Each team member created their code independently and then sent it to me.

Nic Williams:

Nic's responsibilies included developing the language processing portion of the code. He utilized the NLTK
library to parse the commands to sparki. He removed all words but the keywords that he chose (colors).
Nic also made the resulting video of our code.

Zijun Xi:

Zijun modified the inverse kinematic code to work over a bluetooth port. He utilized pySerial in order to
connect to the 

## Results
This project was a little more difficult that expected. We had many compatibility issues with the first camera.
We ended up rigging our macbook camera. There were also many methods of completing the visual portion which was my
responsibility. I attempted to complete by using Haar Cascades but realized this would take much too long and would not be
completed with the time alloted. I then wanted to use multiple shape detection but the program had troubles differentiating
between the objects.I ended up simply using cicles to detect the objects and color to filter through the options.
There are many ways to improve this, given the time. I may return as openCV has many options that I want to improve on.

Resulting video: https://youtu.be/lbfPLBYJUpA
