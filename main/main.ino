// Made by : 
//  
// Leonardi
// e-mail  : leochen123987@gmail.com
// github  : github.com/akvavit01
//

// Program for solenoid-based robotic arm
// Made with Arduino UNO based board

// Header inclusion
// Arduino.h
#include <Arduino.h>

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

void setup()
{
    // Servo initialization
    // Object assignment
    Servo leftServo;
    Servo rightServo;

    // Pin assignment
    leftServo.attach(SERVO_L, SERVO_L_MIN_PWM, SERVO_L_MAX_PWM);
    rightServo.attach(SERVO_R, SERVO_R_MIN_PWM, SERVO_R_MAX_PWM);

    // Initial position
    while ( (leftServo.read() != SERVO_L_MIN_ANG) && (rightServo.read() != SERVO_R_MIN_ANG) )
    {
        // Setting both servo to minimal angle
        leftServo.write(SERVO_L_MIN_ANG);
        rightServo.write(SERVO_R_MIN_ANG);
    }

    // Stepper motor initialization
    // Object assignment
    AccelStepper yawMotor(STEPPER_PIN_AMOUNT, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);

    // Set stepper motor acceleration and speed
    yawMotor.setMaxSpeed(STEPPER_MAX_SPEED);
    yawMotor.setAcceleration(STEPPER_ACCEL);

    // Initial position
    while (yawMotor.currentPosition() != STEPPER_DEFAULT_POS)
    {
        yawMotor.moveTo(STEPPER_DEFAULT_POS);
        yawMotor.setSpeed(STEPPER_DEFAULT_SPEED);
        yawMotor.run();
    }

    // Solenoid initialization
    Solenoid solenoid{RELAY_PIN};
    solenoid.off(); // Turning off solenoid

    // Serial communication initialization
    BT.begin(BT_BAUDRATE);
}

void loop()
{
    BT.println("WOLOLO");
    delay(1000);
}
