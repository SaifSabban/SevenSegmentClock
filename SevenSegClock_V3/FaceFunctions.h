/* SevenSegClock FaceFuntion Header

  This Header is used to set Faces that show randomly during
  the 25 seconds mark. To add a face, simply add the faces you want shown to
  the FaceEmoteArray. Then add the duration of the faces to FaceEmoteTimeArray,
  making sure that the sum is divisable by 10000ms. Then add a new FaceSize,
  and increment the numbers, and adding the FaceSize to the FaceSizeArray.

  See the included readme for additional information.
*/

char* FaceEmoteArray[][31] { // The Faces of the Emoticons, to add more just add a new {} and have the haves each face be 4 digits long
  {"i  1", "1  i", " i1 ", " 1i ", " i1 ", "1  i", "i  1"},
  {"*,@*", "-,@-", "*,@*", "*#@*", "-#@-", "*#@*"},
  {"0!%0", "-!%-", "0!%0", "0+%0", "0  0", "0+%0", "0  0", "0+%0", "0  0", "~  ~", "^  ^", "~  ~" , "^  ^", "~  ~", "^  ^", "~  ~", "*__*", "*!%*", "    ", "*!%*", "    ", "*!%*", "    ", "*!%*", "    ", "*!%*", "    ", "*!%*", "    ", "~!%~", "$  $"},
  {"   *", "  * ", " *  ", "*   ", "o   ", " o  ", "  o ", "   o"},
  {"0  0", "-  -", "0  0", "-  -", "0  0", "-xi-"},
  {"    ", "   x", "  xa", " xav", "xave", "ave ", "ve a", "e a ", " a g", "a go", " goo", "good", "ood ", "od d", "d da", " day", "day ", "ay  ", "y   ", "    "}
};

const int FaceEmoteTimeArray[][31] { // Timing for how long to show the Emoticons Face, the corresponde with FaceEmoteArray
  {143, 143, 143, 142, 143, 143, 143},
  {417, 167, 416, 416, 167, 417},
  {1000, 150, 850, 90, 90, 90, 90, 190, 300, 750, 150, 300, 150, 1000, 150, 650, 1000, 117, 50, 117, 50, 117, 50, 117, 49, 117, 49, 117, 50, 1000, 1000},
  {125, 125, 125, 125, 125, 125, 125, 125},
  {250, 250, 250, 400, 550, 300},
  {250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250}
};

const int FaceSize0 = sizeof(FaceEmoteTimeArray[0]) / sizeof(FaceEmoteTimeArray[0][0]); // Determins the size of each array
const int FaceSize1 = sizeof(FaceEmoteTimeArray[1]) / sizeof(FaceEmoteTimeArray[1][0]);
const int FaceSize2 = sizeof(FaceEmoteTimeArray[2]) / sizeof(FaceEmoteTimeArray[2][0]);
const int FaceSize3 = sizeof(FaceEmoteTimeArray[3]) / sizeof(FaceEmoteTimeArray[3][0]);
const int FaceSize4 = sizeof(FaceEmoteTimeArray[4]) / sizeof(FaceEmoteTimeArray[4][0]);
const int FaceSize5 = sizeof(FaceEmoteTimeArray[5]) / sizeof(FaceEmoteTimeArray[5][0]);

const int FaceSizeArray[] {// Size of eash singular array, to add face add a new FaceSize, and incement it by one, then add that constant to FaceSizeArray
  FaceSize0,
  FaceSize1,
  FaceSize2,
  FaceSize3,
  FaceSize4,
  FaceSize5
};
