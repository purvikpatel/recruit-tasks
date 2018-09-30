#!/usr/bin/env python
import rospy
from img_processing.msg import centers
from image_processing import findCenter

def talker():
    pub = rospy.Publisher('chatter',centers, queue_size = 10)
    rospy.init_node('talker',anonymous=True)
    rate = rospy.Rate(10)
    msg = centers()
    msg.centers = findCenter()

    while not rospy.is_shutdown():
        rospy.loginfo(msg)
        pub.publish(msg)
        rate.sleep()


    


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass


