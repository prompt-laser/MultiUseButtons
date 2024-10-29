/************************************************************* 
 *Author: Jacob Gilsdorf (prompt-laser)
 *Version: V 0.1.0
 *Last Edit(D.M.Y): 29.10.2024
 *Description: Library for supporting short and long presses of
				a button connected to ground
 *************************************************************/

class MultiUseButton {
	private:
		int _pin;											//variable for the pin the button is connected to
		int _delay;											//delay, in milliseconds, for the delayed function to fire
		long _start;										//start milliseconds of when the button was pressed
		long _end;											//end milliseconds of when button was released
		bool _btnPressed;									//whether the button is currently pressed or not
		bool _timer;										//whether the timer is currently running

		void (*instant_function)();							//variable for the instant function
		void (*delay_function)();							//variable for the delay function

		void AttachInstantFunction(void (*));				//declaration of function to assign instant function
		void AttachDelayFunction(void (*));					//declaration of function to assign the delay function

	public:
		MultiUseButton(int pin){							//constructor
			_pin = pin;										//assign pin variable to passed value
			pinMode(_pin, INPUT_PULLUP);					//set assigned pin to an input and pull it up for connecting to ground
			_timer = false;									//timer is not running
			_start = 0;										//initialize timer start varaible
			_end = 0;										//initialize timer end variable
		}

		void SetDelayTimer(int delay){						//set delay for delay function
			_delay = delay;									//assign to passed value
		}

		void AttachInstantFunction(void (*function)()){		//assign the function to fire for instant press
			instant_function = function;
		}

		void AttachDelayFunction(void (*function)()){		//assign the function to fire for delayed press
			delay_function = function;
		}

		void Toggle(){										//toggle button state
			if(_btnPressed){
				_btnPressed = false;
			}else{
				_btnPressed = true;
			}
		}

		void Run(){											//main function
			if(_btnPressed && !_timer){						//button pressed, timer not running
				_start = millis();							//set start of timer to now
				_timer = true;								//set timer state to running
			}
			
			if(!_btnPressed){								//button released
				_end = millis();							//set end of timer ot now
				 if(_timer){								//timer is running
					if(_end-_start > _delay){				//if timer was running longer than delay
						(*delay_function)();				//fire delay function
					}else{									//everything else
						(*instant_function)();				//fire instant function
					}
				 }
				_timer = false;								//state timer state to stopped
			}
		}
};