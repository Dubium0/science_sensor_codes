#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import rospy
import matplotlib.pyplot as plt
from std_msgs.msg import String

df = {"temperature":[],"altitude":[],"pressure":[]}

def plotting(data):
    data_list = data.data.split(",")
    
    df["temperature"].append(float(data_list[0]))
    df["altitude"].append(float(data_list[2]))
    df["pressure"].append(float(data_list[1]))
    
    plt.subplot(3,1,1)
    plt.plot(df["temperature"],color = "blue")
    plt.ylabel("Celcius")
    
    plt.subplot(3,1,2)
    plt.plot(df["altitude"],color = "red")
    plt.ylabel("meter")
    
    plt.subplot(3,1,3)
    plt.plot(df["pressure"],color = "yellow")
    plt.ylabel("Pa")
    
    plt.draw()
    plt.pause(0.0001)
    



if __name__ == '__main__' :
    
	rospy.init_node('graph' , anonymous=True)
	rospy.Subscriber('SENSORS', String , plotting)
	plt.show()
	rospy.spin()
