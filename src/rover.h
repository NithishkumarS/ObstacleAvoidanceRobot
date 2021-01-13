/*
 * rover.h
 *
 *  Created on: Jan 12, 2020
 *      Author: Nithish
 *
 *  References: https://www.instructables.com/How-to-use-the-L293D-Motor-Driver-Arduino-Tutorial/
 *
 */

#ifndef INCLUDE_ROVER_H_
#define INCLUDE_ROVER_H_

class Rover {
  private:
    // Right Motor A connections
    int _right_pwm_pin; // PWM control pin (ENA)
    int _right_dir_in1; // right direction control pin (IN1)
    int _right_dir_in2; // right direction control pin (IN2)

    // Left Motor B connections
    int _left_pwm_pin; // PWM control pin (ENB)
    int _left_dir_in3; // left direction control pin (IN3)
    int _left_dir_in4; // left direction control pin (IN4)

    const int _right_switch_pin; // right switch pin
    const int _left_switch_pin;  // left switch pin

  public:
    Rover(int right_pwm, int right_in1, int right_in2,
          int left_pwm, int left_in3, int left_in4,
          int switch_left, int switch_right)
          : _left_switch_pin(switch_left), _right_switch_pin(switch_right),
			_right_pwm_pin(right_pwm), _right_dir_in1(right_in1), _right_dir_in2(right_in2),
            _left_pwm_pin(left_pwm), _left_dir_in3(left_in3), _left_dir_in4(left_in4)
    {
      // Initial configuration setup of control pins
      pinMode(_right_pwm_pin, OUTPUT);
      pinMode(_left_pwm_pin, OUTPUT);
      pinMode(_right_dir_in1, OUTPUT);
      pinMode(_right_dir_in2, OUTPUT);
      pinMode(_left_dir_in3, OUTPUT);
      pinMode(_left_dir_in4, OUTPUT);

      // Internal Pullup resistors of Arduino is configured
      // When limit switch is pressed, Pin connected to limit switches gets connected to ground (LOW)
      pinMode(_right_switch_pin, INPUT_PULLUP);
      pinMode(_left_switch_pin, INPUT_PULLUP);
    }

    // checks switch status and return the command to be executed
	int SwitchStatus() {
	  int right_switch = digitalRead(_right_switch_pin);
	  int left_switch = digitalRead(_left_switch_pin);

	  if(left_switch == LOW && right_switch == LOW) {
		return 0;
	  }
	  else if (left_switch == LOW) {
		return 1;
	  }
	  else if(right_switch == LOW) {
		return 2;
	  }
	}

    void Forward() {
      digitalWrite(_right_dir_in1, HIGH);
      digitalWrite(_right_dir_in2, LOW);
      analogWrite(_right_pwm_pin, 120);

      digitalWrite(_left_dir_in3, HIGH);
      digitalWrite(_left_dir_in4, LOW);
      analogWrite(_left_pwm_pin, 120);
    }

    void Backward() {
      digitalWrite(_right_dir_in1, LOW);
      digitalWrite(_right_dir_in2, HIGH);
      analogWrite(_right_pwm_pin, 120);

      digitalWrite(_left_dir_in3, LOW);
      digitalWrite(_left_dir_in4, HIGH);
      analogWrite(_left_pwm_pin, 120);
    }

    void Left(){
      digitalWrite(_right_dir_in1, HIGH);
      digitalWrite(_right_dir_in2, LOW);
      analogWrite(_right_pwm_pin, 120);

      digitalWrite(_left_dir_in3, LOW);
      digitalWrite(_left_dir_in4, HIGH);
      analogWrite(_left_pwm_pin, 120);
    }

    void Right(){
      digitalWrite(_right_dir_in1, LOW);
      digitalWrite(_right_dir_in2, HIGH);
      analogWrite(_right_pwm_pin, 120);

      digitalWrite(_left_dir_in3, HIGH);
      digitalWrite(_left_dir_in4, LOW);
      analogWrite(_left_pwm_pin, 120);
    }

    void Stop() {
      digitalWrite(_right_dir_in1, LOW);
      digitalWrite(_right_dir_in2, LOW);

      digitalWrite(_left_dir_in3, LOW);
      digitalWrite(_left_dir_in4, LOW);
    }

};

#endif   /* INCLUDE_ROVER_H_ */
