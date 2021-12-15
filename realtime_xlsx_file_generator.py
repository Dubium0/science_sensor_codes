# -*- coding: utf-8 -*-
"""
Created on Mon Dec 13 01:03:23 2021

@author: LENOPC
"""


#sensor data generator 
import random
import pandas as pd
import xlsxwriter
import matplotlib.pyplot as plt
#import rospy 
#from std_msgs.msg import String

"""
'Random sensor values' part not necessery for ros implementation. We will get sensor values from publisher.
 
"""

# random sensor values
def temperature():
    x = random.randint(20,30)
    return x


def pressure():
    x = random.randint(500,550)
    return x 
    
    
def altitude():
    x = random.randint(50,60)
    return x 

def radiation():
    x = random.randint(1000,1100)
    return x 


def moisture():
    x = random.randint(220,240)
    return x


# convert and append to dict

def callback(sensor_datas):
    data_list =sensor_datas.split(",") # we will write data.data instead of sensor_datas
    k = 0
    for i in dictionary:
        dictionary[i].append(float(data_list[k]))
        k+=1
    
    plt.subplot(5,1,1)
    plt.plot(dictionary["temperature"],color = "blue")
    plt.ylabel("Celcius")
    
    plt.subplot(5,1,2)
    plt.plot(dictionary["altitude"],color = "red")
    plt.ylabel("meter")
    
    plt.subplot(5,1,3)
    plt.plot(dictionary["pressure"],color = "yellow")
    plt.ylabel("Pa")
    
    plt.subplot(5,1,4)
    plt.plot(dictionary["radiation"],color = "green")
    plt.ylabel("?")
    
    plt.subplot(5,1,5)
    plt.plot(dictionary["moisture"],color = "black")
    plt.ylabel("?")
    
    plt.draw()
    plt.pause(0.0001)

def create_excel_file(dictionary):
    # read sensor datas
    
    df = pd.DataFrame(dictionary) # be sure that it is on the current directory
    # create new excel file's path
    file_path = "./bunee2.xlsx" # this should be the path is  current directory
    
    #add extra index col
    df["index"]  = [i for i in range(len(df))] # to plot easily
    
    # create new excel file
    workbook = xlsxwriter.Workbook(file_path)
    
    #create sheet1
    worksheet_  = workbook.add_worksheet()
    
    # fill sheet1 with sensor values
    for index,name in enumerate(df.columns):
        worksheet_.write(0,index,name)# 
        worksheet_.write_column(1,index,df[name])


    # create a blank chart
    chart = workbook.add_chart({"type":"scatter","subtype":"straight"})
    #fill chart categories x-axis  values y-axis
    chart.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$A$2:$A${}".format(len(df)+1),
                      "name":"temperature"})
    # name axs
    chart.set_x_axis({'name': 'Index'})
    chart.set_y_axis({'name': 'Temperature(C)'})
    # add chart to sheet1 at certain position it generally takes 15x8 (lenxwidth) places
    worksheet_.insert_chart("I1",chart)
    
    
    chart1 = workbook.add_chart({"type":"scatter","subtype":"straight"})
    chart1.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$B$2:$B${}".format(len(df)+1),
                      "name":"pressure"})
    chart1.set_x_axis({'name': 'Index'})
    chart1.set_y_axis({'name': 'Pressure(Pa)'})
    worksheet_.insert_chart("I16",chart1)
    
    chart2 = workbook.add_chart({"type":"scatter","subtype":"straight"})
    chart2.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$C$2:$C${}".format(len(df)+1),
                      "name":"altitude"})
    chart2.set_x_axis({'name': 'Index'})
    chart2.set_y_axis({'name': 'Altitude(meter)'})
    worksheet_.insert_chart("Q1",chart2)
    
    chart3 = workbook.add_chart({"type":"scatter","subtype":"straight"})
    chart3.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$D$2:$D${}".format(len(df)+1),
                      "name":"radiation"})
    chart3.set_x_axis({'name': 'Index'})
    chart3.set_y_axis({'name': 'Radiation(?)'})
    worksheet_.insert_chart("Q16",chart3)
    
    chart4 = workbook.add_chart({"type":"scatter","subtype":"straight"})
    chart4.add_series({"categories":"=Sheet1!$F$2:$F${}".format(len(df)+1),
                      "values":"=Sheet1!$E$2:$E${}".format(len(df)+1),
                      "name":"moisture"})
    chart4.set_x_axis({'name': 'Index'})
    chart4.set_y_axis({'name': 'Moisture(?)'})
    worksheet_.insert_chart("Y1",chart4)
    
    workbook.close()



dictionary =  {"temperature":[],"pressure":[],"altitude":[],"radiation":[],"moisture":[]}
x= 0
while x<100: # if __name__=="__main__":
    x+=1
    
    #rospy.init_node("excel_writer")
    #rospy.Subscriber("SENSORS",String,callback) # we will call callback here
    sensor_datas = "{},{},{},{},{}".format(temperature(),pressure(),altitude(),radiation(),moisture()) # it will be data.data for ros sub
    
    callback(sensor_datas)# we will directly write data.data for ros implementation
    
    plt.show()
    create_excel_file(dictionary)
    #rospy.spin()
    
    
    
    #time.sleep(0.5)
    
    