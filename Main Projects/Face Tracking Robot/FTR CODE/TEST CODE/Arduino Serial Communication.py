
import serial
import time

# Set up Arduino serial communication
arduino = serial.Serial(port='COM3', baudrate=9600)  # Adjust the COM port as necessary

while True:
    try:
        # Prompt the user to input coordinates
        coordinates = input("Enter coordinates (e.g., x,y): ")

        # Send the coordinates to Arduino
        arduino.write(coordinates.encode())
        print(f"Coordinates sent: {coordinates}")

        # Add a short delay
        time.sleep(0.1)

    except KeyboardInterrupt:
        # Exit loop on Ctrl+C
        print("Exiting program.")
        break

