/*************************************************************
 * PROGRAM NAME: Instant LED Patterns
 * PROGRAM DESCRIPTION: Shows 1 of 5 patterns of LED lights
 *   based in decrement (left button) and increment 
 *   right button). The values wrap around, so decrementing
 *   from the first pattern will initiate the fifth pattern
 *   and incrementing from fifth pattern will initiate first
 *   pattern. If both buttons are pressed, the LEDs are reset
 *   after a sequence of flashes that end after the pressing
 *   stops.
 * PROGRAMMER: Mohammad Mahdi Mahboob
 * DATE: June 11, 2021
 *************************************************************/

#define PBR 2 // Right PB (increment)
#define PBL 3 // Left PB (decrement)
# define MOD 5 // modulus value for number of patterns
#define s Serial // was used during debugging
#define dw digitalWrite // shortcut for digitalWrite
#define dr digitalRead // shortcut for digitalRead
#define pm pinMode // shortcut for pinMode

// Array of LED pins from leftmost LED to rightmost LED
const int LEDS[] = {10, 11, 12, 13, 9,
                    8, 7, 6, 5, 4
                   };


// Counter to track the current pattern
int cnt;

// Booleans to keep track of left and right PB states
// and flag if a reset is necessary.
bool prLeft, prRight, reset;

/**
 * Button press checking
 * -------------------------------------------------------
 * These blocks check for pushbutton presses to determine
 * whether or not to decrement, increment or reset the
 * pattern. 
 * -------------------------------------------------------
 */

/**
 * Boolean return which checks and indicates if a
 * pushbutton was pressed and if both were pressed,
 * sets reset to true so that next loop() iteration
 * will trigger the reset. Calls checkButton() for
 * both PBs, sending the count (ref) and required 
 * values of each PB, including the current state 
 * (ref), the pin # of the PB, and its increment
 * value (right = +1; left = -1).
 */
bool buttonChecker() {
  // Check right button for press
  checkButton(cnt, prRight, PBR, 1);
  // Check left button for press
  checkButton(cnt, prLeft, PBL, -1);
  if (prLeft && prRight) {
    reset = 1;
    return 1;
  }
  return prLeft || prRight;
}

/**
 * Takes in the pattern count and current button
 * state as ref variables to adjust, as well as the
 * current button and a direction indicating either
 * an increment or a decrement. Checks if a the 
 * given button was pressed and if so, adjusts 
 * the pattern count accordingly. Uses modulus
 * to wrap around easier.
 */
void checkButton(int &c, bool &pr, int PB, int dir) {
  if (!pr && dr(PB)) {
    pr = 1;
    c = (c + dir) % MOD;
    if (c < 0) c += MOD;
  } else if (!dr(PB)) {
    pr = 0;
  }
}

/**
 * Pattern sequences and selection
 * -------------------------------------------------------
 * These blocks handle choosing and playing the pattern
 * corresponding to the current pattern count, and check
 * for button presses frequently to allow for smooth
 * transitioning to the next pattern or the reset.
 * -------------------------------------------------------
 */

/**
 * Switch selection of the pattern to play based on
 * the pattern count.
 */
void patternSelect() {
  switch (cnt) {
    case 0:
      patternUno();
      break;
    case 1:
      patternDos();
      break;
    case 2:
      patternTres();
      break;
    case 3:
      patternQuatro();
      break;
    default:
      patternFiveInSpanish();
      break;
  }
}

/**
 * First pattern is just lights turning on
 * LEDs from left to right and then turning
 * off from left to right periodically.
 */
void patternUno() {
  // Turn on all LEDs one-by-one from
  // left to right
  for (int i = 0; i < 10; i++) {
    dw(LEDS[i], 1);
    // Always check for a button press
    // to make transitions smooth
    // If there is a button press, turn
    // off all lights and leave method
    if (buttonChecker()) {
      configLights(0);
      return;
    }
    // Delay while checking for button press,
    // leave method in case of a press
    if (smoothDelay(75)) return;
  }
  if (buttonChecker()) {
    configLights(0);
    return;
  }
  // Turn off all LEDs one-by-one from
  // left to right
  for (int i = 0; i < 10; i++) {
    dw(LEDS[i], 0);
    if (buttonChecker()) {
      configLights(0);
      return;
    }
    if (smoothDelay(75)) return;
  }
}

