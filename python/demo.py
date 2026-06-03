from robot_arm import RobotArm
import time

arm = RobotArm()

arm.set_velocity()

def pickup(base):
    arm.grip(180)
    arm.move(base, 55, 115)
    arm.move(wrist=180)
    arm.grip(70)
    arm.move(base, 90, 115)


def drop(base):
    arm.move(base, 90, 115)
    arm.move(base, 55, 115)
    arm.move(wrist=180)
    arm.grip(180)
    arm.move(base, 90, 115)


arm.home()
time.sleep(1)

pickup(25)
drop(155)

pickup(155)
drop(25)

arm.home()