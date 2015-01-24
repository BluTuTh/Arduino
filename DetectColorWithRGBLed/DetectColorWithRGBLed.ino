// Define color sensor LED pins
const int ledArray[] = {10,11,12};

// Was balance set?
boolean balanceSet = false;

// Placeholders for color detected
int red = 0;
int green = 0;
int blue = 0;

// Floats to hold color arrays
float colorArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};

// Placeholder for average
int avgRead;
// Light adjustment
int bright = 0;

void setup() {
  // Setup the outputs for the color sensor
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
 
  // Begin serial communication
  Serial.begin(9600);
}

void loop() {
  checkBalance();
  checkColor();
  //printColor();
  printColorHEX();
  
  delay(5000);
}

void checkBalance() {
  // Check if the balance has been set, if not, set it
  if(balanceSet == false){
    setBalance();
  }
}

void setBalance() {
  // Set white balance
  
  // Delay for five seconds
  Serial.println("Set white");
  delay(5000);
  
  // Scan the white sample.
  // Go through each light, get a reading,
  // set the base reading for each color red, green, and blue to the white array
  for (int i = 0; i<= 2; i++) {
     digitalWrite(ledArray[i], HIGH);
     delay(100);
     getReading(5);
     whiteArray[i] = avgRead;
     digitalWrite(ledArray[i], LOW);
     delay(100);
  }
  // We are done with scanning white, 
  // now it will pulse blue to tell you that it is time for the black (or grey) sample.
  
  // Set black balance
  Serial.println("Set black");
  delay(5000);
  
  // Go ahead and scan, sets the color values for red, green, and blue when exposed to black
  for (int i = 0; i <= 2; i++) {
     digitalWrite(ledArray[i], HIGH);
     delay(100);
     getReading(5);
     blackArray[i] = avgRead;
     digitalWrite(ledArray[i], LOW);
     delay(100);
  }
  
  // Set boolean value so we know that balance is set
  balanceSet = true;

  Serial.println("Balance set!");
  Serial.println("----------------------");

  Serial.print("WHITE - R:");
  Serial.print(whiteArray[0]);
  Serial.print("\tG:");
  Serial.print(whiteArray[1]);
  Serial.print("\tB:");
  Serial.println(whiteArray[2]);

  Serial.print("BLACK - R:");
  Serial.print(blackArray[0]);
  Serial.print("\tG:");
  Serial.print(blackArray[1]);
  Serial.print("\tB:");
  Serial.println(blackArray[2]);
  
  delay(5000);
}

void checkColor() {
  for (int i = 0; i <= 2; i++){
    // Turn or the LED, red, green or blue depending which iteration   
    digitalWrite(ledArray[i], HIGH);
    // Delay to allow CdS to stabalize, they are slow
    delay(100);   
    // Take a reading 5 times    
    getReading(5);
    // Set the current color in the array to the average reading
    colorArray[i] = avgRead;
    // Calibrate
    float greyDiff = whiteArray[i] - blackArray[i];
    // The reading returned minus the lowest value
    // divided by the possible range multiplied by 255
    // will give us a value roughly between 0-255 representing
    // the value for the current reflectivity (for the color it is exposed to) of what is being scanned
    colorArray[i] = (colorArray[i] - blackArray[i]) / (greyDiff) * 255; 
    
    // Turn off the current LED
    digitalWrite(ledArray[i], LOW);
    delay(100);
  }
}
void getReading(int times) {
  int reading;
  int combined = 0;
  
  // Take the reading as many times was requested and add them up
  for (int i = 0; i < times; i++) {
    reading = analogRead(0);
    combined = reading + combined;
    delay(10);
  }
  
  // Calculate the average
  avgRead = (combined) / times;
}

// Prints the colors in the color array
void printColor() {
  Serial.print("R = ");
  Serial.print(int(colorArray[0]));
  Serial.print("\tG = ");
  Serial.print(int(colorArray[1]));
  Serial.print("\tB = ");
  Serial.println(int(colorArray[2]));
}

// Prints the color in HEX
void printColorHEX(){
  int R = int(colorArray[0]);
  int G = int(colorArray[1]);
  int B = int(colorArray[2]);
  
  long rgb = 0;
  rgb = ((long)R << 16) | ((long)G << 8 ) | (long)B;
  Serial.println("R:" + String(R) + " G:" + String(G) + " B:" + String(B));
  Serial.println("Hex: #" + String(rgb, HEX));
}