/**
 * Second pattern turns on corresponding
 * colours on each end in pairs and
 * converges to the middle, and then
 * turns off each colour pair while
 * converging to the middle.
 */
void patternDos() {
  // The same process happens twice, the
  // difference is that the first time, it turns
  // on and the second time it turns off.
  // j will be 1 then 2, and sending j&1
  // will give 1 first and 0 the second time,
  // which gives us 1 for on and 0 for off.
  for (int j = 1; j < 3; j++) {
    // From the outermost LEDs, toggle
    // LEDs with the same colour.
    // They are paired as {i, 9 - i}
    // As always check for presses between
    // toggles and have some delay.
    for (int i = 0; i < 5; i++) {
      dw(LEDS[i], j&1);
      dw(LEDS[9 - i], j&1);
      if (buttonChecker()) {
        configLights(0);
        return;
      }
      if (smoothDelay(200)) return;
    }
  }
}


/**
 * Third pattern blinks corresponding
 * colours one by one while converging to
 * the centre. Left colour blinks first.
 */
void patternTres() {
  // side just determines whether or not the
  // left or right LED of th current colour
  // will blink.
  int side = 0;
  // 5 colours so 5 iterations, always check for
  // button press
  for (int i = 0; i < 5; i++) {
    if (buttonChecker()) {
      configLights(0);
      return;
    }
    // Blink one of the 2 LEDs of the current
    // colour. When j is 0, it will blink the
    // left one, and when it is 1, it will blink
    // the right colour by assigning the required
    // index to side. Have some delays and always
    // check for a button press.
    for (int j = 0; j < 2; j++) {
      side = j ? 9 - i : i;
      if (buttonChecker()) {
        configLights(0);
        return;
      }
      dw(LEDS[side], 1);
      if (buttonChecker()) {
        configLights(0);
        return;
      }
    if (smoothDelay(250)) return;
      if (buttonChecker()) {
        configLights(0);
        return;
      }
      dw(LEDS[side], 0);
    }
  }
}

/**
 * Fourth pattern creates a sliding
 * bar of 4 LEDS that bounces from
 * end to end repeatedly. The first
 * four colours are turned on, then
 * the sliding repeats in a loop.
 */
void patternQuatro() {
  // flag to determine if looping is safe
  bool leave = 0;
  // Keep track of leftmost and rightmost
  // on LEDs
  int lft = 0, rit = 3;
  // Turn on first 4 LEDs
  // Again always check for button press
  configLights(lft, rit + 1, 1);
  if (buttonChecker()) {
    configLights(0);
    leave = 1; 
  }
  // Delay and check
  if (smoothDelay(150)) return;
  // While loop to move the window left to right
  // When moving left to right, turn off the leftmost
  // LED and turn on the pin right of the rightmost
  // LED that is on. Prefix and postfix increments are
  // used to make this easier to do and less lines.
  // As always check for button presses, and have
  // some delay. When moving right to left, the same
  // principle applies, instead this time turn off
  // rightmost LED and turn on the LED beside leftmost
  // on LED. Prefix and postfix increments were used
  // to make this easier.
  while (!leave) {
    if (buttonChecker()) {
      configLights(0);
      return;
    }
    // Left to right
    for (int i = 0; i < 6; i++) {
      dw(LEDS[lft++], 0);
      dw(LEDS[++rit], 1);
      if (buttonChecker()) {
        configLights(0);
        return;
      }
    if (smoothDelay(150)) return;
    }
    
    // Right to left
    for (int i = 0; i < 6; i++) {
      dw(LEDS[rit--], 0);
      dw(LEDS[--lft], 1);
      if (buttonChecker()) {
        configLights(0);
        return;
      }
    if (smoothDelay(150)) return;
    }
    if (buttonChecker()) {
      configLights(0);
      leave = 1;
    }
  }
}

