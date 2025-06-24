#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

struct WasteCategory {
    string name;
    double weeklyWaste;
    double currentRecycleRate;
    double targetRecycleRate;
    double co2Factor;
    double waterFactor;
    double energyFactor;
};


void displayHeader();
void mainMenu();
void calculateWasteReduction();
void showHistory();
void displayEnvironmentalTips();
void inputWasteData(vector<WasteCategory> &categories);
void calculateImpact(const vector<WasteCategory> &categories);
void addToHistory(const vector<WasteCategory> &categories, double totalReduction, double totalCO2);
void clearInputBuffer();

vector<vector<WasteCategory>> calculationHistory;
vector<double> reductionHistory;
vector<double> co2History;

int main() {
    displayHeader();
    mainMenu();
    return 0;
}

void displayHeader() {
    cout << "============================================================\n";
    cout << "   GREEN CITY: ADVANCED SMART WASTE MANAGEMENT SYSTEM\n";
    cout << "============================================================\n\n";
    cout << "This program helps cities and individuals track waste reduction\n";
    cout << "and environmental impact through improved waste management.\n\n";
}

void mainMenu() {
    int choice;
    do {
        cout << "\n============ MAIN MENU ============\n";
        cout << "1. Calculate Waste Reduction Impact\n";
        cout << "2. View Calculation History\n";
        cout << "3. Environmental Tips\n";
        cout << "4. Exit Program\n";
        cout << "===================================\n";
        cout << "Enter your choice: ";
 n";
        }
    } while(choice != 4);
}

void calculateWasteReduction() {
    vector<WasteCategory> categories = {
        {"Organic Waste", 0, 0, 0, 0.25, 10, 0.5},
        {"Plastic", 0, 0, 0, 1.5, 50, 5},
        {"Paper", 0, 0, 0, 0.5, 100, 3},
        {"Metal", 0, 0, 0, 2.0, 40, 10},
        {"Glass", 0, 0, 0, 0.3, 20, 1},
        {"Other Waste", 0, 0, 0, 0.8, 20, 2}
    };

    inputWasteData(categories);
    calculateImpact(categories);
}

void inputWasteData(vector<WasteCategory> &categories) {
    cout << "\n===== WASTE DATA INPUT =====\n";
    for (auto &category : categories) {
        cout << "\nCategory: " << category.name << "\n";

        cout << "Enter weekly waste (kg): ";
        while (!(cin >> category.weeklyWaste) || category.weeklyWaste < 0) {
            cout << "Invalid input. Please enter a positive number: ";
            clearInputBuffer();
        }

        cout << "Enter current recycling rate (%): ";
        while (!(cin >> category.currentRecycleRate) ||
               category.currentRecycleRate < 0 || category.currentRecycleRate > 100) {
            cout << "Invalid input. Please enter a value between 0-100: ";
            clearInputBuffer();
        }

        cout << "Enter target recycling rate (%): ";
        while (!(cin >> category.targetRecycleRate) ||
               category.targetRecycleRate < 0 || category.targetRecycleRate > 100 ||
               category.targetRecycleRate < category.currentRecycleRate) {
            cout << "Invalid input. Must be between 0-100 and higher than current rate: ";
            clearInputBuffer();
        }

        clearInputBuffer();
    }
}

