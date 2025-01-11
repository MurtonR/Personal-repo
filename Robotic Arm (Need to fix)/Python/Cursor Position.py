
import serial
import pyautogui
import time



arduino = serial.Serial(port='COM1', baudrate=9600) #Sets up serial communication

while True:
    x, y = pyautogui.position()
    inverted_y = pyautogui.size().height - y  #Invert the y-coordinate
    centered_x = x - (pyautogui.size().width // 2)  #Centre the x-coordinate
    centered_x = centered_x * -1
    inverted_y = inverted_y + 5
    centered_x = centered_x -10


    if centered_x != 0 and inverted_y != 0:
       data = f"{inverted_y //5.7},{centered_x//8}\n"  # Format the data (e.g., "X,Y\n")
       arduino.write(data.encode())  # Send the data to Arduino
       print(data)
       time.sleep(0.1)
         # Prevents the code from sending message
else:
    time.sleep(0.01)