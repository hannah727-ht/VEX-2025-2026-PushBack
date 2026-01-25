# VEX-2025-2026-PushBack (with PID control)
this is the coding record for 1509Z for push back season of VEX robotics

## Overview
This project focuses on improving robot movement accuracy. In other word,
through the code to improve the accuracy of the robot so my team can spend
less time when we go to a new field.

To address this problem, I implemented a PID control loop that allows
the robot to run the eacatly route everytime regardless to field impact.

## Motivation
During the High Stakes competition season, I noticed that the robot
would deviate from its intended path when the fricction of the field 
change(even really small change) or when wheel slip occurred. This 
motivated me to explore a more stable control methods to improve 
stability and consistency.

## Technologies Used
- Pros
- VEX Robotics API
- Motors and motor groups
- Sensors (e.g. encoders, inertial sensor)

## Key Features
- PID-based drive control
- Push back compensation logic
- Real-time position and heading correction
- Tunable PID parameters (kP, kI, kD)

## How It Works
The control loop continuously compares the robot’s current position or
heading with a target value. The PID controller calculates an error and
adjusts motor power to reduce that error over time.

This allows the robot to recover from external disturbances, such as
being pushed, and return to its intended trajectory.

## Challenges Faced
- Oscillation due to overly large kP values  
- Slow response when kP was too small  
- Integrator wind-up issues in early versions  
- Sensor noise affecting derivative calculations  

## What I Learned
- How feedback control improves system stability  
- The practical trade-offs between responsiveness and overshoot  
- The importance of tuning PID parameters  
- How physical factors (friction, wheel slip) affect control performance  

## Future Improvements
- Add feedforward control for faster response  
- Improve sensor filtering  
- Combine PID with odometry for better position tracking  

## Notes
All code in this repository was written and tuned by me as part of my
learning process during the competition season.
