#include <iostream>
#include <cstring> // For strcpy, strcmp, etc.
#include <cmath>
using namespace std;
//hello world

// Function prototypes
void   activitiesAssign(int, char[], char[]);
int    activitiesOption(char[]);
double calcAddOns(int, int, int, int);
double calcDiscount(double);
int    calcPassenger(char[]);
void   carSuggestionName(char[], int, int, double&);
void   carSuggestionNameEV(char[], int, int, double&);
double carSuggestionPrice(char[]);
void   drivingStyle(char[], bool);
bool   licenseName(char[], int &);
int    idAssign(char[]);

int main() {
    int amountOfPassengers, codeActivities, ownerID, month = 0, week = 0, day = 0, timeOption;
    double carPrice, totalPrice, bfrDiscount, addOnsPrice, timeFee, totalPriceSST, totalPriceDisc, totalSST;
    bool systemLoop, addOnsLoop, hasLicense;
    char carChoice[20], licenseValidity[30], userDrivingStyle[30], drivingChoice[30], ownerName[50], typeOfActivity[20], loopOption[5], validInput[5], addOnsOption[10];

    totalPrice = 0;
    systemLoop = true;

    cout << "-=+ WELCOME TO GRAND WHEELS AUTO RENTALS +=-" << endl;

    while (systemLoop) {
        hasLicense = licenseName(ownerName, ownerID);
        
        if (hasLicense == false)
        {
        	return 0;
		}

        if (strcmp(ownerName, "blank") != 0) {
            drivingStyle(userDrivingStyle, hasLicense);
            if (strcmp(userDrivingStyle, "Self-Driving Vehicle") == 0) {
                codeActivities = activitiesOption(userDrivingStyle);
                activitiesAssign(codeActivities, typeOfActivity, userDrivingStyle);
                amountOfPassengers = calcPassenger(userDrivingStyle);
                carSuggestionNameEV(carChoice, codeActivities, amountOfPassengers, carPrice);
                totalPrice += carPrice;
            } else {
                codeActivities = activitiesOption(userDrivingStyle);
                activitiesAssign(codeActivities, typeOfActivity, userDrivingStyle);
                amountOfPassengers = calcPassenger(userDrivingStyle);
                carSuggestionName(carChoice, codeActivities, amountOfPassengers, carPrice);
                totalPrice += carPrice;
            }

            do {
                cout << "Would you like to enter Months, Weeks, or Days to determine your rental period?" << endl
                     << "1. Month" << endl
                     << "2. Weeks" << endl
                     << "3. Days" << endl;
                cin >> timeOption;
                if (timeOption == 1) {
                    cout << "Month: ";
                    cin >> month;
                    while (month <= 0) {
                        cout << "There was an invalid input in MONTH" << endl;
                        cout << "Month (Insert the correct value): ";
                        cin >> month;
                    }
                    timeFee = month * 1500;
                    strcpy(validInput, "False");
                } else if (timeOption == 2) {
                    cout << "Week: ";
                    cin >> week;
                    while (week <= 0) {
                        cout << "There was an invalid input in WEEK" << endl;
                        cout << "Week (Insert the correct value): ";
                        cin >> week;
                    }
                    timeFee = week * 350;
                    strcpy(validInput, "False");
                } else if (timeOption == 3) {
                    cout << "Days: ";
                    cin >> day;
                    while (day <= 0) {
                        cout << "There was an invalid input in DAY" << endl;
                        cout << "Days (Insert the correct value): ";
                        cin >> day;
                    }
                    timeFee = day * 50;
                    strcpy(validInput, "False");
                } else {
                    cout << "Invalid Input, Try Again" << endl;
                    strcpy(validInput, "True");
                }
            } while (strcmp(validInput, "True") == 0);

            totalPrice += timeFee;

            do {
                cout << "Do you want an Add-Ons? Y/N" << endl;
                cin >> addOnsOption;
                if (strcmp(addOnsOption, "Y") == 0 || strcmp(addOnsOption, "y") == 0) {
                    addOnsPrice = calcAddOns(month, week, day, timeOption);
                    addOnsLoop = false;
                } else if (strcmp(addOnsOption, "N") == 0 || strcmp(addOnsOption, "n") == 0) {
                    addOnsPrice = 0;
                    addOnsLoop = false;
                } else {
                    cout << "ERROR: Invalid input. Please try again" << endl;
                    addOnsLoop = true;
                }
            } while (addOnsLoop);

            totalPrice += addOnsPrice;
            bfrDiscount = calcDiscount(totalPrice);
            
            if (bfrDiscount == 0) {
                totalSST = totalPrice * 0.08;
                totalPriceSST = totalPrice + totalSST;
            } else {
                totalPriceDisc = totalPrice - bfrDiscount;
                totalSST = totalPriceDisc * 0.08;
                totalPriceSST = totalPriceDisc + totalSST;
            }

            cout << "=============== CUSTOMER'S INVOICE ===============" << endl;
            cout << "Driver's Name: " << ownerName << endl;
            cout << "License ID: " << ownerID << endl << endl;
            cout << "Driving Style: " << userDrivingStyle << endl;
            cout << "Amount Of Passengers: " << amountOfPassengers << endl;
            cout << "Type Of Activities: " << typeOfActivity << endl;
            cout << "The Car You Have Chosen: " << carChoice << endl << endl;
            cout << "[Rental Period]" << endl;
            if (timeOption == 1) {
                cout << "Months: " << month << endl << endl;
            } else if (timeOption == 2) {
                cout << "Weeks: " << week << endl << endl;
            } else {
                cout << "Days: " << day << endl << endl;
            }

            if (addOnsPrice != 0) {
                cout << "Add-Ons: RM" << addOnsPrice << endl << endl;
            }

            if (bfrDiscount == 0) {
            	cout << "Total Price Before SST: RM" << totalPrice << endl << endl;
            	cout << "Sales Tax: RM" << totalSST << endl << endl;
                cout << "Total Price: RM" << totalPriceSST << endl;
            } else {
            	cout << "Total Price Before Discount (Excluding SST 8%): RM" << totalPrice << endl << endl;
                cout << "Discount: RM" << bfrDiscount << endl;
                cout << "Sales Tax: RM" << totalSST << endl << endl;
                cout << "Total Price: RM" << totalPriceSST << endl;
            }

            cout << "=============== CUSTOMER'S INVOICE ===============" << endl;
            cout << "Do you want to continue using the system? Y/N" << endl;
            cin >> loopOption;
            if (strcmp(loopOption, "y") == 0 || strcmp(loopOption, "Y") == 0) {
                systemLoop = true;
            } else {
                systemLoop = false;
                cout << endl << "---===Thank You For Using Grand Wheels Auto Services===---" << endl;
            }
        }
    }
    return 0;
}

