/* SevenSegClock

  This Work Was influnced By Mohit Bhoite's SevSeg Display:
  https://www.bhoite.com/2015/08/sevenseg/
  And has used a modified vertion of the SevSeg Library by Dean Reading:
  https://github.com/DeanIsMe/SevSeg
  SevenSegClock was coded by Saif Sabban. This is an opensource Project.

  This is the main body of the SevenSegClock code which contains most
  of the functions needed to run the SevenSegClock.

  See the included readme for additional information.
*/

/*---------------------------*//* Statments Functions *//*---------------------------*/
#include "FaceFunctions.h" // Calls On FaceFunctions Header
#include "SevSeg.h" // Calls On SevSeg Library (SSS Modified)
#include "Variable.h" // Calls On Variable Header
SevSeg sevseg; // Defines Seven Segment Display As sevseg

/*---------------------------*//* Particle Functions *//*---------------------------*/
int DST_Show_1(String command) { // Choose if you want to apply Daylight Saving. 0 = Don't Apply, 1 = Apply. Set Using The Particle Function
  command = command.toUpperCase();
  if (command == "NO" || command == "0" || command == "FALSE") { // If any of these are typed in, the daylights savings will be removed
    Daylight = 0;
    return 0;
  }
  else if (command == "YES" || command == "1" || command == "TRUE") { // If any of these are typed in, the daylights savings will be removed
    Daylight = 1;
    return 1;
  }
  else { // If anything else is inputted an 999 is returned
    return 999;
  }
}

int FaceReveal(String command) { // Set A Face To Show In That Instant, Via The Particle Function
  ScarFace = command.toInt();
  if ((ScarFace < FacesNumber) && (ScarFace >= 0)) { // If the number entered is within the correct face limit, then a face will play on the SevSeg
    StopClock = 1;
    FaceCount = 0;
    return ScarFace;
  }
  else if (ScarFace == FacesNumber) { // If the Final Face is Entered, then the date will play on the SevSeg
    StopClock = 1;
    FaceCount = FaceRepeat;
    return ScarFace;
  }
  else { // If anything else is inputted an 999 is returned
    StopClock = 0;
    return 999;
  }
}

int HourFormat_24_0(String command) { // What Will your Hour Format be? 24 hours or 12 hours. 0 = 24 Hour, 1 = 12 Hour.
  if (command == "24" || command == "0") { // if 24 or 1 is entered then the SevSeg will display as a 24 hour clock
    HourType = 0;
    return 24;
  }
  else if (command == "12" || command == "1") { // if 12 or 0 is entered then the SevSeg will display as a 12 hour clock
    HourType = 1;
    return 12;
  }
  else { // If anything else is inputted an 999 is returned
    return 999;
  }
}

int Restart_0(String command) { // Restarts Particle Photon, Yes Or 0. Set Using The Particle Function
  command = command.toUpperCase();
  if (command == "YES" || command == "0") { // If yes or 0 are entered then the SevenSegClock will restart
    void(* resetFunc) (void) = 0;
    resetFunc();
  }
  else { // If anything else is inputted an 999 is returned
    return 999;
  }
}

int ShowPM_1(String command) { // Show PM dot on the right most Decimal Point. 0 Dosn't Show PM, 1 shows PM. Set Using The Particle Function
  command = command.toUpperCase();
  if (command == "NO" || command == "0" || command == "FALSE") { // If any of these are typed in, then the PM dot will not show when in 12 hour mode
    PMInd = 0;
    return 0;
  }
  else if (command == "YES" || command == "1" || command == "TRUE") { // If any of these are typed in, then the PM dot will show when in 12 hour mode
    PMInd = 1;
    return 1;
  }
  else { // If anything else is inputted an 999 is returned
    return 999;
  }
}

int TimeZone(String command) { // Set Time Zone, Via The Particle Function
  float ZoneSet = command.toFloat();
  if ((ZoneSet <= 14) && (ZoneSet >= -12)) { // If anything between -14 and 12 are typed in then that will be the timezone offset in respect to GMT.
    Time.zone(ZoneSet);
    return ZoneSet;
  }
  else { // If anything else is inputted an 999 is returned
    return 999;
  }
}