/**
 * Fifth pattern blinks all the LEDs
 * once then blinks the left half twice,
 * followed by the right half blinking
 * twice as well. The sequence then
 * repeats.
 */
void patternFiveInSpanish() {
  // Used to determine and track which
  // half of the LED strip to blink.
  int half = 0;
  // Turn all lights on for a bit
   configLights(1);
  if (smoothDelay(500)) return;
  // Turn off all lights for a bit
  configLights(0);
  if (smoothDelay(200)) return;
  // Blink each half twice (2 x 2 halves = 4)
  // The first two will be left half, second two
  // will be right half, so set half to the leftmost
  // LED (0 for the first 2, 5 for the next 2).
  // Blink each half and as always check for button presses
  // and allow for a slight delay.
  for (int i = 0; i < 4; i++) {
    half = i < 2 ? 0 : 5;
    if (buttonChecker()) {
      configLights(0);
      return;
    }
    // Similar to logic in second pattern, first turn on
    // the half, then off. Since j is 1 or 2, 1 & 1 gives 1
    // output of 1 for on, and 2 & 1 gives 0 for off.
    // As always check for button presses with some delay.
    for (int j = 1; j < 3; j++) {
      if (buttonChecker()) {
        configLights(0);
        return;
      }
      configLights(half, half + 5, j&1);
    if (smoothDelay(200)) return;
    }
  }
}


/**
 * The reset causes all LEDS to flash
 * simultaneously and repeatedly until
 * the buttons are no longer pressed,
 * then after 4 more flashes to indicate
 * a reset has occured, resets all values
 * and counts to 0, causing the first pattern
 * to then occur in the next iteration of
 * loop().
 */
void resetAll() {
  // Turn off all lights
  configLights(0);
  // Keep track of toggle state to
  // allow for the lights to all blink
  bool out = 1;
  // Turn on and off 4 times each, so 8 time total
  for (int t = 0; t < 8; t++) {
    // Turn LED on or off
    configLights(out);
    // toggle the state of output
    out = !out;
    delay(300);
  }
  // Reset all values
  cnt = prLeft = prRight = reset = 0;
}

/**
 * Useful methods
 * -------------------------------------------------------
 * These blocks contain code that allows other parts of
 * the program to run smoothly and avoid repetition.
 * -------------------------------------------------------
 */

/**
 * Sets all lights to the given value.
 */
void configLights(int state) {
  for (int i = 0; i < 10; i++) {
    dw(LEDS[i], state);
  }
}

/**
 * configLights() overload that sets all lights in
 * the range [l, r) to the given value.
 */
void configLights(const int &l, const int &r, int state) {
  for (int i = l; i < r; i++) {
    dw(LEDS[i], state);
  }
}

/**
 * Modified delay code that takes in a
 * wait value in ms and checks in a loop
 * each cycle for a button press. This
 * allows for smoother transitions between
 * patterns.
 */
bool smoothDelay(const int t) {
  for (int i = 0; i < t; i++) {
    for (int i = 0; i < 2; i++) {
      if (buttonChecker()) return 1;
    }
  }
  return 0;
}

/**
 * Setup and loop
 * -------------------------------------------------------
 * I mean the title is pretty self-explanatory...
 * -------------------------------------------------------
 */

/**
 * Code that sets the pins for PBs to be input
 * and pins for LEDs to be outputs. Sets all
 * global variables to 0.
 */
void setup()
{
  pm(PBL, INPUT);
  pm(PBR, INPUT);
  cnt = prLeft = prRight = reset = 0;
  for (int i = 0; i < 10; i++) {
    pm(LEDS[i], OUTPUT);
  }
}

/**
 * Loop checks if a reset has been triggered,
 * and if not runs buttonChecker and then
 * patternSelect() to determine the pattern
 * to display. When no buttons are pressed,
 * this allows for patterns to repeat (except
 * the fourth pattern which requires an initial
 * configuration before repetion, which would
 * be inefficient to run each time).
 */
void loop()
{
  if (reset) resetAll();
  buttonChecker();
  patternSelect();
}