// Function definitions
void activitiesAssign(int assignCode, char typeActivities[], char drivingChoice[]) {
    if (strcmp(drivingChoice, "Self-Driving Vehicle") == 0) {
        switch (assignCode) {
            case 1:
                strcpy(typeActivities, "Short Trip");
                break;
            case 2:
                strcpy(typeActivities, "Long Trip");
                break;
            case 3:
                strcpy(typeActivities, "Leisure");
                break;
            default:
                cout << "ERROR: Invalid activity code." << endl;
                break;
        }
    } else if (strcmp(drivingChoice, "Personal Rent") == 0) {
        switch (assignCode) {
            case 1:
                strcpy(typeActivities, "Offroad");
                break;
            case 2:
                strcpy(typeActivities, "Short Trip");
                break;
            case 3:
                strcpy(typeActivities, "Long Trip");
                break;
            case 4:
                strcpy(typeActivities, "Leisure");
                break;
            default:
                cout << "ERROR: Invalid activity code." << endl;
                break;
        }
    }
}

int activitiesOption(char drivingStyle[]) {
    int codeActivities;
    bool codeFlag;

    do {
        if (strcmp(drivingStyle, "Self-Driving Vehicle") == 0) {
            cout << " ---Type of Activities with car--- \n[1] Short Trip\n[2] Long Trip\n[3] Leisure\nEnter Code Type of Activities: ";
            cin >> codeActivities;
            if (codeActivities < 1 || codeActivities > 3) {
                cout << "ERROR: Please enter a valid input (1/2/3)." << endl;
                codeFlag = true;
            } else {
                codeFlag = false;
            }
        } else {
            cout << " ---Type of Activities with car--- \n[1] Offroad\n[2] Short Trip\n[3] Long Trip\n[4] Leisure\nEnter Code Type of Activities: ";
            cin >> codeActivities;
            if (codeActivities < 1 || codeActivities > 4) {
                cout << "ERROR: Please enter a valid input (1/2/3/4)." << endl;
                codeFlag = true;
            } else {
                codeFlag = false;
            }
        }
    } while (codeFlag);

    return codeActivities;
}