/*---------------------------*//* Clock Functions *//*---------------------------*/
void setup() { // Sets Up the initial Code.
  pinMode(Colon, OUTPUT); // Sets Up Colon as Output.
  pinMode(ColonGnd, OUTPUT); // Sets Up ColonGnd as Output.
  digitalWrite(Colon, HIGH); // Sets Up Colon as LOW.
  digitalWrite(ColonGnd, LOW); // Sets Up ColonGnd as Gnd.

  pinMode(Degree, OUTPUT); // Sets Up Colon as Output.
  pinMode(DegreeGnd, OUTPUT); // Sets Up ColonGnd as Output.
  digitalWrite(Degree, LOW); // Sets Up Colon as LOW.
  digitalWrite(DegreeGnd, LOW); // Sets Up ColonGnd as Gnd.

  Particle.syncTime(); /*Sync To Current Time To The Particle Cloud*/
  Time.zone(ZoneSet); /*Sets Time Zone*/

  byte hardwareConfig = COMMON_CATHODE; // Is SevSeg COMMON_CATHODE , or COMMON_ANODE.
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments); // Sets Up The SevSeg Display (hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments).
  sevseg.setBrightness(90); // Brightness Of Sevseg LED, 100 = 100%

  Particle.function("DST_Show_1", DST_Show_1); // Sets Particle Function For Daylights Savings
  Particle.function("FaceReveal", FaceReveal); // Shows Face A Face
  Particle.function("HourFormat_24_0", HourFormat_24_0); // Sets Particle Function For Hour Format
  Particle.function("Restart_0", Restart_0); // Restarts Particle Photon
  Particle.function("ShowPM_1", ShowPM_1); // Sets Particle Function For Showing PM Decimal Point
  Particle.function("TimeZone", TimeZone); // Sets Particle Function For Time Zone
  Particle.variable("1_Year", Year); // Shows The Current Year as a Particle Variable
  Particle.variable("2_Month", Month); // Shows The Current Month as a Particle Variable
  Particle.variable("3_Day", Day); // Shows The Current Day as a Particle Variable
  Particle.variable("4_Hour", Hour); // Shows The Current Hour as a Particle Variable
  Particle.variable("5_Min", Min); // Shows The Current Minute as a Particle Variable
  Particle.variable("6_Sec", Sec); // Shows The Current Second as a Particle Variable
}

void loop() { // Main Loop.
  TimeGet(); // Getting Time From Last Synced Time And Internal RTC
  if (StopClock == 0) { // Allows the clock to check if it needs to sync time or just displays the SevSeg
    SyncCheck(); // Syncs Time With Unix Cloud
    ScreenShow();  // What To Show On SevSeg Screen
  }
  else if (StopClock == 1) { // Stops the clock to show user desired face
    digitalWrite(Colon, LOW); // Disables the colon
    RandNumber2 = 1;  // Disables the chance of notshowing a face
    Faces(ScarFace); // Shows the Desired Face
    StopClock = 0; // Resumes normal Clock & face System
  }
}

void ClockPrint() { // Printing Clock Time
  if ((Sec % 2) != 0) { // If the second is divisable by 2 then don't show the colon
    digitalWrite(Colon, LOW);
  }
  else { // If the second is not divisable by 2 then show the colon
    digitalWrite(Colon, HIGH);
  }

  if ((HourType == 1) && (PMInd == 1)) { // If the time is set to 12 hour mode, and to allow the PM Dot To Show, This will run to allow the clock to look pleasing
    if (!Time.isAM()) {
      sevseg.setNumber(FinalTime, 0);
    }
    else {
      if (Hour >= 10) {
        sevseg.setNumber(FinalTime);

      }
      else if (Hour < 10) {
        String TempValue = " " + String(FinalTime);
        char* TTimePrint = const_cast<char*>(TempValue.c_str());;
        sevseg.setChars(TTimePrint);
      }
    }
  }

  else if ((HourType == 1) && (PMInd == 0)) { // If the time is set to 12 hour mode, and to not allow the PM Dot To Show, This will run to allow the clock to look pleasing
    if (Hour >= 10) {
      sevseg.setNumber(FinalTime);
    }
    else if (Hour < 10) {
      String TempValue = " " + String(FinalTime);
      char* TTimePrint = const_cast<char*>(TempValue.c_str());;
      sevseg.setChars(TTimePrint);
    }
  }

  else { // If the time is set to 24 hour mode this will run and allows the clock to look normal
    sevseg.setNumber(FinalTime);
  }
  sevseg.refreshDisplay();
}

