//code here is a copy from the state machine test code, this is to have a seperate test version that can be run independently without modifying main code


char xCoord[9];
char yCoord[9];
int arrayPos = 0;
int arrayNum = 0;
int faceX = 0;
int faceY = 0;
String inputString;
int seperator;

void setup() {
  
  Serial.begin(9600);
}

void getCoordinates(char byte){  //runs for every byte in the serial communication, outputs whole coordinates
  
   if (byte == 'n') { //checks to see if endline character is found
     
      seperator = inputString.indexOf(','); //sets seperator to be the position in the string where the comma is present
      if (seperator != -1) { // runs if comma is present 
          faceX = inputString.substring(0, seperator).toInt();  //sets the x coordinate to be all the numbers before the comma
          faceY = inputString.substring(seperator + 1).toInt(); //sets the y coordinate to be all the numbers after the comma
          Serial.println (" x: " + String(faceX) + ", y: " + String(faceY)); //prints full coordinates. 
      }
      inputString = ""; 
    }
  else { //adds each part to the input string when the endline character is not found
    inputString += byte; 
  }
}

void loop() {
  
  //data from python needs to be organised like this ___,___n    where the blanks are the x and y values, the n is there to end the communication
  while (Serial.available() > 0) { //checks to see if there is any serial communication
  
    char byte = Serial.read(); //set byte from serial communication
    Serial.print(byte); //print byte
    getCoordinates(byte); //run function to get coordinates

}
}
