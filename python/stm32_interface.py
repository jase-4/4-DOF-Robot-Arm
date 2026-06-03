import serial
import time

stm = serial.Serial('/dev/ttyACM1', 115200, timeout=1)
time.sleep(2)


def read_line():
    return stm.readline().decode(errors="ignore").strip()


def send(cmd: str):
    stm.write((cmd + "\n").encode())


def wait_till_done(timeout=5):
    start = time.time()

    while time.time() - start < timeout:
        msg = read_line()
        if msg:
            print("STM32:", msg)
        if msg == "DONE":
            return

    raise TimeoutError("No DONE received")


def wait_till_ready(timeout=5):
    start = time.time()

    while time.time() - start < timeout:
        send("PING")
        msg = read_line()

        if msg:
            print("STM32:", msg)

        if msg == "READY":
            return

        time.sleep(0.2)

    raise TimeoutError("No READY received")


def send_pose(pose):
    send(f"POSE {pose.base} {pose.elbow} {pose.wrist}")


def send_velocity(vel):
    send(f"VELO {vel.base} {vel.elbow} {vel.wrist} {vel.gripper}")


def grip(angle):
    send(f"GRIP {angle} 0")
    wait_till_done()