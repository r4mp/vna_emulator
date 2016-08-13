#ifdef _WIN32
#include <conio.h>
#elif _WIN64
#include <conio.h>
#endif

#include <iostream>
using namespace std;

#ifdef __unix__
#include <termios.h>
#include <unistd.h>

int getch(void) {
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);          /* store old settings */
    newt = oldt;                             /* copy old settings to new settings */
    newt.c_lflag &= ~(ICANON | ECHO);        /* make one change to old settings in new settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); /* apply the new settings immediatly */
    ch = getchar();                          /* standard getchar call */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /* reapply the old settings */

    return ch;                               /* return received char */
}
#endif

double get_rand(double min, double max) {
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

int main(void) {
    char incoming_char = '\0';
    int num_steps = 10;
    double start_freq = 23000000.0;
    double stop_freq = 27000000.0;
    double current_freq = 0.0;

    double fwd = 0.0;
    double rev = 0.0;

    while(true) {
        incoming_char = getch();

        switch(incoming_char) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                break;
            case 'S':
            case 's':
                for(int i=0; i < num_steps; i++) {
                    current_freq = start_freq + (stop_freq - start_freq) / (num_steps - 1) * i;

                    cout << fixed << current_freq
                        << ",0,"
                        << get_rand(0, 12) // VSWR
                        << ","
                        << fwd
                        << ","
                        << rev << endl;
                }
                break;
            case '?':
                // Report current configuration to PC
                cout << "Start Freq: " << start_freq << endl;
                cout << "StopFreq: " << start_freq << endl;
                cout << "Num Steps: " << num_steps << endl;
                break;
            default:
                break;
        }
    }
}