double calcAddOns(int month, int week, int days, int timeType) {
    double addOns, totalAddOns = 0;
    bool insuranceBlock = false, babyBlock = false, systemBlock = false, tankBlock = false;
    int option;
    char question[5];

    do {
        cout << "Please choose an Add-Ons you desire" << endl;
        if (!insuranceBlock) cout << "1. Travel Insurance: RM200" << endl;
        if (!babyBlock) cout << "2. Baby seats: RM20" << endl;
        if (!systemBlock) cout << "3. Entertainment systems: RM50" << endl;
        if (timeType == 3 && !tankBlock) {
            if (days < 3) {
                cout << "Reminder that you are required to pay for a full fuel tank since you are renting for less than 3 days" << endl;
                totalAddOns += 100;
                tankBlock = true;
            } else {
                cout << "4. Full Fuel Tank: RM100" << endl;
            }
        } else if (!tankBlock) {
            cout << "4. Full Fuel Tank: RM100" << endl;
        }

        cin >> option;
        if (option == 1 && !insuranceBlock) {
            cout << "You have chosen TRAVEL INSURANCE" << endl;
            addOns = 200;
            insuranceBlock = true;
        } else if (option == 2 && !babyBlock) {
            cout << "You have chosen BABY SEATS" << endl;
            addOns = 20;
            babyBlock = true;
        } else if (option == 3 && !systemBlock) {
            cout << "You have chosen ENTERTAINMENT SYSTEMS" << endl;
            addOns = 50;
            systemBlock = true;
        } else if (option == 4 && !tankBlock) {
            cout << "You have chosen FULL FUEL TANK" << endl;
            addOns = 100;
            tankBlock = true;
        } else {
            cout << "Invalid option or already chosen. Please try again." << endl;
            continue;
        }

        totalAddOns += addOns;

        if (insuranceBlock && babyBlock && systemBlock && tankBlock) {
            cout << "You've purchased all add-ons." << endl;
            break;
        }

        cout << "Do you want to keep adding more add-ons? Y/N" << endl;
        cin >> question;
    } while (strcmp(question, "Y") == 0 || strcmp(question, "y") == 0);

    return totalAddOns;
}

