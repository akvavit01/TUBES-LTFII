// Program for solenoid-based robotic arm
// Made with Arduino UNO based board
// and MeArm based frame
//
// FOR TUBES!!!
//
// Made by : 
//  
// Leonardi
// e-mail  : leochen123987@gmail.com
// github  : github.com/akvavit01
//

// Header inclusion
// For servos
#include <Servo.h>

// For stepper motors
#include <AccelStepper.h>

// Pin declaration
// Servo pin declaration
#define SERVO_L 6 // M1
#define SERVO_R 7 // M2

// Stepper motor pin declaration
#define STEPPER_PIN1 2 // S1
#define STEPPER_PIN2 3 // S2
#define STEPPER_PIN3 4 // S3
#define STEPPER_PIN4 5 // S4

// Relay pin declaration
#define RELAY_PIN 8 // RELAY

// Servo constants
// Values are taken from calibration result
#define SERVO_L_MIN_ANG 180
#define SERVO_L_MAX_ANG 0
#define SERVO_L_MIN_PWM 2200
#define SERVO_L_MAX_PWM 800

#define SERVO_R_MIN_ANG 0
#define SERVO_R_MAX_ANG 180
#define SERVO_R_MIN_PWM 800
#define SERVO_R_MAX_PWM 2200

// Stepper motor constants
#define STEPPER_PIN_AMOUNT 4
#define STEPPER_DEFAULT_SPEED 5
#define STEPPER_MAX_SPEED 10
#define STEPPER_ACCEL 5
#define STEPPER_DEFAULT_POS 0 // To be edited

// Bluetooth serial constants
#define BT Serial
#define BT_BAUDRATE 57600

// Solenoid class definition
class Solenoid
{
    private :
        byte pin;
    
    public :
        Solenoid(byte pin)
        {
            this->pin = pin;

            pinMode(pin, OUTPUT);
            digitalWrite(pin, LOW);
        }

        void on()
        {
            digitalWrite(pin, HIGH);
        }

        void off()
        {
            digitalWrite(pin, LOW);
        }
};

// Object declaration
// Servo object declaration
Servo leftServo;
Servo rightServo;
// Stepper motor object declaration
AccelStepper panMotor(STEPPER_PIN_AMOUNT, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);
// Solenoid object declaration
Solenoid solenoid{RELAY_PIN};

// Function prototype declaration
// Function to set all actuator to default state
void defaultState();

void setup()
{
    // Pin assignment
    leftServo.attach(SERVO_L, SERVO_L_MIN_PWM, SERVO_L_MAX_PWM);
    rightServo.attach(SERVO_R, SERVO_R_MIN_PWM, SERVO_R_MAX_PWM);

    // Set stepper motor acceleration and speed
    panMotor.setMaxSpeed(STEPPER_MAX_SPEED);
    panMotor.setAcceleration(STEPPER_ACCEL);

    // Serial communication initialization
    BT.begin(BT_BAUDRATE);

    

    // Wait for bluetooth connection
    while (!BT)
    {
        ;
    }

    BT.println("*     !!! Bluetooth connected !!!     *");

    // Instructions
    BT.println("***************************************");
    BT.println("*          Solenoid Robot Arm         *");
    BT.println("*           - How to use  -           *");
    BT.println("***************************************");
    BT.println("*                                     *");
    BT.println("* - Controls -                        *");
    BT.println("*    'W'     -- Move forward          *");
    BT.println("*    'S'     -- Move backward         *");
    BT.println("*    'A'     -- Turn left             *");
    BT.println("*    'D'     -- Turn right            *");
    BT.println("*    'J'     -- Solenoid ON           *");
    BT.println("*    'K'     -- Solenoid OFF          *");
    BT.println("*                                     *");
    BT.println("* - Others -                          *");
    BT.println("*    'M'     -- Default Position      *");
    BT.println("*                                     *");
    BT.println("* or use any kind of joystick         *");
    BT.println("* or peripherals                      *");
    BT.println("*                                     *");
    BT.println("***************************************");
}

void defaultState()
{
    // Setting all actuators to default state
    // Servo initial position
    while ( (leftServo.read() != SERVO_L_MIN_ANG) && (rightServo.read() != SERVO_R_MIN_ANG) )
    {
        // Setting both servo to minimal angle
        leftServo.write(SERVO_L_MIN_ANG);
        rightServo.write(SERVO_R_MIN_ANG);
    }    

    // Stepper motor initial position
    while (panMotor.currentPosition() != STEPPER_DEFAULT_POS)
    {
        panMotor.moveTo(STEPPER_DEFAULT_POS);
        panMotor.setSpeed(STEPPER_DEFAULT_SPEED);
        panMotor.run();
    }
    
    // Turning off solenoid
    solenoid.off();
}

void loop()
{
    unsigned int command; // variable to store commands
  
    // If connection severed,
    // setting every actuator to default state
    if (!BT.available() )
    {
        defaultState();
    }
    // Reading and executing command
    else
    {
        command = BT.read();
        //BT.print("Command : "); // For debugging input command
        //BT.println(command);

        // Move forward command
        if (command == 'w')
        {
            BT.println("Moving forward");

        }

        // Move backward command
        else if (command == 's')
        {
            BT.println("Moving backward");
            
        }

        // Tilt left command
        else if (command == 'a')
        {
            BT.println("Tilting left");
            
        }

        // Tilt right command
        else if (command == 'd')
        {
            BT.println("Tilting right");
            
        }

        // Solenoid on command
        else if (command == 'j')
        {
            BT.println("Solenoid ON");
            solenoid.on();
        }

        // Solenoid off command
        else if (command == 'k')
        {
            BT.println("Solenoid OFF");
            solenoid.off();
        }

        // Default command
        else if (command == 'm')
        {
            BT.println("Setting to default");
            defaultState();
        }
    }
}
