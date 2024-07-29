#include <algorithm>
#include <iostream>
#include <random>

int const ROW = 4;
int const COLUMN = 4;
int const MAX_AVAILABLE_MOVES = 4;
int const EMPTY_CELL = 0;

void inicializeMatrix(int matrixTag[ROW][COLUMN]);

void demonstrateMatrix(int matrixTag[ROW][COLUMN]);

void fillNambersAvailableForMove(int matrixTag[ROW][COLUMN], int numbersAvailableForMove[MAX_AVAILABLE_MOVES]);

void swapNumberOnZero(int matrixTag[ROW][COLUMN], int selectedNumber);

bool checkingForTheOrderOfDigits(int matrixTag[ROW][COLUMN]);

bool isNumberCorrect(int numbersAvailableForMove[4], int selectedNumber);

void move(int matrixTag[ROW][COLUMN]);

int main()
{
	setlocale(LC_ALL, "RU");

	int matrixTag[ROW][COLUMN] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 0}
	};

	inicializeMatrix(matrixTag);

	do
	{
		demonstrateMatrix(matrixTag);
		move(matrixTag);

	} while (checkingForTheOrderOfDigits(matrixTag));

	std::cout << "Игра закончена! Поздравляю!!!";

	return 0;
}

void inicializeMatrix(int matrixTag[ROW][COLUMN]) {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(&matrixTag[0][0], &matrixTag[3][4], generator);
}

void demonstrateMatrix(int matrixTag[ROW][COLUMN]) {
	for (int ii = 0; ii < ROW; ii++) {
		for (int jj = 0; jj < COLUMN; jj++) {
			if (matrixTag[ii][jj] == EMPTY_CELL) {
				std::cout << ". ";
			}
			else if (matrixTag[ii][jj] > 0 && matrixTag[ii][jj] < 10) {
				std::cout << matrixTag[ii][jj] << ' ';
			}
			else {
				std::cout << matrixTag[ii][jj];
			}
			std::cout << ' ';
		}
		std::cout << '\n';
	}
}

void fillNambersAvailableForMove(int matrixTag[ROW][COLUMN], int numbersAvailableForMove[MAX_AVAILABLE_MOVES]) {

	for (int ii = 0; ii < ROW; ii++) {
		for (int jj = 0; jj < COLUMN; jj++) {
			if (matrixTag[ii][jj] == EMPTY_CELL) {
				if (jj < COLUMN - 1)
					numbersAvailableForMove[0] = matrixTag[ii][jj + 1];

				if (ii < ROW - 1)
					numbersAvailableForMove[1] = matrixTag[ii + 1][jj];

				if (ii > 0)
					numbersAvailableForMove[2] = matrixTag[ii - 1][jj];

				if (jj > 0)
					numbersAvailableForMove[3] = matrixTag[ii][jj - 1];

			}
		}
	}
}

void swapNumberOnZero(int matrixTag[ROW][COLUMN], int selectedNumber) {

	for (int ii = 0; ii < ROW; ii++) {
		for (int jj = 0; jj < COLUMN; jj++) {
			if (matrixTag[ii][jj] == EMPTY_CELL) {
				matrixTag[ii][jj] = selectedNumber;
			}
			else if (matrixTag[ii][jj] == selectedNumber) {
				matrixTag[ii][jj] = EMPTY_CELL;
			}
		}
	}

}

bool checkingForTheOrderOfDigits(int matrixTag[ROW][COLUMN]) {
	int orderOfDigits[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 0}
	};

	for (int ii = 0; ii < ROW; ii++)
		for (int jj = 0; jj < COLUMN; jj++)
			if (matrixTag[ii][jj] == orderOfDigits[ii][jj])
				return true;

	return false;
}

bool isNumberCorrect(int numbersAvailableForMove[4], int selectedNumber) {
	for (int ii = 0; ii < MAX_AVAILABLE_MOVES; ii++)
		if (selectedNumber == numbersAvailableForMove[ii])
			return true;

	return false;
}

void move(int matrixTag[ROW][COLUMN]) {

	int arrayAvailableNumbers[MAX_AVAILABLE_MOVES] = { -1, -1, -1, -1 };
	int selectedNumber;
	do
	{
		std::cout << "Выберете цифру, которую хотите передвинуть: ";
		std::cin >> selectedNumber;

		arrayAvailableNumbers[0] = -1;
		arrayAvailableNumbers[1] = -1;
		arrayAvailableNumbers[2] = -1;
		arrayAvailableNumbers[3] = -1;

		fillNambersAvailableForMove(matrixTag, arrayAvailableNumbers);

		if (selectedNumber < 1 || selectedNumber > 15) {
			std::cout << "\nВведите число от 1 до 15:\n";
			continue;
		}

		if (!isNumberCorrect(arrayAvailableNumbers, selectedNumber)) {
			std::cout << "\nВыберете цифру, которую можно подвинуть в пустую ячейку!\n";
			continue;
		}


	} while ((selectedNumber < 1 || selectedNumber > 15) || !isNumberCorrect(arrayAvailableNumbers, selectedNumber));

	swapNumberOnZero(matrixTag, selectedNumber);
}

