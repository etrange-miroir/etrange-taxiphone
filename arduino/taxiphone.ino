// number of phones
const int NUMBER_OF_PHONES = 4;
// input pins for dial
const int DIAL_IN[NUMBER_OF_PHONES] = {A4,A1,9,12};
// input pin for end of dial
const int END_DIAL[NUMBER_OF_PHONES] = {A5,A2,8,11};
// input pin for phone handling
const int PHONE_HANDLE[NUMBER_OF_PHONES] = {A3,A0,10,13};
// the sum of clicks when released gently 
int sum[NUMBER_OF_PHONES] = {0,0,0,0};
// the state of each phone handle
boolean decroche[NUMBER_OF_PHONES] = {false,false,false,false};
// number of phones currently plugged
int numberOfPhones = 0;

// setup
void setup() {
  // logging purpose
  Serial.begin(9600);
  // setup the pins of the rotary button
  int i;
  for (i = 4; i < 8; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  // check how many phones are connected
  for (i = 4; i < 8; i++) {
    if (digitalRead(i) == LOW) {
      numberOfPhones = i-3;
      //Serial.print(numberOfPhones);
      //Serial.println(" telephones de connecte");
    }
  }
  // setup pins of the phones
  for (i = 0; i < numberOfPhones; i++) {
    pinMode(DIAL_IN[i], INPUT);
    pinMode(END_DIAL[i], INPUT);
    pinMode(PHONE_HANDLE[i], INPUT);
  }
}
 
// loop
void loop() {
  int i;
  for (i = 0; i < numberOfPhones; i++) {
    computePhone(i);
  }
}
 
// compute the number dialed (if any) for the given phone
void computePhone(int index) {
  // only compute dialed number when the handle is pulled
  if (digitalRead(PHONE_HANDLE[index]) == HIGH) {
    decroche[index] = true;
    boolean ended = false;
    // when end dial contact is activated
    if (digitalRead(END_DIAL[index]) == HIGH) {
      // count the number of opened contact occurences
      if (digitalRead(DIAL_IN[index]) == LOW) {
        sum[index]++;
        // empiric delay that just work
        delay(32);
      }
    }
    // dialing ended
    else {
      ended = true;
    }
    // end dial contact is opened
    if (sum[index] != 0 && ended) {
      // sends the result only when different from 0
      sendNote(index, (sum[index]/3)%10);
      // resets the sum
      sum[index] = 0;
    }
  }
  else if (decroche[index]){
    // send a note to stop the sound
    decroche[index] = false;
    //midi.sendNoteOn(1, 100 + index, 127);
    //SerialUSB.print("Telephone numero ");
    //SerialUSB.print(index+1);
    //SerialUSB.println(" raccroche");
    Serial.print(100 + index);
    Serial.print("#");
  }
}
 
void sendNote(int index, int dialedNumber) {
  // if the number 5 has been dialed on phone n°1, will send the note 5
  // if the number 8 has been dialed on phone n°2, will send the note 18
  // so the tens digit stands for the phone, the units digit for the dialed number
  int note = index*10 + dialedNumber;
  //midi.sendNoteOn(1, note, 127);
  //SerialUSB.println(note);
  Serial.print(note);
  Serial.print("#");
}
