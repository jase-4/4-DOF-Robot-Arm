from stm32_interface import send_pose, send_velocity, grip, wait_till_done
from models import Pose, Velocity


class RobotArm:
    def __init__(self):
        self.pose = Pose(25, 55, 115)

        self.velocity = Velocity(
            base=200.0,
            elbow=120.0,
            wrist=120.0,
            gripper=220.0
        )

    def move(self, base=None, elbow=None, wrist=None):
        if base is not None:
            self.pose.base = base
        if elbow is not None:
            self.pose.elbow = elbow
        if wrist is not None:
            self.pose.wrist = wrist

        send_pose(self.pose)
        wait_till_done()

    def set_velocity(self):
        send_velocity(self.velocity)

    def grip(self, angle):
        grip(angle)

    def home(self):
        self.move(85, 180, 180)
        self.grip(45)