#include <SoftwareSerial.h>

//=====[ Settings ]===========================================================================================
int PIN_SERIAL_RX = 2;
int PIN_SERIAL_TX = 3;

int PIN_R1_10 = 10
int PIN_R1_15 = 11
int PIN_R1_20 = 12
int PIN_R1_40 = 13
int PIN_R1_80 = 14
int PIN_R1_160 = 15

int PIN_R2_10 = 16
int PIN_R2_15 = 17
int PIN_R2_20 = 18
int PIN_R2_40 = 19
int PIN_R2_80 = 20
int PIN_R2_160 = 21

int PIN_R3_10 = 22
int PIN_R3_15 = 23
int PIN_R3_20 = 24
int PIN_R3_40 = 25
int PIN_R3_80 = 26
int PIN_R3_160 = 27

int PIN_R4_10 = 28
int PIN_R4_15 = 29
int PIN_R4_20 = 30
int PIN_R4_40 = 31
int PIN_R4_80 = 32
int PIN_R4_160 = 33

int PIN_R5_10 = 34
int PIN_R5_15 = 35
int PIN_R5_20 = 36
int PIN_R5_40 = 37
int PIN_R5_80 = 38
int PIN_R5_160 = 39

int PIN_R6_10 = 40
int PIN_R6_15 = 41
int PIN_R6_20 = 42
int PIN_R6_40 = 43
int PIN_R6_80 = 44
int PIN_R6_160 = 45

int PIN_BUZZ = 4

int N_RIGS = 6
int N_BANDS = 6

int BAUD_RATE = 38400

// Define the serial pin object
SoftwareSerial board_serial(PIN_SERIAL_RX, PIN_SERIAL_TX);

// Define matrix of state. Rows are rigs, columns are bands.
int states[N_RIGS][N_BANDS];


//=====[ Aux functions ]===========================================================================================
void update_states_from_rigs(){
  // This function reads the different pins and updates the states
  // matrix.
  int a = 1;
}


bool check_states(){
  // This function makes sure that there is only one rig per band. To do this
  // it computes the sum of the elements in each column and row and verifies 
  // that it is always equal or smaller than 1.
  // If this is the case it returns true, otherwise false.
  int sum = 0;
  bool is_fine = true;
  
  // finding the row sum 
  sum = 0;
  for (i = 0; i < N_RIGS; ++i) { 
    for (j = 0; j < N_BANDS; ++j) {   
      // Add the element 
      sum = sum + states[i][j];
    } 
    // Check if it is larger than 1
    if (sum > 1) {
      is_fine = false;  
    }
    // Reset the sum 
    sum = 0; 
  }

  // finding the column sum 
  sum = 0;
  for (i = 0; i < N_BANDS; ++i) { 
    for (j = 0; j < N_RIGS; ++j) {   
      // Add the element 
      sum = sum + states[j][i];
    } 
    // Check if it is larger than 1
    if (sum > 1) {
      is_fine = false;  
    }
    // Reset the sum 
    sum = 0; 
  }
  
  return is_fine;  
}


void send_states_through_serial(){
  // This function sends the states through the serial port for
  // the out arduino to read them and take action
  int a = 1;
}


//=====[ Main functions ]===========================================================================================
// Setup function
void setup() {

  // Set the data rate for the SoftwareSerial port
  board_serial.begin(BAUD_RATE);
  board_serial.println("Setting up...");
  
  // Initialize states
  for (int i =0; i < N_RIGS; i++) {
    for (int j =0; j < N_BANDS; j++) {
      states[i][j] = 0;
    }
  }

  // Setup pins
  pinMode(PIN_R1_10, INPUT);
  pinMode(PIN_R1_15, INPUT);
  pinMode(PIN_R1_20, INPUT);
  pinMode(PIN_R1_40, INPUT);
  pinMode(PIN_R1_80, INPUT);
  pinMode(PIN_R1_160, INPUT);
  
  pinMode(PIN_R2_10, INPUT);
  pinMode(PIN_R2_15, INPUT);
  pinMode(PIN_R2_20, INPUT);
  pinMode(PIN_R2_40, INPUT);
  pinMode(PIN_R2_80, INPUT);
  pinMode(PIN_R2_160, INPUT);
  
  pinMode(PIN_R3_10, INPUT);
  pinMode(PIN_R3_15, INPUT);
  pinMode(PIN_R3_20, INPUT);
  pinMode(PIN_R3_40, INPUT);
  pinMode(PIN_R3_80, INPUT);
  pinMode(PIN_R3_160, INPUT);

  pinMode(PIN_R4_10, INPUT);
  pinMode(PIN_R4_15, INPUT);
  pinMode(PIN_R4_20, INPUT);
  pinMode(PIN_R4_40, INPUT);
  pinMode(PIN_R4_80, INPUT);
  pinMode(PIN_R4_160, INPUT);

  pinMode(PIN_R5_10, INPUT);
  pinMode(PIN_R5_15, INPUT);
  pinMode(PIN_R5_20, INPUT);
  pinMode(PIN_R5_40, INPUT);
  pinMode(PIN_R5_80, INPUT);
  pinMode(PIN_R5_160, INPUT);

  pinMode(PIN_R6_10, INPUT);
  pinMode(PIN_R6_15, INPUT);
  pinMode(PIN_R6_20, INPUT);
  pinMode(PIN_R6_40, INPUT);
  pinMode(PIN_R6_80, INPUT);
  pinMode(PIN_R6_160, INPUT);
}

// Loop function
void loop() {
  // 1. Check radio states
  // 2. Check if there's only one rig per band
  // 3. If not, make the buzzer sound
  // 4. If so, send the state to the output board

}
