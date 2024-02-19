#!/usr/bin/env python3
from tkinter import*
import rospy
from std_msgs.msg import UInt16
from std_msgs.msg import Float64
from sensor_msgs.msg import JointState
from std_msgs.msg import Header

frame = Tk()
frame.geometry("200x200")

rospy.init_node('GUI_SERVO')
rate = rospy.Rate(10)
rate.sleep()

joint_pub = rospy.Publisher('joint_states', JointState, queue_size=10)
servo1_pub = rospy.Publisher("servo1",Float64,queue_size=10)
servo2_pub = rospy.Publisher("servo2",Float64,queue_size=10)

def joint():
    # joint = event.position[0]
    # servo0_pub.publish(joint)
    # rospy.loginfo(joint)
    # event.position[0] = servo1.get()
    # event.position[1] = servo2.get()
    joint = JointState()
    joint.header = Header()
    joint.header.stamp = rospy.Time.now()
    joint.name = ['joint1', 'joint2']
    joint.position = [(servo1.get()/150)*3.1416, (servo2.get()*0.02)/110]
    joint.velocity = []
    joint.effort = []
    joint_pub.publish(joint)

def pot0(event):
    if event.data <= 20:
        pot0 = 0
    elif event.data >= 130:
        pot0 = 150
    else :
        pot0 = event.data
    # L.config(text=str(pot0))
    servo1.set(pot0)
    servo1_pub.publish(pot0)

def pot1(event):
    if event.data <= 20:
        pot1 = 0
    elif event.data >= 90:
        pot1 = 110
    else :
        pot1 = event.data
    # R.config(text=str(pot1))
    servo2.set(pot1)
    servo2_pub.publish(pot1)

# joint_sub = rospy.Subscriber("/joint_states",JointState,callback = joint)
chatter0_sub = rospy.Subscriber("chatter0",Float64,callback = pot0)
chatter1_sub = rospy.Subscriber("chatter1",Float64,callback = pot1)

name = Label(frame,font=('Arial',30),text="Daijujin")
name.pack()
# R = Label(frame,font=('Arial',30),text="0")
# R.pack()

servo1 = Scale(frame, from_=0, to=150, orient=HORIZONTAL)
servo1.set(0) # 0 is defult value for scale
servo1.pack()

def Talker1(event):
    cmd_val1 = Float64(servo1.get())
    # rospy.loginfo(cmd_val)
    servo1_pub.publish(cmd_val1)
    # joint_pub.publish(cmd_val)

servo1.bind("<ButtonRelease>", Talker1)

servo2 = Scale(frame, from_=0, to=110, orient=HORIZONTAL)
servo2.set(0) # 0 is defult value for scale
servo2.pack()

def Talker2(event):
    cmd_val2 = Float64(servo2.get())
    # rospy.loginfo(cmd_val)
    servo2_pub.publish(cmd_val2)
    # joint_pub.publish(cmd_val)

servo2.bind("<ButtonRelease>", Talker2)

# B1 = Button(frame, text= "ON", command = lambda: Talker1())
# B1.pack()

def update():
    joint()
    frame.after(1, update)

update()
frame.mainloop()
