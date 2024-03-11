#include "main.h"
#include "api.h"
#include "lemlib/api.hpp"
#include "autons.hpp"
#include "Catapult.hpp"
#include "Intake.hpp"
#include "Wings.hpp"
#include "Constants.hpp"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// drive motors
pros::Motor lF(-18, pros::E_MOTOR_GEARSET_06); // left front motor. port 12, reversed
pros::Motor lM(-17, pros::E_MOTOR_GEARSET_06); // left middle motor. port 11, reversed
pros::Motor lB(-16, pros::E_MOTOR_GEARSET_06); // left back motor. port 1, reversed
pros::Motor rF(13, pros::E_MOTOR_GEARSET_06); // right front motor. port 2
pros::Motor rM(14, pros::E_MOTOR_GEARSET_06); // right middle motor. port 11
pros::Motor rB(15, pros::E_MOTOR_GEARSET_06); // right back motor. port 13

// motor groups
pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group

// Inertial Sensor on port 2
pros::Imu imu(7);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 360
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            6, // derivative gain (kD)
                                            3, // anti windup
                                            2, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            4, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(2.2, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             8, // derivative gain (kD)
                                             3, // anti windup
                                             3, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             8, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
// note that in this example we use internal motor encoders (IMEs), so we don't p+ass vertical tracking wheels
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// create the chassis

lemlib::Chassis ppchassis(drivetrain, linearController, angularController, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    ppchassis.calibrate(); // calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", ppchassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", ppchassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", ppchassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", ppchassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
ASSET(example_txt); // '.' replaced with "_" to make c++ happy

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
    
    Catapult cata(CataPort, SmallCataPort); 
    Intake intake(IntakePort);
    Wings wings(PistonPort1, PistonPort2, HangPort, HangPort2);

	SixTriballAutonomous();
	// oppositeSideWPAutonomous();
	// programmingSkills();
	// disruptAuton();
	// testingDrive();
	// testingTurn();
    // fineTuneTesting();
}

/**
 * Runs in driver control
*/
void opcontrol() {
    Catapult cata(CataPort, SmallCataPort); 
    Intake intake(IntakePort);
    Wings wings(PistonPort1, PistonPort2, HangPort, HangPort2);
    Systems systems(cata, intake, wings);
    
    wings.activateHang(false);

    // controller
    // loop to continuously update motors
    while (true) {
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive
        ppchassis.curvature(leftY, rightX, 2.2);
        systems.update();
        // delay to save resources
        pros::delay(10);
    }
}