double calcDiscount(double totalPrice) {
    double bfrdisc = 0;
    char choosepromo[5], promo[20];
    bool discountLoop = true;

    while (discountLoop) {
        cout << "Do you want to apply a promo code [Y/N]: ";
        cin >> choosepromo;
        if (strcmp(choosepromo, "Y") == 0 || strcmp(choosepromo, "y") == 0) {
            cout << "Got a promo code? Add it now! (Enter 'X' To Skip This Section): ";
            cin >> promo;
            if (strcmp(promo, "THEJOURNEY") == 0 || strcmp(promo, "10KMTRIP") == 0 || strcmp(promo, "BESTCARRENT") == 0) {
                bfrdisc = 0.2 * totalPrice;
                discountLoop = false;
            } else if (strcmp(promo, "X") == 0 || strcmp(promo, "x") == 0) {
                discountLoop = false;
            } else {
                cout << "Invalid Promo Code!! " << endl;
            }
        } else if (strcmp(choosepromo, "N") == 0 || strcmp(choosepromo, "n") == 0) {
            discountLoop = false;
        } else {
            cout << "Invalid Input! " << endl;
        }
    }

    return bfrdisc;
}

int calcPassenger(char drivingChoice[]) {
    int amountOfPassengers;
    bool passengerFlag;

    do {
        cout << "Enter the amount of passengers: ";
        cin >> amountOfPassengers;
        if (amountOfPassengers < 1) {
            cout << "Sorry invalid input. Please enter a positive integer" << endl;
            passengerFlag = true;
        } else if ((strcmp(drivingChoice, "Self-Driving Vehicle") == 0 && amountOfPassengers > 6) || (strcmp(drivingChoice, "Personal Rent") == 0 && amountOfPassengers > 8)) {
            cout << "Sorry, too many passengers! No car fits" << endl;
            passengerFlag = true;
        } else {
            passengerFlag = false;
        }
    } while (passengerFlag);

    return amountOfPassengers;
}

