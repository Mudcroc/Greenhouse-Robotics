

//I am creating variables with specific names and assigning them a certain value to be used later.

const unsigned long eventInterval = 1000; // 'eventInterval' is 1 second

//'previousTime1' correlates to the fans, 'previousTime2' correlates to the pumps

unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;

// this line of code tells the arduino which pins the fans and pump are plugged into

int fan = 9;
int pump = 3;

void setup() {

  //stating that the fans and pumps are something that gets power outputted to them

  pinMode(fan, OUTPUT);
  pinMode(pump, OUTPUT);

  //setting up communication to the serial monitor

  Serial.begin(9600);
}

//everything inside this loop will run forever, everything inside it controls the intervals at which the program operates.

void loop() {

  //here i am setting up the sub-program that will focus on reading the infomation from the temprature sensor.
  //I create two varibles, one called 'val': made to store raw sensor infomation, and 'dat': to store the calculated temperature.
  //the section 'dat = (double)val * (5 / 10.24);', functions by deviding 5 by 10.24.
  //it then takes the outcome of that equation and multiplies 'val' by it, converting the raw infomation into a temperature ('dat').
  //the value of 'dat' (the temprature) is then displayed on the serial monitor

  uint16_t val;
  double dat;
  val = analogRead(A0);
  dat = (double)val * (5 / 10.24);
  Serial.print("Tep:");
  Serial.print(dat);
  Serial.println("C");

  //this currentTime = millis states that the variable called 'currentTime' is whatever the number of milliseconds is

  unsigned long currentTime = millis();

  //this line subtracts whatever the current millisecond is, that from whatever the previous time was.
  //if the remainder is equal or greater then the 'eventInterval' (which is 1000) its asks what the current temperature ('dat') is.
  //if the temperature reading is equal to or greater than 35, then the fan will turn on.
  //if the temperature doesnt meet the requirements the fan will stay off.
  //if the fan does turn on, it will turn off if the remainder of whaterever the current millisecond is minus the previous time is greater or equal to 5000.

  if (currentTime - previousTime1 >= eventInterval) {
    if (dat >= 35) {
      digitalWrite(9, HIGH);
      Serial.println("fan on");
    } else {
      digitalWrite(9, LOW);
      Serial.println("fan off");
    }
    if (currentTime - previousTime1 >= 5000) {
      Serial.println("fan off");
    }

    //this line subtracts whatever the 'currentTime' is from whatever the 'previousTime1' if the outcome is greater or equal to 5000
    //then it will turn off the fan. it will then set whatever the previous time was to whatever the current millisecond is.

    if (currentTime - previousTime1 >= 5000) {
      digitalWrite(9, LOW);
      Serial.println("fan off");

      previousTime1 = millis();
    }

    //this line of code controls the pump, it says to subtract the 'currentTime' from 'previousTime2'.
    //if the outcome is equal to or is greater than 3000, turn on the pump.

    if (currentTime - previousTime2 >= 3000) {
      digitalWrite(3, HIGH);
      Serial.println("pumpOn");
    }

    //this line subtracts whatever the 'currentTime' is from previous time. if the outcome is something greater or equal to 10000, then it will turn off the pump.
    //it will follow on by setting whatever the previous time was to whatever the current millisecond is.

    if (currentTime - previousTime2 >= 10000) {
      digitalWrite(3, LOW);
      Serial.println("pumpOff");

      previousTime2 = millis();
    }

    //this line states that if temprature 'dat' inside the box is equal to, or higher than 45 degrees it will switch off both fans and the pump.
    //this is done so the motors dont spin for long periods of time, something which could quicking their wear and tear. 

    if (currentTime - previousTime1 >= 1000) {
      if (dat >= 45){
      digitalWrite(9, LOW);
      Serial.println("fan off");
      digitalWrite(3, LOW);
      Serial.println("pump off");

      previousTime1 = millis();
      }
    }
  }
}


//once the program runs through all of its commands, it will return to the start of the loop
