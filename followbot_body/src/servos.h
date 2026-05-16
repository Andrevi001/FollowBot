#include <ESP32Servo.h>

const int PAN = 25;
const int TILT = 26;

Servo servoPan;
Servo servoTilt;

class Pan_Tilt {
private:
    int16_t pan = 75;
    int16_t tilt = 70;

    Pan_Tilt() {}

    Pan_Tilt(const Pan_Tilt&) = delete;
    Pan_Tilt& operator=(const Pan_Tilt&) = delete;

public:
    static Pan_Tilt& getInstance() {
        static Pan_Tilt instance;
        return instance;
    }

    void centerFov() {
        pan = 75;
        tilt = 70;
        servoPan.write(pan);
        servoTilt.write(tilt);
    }

    void updateServos(int8_t pan_sum, int8_t tilt_sum) {
        if (pan_sum != 0) {
            if (pan_sum > 0) {
                for (int i = pan; i <= (pan + pan_sum); i++) {
                    servoPan.write(i);
                }
            } else {
                for (int i = pan; i >= (pan + pan_sum); i--) {
                    servoPan.write(i);
                }
            }
            pan += pan_sum;
        }

        if (tilt_sum != 0) {
            if (tilt_sum > 0) {
                for (int i = tilt; i <= (tilt + tilt_sum); i++) {
                    servoTilt.write(i);
                }
            } else {
                for (int i = tilt; i >= (tilt + tilt_sum); i--) {
                    servoTilt.write(i);
                }
            }
            tilt += tilt_sum;
        }
    }

    int16_t getPan() const { return pan; }
    int16_t getTilt() const { return tilt; }
};

Pan_Tilt& pt = Pan_Tilt::getInstance();