void carSuggestionName(char carChoice[], int codeActivities, int amountOfPassengers, double &price) {
    int codeCars;
    bool activityLoop = false, carChoiceLoop;

    do {
        if (codeActivities == 1) {
            do {
                carChoiceLoop = false;
                if (amountOfPassengers < 6) {
                    cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                    cout << "[1] JEEP (RM1400)" << endl;
                    cout << "[2] Isuzu D-Max (RM850)" << endl;
                    cout << "[3] Toyota Hilux (RM650)" << endl;
                    cout << "Code Cars: ";
                    cin >> codeCars;
                    switch (codeCars) {
                        case 1:
                            strcpy(carChoice, "JEEP");
                            price = 1400;
                            break;
                        case 2:
                            strcpy(carChoice, "Isuzu D-Max");
                            price = 850;
                            break;
                        case 3:
                            strcpy(carChoice, "Toyota Hilux");
                            price = 650;
                            break;
                        default:
                            cout << "Invalid Code Cars!! " << endl;
                            carChoiceLoop = true;
                    }
                } else {
                    cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                    cout << "[1] Hyundai Palisade (RM600)" << endl;
                    cout << "[2] Toyota Highlander (RM650)" << endl;
                    cout << "[3] Infiniti QX80 (RM800)" << endl;
                    cout << "Code Cars: ";
                    cin >> codeCars;
                    switch (codeCars) {
                        case 1:
                            strcpy(carChoice, "Hyundai Palisade");
                            price = 600;
                            break;
                        case 2:
                            strcpy(carChoice, "Toyota Highlander");
                            price = 650;
                            break;
                        case 3:
                            strcpy(carChoice, "Infiniti QX80");
                            price = 800;
                            break;
                        default:
                            cout << "Invalid Code Cars!! " << endl;
                            carChoiceLoop = true;
                    }
                }
            } while (carChoiceLoop);
        } else if (codeActivities == 2) {
            do {
                carChoiceLoop = false;
                if (amountOfPassengers < 6) {
                    cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                    cout << "[1] Perodua Axia (RM80)" << endl;
                    cout << "[2] Perodua Bezza (RM120)" << endl;
                    cout << "[3] Proton Iriz (RM100)" << endl;
                    cout << "Code Cars: ";
                    cin >> codeCars;
                    switch (codeCars) {
                        case 1:
                            strcpy(carChoice, "Perodua Axia");
                            price = 80;
                            break;
                        case 2:
                            strcpy(carChoice, "Perodua Bezza");
                            price = 120;
                            break;
                        case 3:
                            strcpy(carChoice, "Proton Iriz");
                            price = 100;
                            break;
                        default:
                            cout << "Invalid Code Cars!! " << endl;
                            carChoiceLoop = true;
                    }
                } else {
                    cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                    cout << "[1] Kia Carnival (RM400)" << endl;
                    cout << "[2] Toyota Sienna (RM380)" << endl;
                    cout << "[3] Honda Odyssey (RM300)" << endl;
                    cout << "Code Cars: ";
                    cin >> codeCars;
                    switch (codeCars) {
                        case 1:
                            strcpy(carChoice, "Kia Carnival");
                            price = 400;
                            break;
                        case 2:
                            strcpy(carChoice, "Toyota Sienna");
                            price = 380;
                            break;
                        case 3:
                            strcpy(carChoice, "Honda Odyssey");
                            price = 300;
                            break;
                        default:
                            cout << "Invalid Code Cars!! " << endl;
                            carChoiceLoop = true;
                    }
                }
            } while (carChoiceLoop);
        } else if (codeActivities == 3) {
            do {
                carChoiceLoop = false;
                if (amountOfPassengers < 6) {
                    cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                    cout << "[1] Toyota Corolla (RM500)" << endl;
                    cout << "[2] Toyota Yaris (RM350)" << endl;
                    cout << "[3] Nissan Serena (RM300)" << endl;
                    cout << "Code Cars: ";
                    cin >> codeCars;
                    switch (codeCars) {
                        case 1:
                            strcpy(carChoice, "Toyota Corolla");
                            price = 500;
                            break;
                        case 2:
                            strcpy(carChoice, "Toyota Yaris");
                            price = 350;
                            break;
                        case 3:
                            strcpy(carChoice, "Nissan Serena");
                            price = 300;
                            break;
                        default:
                            cout << "Invalid Code Cars!! " << endl;
                            carChoiceLoop = true;
                    }
                } else {
                    cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                    cout << "[1] Toyota Vellfire (RM450)" << endl;
                    cout << "[2] Hyundai Grand Starex (RM350)" << endl;
                    cout << "[3] Perodua Aruz (RM300)" << endl;
                    cout << "Code Cars: ";
                    cin >> codeCars;
                    switch (codeCars) {
                        case 1:
                            strcpy(carChoice, "Toyota Vellfire");
                            price = 450;
                            break;
                        case 2:
                            strcpy(carChoice, "Hyundai Grand Starex");
                            price = 350;
                            break;
                        case 3:
                            strcpy(carChoice, "Perodua Aruz");
                            price = 300;
                            break;
                        default:
                            cout << "Invalid Code Cars!! " << endl;
                            carChoiceLoop = true;
                    }
                }
            } while (carChoiceLoop);
        } else if (codeActivities == 4) {
            do {
                carChoiceLoop = false;
                if (amountOfPassengers < 6) {
                    cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                    cout << "[1] Mercedes-Benz G-Class (RM2000)" << endl;
                    cout << "[2] Rolls-Royce Phantom (RM2000)" << endl;
                    cout << "[3] Bentley Continental GT (RM2000)" << endl;
                    cout << "Code Cars: ";
                    cin >> codeCars;
                    switch (codeCars) {
                        case 1:
                            strcpy(carChoice, "Mercedes-Benz G-Class");
                            price = 2000;
                            break;
                        case 2:
                            strcpy(carChoice, "Rolls-Royce Phantom");
                            price = 2000;
                            break;
                        case 3:
                            strcpy(carChoice, "Bentley Continental GT");
                            price = 2000;
                            break;
                        default:
                            cout << "Invalid Code Cars!! " << endl;
                            carChoiceLoop = true;
                    }
                } else {
                    cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                    cout << "[1] Land Rover Defender 130 (RM500)" << endl;
                    cout << "[2] 2025 Cadillac Escalade (RM1000)" << endl;
                    cout << "[3] Mercedes-Benz V-Class (RM400)" << endl;
                    cout << "Code Cars: ";
                    cin >> codeCars;
                    switch (codeCars) {
                        case 1:
                            strcpy(carChoice, "Land Rover Defender 130");
                            price = 500;
                            break;
                        case 2:
                            strcpy(carChoice, "2025 Cadillac Escalade");
                            price = 1000;
                            break;
                        case 3:
                            strcpy(carChoice, "Mercedes-Benz V-Class");
                            price = 400;
                            break;
                        default:
                            cout << "Invalid Code Cars!! " << endl;
                            carChoiceLoop = true;
                    }
                }
            } while (carChoiceLoop);
        } else {
            cout << "Invalid code Activities!! " << endl;
            cout << "Please enter again" << endl;
            activityLoop = true;
        }
    } while (activityLoop);
}

