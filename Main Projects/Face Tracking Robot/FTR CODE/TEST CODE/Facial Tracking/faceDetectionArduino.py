#This code is modified from the libraries facial tracking example code, with the added components being python-arduino communication, obtaining x and y values, calibration and code required to only detect the closest face by comparing bounding boxes
                   
import mediapipe as mp
import cv2
import serial
import time
mp_face_detection = mp.solutions.face_detection
mp_drawing = mp.solutions.drawing_utils
arduino = serial.Serial(port='COM4', baudrate=9600)  # Adjust the COM port as necessary

# For webcam input:
cap = cv2.VideoCapture(0)
with mp_face_detection.FaceDetection(
  #
    model_selection=0, min_detection_confidence=0.5) as face_detection:
  while cap.isOpened():
    success, image = cap.read()
    if not success:
      print("Ignoring empty camera frame.")
      # If loading a video, use 'break' instead of 'continue'.
      continue

    # To improve performance, optionally mark the image as not writeable to
    # pass by reference.
    image.flags.writeable = False
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = face_detection.process(image)

    # Draw the face detection annotations on the image.
    image.flags.writeable = True
    image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    if results.detections: 
      
      closest_face = max(results.detections, key = lambda d:d.location_data.relative_bounding_box.width * #Only detects closest face 
        d.location_data.relative_bounding_box.height) #Gets the detection that has the largest bounding box, is the closest
      mp_drawing.draw_detection(image, closest_face)  #Draws bounding box for the closest face detected
      
    else:
      print("NO FACE DETECTED!!") #Error prevention if no faces are detected
      continue
    bboxC = closest_face.location_data.relative_bounding_box #Gets the coordinates of the closest face detected
    h, w, _ = image.shape  
    x = int(bboxC.xmin * w)  #get xq
    y = int(bboxC.ymin * h)  #get y#
    y = 270 - y #calibration
 

    # display camera, flip the image
    cv2.imshow('MediaPipe Face Detection', cv2.flip(image, 1))
    print(f"Face position: x={x}, y={y}")  # print x and y positions, y has been flipped
    
    #coordinates are the center of the head
    coordinates = (f"{x},{y}n")
  
    # Send the coordinates to Arduino
    arduino.write(coordinates.encode())
    print(f"Coordinates sent: {coordinates}")

    # Add a short delay
    time.sleep(0.1) 

   
        # Check for the 'q' key to exit the loop
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               