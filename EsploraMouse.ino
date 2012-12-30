#include <Esplora.h>

boolean active = false;// whether or not to control the mouse
boolean prevStates[4];// previous switch state

const byte buttons[] = { SWITCH_UP, SWITCH_RIGHT, SWITCH_DOWN, SWITCH_LEFT };
const char mouseActions[] = { ' ', MOUSE_RIGHT, MOUSE_MIDDLE, MOUSE_LEFT };

void setup() {
   //The switch that will initiate the Mouse press
  pinMode(2,INPUT);
  //The switch that will terminate the Mouse press
  pinMode(3,INPUT);
  Mouse.begin();
}

void loop() {
  boolean newState = Esplora.readButton(buttons[0]);
  if (prevStates[0] != newState) {
    if (newState == PRESSED) {
      active = !active;
      if (active == true)
        Esplora.writeRGB(0,255,0);
      else
        Esplora.writeRGB(0,0,0);
    }
    prevStates[0] = newState;
  }


  // if the mouse control state is active, read the joystick and move the mouse:
  if (active == true) {
    int threshold = map(Esplora.readSlider(),0,1024,10,70);
    int x = Esplora.readJoystickX();
    int y = Esplora.readJoystickY();
    Mouse.move(-(x/threshold), (y/threshold), 0);
  }  

  for (byte z = 1; z <= 3; z++) {
    boolean newState = Esplora.readButton(buttons[z]);
    if (prevStates[z] != newState) {
      if (newState == PRESSED)
        Mouse.press(mouseActions[z]);
      else if (newState == RELEASED)
        Mouse.release(mouseActions[z]);
    }
    prevStates[z] = newState;
  }
  delay(50);
}

