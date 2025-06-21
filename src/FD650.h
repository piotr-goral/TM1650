/** ============================================
 * 7 segment display driver for module based on FD650 chip
 * Copyright (c) 2015 Anatoli Arkhipenko
 * 
 * 
 * Przykład wykonany na podstawie oryginalnego projektu w/w autora.
 *	Zmiany:
 *		- Zmieniona została tablica danych kształtów wyświetlanych znaków. 
 *		- Zmieniona została kolejność rozmieszczenia znaków na wyświetlaczu.  
 *		- 
 *	Pozostałe elementy pozostały w oryginalnej formie. 
 *	Elementy zmienione dotyczyły niedopasowania programu do płytki na której wykonano testy.
 * ===============================================*/

#include <Arduino.h>
#include <Wire.h>


#ifndef _FD650_H_
#define _FD650_H_

//#define FD650_USE_PROGMEM

#ifdef FD650_USE_PROGMEM
    #if (defined(__AVR__))
      #include <avr\pgmspace.h>
    #else
      #include <pgmspace.h>
    #endif
#endif

#define FD650_DISPLAY_BASE 0x34 // Address of the left-most digit 
#define FD650_DCTRL_BASE   0x24 // Address of the control register of the left-most digit
#define FD650_NUM_DIGITS   16 // max number of digits
#define FD650_MAX_STRING   128 // number of digits

#define FD650_BIT_ONOFF	0b00000001
#define FD650_MSK_ONOFF	0b11111110
#define FD650_BIT_DOT		0b00000001
#define FD650_MSK_DOT		0b11110111
#define FD650_BRIGHT_SHIFT	4
#define FD650_MSK_BRIGHT	0b10001111
#define FD650_MIN_BRIGHT	0
#define FD650_MAX_BRIGHT	7

