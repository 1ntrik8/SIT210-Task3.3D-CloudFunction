
/*
Leigh Rowell - SIT210
Ontrack 3.3D - Buddy System

Ref:
https://docs.particle.io/tutorials/hardware-projects/hardware-examples/photon/

Steps: Photon
1) Build an embedded system using your Particle device and 1 LED light.
2) We have setup a Photon at RIoT lab that sends “wave” signal to any registered Particle device. It is intended to simulate a Photon buddy that supposedly detects a waving motion using the motion sensor; i.e. when someone moves their hand left and right in front of the sensor.
a) This photon publishes using following command every minute or so: Particle.publish("Deakin_RIOT_SIT210_Photon_Buddy", "wave");
3) Create a handler method that whenever your system received a “wave”, the system will flash the LED 3 times.
4) Test out the system.
*/


// Define constants
#define LEDPIN D7
#define EVENTNAME "Deakin_RIOT_SIT210_Photon_Buddy"

// Declare delay times for LED flashes
#define SHORTDELAY 200
#define LONGDELAY 800


// Declare functions
void eventHandler(const char *event, const char *data); 
void waveHandler();
void patHandler();
void unknownHandler();

void setup() {
    // Setup pin modes..
    pinMode(LEDPIN, OUTPUT); // Our on-board LED is output as well

    // Here we are going to subscribe to your buddy's event using Particle.subscribe
    // Subscribe will listen for the event "Deakin_RIOT_SIT210_Photon_Buddy" and, when it finds it, will run the function eventHandler()
    Particle.subscribe(EVENTNAME, eventHandler);
    
    // Setup serial communication
    Serial.begin(9600);
    while (!Serial.available() && millis() < 30000) {
    Serial.println("Press any key to start.");
    Particle.process();
    delay(1000);
    }
    Serial.println("Buddy System - Ontrack Task 3.3D");
    Serial.println("################################");

}


void loop() {
    // Nothing is required here as the Particle.subscribe declaration above sets the device to monitor for the event to be published...
    
}


void eventHandler(const char *event, const char *data)
{
    // This is called when the Deakin device publishes an event..
    
    /* Particle.subscribe handlers are void functions, which means they don't return anything.
      They take two variables-- the name of your event, and any data that goes along with your event.
      In this case, the event will be const EVENTNAME and the data will be "wave" or "pat".

      Use strcmp(), which compares two chars and if they are the same strcmp will return 0.
      
     */
    
    Serial.print("Time: ");
    Serial.print(Time.hour());
    Serial.print(":");
    Serial.print(Time.minute());
    Serial.print(":");
    Serial.print(Time.second());
    Serial.print(" - ");
    
    
    if (strcmp(data,"wave")==0) {
        // call the wave function
        Serial.println("Wave event received..");
        waveHandler();
    }
    else if (strcmp(data,"pat")==0) {
        // call the pat function
        Serial.println("Pat event received..");
        patHandler();
    }
    else {
        // if the data is something else, call the unknown handler
        Serial.print("Unknown event received: ");
        Serial.print(event);
        Serial.print(", data: ");
        Serial.println(data);
        unknownHandler();
    }
}

void waveHandler()
{
    // Flash the LED 3 times with short delay..
    for(int i = 0; i < 3; i++)
    {
        digitalWrite(LEDPIN, HIGH);
        delay(SHORTDELAY);
        digitalWrite(LEDPIN, LOW);
        delay(SHORTDELAY);
    }
}

void patHandler()
{
    // Flash the LED 2 times with long delay..
    for(int i = 0; i < 2; i++)
    {
        digitalWrite(LEDPIN, HIGH);
        delay(LONGDELAY);
        digitalWrite(LEDPIN, LOW);
        delay(LONGDELAY);
    }
}

void unknownHandler()
{
    // Flash the LED 5 times with short delay..
    for(int i = 0; i < 5; i++)
    {
        digitalWrite(LEDPIN, HIGH);
        delay(SHORTDELAY);
        digitalWrite(LEDPIN, LOW);
        delay(SHORTDELAY);
    }
}


