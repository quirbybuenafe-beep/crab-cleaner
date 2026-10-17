#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

// Function to convert feet to meters
double feetToMeters(double feet) {
    return feet * 0.3048;
}

// Function to convert minutes to seconds
double minutesToSeconds(double minutes) {
    return minutes * 60;
}

// Function to convert seconds to minutes and seconds
void secondsToMinutesAndSeconds(double totalSeconds, int &minutes, int &seconds) {
    minutes = static_cast<int>(totalSeconds) / 60;
    seconds = static_cast<int>(totalSeconds) % 60;
}

// Function to animate the loading process (spinner) and show total time left
void loadingAnimation(double cleaningTimeSeconds, const string &message) {
    int speed = 100; // Adjust speed of animation (milliseconds per frame)
    int frames = static_cast<int>(cleaningTimeSeconds); // Number of frames based on cleaning time
    const char spinner[] = {'|', '/', '-', '\\'}; // Array of spinner characters
    int spinnerIndex = 0; // Index to switch between spinner characters
    int minutes, seconds;

    // Calculate total cleaning time in minutes and seconds
    secondsToMinutesAndSeconds(cleaningTimeSeconds, minutes, seconds);

    cout << message << endl;
    for (int i = 0; i < frames; ++i) {
        secondsToMinutesAndSeconds(cleaningTimeSeconds - i, minutes, seconds); // Calculate time left

        // Display the spinner and time remaining in minutes:seconds format
        cout << "\r[" << spinner[spinnerIndex] << "] " << message
             << " Time Left: "
             << minutes << "m " << seconds << "s  "
             << "Total Time: "
             << minutes << "m " << seconds << "s"; // Show total time
        cout.flush();
        spinnerIndex = (spinnerIndex + 1) % 4; // Switch spinner character

    }

    cout << "\n\nDone!" << endl;
}

void calculateCleaningTime() {
    vector<double> conveyorLengths;  // Store multiple conveyor lengths
    double speed = 30.0;             // Default speed in meters per minute
    double totalLength = 0.0;        // Total length of all conveyors
    double totalTimeMinutes = 0.0;   // Total cleaning time in minutes
    double totalTimeSeconds = 0.0;   // Total cleaning time in seconds
    char addMore;                    // Option to add more lengths
    char resetChoice;                // Choice to reset or continue
    int unitChoice;                  // Unit choice: meters or feet

    cout << "\n=============================" << endl;
    cout << " CRAB CONVEYOR CLEANING SYSTEM" << endl;
    cout << "=============================\n" << endl;

    // Step 1: Select unit of measurement
    cout << "\nEnter the unit of measurement: (1 for meters, 2 for feet): ";
    cin >> unitChoice;

    string unit = (unitChoice == 1) ? "meters" : "feet";
    bool isFeet = (unitChoice == 2);  // Flag to check if input is in feet

    conveyorLengths.clear();  // Clear the previous lengths
    totalLength = 0.0;

    // Step 2: Input multiple conveyor lengths
    cout << "\nEnter the lengths of the conveyors in " << unit << ".\n" << endl;
    do {
        double length;
        cout << "Enter the length of the conveyor: ";
        cin >> length;

        if (isFeet) {
            length = feetToMeters(length);
            cout << "Converted to meters: " << fixed << setprecision(2) << length << " meters.\n" << endl;
        }

        conveyorLengths.push_back(length);

        cout << "Would you like to add another conveyor length? (Y/N): ";
        cin >> addMore;
    } while (addMore == 'Y' || addMore == 'y');

    // Calculate total length
    for (double length : conveyorLengths) {
        totalLength += length;
    }

    cout << "\nTotal Length of Conveyors: "
         << fixed << setprecision(2) << totalLength << " meters.\n" << endl;

    // Step 3: Adjust cleaning speed
    cout << "\nThe default cleaning speed is 30 meters per minute." << endl;
    cout << "Do you want to adjust the cleaning speed? (1 for Yes, 0 for No): ";
    cin >> unitChoice;

    if (unitChoice == 1) {
        cout << "\nEnter the new cleaning speed (in meters per minute): ";
        cin >> speed;
    }

    cout << "\nCleaning Speed: " << fixed << setprecision(2)
         << speed << " meters/minute.\n" << endl;

    // Step 4: Calculate total cleaning time
    totalTimeMinutes = totalLength / speed;
    totalTimeSeconds = minutesToSeconds(totalTimeMinutes);

    // Convert total time from seconds to minutes and seconds
    int minutes, seconds;
    secondsToMinutesAndSeconds(totalTimeSeconds, minutes, seconds);

    // Display cleaning time in minutes and seconds
    cout << "\nTime Required for Cleaning: "
         << minutes << "m " << seconds << "s.\n" << endl;

    // Loading animation for cleaning process
    loadingAnimation(totalTimeSeconds, "Cleaning the conveyor...");

    // Option to reset
    cout << "\nWould you like to reset and calculate again? (Y/N): ";
    cin >> resetChoice;

    if (resetChoice == 'Y' || resetChoice == 'y') {
        calculateCleaningTime();  // Reset and run the calculation again
    }

    cout << "\nExiting the Cleaning System\n" << endl;
}

int main() {
    cout << "=======================================" << endl;
    cout << " Welcome to the Crab Conveyor Cleaning " << endl;
    cout << "=======================================\n" << endl;

    calculateCleaningTime();

    return 0;
}
