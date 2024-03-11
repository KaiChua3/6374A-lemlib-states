#include "main.h"
#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "autons.hpp"
#include "Catapult.hpp"
#include "Intake.hpp"
#include "Wings.hpp"
#include "Constants.hpp"

Catapult cata(CataPort, SmallCataPort); 
Intake intake(IntakePort);
Wings wings(PistonPort1, PistonPort2, HangPort, HangPort2);

void SixTriballAutonomous() {
    ppchassis.setPose(0, 0, 0);

    intake.spinIntake(-1 * IntakeSpeed);
    ppchassis.moveToPoint(-32, 50, 2000, 100);
    ppchassis.waitUntilDone();
    
    ppchassis.turnTo(-1000, 50, 800, 90);
    ppchassis.waitUntilDone();

    intake.spinIntake(IntakeSpeed);
    ppchassis.moveToPoint(2, 50, 1200, 100);
    ppchassis.waitUntilDone();
    
    intake.spinIntake(0);
    ppchassis.turnTo(-33, 23, 800, 90);
    ppchassis.waitUntilDone();

    intake.spinIntake(-1 * IntakeSpeed);
    ppchassis.moveToPoint(-29, 23, 1500, 100);
    ppchassis.waitUntilDone();
    
    ppchassis.turnTo(4, 50, 800, 90);
    ppchassis.waitUntilDone();

    intake.spinIntake(IntakeSpeed);
    ppchassis.moveToPoint(4, 50, 1500, 100);
    ppchassis.waitUntilDone();
    
    ppchassis.turnTo(0, -8, 800, 90);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(0, -8, 1200, 100);
    ppchassis.waitUntilDone();

    
}

void oppositeSideWPAutonomous() {
    ppchassis.setPose(0, 0, 0);

    intake.spinIntake(-1 * IntakeSpeed);
    ppchassis.moveToPose(0, 0, 17, 1000, {.minSpeed = 110});
    ppchassis.waitUntilDone();

    ppchassis.moveToPose(18, 48, 27, 1000, {.minSpeed = 90});
    ppchassis.waitUntilDone();
    
    wings.activateWings(true);
    ppchassis.moveToPose(19, 44, -78, 1000, {.minSpeed = 75});
    ppchassis.waitUntilDone();
    
    ppchassis.turnTo(12, 1000, 1000, 90);
    ppchassis.waitUntilDone();
    
    ppchassis.moveToPose(19, 10, 23, 2000, {.forwards = false, .minSpeed = 110});
    ppchassis.waitUntilDone();
    
    wings.activateWings(false);
    ppchassis.moveToPose(19, 15, 23, 750, {.minSpeed = 127});
    ppchassis.waitUntilDone();
    
    ppchassis.turnTo(1.5, 19, 800, 90);
    ppchassis.waitUntilDone();

    ppchassis.moveToPose(7.5, 19, -56, 1500, {.minSpeed = 110});
    ppchassis.waitUntilDone();
    
    ppchassis.moveToPose(-13, -12, -148, 1500, {.minSpeed = 90});
    ppchassis.waitUntilDone();
    
    wings.activateWings(true);
    ppchassis.turnTo(14, -24, 800, 90);
    ppchassis.waitUntilDone();

    wings.activateWings(false);
    ppchassis.moveToPose(34, -30, -230, 2000, {.minSpeed = 110});
    ppchassis.waitUntilDone();

    intake.spinIntake(IntakeSpeed);
}

void programmingSkills() {
    ppchassis.setPose(0, 0, 0);

    ppchassis.moveToPose(-15, 6, 85, 2000, {.minSpeed = 110});
    ppchassis.waitUntilDone();

    ppchassis.turnTo(74, 57, 800);
    ppchassis.waitUntilDone();

    wings.activateWings(true);
    cata.launch(CataSpeed);
    pros::delay(30000);

    cata.launch(0);

    wings.activateWings(false);
    ppchassis.moveToPose(-9, 6, 180, 1000, {.minSpeed = 110});
    ppchassis.waitUntilDone();

    ppchassis.moveToPose(-12, 21, 180, 1500, {.forwards = false, .minSpeed = 110});
    ppchassis.waitUntilDone();

    ppchassis.moveToPose(-12, 12, 180, 1000, {.minSpeed = 110});
    ppchassis.waitUntilDone();

    ppchassis.turnTo(10, -5, 800);
    ppchassis.waitUntilDone();
    
    ppchassis.moveToPose(10, -5, 98, 2000, {.minSpeed = 80});
    ppchassis.waitUntilDone();
    
    ppchassis.moveToPose(71, -5, 90, 1500, {.minSpeed = 110});
    ppchassis.waitUntilDone();
    
    ppchassis.turnTo(71, -1000, 800);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(102, 6, 1500, false);
    ppchassis.waitUntilDone();

    ppchassis.turnTo(102, 26, 800, false);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(105, 26, 1000, false);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(98, 10, 1000);
    ppchassis.waitUntilDone();

    ppchassis.turnTo(61, 39, 800);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(61, 20, 1500);
    ppchassis.waitUntilDone();

    ppchassis.turnTo(73, 72, 800, false);
    ppchassis.waitUntilDone();

    wings.activateWings(true);
    ppchassis.moveToPoint(93, 33, 2000, false);
    ppchassis.waitUntilDone();

    wings.activateWings(false);
    ppchassis.moveToPoint(63, 44, 1500);
    ppchassis.waitUntilDone();

    ppchassis.turnTo(100, 85, 1000, false);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(95, 60, 2000, false);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(63, 60, 1500);
    ppchassis.waitUntilDone();

    ppchassis.turnTo(130, 120, 1200, false);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(112, 100, 2000, false);
    ppchassis.waitUntilDone();

    ppchassis.turnTo(108, 72, 800, false);
    ppchassis.waitUntilDone();

    wings.activateWings(true);
    ppchassis.moveToPoint(108, 72, 2500, false);
    ppchassis.waitUntilDone();


}

void testingDrive() {
    ppchassis.setPose(0, 0, 0);
    ppchassis.moveToPoint(0, 24, 5000, 110);
}

void testingTurn() {
    ppchassis.setPose(0, 0, 0);
    ppchassis.turnTo(24, 0, 750, 110);
}

void fineTuneTesting() {
    ppchassis.setPose(0, 0, 0);

    ppchassis.moveToPoint(0, 24, 10000, 110);
    ppchassis.waitUntilDone();

    ppchassis.turnTo(-24, 24, 10000, 90);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(-24, 24, 1000, 110);
    ppchassis.waitUntilDone();

    ppchassis.turnTo(-24, 1000, 750, 90);
    ppchassis.waitUntilDone();

    ppchassis.moveToPoint(-24, 36, 1000, 127);
    ppchassis.waitUntilDone();

}

void disruptAuton() {
    
}