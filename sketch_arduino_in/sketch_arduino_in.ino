#include <SoftwareSerial.h>
#define N_RIGS 6
#define N_BANDS 6

//=====[ Settings ]===========================================================================================
int PIN_SERIAL_RX = 2;
int PIN_SERIAL_TX = 3;

/*                                    10m 15m 20m 40m 80m 160m  */
int PIN_RIG_BAND[N_RIGS][N_BANDS] = {{10, 11, 12, 13, 14, 15},   // RIG1 
                                     {16, 17, 18, 19, 20, 21},   // RIG2
                                     {22, 23, 24, 25, 26, 27},   // RIG3
                                     {28, 29, 30, 31, 32, 33},   // RIG4
                                     {34, 35, 36, 37, 38, 39},   // RIG5
                                     {40, 41, 42, 43, 44, 45}};  // RIG6

int PIN_BUZZ = 4;

int BAUD_RATE = 38400;

// Define the serial pin object
SoftwareSerial board_serial(PIN_SERIAL_RX, PIN_SERIAL_TX);

// Define matrix of state. Rows are rigs, columns are bands.
int states[N_RIGS][N_BANDS];


//=====[ Aux functions ]===========================================================================================
void update_states_from_rigs(){
  /* This function reads the different pins and updates the states
   * matrix.
   */
  for (int i = 0; i < N_BANDS; ++i) { 
    for (int j = 0; j < N_RIGS; ++j) {
      if (digitalRead(PIN_RIG_BAND[i][j]) == HIGH){
        states[i][j] = 1;
      }
      else{
        states[i][j] = 0;
      }
    }
  }
}


bool check_states(){
  /* This function makes sure that there is only one rig per band. To do this
   * it computes the sum of the elements in each column and verifies 
   * that it is always equal or smaller than 1.
   * If this is the case it returns true, otherwise false.
   */
  bool is_fine = true;

  // Not more than one rig on the same band
  int sum = 0;
  for (int i = 0; i < N_BANDS; ++i) { 
    for (int j = 0; j < N_RIGS; ++j) {   
      // Add the element 
      sum += states[j][i];
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
  /* This function sends the states through the serial port for
   * the out arduino to read them and take action
   *Flattens the 2D array into a String with start and end markers
   */
  // Declare string with start marker
  String transmitted_state = String("<");

  // Attach the elements of the array to the string
  for (int i = 0; i < N_RIGS; i++) {
    for (int j = 0; j < N_BANDS; j++) {
      transmitted_state = String(transmitted_state + char(states[i][j]));
    }
  }

  // Attach the end marker
  transmitted_state = String(transmitted_state + ">");

  // Convert String to array of chars to properly send it via serial
  char transmitted_state_char[N_RIGS * N_BANDS + 2] = { 0 };
  transmitted_state.toCharArray(transmitted_state_char, N_RIGS * N_BANDS + 2);
  
  // Send array of chars through the serial
  if (board_serial.availableForWrite() > (N_RIGS + N_BANDS + 2)) {
    board_serial.write(transmitted_state_char);
  }
}


//=====[ Main functions ]===========================================================================================
void setup() {

  // Set the data rate for the SoftwareSerial port
  board_serial.begin(BAUD_RATE);
  board_serial.println("Setting up...");
  
  // Initialize states and setup input pins
  for (int i = 0; i < N_RIGS; i++) {
    for (int j = 0; j < N_BANDS; j++) {
      states[i][j] = 0;
      pinMode(PIN_RIG_BAND[i][j], INPUT);
    }
  }

  // Setup output pin
  pinMode(PIN_BUZZ, OUTPUT);
}


void loop() {
  // Check radio states
  update_states_from_rigs();
  
  // Check if there's only one rig per band
  bool ok = check_states();

  // If it is OK, send the states to the out arduino and make sure the 
  // buzzer is off
  if (ok == true){
    send_states_through_serial();
    digitalWrite(PIN_BUZZ, LOW);
  }
  // If it is not OK, make the buzzer sound (and do not pass any state update
  // out arduino
  else{
    digitalWrite(PIN_BUZZ, HIGH);
  }
}
