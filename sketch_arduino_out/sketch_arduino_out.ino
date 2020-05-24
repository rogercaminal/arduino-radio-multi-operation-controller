#include <SoftwareSerial.h>
#define N_RIGS 6
#define N_BANDS 6

boolean newData = false;
const byte numChars = N_RIGS * N_BANDS;
char receivedChars[numChars];

//=====[ Settings ]===========================================================================================
int PIN_SERIAL_RX = 2;
int PIN_SERIAL_TX = 3;

//                                    10m 15m 20m 40m 80m 160m  
int PIN_RIG_BAND[N_RIGS][N_BANDS] = {{10, 11, 12, 13, 14, 15},   // RIG1 
                                     {16, 17, 18, 19, 20, 21},   // RIG2
                                     {22, 23, 24, 25, 26, 27},   // RIG3
                                     {28, 29, 30, 31, 32, 33},   // RIG4
                                     {34, 35, 36, 37, 38, 39},   // RIG5
                                     {40, 41, 42, 43, 44, 45}};  // RIG6

int BAUD_RATE = 38400;

// Define the serial pin object
SoftwareSerial board_serial(PIN_SERIAL_RX, PIN_SERIAL_TX);

// Define matrix of state. Rows are rigs, columns are bands.
int states[N_RIGS][N_BANDS];


//=====[ Aux functions ]===========================================================================================
void update_output_from_states(){
  /* This function reads the different pins and updates the states
   * matrix.
   */
  for (int i = 0; i < N_BANDS; ++i) { 
    for (int j = 0; j < N_RIGS; ++j) {
      if (states[i][j] == 1){
        digitalWrite(PIN_RIG_BAND[i][j], HIGH);
      }
      else{
        digitalWrite(PIN_RIG_BAND[i][j], LOW);
      }
    }
  }
}


void get_states_from_serial(){
  /* This function receives the states from the serial port
   */

  // Read the buffer and store it into chars
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

      if (recvInProgress == true) {
        if (rc != endMarker) {
          receivedChars[ndx] = rc;
          ndx++;
          if (ndx >= numChars) {
            ndx = numChars - 1;
          }
        }
        else {
          receivedChars[ndx] = '\0'; // terminate the string
          recvInProgress = false;
          ndx = 0;
          newData = true;
        }
      }

      else if (rc == startMarker) {
        recvInProgress = true;
      }
    }

    // Transform the array of chars to the states matrix
  for (int i = 0; i < N_RIGS; i++) {
    for (int j = 0; j < N_BANDS; j++) {
      states[i][j] = atoi(receivedChars[N_RIGS*i + j]);
    }
  }

}


//=====[ Main functions ]===========================================================================================
// Setup function
void setup() {

  // Set the data rate for the SoftwareSerial port
  board_serial.begin(BAUD_RATE);
  board_serial.println("Setting up...");
  
  // Initialize states and setup input pins
  for (int i = 0; i < N_RIGS; i++) {
    for (int j = 0; j < N_BANDS; j++) {
      states[i][j] = 0;
      pinMode(PIN_RIG_BAND[i][j], OUTPUT);
    }
  }
}

// Loop function
void loop() {
  // Read the serial
  get_states_from_serial();
  
  // Update the output states
  update_output_from_states();
}
