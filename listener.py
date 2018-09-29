#!/usr/bin/env python
import rospy
from img_processing.msg import centers

def callback(data):
    x = data.centers
    print(x)

def listener():
    rospy.init_node('listener',anonymous=True)
    rospy.Subscriber('chatter',centers,callback)

    rospy.spin()

if __name__ == '__main__':
    listener()
