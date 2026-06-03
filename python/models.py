class Pose:
    def __init__(self, base, elbow, wrist):
        self.base = base
        self.elbow = elbow
        self.wrist = wrist


class Velocity:
    def __init__(self, base, elbow, wrist, gripper):
        self.base = base
        self.elbow = elbow
        self.wrist = wrist
        self.gripper = gripper