void calculateImpact(const vector<WasteCategory> &categories) {
    double totalReduction = 0;
    double totalCO2 = 0;
    double totalWaterSaved = 0;
    double totalEnergySaved = 0;

    cout << "\n\n======= ENVIRONMENTAL IMPACT REPORT =======\n";
    cout << setw(15) << left << "CATEGORY"
         << setw(12) << "CURRENT"
         << setw(12) << "FUTURE"
         << setw(10) << "REDUCTION"
         << setw(10) << "CO2 SAVED"
         << setw(15) << "WATER SAVED"
         << setw(15) << "ENERGY SAVED" << "\n";
    cout << setw(15) << ""
         << setw(12) << "(kg/week)"
         << setw(12) << "(kg/week)"
         << setw(10) << "(kg/week)"
         << setw(10) << "(kg/week)"
         << setw(15) << "(liters/week)"
         << setw(15) << "(kWh/week)" << "\n";
    cout << "-----------------------------------------------------------------\n";

    for (const auto &cat : categories) {
        double currentLandfill = cat.weeklyWaste * (1 - cat.currentRecycleRate/100);
        double futureLandfill = cat.weeklyWaste * (1 - cat.targetRecycleRate/100);
        double reduction = currentLandfill - futureLandfill;
        double co2Reduction = reduction * cat.co2Factor;
        double waterSaved = reduction * cat.waterFactor;
        double energySaved = reduction * cat.energyFactor;

        totalReduction += reduction;
        totalCO2 += co2Reduction;
        totalWaterSaved += waterSaved;
        totalEnergySaved += energySaved;

        cout << fixed << setprecision(2);
        cout << setw(15) << left << cat.name
             << setw(12) << currentLandfill
             << setw(12) << futureLandfill
             << setw(10) << reduction
             << setw(10) << co2Reduction
             << setw(15) << waterSaved
             << setw(15) << energySaved << "\n";
    }

    cout << "-----------------------------------------------------------------\n";
    cout << setw(39) << left << "TOTALS:"
         << setw(10) << totalReduction
         << setw(10) << totalCO2
         << setw(15) << totalWaterSaved
         << setw(15) << totalEnergySaved << "\n";
    cout << "===============================================================\n";


    cout << "\n ANNUAL PROJECTIONS:\n";
    cout << "  - Landfill reduction: " << totalReduction * 52 << " kg/year\n";
    cout << "  - CO2 emissions saved: " << totalCO2 * 52 << " kg/year\n";
    cout << "  - Water saved: " << totalWaterSaved * 52 << " liters/year\n";
    cout << "  - Energy saved: " << totalEnergySaved * 52 << " kWh/year\n";

    cout << "\n ENVIRONMENTAL EQUIVALENCIES:\n";
    cout << "  - CO2 savings equivalent to planting " << ceil(totalCO2 * 52 / 5) << " trees annually\n";
    cout << "  - Water savings could supply " << ceil(totalWaterSaved * 52 / 150000) << " households for a year\n";
    cout << "  - Energy savings could power " << ceil(totalEnergySaved * 52 / 4000) << " homes for a year\n";

    addToHistory(categories, totalReduction, totalCO2);
}

void addToHistory(const vector<WasteCategory> &categories, double totalReduction, double totalCO2) {
    calculationHistory.push_back(categories);
    reductionHistory.push_back(totalReduction);
    co2History.push_back(totalCO2);
    cout << "\nCalculation saved to history!\n";
}

void showHistory() {
    if (calculationHistory.empty()) {
        cout << "\nNo calculation history available.\n";
        return;
    }

    cout << "\n===== CALCULATION HISTORY =====\n";
    for (size_t i = 0; i < calculationHistory.size(); i++) {
        cout << "\nEntry #" << i+1 << " - Reduction: " << fixed << setprecision(2)
             << reductionHistory[i] << " kg/week, CO2 Saved: " << co2History[i] << " kg/week\n";

        if (i == 0 || i == calculationHistory.size() - 1) {
            cout << "  Categories: ";
            for (const auto &cat : calculationHistory[i]) {
                cout << cat.name << " (" << cat.weeklyWaste << "kg) ";
            }
            cout << "\n";
        }
    }
    cout << "\nTotal entries: " << calculationHistory.size() << "\n";


    if (calculationHistory.size() > 1) {
        auto maxReduction = *max_element(reductionHistory.begin(), reductionHistory.end());
        auto minReduction = *min_element(reductionHistory.begin(), reductionHistory.end());
        double avgReduction = 0;
        for (double val : reductionHistory) avgReduction += val;
        avgReduction /= reductionHistory.size();

        cout << "\n STATISTICS:\n";
        cout << "  Max Reduction: " << maxReduction << " kg/week\n";
        cout << "  Min Reduction: " << minReduction << " kg/week\n";
        cout << "  Avg Reduction: " << avgReduction << " kg/week\n";
    }
}

void displayEnvironmentalTips() {
    cout << "\n===== ENVIRONMENTAL TIPS =====\n";
    cout << "1. Separate waste at the source to improve recycling efficiency\n";
    cout << "2. Compost organic waste to reduce landfill methane emissions\n";
    cout << "3. Choose products with minimal packaging to reduce plastic waste\n";
    cout << "4. Participate in community recycling programs\n";
    cout << "5. Repair and reuse items instead of discarding them\n";
    cout << "6. Support businesses with sustainable waste management practices\n";
    cout << "7. Educate others about the importance of proper waste disposal\n";
    cout << "8. Use reusable containers instead of single-use plastics\n";
    cout << "9. Opt for digital documents to reduce paper waste\n";
    cout << "10. Advocate for better waste management policies in your community\n";
    cout << "===================================\n";
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//