void carSuggestionNameEV(char carChoice[], int codeActivities, int amountOfPassengers, double &price) {
    int codeCars;
    bool activityLoop = false, carChoiceLoop;

    do {
        if (codeActivities == 1) {
            do {
                carChoiceLoop = false;
                cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                cout << "[1] Tesla Model 3 (RM300)" << endl;
                cout << "[2] Nissan Leaf e+ (RM250)" << endl;
                cout << "[3] Hyundai Kona Electric (RM225)" << endl;
                cout << "Code Cars: ";
                cin >> codeCars;
                switch (codeCars) {
                    case 1:
                        strcpy(carChoice, "Tesla Model 3");
                        price = 300;
                        break;
                    case 2:
                        strcpy(carChoice, "Nissan Leaf e+");
                        price = 250;
                        break;
                    case 3:
                        strcpy(carChoice, "Hyundai Kona Electric");
                        price = 225;
                        break;
                    default:
                        cout << "Invalid Code Cars!! " << endl;
                        carChoiceLoop = true;
                }
            } while (carChoiceLoop);
        } else if (codeActivities == 2) {
            do {
                carChoiceLoop = false;
                cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                cout << "[1] Tesla Model S (RM450)" << endl;
                cout << "[2] Lucid Air Dream Edition (RM350)" << endl;
                cout << "[3] Mercedes-Benz EQS (RM300)" << endl;
                cout << "Code Cars: ";
                cin >> codeCars;
                switch (codeCars) {
                    case 1:
                        strcpy(carChoice, "Tesla Model S");
                        price = 450;
                        break;
                    case 2:
                        strcpy(carChoice, "Lucid Air Dream Edition");
                        price = 350;
                        break;
                    case 3:
                        strcpy(carChoice, "Mercedes-Benz EQS");
                        price = 300;
                        break;
                    default:
                        cout << "Invalid Code Cars!! " << endl;
                        carChoiceLoop = true;
                }
            } while (carChoiceLoop);
        } else if (codeActivities == 3) {
            do {
                carChoiceLoop = false;
                cout << "Suggested Type of Cars based on said Activities and amount of passengers" << endl;
                cout << "[1] Tesla Model X (RM650)" << endl;
                cout << "[2] Audi e-tron GT (RM500)" << endl;
                cout << "[3] Lucid Air Touring (RM550)" << endl;
                cout << "Code Cars: ";
                cin >> codeCars;
                switch (codeCars) {
                    case 1:
                        strcpy(carChoice, "Tesla Model X");
                        price = 650;
                        break;
                    case 2:
                        strcpy(carChoice, "Audi e-tron GT");
                        price = 500;
                        break;
                    case 3:
                        strcpy(carChoice, "Lucid Air Touring");
                        price = 550;
                        break;
                    default:
                        cout << "Invalid Code Cars!! " << endl;
                        carChoiceLoop = true;
                }
            } while (carChoiceLoop);
        } else {
            cout << "Invalid code Activities!! " << endl;
            cout << "Please enter again" << endl;
            activityLoop = true;
        }
    } while (activityLoop);
}

