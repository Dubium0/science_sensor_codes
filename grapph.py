# -*- coding: utf-8 -*-
"""
Created on Sun Dec 12 12:55:11 2021

@author: LENOPC
"""

import rospy
import matplotlib.pyplot as plt
from std_msgs.msg import UInt8



dictionary = {"temperature":[],"altitude":[],"pressure":[]}
name_list = ["pressure","altitude","temperature"]
x = 0
def data_collect(data):
    dictionary[name_list].append(data.data)
    x+=1

    
    
def plotting():
    plt.subplot(3,1,1)
    plt.plot(df["temperature"],color = "blue",label = "temperature")
    plt.ylabel("C")
    plt.legend()
    plt.subplot(3,1,2)
    plt.plot(df["altitude"],color = "red",label = "altitude")
    plt.ylabel("m")
    plt.legend()
    plt.subplot(3,1,3)
    plt.plot(df["pressure"],color = "yellow",label = "pressure")
    plt.ylabel("Pa")
    plt.legend()
    plt.draw()
    plt.pause(0.0001)
    



if __name__ == '__main__' :
    
	rospy.init_node('graph' , anonymous=True)
	rospy.Subscriber('SENSORS', UInt8 , plotting)
    data_collect(data)
	plt.show()
	rospy.spin()