#ifndef FD650_USE_PROGMEM
const byte FD650_CDigits[128] {
#else
const PROGMEM byte FD650_CDigits[128] {
#endif
//tm1650
//0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x00
//  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x10
//  0x00, 0x82, 0x21, 0x00, 0x00, 0x00, 0x00, 0x02, 0x39, 0x0F, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00, // 0x20
//  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f, 0x00, 0x00, 0x00, 0x48, 0x00, 0x53, // 0x30
//  0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x6F, 0x76, 0x06, 0x1E, 0x00, 0x38, 0x00, 0x54, 0x3F, // 0x40
//  0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x00, 0x0F, 0x00, 0x08, // 0x50 
//  0x63, 0x5F, 0x7C, 0x58, 0x5E, 0x7B, 0x71, 0x6F, 0x74, 0x02, 0x1E, 0x00, 0x06, 0x00, 0x54, 0x5C, // 0x60
//  0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x30, 0x0F, 0x00, 0x00  // 0x70
//FD650
//0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x00
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0x10
  0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x20, 0x87, 0x63, 0x00, 0x00, 0x00, 0x10, 0x08, 0x00, // 0x20
  0xE7, 0x60, 0xB3, 0x73, 0x74, 0x57, 0xD7, 0x62, 0xF7, 0x76, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, // 0x30
  0x00, 0xF6, 0xD5, 0x87, 0xF1, 0x97, 0x96, 0xC7, 0xF4, 0x60, 0xE1, 0x00, 0x85, 0x00, 0xE6, 0xE7, // 0x40
  0xB6, 0x76, 0x90, 0x57, 0x95, 0xE5, 0x00, 0x00, 0x00, 0x75, 0x00, 0x87, 0x00, 0x63, 0x00, 0x01, // 0x50 
  0x36, 0xF6, 0xD5, 0x91, 0xF1, 0x97, 0x96, 0xC7, 0xD4, 0x40, 0xE1, 0x00, 0x85, 0x00, 0xD0, 0xD1, // 0x60
  0xB6, 0x76, 0x90, 0x57, 0x95, 0xC1, 0x00, 0x00, 0x00, 0x75, 0x00, 0x87, 0x03, 0x63, 0x00, 0x00  // 0x70
};

class FD650 {
    public:
        FD650(unsigned int aNumDigits = 4);
        
	void	init();
	void	clear();
	void	displayOn();
	void	displayOff();
	void	displayState(bool aState);
	void	displayString(char *aString);
	int 	displayRunning(char *aString);
	int 	displayRunningShift();
	void	setBrightness(unsigned int aValue = FD650_MAX_BRIGHT);
	void	setBrightnessGradually(unsigned int aValue = FD650_MAX_BRIGHT);
	inline unsigned int getBrightness() { return iBrightness; };

	void	setPosition(unsigned int aPos, byte aValue);
	void	setDot(unsigned int aPos, bool aState);
	byte	getPosition(unsigned int aPos) { return iBuffer[aPos]; };
	inline unsigned int	getNumPositions() { return iNumDigits; };

    private:
	char 	*iPosition;
	bool	iActive;
	unsigned int	iNumDigits;
	unsigned int	iBrightness;
    char	iString[FD650_MAX_STRING+1];
    byte 	iBuffer[FD650_NUM_DIGITS+1];
    byte 	iCtrl[FD650_NUM_DIGITS];
};

//  ----  Implementation ----

/** Constructor, uses default values for the parameters
 * so could be called with no parameters.
 * aNumDigits - number of display digits (default = 4)
 */
FD650::FD650(unsigned int aNumDigits) {
	iNumDigits =  (aNumDigits > FD650_NUM_DIGITS) ? FD650_NUM_DIGITS : aNumDigits;
}

/** Initialization
 * initializes the driver. Turns display on, but clears all digits.
 */
void FD650::init() {
	iPosition = NULL;
	for (int i=0; i<iNumDigits; i++) {
		iBuffer[i] = 0;
		iCtrl[i] = 0;
	}
    Wire.beginTransmission(FD650_DISPLAY_BASE);
    iActive = (Wire.endTransmission() == 0);
	clear();
	displayOn();
}

/** Set brightness of all digits equally
 * aValue - brightness value with 1 being the lowest, and 7 being the brightest
 */
void FD650::setBrightness(unsigned int aValue) {
	if (!iActive) return;

	iBrightness = (aValue > FD650_MAX_BRIGHT) ? FD650_MAX_BRIGHT : aValue;

	for (int i=0; i<iNumDigits; i++) {
		Wire.beginTransmission(FD650_DCTRL_BASE+i);
		iCtrl[i] = (iCtrl[i] & FD650_MSK_BRIGHT) | ( iBrightness << FD650_BRIGHT_SHIFT );
		Wire.write((byte) iCtrl[i]);
		Wire.endTransmission();
	}
}

/** Set brightness of all digits equally
 * aValue - brightness value with 1 being the lowest, and 7 being the brightest
 */
void FD650::setBrightnessGradually(unsigned int aValue) {
	if (!iActive || aValue == iBrightness) return;

	if (aValue > FD650_MAX_BRIGHT) aValue = FD650_MAX_BRIGHT;
	int step = (aValue < iBrightness) ? -1 : 1;
	unsigned int i = iBrightness;
	do {
		setBrightness(i);
		delay(50);
		i += step;
	} while (i!=aValue);
}

/** Turns display on or off according to aState
 */
void FD650::displayState (bool aState)
{
  if (aState) displayOn ();
  else displayOff();
}

/** Turns the display on
 */
void FD650::displayOn ()
// turn all digits on
{
  if (!iActive) return;
  for (int i=0; i<iNumDigits; i++) {
    Wire.beginTransmission(FD650_DCTRL_BASE+i);
	iCtrl[i] = (iCtrl[i] & FD650_MSK_ONOFF) | FD650_BIT_DOT;
    Wire.write((byte) iCtrl[i]);
    Wire.endTransmission();
  }
}
/** Turns the display off
 */
void FD650::displayOff ()
// turn all digits off
{
  if (!iActive) return;
  for (int i=0; i<iNumDigits; i++) {
    Wire.beginTransmission(FD650_DCTRL_BASE+i);
	iCtrl[i] = (iCtrl[i] & FD650_MSK_ONOFF);
    Wire.write((byte) iCtrl[i]);
    Wire.endTransmission();
  }
}


/** Directly write to the digit register of the digital position
 * aPos = position to set the digit register for
 * aValue = value to write to the position
 *
 * Internal position buffer is updated as well
 */
void FD650::setPosition(unsigned int aPos, byte aValue) {
	if (!iActive) return;
	if (aPos < iNumDigits) {
	    Wire.beginTransmission(FD650_DISPLAY_BASE + (int) aPos);
	    iBuffer[aPos] = aValue;
	    Wire.write(aValue);
	    Wire.endTransmission();
	}
}

/** Directly set/clear a 'dot' next to a specific position
 * aPos = position to set/clear the dot for
 * aState = display the dot if true, clear if false
 *
 * Internal buffer is updated as well
 */
void	FD650::setDot(unsigned int aPos, bool aState) {
	iBuffer[aPos] = iBuffer[aPos] & 0xF7 |(aState ? 0b00001000 : 0);
	setPosition(aPos, iBuffer[aPos]);
}

/** Clear all digits. Keep the display on.
 */
void FD650::clear()
// clears all digits
{
  if (!iActive) return;
  for (int i=0; i<iNumDigits; i++) {
    Wire.beginTransmission(FD650_DISPLAY_BASE+i);
 	iBuffer[i] = 0;
	Wire.write((byte) 0);
    Wire.endTransmission();
  }
}

/** Display string on the display 
 * aString = character array to be displayed
 *
 * Internal buffer is updated as well
 * Only first N positions of the string are displayed if
 *  the string is longer than the number of digits
 */
void FD650::displayString(char *aString)
{
	if (!iActive) return;
	int i=0;
	  byte a = ((byte) aString[i]) & 0b01111111;
	  byte dot = ((byte) aString[i]) & 0b00001000;
#ifndef FD650_USE_PROGMEM	  
	  iBuffer[i] = FD650_CDigits[a];
#else
	  iBuffer[i] = pgm_read_byte_near(FD650_CDigits + a);
#endif
	  if (a) {
	    Wire.beginTransmission(FD650_DISPLAY_BASE+2);
	    Wire.write(iBuffer[i] | dot);
	    Wire.endTransmission();
	  }

	i=1;
	  a = ((byte) aString[i]) & 0b01111111;
	  dot = ((byte) aString[i]) & 0b00001000;
#ifndef FD650_USE_PROGMEM	  
	  iBuffer[i] = FD650_CDigits[a];
#else
	  iBuffer[i] = pgm_read_byte_near(FD650_CDigits + a);
#endif
	  if (a) {
	    Wire.beginTransmission(FD650_DISPLAY_BASE+3);
	    Wire.write(iBuffer[i] | dot);
	    Wire.endTransmission();
	  }

	i=2;
	  a = ((byte) aString[i]) & 0b01111111;
	  dot = ((byte) aString[i]) & 0b00001000;
#ifndef FD650_USE_PROGMEM	  
	  iBuffer[i] = FD650_CDigits[a];
#else
	  iBuffer[i] = pgm_read_byte_near(FD650_CDigits + a);
#endif
	  if (a) {
	    Wire.beginTransmission(FD650_DISPLAY_BASE+1);
	    Wire.write(iBuffer[i] | dot);
	    Wire.endTransmission();
	  }

	i=3;
	  a = ((byte) aString[i]) & 0b01111111;
	  dot = ((byte) aString[i]) & 0b00001000;
#ifndef FD650_USE_PROGMEM	  
	  iBuffer[i] = FD650_CDigits[a];
#else
	  iBuffer[i] = pgm_read_byte_near(FD650_CDigits + a);
#endif
	  if (a) {
	    Wire.beginTransmission(FD650_DISPLAY_BASE+0);
	    Wire.write(iBuffer[i] | dot);
	    Wire.endTransmission();
	  }

}

/** Display string on the display in a running fashion
 * aString = character array to be displayed
 *
 * Starts with first N positions of the string.
 * Subsequent characters are displayed with 1 char shift each time displayRunningShift() is called
 *
 * returns: number of iterations remaining to display the whole string
 */
int FD650::displayRunning(char *aString) {

	strncpy(iString, aString, FD650_MAX_STRING+1);
	iPosition = iString;
	iString[FD650_MAX_STRING] = '\0'; //just in case.
    	displayString(iPosition);

	int l = strlen(iPosition);
	if (l <= iNumDigits) return 0;
	return (l - iNumDigits);
}

/** Display next segment (shifting to the left) of the string set by displayRunning()
 * Starts with first N positions of the string.
 * Subsequent characters are displayed with 1 char shift each time displayRunningShift is called
 *
 * returns: number of iterations remaining to display the whole string
 */
int FD650::displayRunningShift() {
    	if (strlen(iPosition) <= iNumDigits) return 0;
    	displayString(++iPosition);
	return (strlen(iPosition) - iNumDigits);
}



#endif /* _FD650_H_ */


