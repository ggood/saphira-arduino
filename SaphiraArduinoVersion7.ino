//
// The Arduino program to control Saphira.
//
// Team Saphira, (c) 2010
//
// We use pulse width modulation (pwm) to control the pressure delivered to each
// pneumatic cylinder.

int pauseInMs           = 7;               // Number of milliseconds per tick
int ticks               = 0;               // Number of ticks that have past since startup
int ticksInThisCycle    = 0;               // Number of ticks within the current cycle
int ticksPerCycle       = 18;              // Start a new cycle of pwm after this many ticks
int bodyLiftSpeed       = 0;
int wingsSpeed          = 0;
int headtiltSpeed       = 0;
int jawSpeed            = 0;
int headtwistLeftSpeed  = 0;
int headtwistRightSpeed = 0;
int eyesSpeed           = 0;
int bodyLiftPin         = 11;
int wingsPin            = 10;
int headtiltPin         = 9;
int jawPin              = 8;
int headtwistLeftPin    = 7;
int headtwistRightPin   = 6;
int eyesPin             = 5;

void setup()
{
   pinMode(bodyLiftPin, OUTPUT); 
   pinMode(wingsPin, OUTPUT);
   pinMode(headtiltPin, OUTPUT);
   pinMode(jawPin, OUTPUT);
   pinMode(headtwistLeftPin, OUTPUT);
   pinMode(headtwistRightPin, OUTPUT);
   pinMode(eyesPin, OUTPUT);   
   
   Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop()
{
   if (Serial.available()) { // If data is available to read,
    int packedValue = Serial.read();
    
    // Unpack it.
    int cylinderNumber = packedValue / 10;
    int _speed = packedValue % 10; 
    
    if (cylinderNumber == 1)  { 
      bodyLiftSpeed = _speed * 2;
    }
    if (cylinderNumber == 2)  {
      wingsSpeed = _speed * 2;
    }
    if (cylinderNumber == 3)  {
      headtiltSpeed = _speed * 2;
    }
    if (cylinderNumber == 4)  {
      jawSpeed = _speed * 2;
    }
    if (cylinderNumber == 5)  {
      headtwistLeftSpeed = _speed * 2;
    }
    if (cylinderNumber == 6)  {
      headtwistRightSpeed = _speed * 2;
    }
    if (cylinderNumber == 7)  {
      eyesSpeed = _speed;
    }

     // Pack it and send it back for confirmation
    int toSendBack = cylinderNumber * 10 + _speed;
    Serial.write(toSendBack);
    
   }
    ticks++;
    ticksInThisCycle++;
    if (ticks % ticksPerCycle == 0) {
      // Start a new cycle
      ticksInThisCycle = 0;
    }
    if (ticksInThisCycle < bodyLiftSpeed) {
      digitalWrite( bodyLiftPin, HIGH);
    } else {
      digitalWrite( bodyLiftPin, LOW);
    }
    
    if (ticksInThisCycle < wingsSpeed)  {
      digitalWrite( wingsPin, HIGH);
    } else {
      digitalWrite( wingsPin, LOW);
    }
    if (ticksInThisCycle < headtiltSpeed)  {
      digitalWrite( headtiltPin, HIGH);
    } else {
      digitalWrite( headtiltPin, LOW);
    }
    if (ticksInThisCycle < jawSpeed)  {
      digitalWrite( jawPin, HIGH);
    } else {
      digitalWrite( jawPin, LOW);
    }
    if (ticksInThisCycle < headtwistLeftSpeed)  {
      digitalWrite( headtwistLeftPin, HIGH);
    } else {
      digitalWrite( headtwistLeftPin, LOW);
    }
    if (ticksInThisCycle < headtwistRightSpeed)  {
      digitalWrite( headtwistRightPin, HIGH);
    } else {
      digitalWrite( headtwistRightPin, LOW);
    }
    if (eyesSpeed == 1)  {
      digitalWrite( eyesPin, HIGH);
    } else {
      digitalWrite( eyesPin, LOW);
    }    
    delay(pauseInMs);
}
