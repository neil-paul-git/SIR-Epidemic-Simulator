/*
AUTHOR: Neil Paul
DATE: 3/24/2025
DESCRIPTION: This program simulates an epidemic using the SIR model with basic text outputs.
*/

#include <iostream>

using namespace std;

//Define limits to the simulation
const int MAX_CYCLES = 100;
const int MIN_POP = 10;
const int MAX_POP = 1000000;

//Declare global variables which are used to manage the epidemic simulations
int popSize, cycles, initSusceptible, initInfected, initRecovered;
double infectionRate, recoveryRate;

#include <iomanip>

//Recursive function which simulates the epidemic cycle by cycle
void simulateEpidemic(int susceptible, int infected, int recovered, int currentCycle) {
    //Stop the simulation when the number of cycles is reached
    if (currentCycle > cycles) {
        cout << "\nAfter " << cycles << " cycles, the simulation is complete.\n";
        return;
    }

    //Stop the simulation if there are no more infected individuals
    if (infected == 0) {
        cout << "\nAfter " << currentCycle << " cycles, the infection has completely ended.\n";
        return;
    }
    
    //Calculate the percentages of the population for each category
    double percentSusceptible = (susceptible * 100.0 / popSize);
    double percentInfected = (infected * 100.0 / popSize);
    double percentRecovered = (recovered * 100.0 / popSize);

    //Ensure that values are printed to 2 decimal places
    cout << fixed << setprecision(2);

    //Print a special message for the starting conditions of the simulation
    if (currentCycle == 0) {
        cout << "\nStarting Conditions:\n";
        cout << "Population Size:\t" << popSize << "\n";
        cout << "Infection Rate:\t\t" << infectionRate << "\n";
        cout << "Recovery Rate:\t\t" << recoveryRate << "\n\n";

        cout << "Susceptible:\t\t" << susceptible << "\t\t(" << percentSusceptible << "%)\n";
        cout << "Infected:\t\t" << infected << "\t\t(" << percentInfected << "%)\n";
        cout << "Recovered:\t\t" << recovered << "\t\t(" << percentRecovered << "%)\n";
    } else {
        //Print out information about the population during the simulation cycle
        cout << "\nCycle " << currentCycle << ":\n";
        cout << "Susceptible:\t\t" << susceptible << "\t\t(" << percentSusceptible << "%)\n";
        cout << "Infected:\t\t" << infected << "\t\t(" << percentInfected << "%)\n";
        cout << "Recovered:\t\t" << recovered << "\t\t(" << percentRecovered << "%)\n";
    }

    //Calculate the amounts of susceptible, infected, and recovered individuals in the next cycle
    int newInfections = min(static_cast<int>(infectionRate * infected * susceptible /
                        static_cast<double>(popSize)), susceptible);
    int newRecoveries = min(static_cast<int>(recoveryRate * infected), infected);

    //Apply the changes to the population
    susceptible -= newInfections;
    infected += (newInfections - newRecoveries);
    recovered += newRecoveries;

    //Recursively call the next cycle of the simulation
    simulateEpidemic(susceptible, infected, recovered, currentCycle + 1);
}

int main() {
    //Declare local variables which start
    int initSusceptible, initInfected, initRecovered;

    //Start program and collect starting variables
    cout << "\nBASIC SIR MODEL EPIDEMIC SIMULATOR\nBy: Neil Paul\n\n";

    cout << "Enter the number of cycles to run (1-" << MAX_CYCLES << "): ";
    cin >> cycles;
    if (cycles <= 0 || cycles > MAX_CYCLES) {
        cerr << "ERROR: Number of cycles must be between 1 and 100.\n";
        return 1;
    }

    cout << "Enter the size of the population (" << MIN_POP << "-" << MAX_POP << "): ";
    cin >> popSize;
    if (popSize < MIN_POP || popSize > MAX_POP) {
        cerr << "ERROR: Population size must be between " << MIN_POP << " and " << MAX_POP << ".\n";
        return 1;
    }

    cout << "Enter the initial number of infected individuals: ";
    cin >> initInfected;
    if (initInfected < 0 || initInfected > popSize) {
        cerr << "ERROR: Initial number of infected individuals is invalid.\n";
        return 1;
    }

    cout << "Enter the initial number of recovered individuals: ";
    cin >> initRecovered;
    if (initRecovered < 0 || initRecovered > (popSize - initInfected)) {
        cerr << "ERROR: Initial number of recovered individuals is invalid.\n";
        return 1;
    }

    cout << "Enter the infection rate (0.00-1.00): ";
    cin >> infectionRate;
    if (infectionRate < 0.0 || infectionRate > 1.0) {
        cerr << "ERROR: Infection rate must be between 0.00 and 1.00.\n";
        return 1;
    }

    cout << "Enter the recovery rate (0.00-1.00): ";
    cin >> recoveryRate;
    if (recoveryRate < 0.0 || recoveryRate > 1.0) {
        cerr << "ERROR: Recovery rate must be between 0.00 and 1.00.\n";
        return 1;
    }

    initSusceptible = popSize - initInfected - initRecovered;

    //Run the simulation
    simulateEpidemic(initSusceptible, initInfected, initRecovered, 0);

    return 0;
}