void drivingStyle(char drivingChoice[], bool hasLicense) {
    bool driverLoop = true;

    do {
        cout << "=====Choose A Method Of Driving=====" << endl;
        cout << "S - Self-Driving Vehicle (EV Only)" << endl;
        if (hasLicense) {
            cout << "PR - Personal Rent" << endl;
        }
        cin >> drivingChoice;
        if (strcmp(drivingChoice, "S") == 0 || strcmp(drivingChoice, "s") == 0) {
            strcpy(drivingChoice, "Self-Driving Vehicle");
            driverLoop = false;
        } else if (hasLicense && (strcmp(drivingChoice, "PR") == 0 || strcmp(drivingChoice, "pr") == 0 || strcmp(drivingChoice, "pR") == 0 || strcmp(drivingChoice, "Pr") == 0)) {
            strcpy(drivingChoice, "Personal Rent");
            driverLoop = false;
        } else {
            cout << "Invalid Input, Try Again" << endl;
        }
    } while (driverLoop);

    cout << "Choice: " << drivingChoice << endl;
}

bool licenseName(char driversName[], int &ownerID) {
    long long ownerLicense[3] = {890729045967, 950523100220, 750815045698};
    long long licenseProof;
    int idOption;
    char option[3];
    bool licenseLoop = true;

    while (licenseLoop) {
        cout << "Do You Have A License? (Y - Yes/N - No) : ";
        cin >> option;
        if (strcmp(option, "Y") == 0 || strcmp(option, "y") == 0) {
            while (licenseLoop) {
                cout << endl << "Enter Your License ID: ";
                cin >> licenseProof;
                if (licenseProof == ownerLicense[0]) {
                    cout << endl << "You Are A Valid Driver, You May Continue To Use Our Services" << endl << endl;
                    strcpy(driversName, "MOHD. FAAIZIE BIN DARMAWAN");
                    ownerID = 890729045967;
                    idOption = 1;
                    licenseLoop = false;
                    return true; // User has a valid license
                } else if (licenseProof == ownerLicense[1]) {
                	cout << endl << "You Are A Valid Driver, You May Continue To Use Our Services" << endl << endl;
                    strcpy(driversName, "MUHAMMAD AKMAR ISYRAQ BIN ZAMRI");
                    ownerID = 950523100220;
                    idOption = 1;
                    licenseLoop = false;
                    return true; // User has a valid license
                } else if (licenseProof == ownerLicense[2]) {
                	cout << endl << "You Are A Valid Driver, You May Continue To Use Our Services" << endl << endl;
                    strcpy(driversName, "LUQMAN BIN MOHAMED AZHAR");
                    ownerID = 750815045698;
                    idOption = 1;
                    licenseLoop = false;
                    return true; // User has a valid license
                } else {
                    cout << "Invalid ID, Try Again or go back?" << endl;
                    cout << "1. Try again" << endl;
                    cout << "2. Go back" << endl;
                    cin >> idOption;
                    if (idOption == 2) {
                        licenseLoop = false;
                    } else if (idOption == 1) {
                    } else {
                        cout << "ERROR: running the program again. Please insert a valid number" << endl;
                    }
                }
            }
            if (idOption == 2) {
                licenseLoop = true;
            }
        } else if (strcmp(option, "N") == 0 || strcmp(option, "n") == 0) {
            cout << endl << "Unfortunately, You Are Not Able To Rent A Car Using Our System" << endl;
            strcpy(driversName, "blank");
            licenseLoop = false;
            return false; // User does not have a license
        } else {
            cout << "Invalid Input, Try Again" << endl;
        }
    }
    return false; // Default return value
}

int idAssign(char ownerName[]) {
    return 0; 
}
