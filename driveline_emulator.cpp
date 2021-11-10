#include<iostream>
#include<ncurses.h>
#include<thread>
#include<chrono>
#include<array>


class Driveline {
private:
    float engine_speed;
    float vehicle_speed;
    int throttle;
    bool brake;
    int gear;
    float max_engine_speed;
    std::array<int, 5> ratio;
public:
    Driveline(): engine_speed(0), vehicle_speed(0), throttle(0), 
        brake(false), gear(0), max_engine_speed(6000), ratio({80,60,40,30,25}) {}
    void loop() {
        while (true) {
            UpdateState();
            PrintState();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    void UpdateState() {
        if (throttle > 0) {
            brake = false;
            SetSpeed(50);
        } else if (vehicle_speed > 0 && !brake) {
            SetSpeed(-(engine_speed/400));
        } else if (vehicle_speed > 0 && brake) {
            SetSpeed(-100);
        }
    }
    void SetThrottle(unsigned int _value) {
        throttle = _value;
    }
    void ToggleBrake() {
        if (brake) {
            brake = false;
        } else {
            brake = true;
        }
    }
    void SetSpeed(float _delta) {
        engine_speed = engine_speed + _delta;
        if (engine_speed < 1500) {
            if (!GearDown() && engine_speed < 0) {
                engine_speed = 0;
            }
        } else if (engine_speed > 4000) {
            if (!GearUp() && engine_speed > max_engine_speed) {
                engine_speed = max_engine_speed;
            }
        }
        vehicle_speed = engine_speed / ratio[gear];
    }
    void PrintState() {
        system("clear");
        std::cout << "RPM:      " << (int)(engine_speed)   << " rpm\r" << std::endl;
        std::cout << "Speed:    " << (int)vehicle_speed << " km/h\r" << std::endl;
        std::cout << "Gear:     " << gear+1 << "\r" << std::endl;
        std::cout << "Throttle: " << throttle << "\r" << std::endl;
        std::cout << "Brake:    " << brake << "\r" << std::endl;
    }
    bool GearUp() {
        bool ret = false;
        if (gear < (sizeof(ratio)/4 - 1)) {
            gear ++;
            engine_speed = vehicle_speed * ratio[gear];
            ret = true;
        }
        return ret;
    }
    bool GearDown() {
        bool ret = false;
        if (gear > 0) {
            gear --;
            engine_speed = vehicle_speed * ratio[gear];
            ret = true;
        }
        return ret;
    }
};

void InputHandler(Driveline* engine) {
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    while (true) {
        char in;
        while ((in = getch()) == ERR) {}
        if (in == '1') {
            engine->SetThrottle(1);
        }
        else if (in == '0') {
            engine->SetThrottle(0);
        }
        if (in == 'b') {
            engine->SetThrottle(0);
            engine->ToggleBrake();
        }
        while (getch() != ERR) {}
        napms(100);
    }
}

int main() {
    Driveline DL1 = Driveline();
    std::thread DrivelineLoop(&Driveline::loop, &DL1);
    std::thread InputLoop(InputHandler, &DL1);

    DrivelineLoop.join();
    InputLoop.join();

    return 0;
}