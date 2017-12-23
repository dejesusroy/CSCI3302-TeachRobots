#include <Sparki.h>
#include <math.h>
#define calcInfo 1
#define mainLab 2
#define labCompl 3

/*
Given pose, how should the wheels rotate to get there?
*/

int state = calcInfo;
// bool arrived = FALSE;

// Inverse Kinematics Given Info
float x_g = 30;
float y_g = 30;
float theta_goal = 90;

// Odometry of Robot
float x_i = 0;
float y_i = 0;
float Thetai = 0;


float curDist;
float curBearing;
float startTime;
float endTime;


/*
// Forward Kinematics Info
float x = 0;
float y = 0;
float theta = 0;
float d = 0.1; // distance between two wheels
*/
float speed = 0.028; // m/s

// Inverse Kinematics Info
float r = 0.03;   // redius of wheels (Should be 3cm)
float phi_L;   // Left wheel rotation
float phi_R;   // Right wheel rotation
float d = 0.085; // Axle diameter (Should be 8.5cm)
float x_r;     // Robot x position
float y_r;     // Robot y position
float theta;   // Robot angle

int speed_L; //Ratio speed for left wheel
int speed_R; //Ratio speed for right wheel

// Inverse Kinematics Calculated Info
float dist;    // The ditance to the goal (rho)
float bearing; // The bearing angle error (alpha)
float heading; // The heading angle error (beta)

float dX;      // The change in position of the robot
float dTheta;  // The speed change in angle of the robot
float dTr;     // The change in angle of the robot 
float dXr;     // The change in position of the robot


// NOT REQUIRED, MAY BE HELPFUL
// Function for radians to degrees
float to_degrees(float radians)
{
   return radians * (180.0 / M_PI);
}

// Function for degrees to radians
float to_radians(float degrees)
{
   return degrees * (M_PI / 180.0);
}

// Function to calculate all errors (Position, heading, bearing)
void calcError()
{
   // Eucledian Distance Formula (From book)
   dist = sqrt((x_r - x_g) * (x_r - x_g) + (y_r - y_g) * (y_r - y_g));
   // Bearing Angle Error (From book)
   bearing = theta - (atan2((y_g - y_r) , (x_g - x_r)));
   // Heading Angle Error (From book)
   heading = theta_goal - theta;

   // Calculate dX (change in position) proportional to rho (distance)
   // Instructions from lab
   dX = (0.1) * dist;
   // Calculate dTheta (change in rotation) proportional to alpha (bearing) and original angle of robot (theta)
   // Instructions from lab
   dTheta = (0.1) * bearing + (0.01) * heading;

   // Calculate right phi
   phi_R = ((2.0 * dX + dTheta * dist) / (2.0 * r));
   // Calculate right phi
   phi_L = ((2.0 * dX - dTheta * dist) / (2.0 * r));
   // Calculate X^dot_r
   dXr = phi_R/2.0+phi_L/2.0;
   // Calculate theta^dot_r
   dTr = (phi_R / d) - (phi_L / d);

}

void calcSpeed()
{
   speed_L = abs(phi_L / max(abs(phi_L), abs(phi_R)) * 100);
   speed_R = abs(phi_R / max(abs(phi_L), abs(phi_R)) * 100);
}


// Will continously print all info
void printInfo()
{
   sparki.println("dXr: ");
   sparki.println(dXr);
   sparki.println("phi_R: ");
   sparki.println(phi_R);
   sparki.println("phi_L: ");
   sparki.println(phi_L);
   sparki.println("Distance Remaining: ");
   sparki.println(curDist);
   sparki.println("SpeedL:");
   sparki.println(speed_L);
   sparki.println("SpeedR:");
   sparki.println(speed_R);
   sparki.updateLCD();
   delay(100);
   sparki.clearLCD();

   /*
   // Print odometry info
   sparki.println("X: ");
   sparki.println(x_i);
   sparki.println("Y: ");
   sparki.println(y_i);
   sparki.println("T: ");
   sparki.println(Thetai);

   sparki.updateLCD();
   delay(100);
   sparki.clearLCD();
   */
}

// Will continuously update odometry and distance remaining
void updateLoc()
{
   x_i = x_i + cos(Thetai) * dXr * 0.1;
   y_i = y_i + sin(Thetai) * dXr * 0.1;
   Thetai = Thetai + dTr * 0.1;
   curDist = sqrt((x_i - x_g) * (x_i - x_g) + (y_i - y_g) * (y_i - y_g));
}

void setup()
{
   sparki.servo(SERVO_CENTER);
   sparki.clearLCD();
   sparki.print("I am ready!");
   sparki.updateLCD();
   delay(2000);
   sparki.clearLCD();

   // Initiate sparki location
   x_r = 0;
   y_r = 0;
   theta = 0;
}

void loop()
{
   // Functions should continously run
   updateLoc();
   printInfo();

   //
   switch(state)
   {
      // Calulate the errors, then print
      case calcInfo:
         startTime = millis();
         calcError();
         calcSpeed();
         state = mainLab;
         break;

/*
      // Decide how to reach goal
      case decisionState:

*/
      // Reach the goal
      case mainLab:
         while(curDist > 0.1)
         {
            if(phi_L  >   0)
            {
               sparki.motorRotate(MOTOR_LEFT, DIR_CCW,speed_L);
            }
            else
            {
               sparki.motorRotate(MOTOR_LEFT, DIR_CW,speed_L);
            }
            if(phi_R   >   0)
            {
               sparki.motorRotate(MOTOR_RIGHT, DIR_CW,speed_R);
            }
            else
            {
               sparki.motorRotate(MOTOR_RIGHT, DIR_CCW,speed_R);
            }
         }
         state = labCompl;
         break;


      // Lab Part II Complete
      case labCompl:
         sparki.moveStop();
         sparki.clearLCD();
         break;
   }
}