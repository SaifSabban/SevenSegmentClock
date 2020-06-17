/* SevenSegClock Variable Header

  This Header is used to set the differenct vaiables that are
  needed to allow the SevenSegClock to work.

  See the included readme for information.
*/

int Colon = D4; // Colon Pin
int ColonGnd = A3; // Colon Gnd Pin

int Degree = D7; // Degree Pin
int DegreeGnd = D6; // Degree Gnd Pin

byte digitPins[] = {A0, A1, A5, WKP}; // Coms Pin For Each Digit // digitPins[] = {1, 2, 3, 4};
byte segmentPins[] = {D2, D0, D3, A2, A4, D5, D1, DAC}; // Pins For Each Segment // segmentPins[] = {A,  B,  C,  D,  E,  F,  G,  DP};
byte numDigits = 4; /*How Many SevSeg Digits Exist?*/
bool disableDecPoint = false; // Disable Decimal Points? False = NO, True = Yes.
bool resistorsOnSegments = false; // Are There Resitor Built into SevSeg? False = NO, True = Yes.
bool updateWithDelays = false; // Delay The Time Between Screen Refreash? False = NO, True = Yes.

int Sec; // Seconds Variable
int Min; // Minutes Variable
int Hour; // Hour Variable
int Day; // Day Variable
int Month; // Month Variable
int Year; // Year Variable
int FinalDate; // Sets Up Date To Show On SevSeg
int FinalTime; // Sets Up Time To Show On SevSeg

int Daylight = 1; // Used To Choose Daylights Savings or Not. 0 = Don't Apply, 1 = Apply.
int HourType = 0; // What Will your Hour Format be? 24 hours or 12 hours. 0 = 24 Hour, 1 = 24 Hour.
int PMInd = 1; // How PM Dot On The Right Most Decimal Point. PMInd = 0 Dosn't Show PM, PMInd = 1 shows PM.
int ZoneSet; // Used To Set Time Zone. 0 = GMT.

int SyncCheckCount; // Used To Make send Sync Time Command Once.

int FaceCount; // Counts How Many Times Faces Have Occured Before Showing Date.
int FaceRepeat = 2; // Max Number of FaceCount before showing date.
int FacesNumber = sizeof(FaceSizeArray) / sizeof(FaceSizeArray[0]); // How Many Faces there are including Date.
int FaceTime = 5; // Half Length Of Time To Show Face in Seconds.
int FaceLength = (FaceTime * 2000); // Length Of Time To Show Face in ms.
int MidSec = 29; // What the Middle of a minute is.
int randNumber; // Random Number Generator To Choose A Face.
int RandNumber2; // Random Number Generator To Choose If Will Show Face, or Keep Showing Time.
int ScarFace; // Used For Choosing A Face To Show Temperarily
int StopClock; // Used To Stop Clock To Show Face
int TotalTime; // Used To Check How Long An Array Of Faces Is
