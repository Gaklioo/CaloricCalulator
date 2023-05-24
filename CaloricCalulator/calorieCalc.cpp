#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
//Constants
class constants {
public:
	const double lbsToKg = 2.205;
	const double inToCm = 2.54;
	const int ftToIn = 12;

	const double sedentary = 1.2; // Desk job, no exercise
	const double lightlyActive = 1.375; // Light Exercise/ sports 1-3d/w
	const double moderatelyActive = 1.55; // Moderate exercise/ sports 6-7 d/w
	const double veryActive = 1.725; // Hard Exercise 2x/Day
	const double extraActive = 1.9; // Marathons, Triathlon, etc.
};

double activityMultiplyer(double bmr, int exerciseLevel) {
	constants vars;
	double activityLevel{};
	switch (exerciseLevel)
	{
	case 1:
		activityLevel = bmr * vars.sedentary;
		break;
	case 2:
		activityLevel = bmr * vars.lightlyActive;
		break;
	case 3:
		activityLevel = bmr * vars.moderatelyActive;
		break;
	case 4:
		activityLevel = bmr * vars.veryActive;
		break;
	case 5:
		activityLevel = bmr * vars.extraActive;
		break;
	}
	return activityLevel;
}

double bmr(double weightLbs, double inHeight, int ftHeight, int age, char gender) {
	//Using Harris-Benedict Formula.
	constants vars;
	double weightKg{ weightLbs / vars.lbsToKg };
	double heightCm{ inHeight * vars.inToCm + (ftHeight * vars.ftToIn)};

	// Source for these variables: https://www.k-state.edu/paccats/Contents/PA/PDF/Physical%20Activity%20and%20Controlling%20Weight.pdf // Page 2.
	double maleBmr{ 66 + (13.7 * weightKg) + (5 * heightCm) - (6.8 * age) };
	double femaleBmr{ 655 + (9.6 * weightKg) + (1.8 * heightCm) - (4.7 * age) };

	if (gender == 'm')
		return maleBmr;
	else
		return femaleBmr;
}

int main() {
	double weight{};
	int heightFt{};
	int heightIn{};
	int age{};
	char gender{};
	int activityLevel{};

	std::cout << "Please enter Exact Weight: ";
	std::cin >> weight;
	std::cout << "Please enter ft Height: ";
	std::cin >> heightFt;
	std::cout << "Please enter in Height: ";
	std::cin >> heightIn;
	std::cout << "Please enter age: ";
	std::cin >> age;
	std::cout << "Please enter gender [m/f]";
	std::cin >> gender;
	std::cout << "Please enter activity level [Sedentary 1, Lightly Active 2, Moderatly Active 3, Very Active 4, Extra Active 5] ";
	std::cin >> activityLevel;

	if ((activityLevel > 5) || (activityLevel <= 0) || (gender != 'm') || (gender != 'f')){
		std::cout << "Incorrect activity level or gender enterd, Please retry.";
		std::cin.clear();
		Sleep(2000);
		system("CLS");
		main();
	}

	double bmrRes = bmr(weight, heightIn, heightFt, age, gender);
	double rcc = activityMultiplyer(bmrRes, activityLevel);

	system("CLS");

	std::cout << "Basic BMR: [" << bmrRes << "]\n";
	std::cout << "Recommended Caloric Intake: [" << rcc << "]\n";
}