void Faces(int FaceNumber) { // What the Faces are, 3 Types: 1) Emoticon, 2) Date, 3) Time. // Each Case Needs To Last 10000ms
  TotalTime = 0;
  if (RandNumber2 >= 1) { // Dosen't allow the bypassing of the faces
    if (FaceCount < FaceRepeat) { // Shows the a face if the FaceCount is less than 2
      if ((FaceNumber >= 0) && (FaceNumber <= (FacesNumber - 1))) { // Calculates the total time a face will run for, to possibly repeat the sequence
        for (int x = 0; x < (FaceSizeArray[FaceNumber]); x++) {
          TotalTime += FaceEmoteTimeArray[FaceNumber][x];
        }

        for (int i = 0; i < (FaceLength / TotalTime); i++) { // Displays the Face with the predetermined duration
          for (int z = 0; z < (FaceSizeArray[FaceNumber]); z++) {
            sevseg.setChars(FaceEmoteArray[FaceNumber][z]);
            Good_Delay(FaceEmoteTimeArray[FaceNumber][z]);
          }
        }
      }
      FaceCount++;
    }
    else if (FaceCount == FaceRepeat) { // Shows the Date when the clock has shown 2 faces
      for (int i = 0; i < (10); i++) {
        sevseg.setNumber(FinalDate, 2);
        Good_Delay(750);
        sevseg.setChars("    ");
        Good_Delay(250);
      }
      FaceCount = 0;
    }
    else { // Resets the FaceCount so that next time a face can be shown
      FaceCount = 0;
    }
  }
  else if (RandNumber2 == 0) { // Bypass's Showing a face and shows the time
    ClockPrint();
  }
}

void Good_Delay(unsigned long MiliSeconds) { // Efficent & Proper Delay Protocol
  int Case_Delay = millis(); // Sets Case_Delay to the current millies value
  while (millis() - Case_Delay <= MiliSeconds) { // compares Case_Delay time to the desire MiliSeconds delay time, and keeps the display working
    sevseg.refreshDisplay(); // Refreashes SevSeg display
  }
}

void ScreenShow() { // What To Show On SevSeg Screen
  if ((Sec >= 0) && (Sec < (MidSec - FaceTime)) || (Sec > (MidSec + FaceTime)) && (Sec <= 60)) { // As long as the time isnt between 25 and 35 seconds, then the clock will be displayed
    ClockPrint();
  }

  else if (Sec == (MidSec - FaceTime)) { // If the Clock is at Exactly 25 seconds it will deactivate the colon and choose a random face to play
    digitalWrite(Colon, LOW);
    RandNumber2 = random(0, 3);
    randNumber = random(0, FacesNumber);
  }

  else if ((Sec >= (MidSec - FaceTime)) && (Sec <= (MidSec + FaceTime))) { // While the clock is between between 25 and 35 seconds, a random face will play
    Faces(randNumber);
  }
  sevseg.refreshDisplay();
}

void SyncCheck() { // Syncs Time With Unix Cloud
  if (Min == 00 && Sec == 00 && SyncCheckCount == 0) { // At exactly every hour the clock will sync with unix time
    Particle.syncTime();
    SyncCheckCount = 1;
  }
  else if (Min != 00 && Sec != 00 && SyncCheckCount != 0) { // This is used so that after the instance of time sync the clock can continue to function
    SyncCheckCount = 0;
  }
}

void TimeGet() { // Getting Time From Last Synced Time And Internal RTC
  Year = Time.year(Time.now()); // Gets the Current Year
  Month = Time.month(Time.now()); // Gets the Current Month
  Day = Time.day(Time.now()); // Gets the Current Day

  if (HourType == 0) { // Gets the Current Hour as a 24 hour model
    if (Daylight == 1) { // Sets hour as daylighs savings
      if (!Time.isDST()) { // If currently on Daylights Savings adds hour
        Hour = Time.hour(Time.now()) + 1;
      }
      else { // If currently not on Daylights Savings dosen't add hour
        Hour = Time.hour(Time.now());
      }
    }
    else { // Ignors Daylights Savings
      Hour = Time.hour(Time.now());
    }
  }

  else if (HourType == 1) { // Gets the Current Hour as a 12 hour model
    if (Daylight == 1) { // Sets hour as daylighs savings
      if (!Time.isDST()) { // If currently on Daylights Savings adds hour
        Hour = Time.hourFormat12(Time.now()) + 1;
      }
      else { // If currently not on Daylights Savings dosen't add hour
        Hour = Time.hourFormat12(Time.now());
      }
    }
    else { // Ignors Daylights Savings
      Hour = Time.hourFormat12(Time.now());
    }
  }

  Min = Time.minute(Time.now()); // Gets the Current Minute
  Sec = Time.second(Time.now()); // Gets the Current Second
  FinalTime = (Hour * 100) + Min; // Sets the Current Time as a 4 digit number
  FinalDate = (Day * 100) + Month; // Sets the Current Date as a 4 digit number
}
