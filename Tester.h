#pragma once

#include "Solver.h"

#include <iostream>
#include <fstream>
using namespace std;


// Набор общих данных для тестов.
struct TestData
{
	unsigned int range;                 // Размер части плоскости.
	unsigned int squares_amount;        // Количество квадратов.
	unsigned int side_length;           // Длина стороны одного квадрата.
};


// Класс, генерирующий задачи и тестирующий алгоритм.
class Tester
{
	private:

	Solver *solver = nullptr;           // Экземпляр класса, решающего задачу
	TestData data;                      // Набор общих данных для тестов


	public:

	// Конструктор.
	explicit Tester(TestData data) : data(data) {}

	// TODO: Написать комментарий.
	void random_tests(unsigned int tests_amount);
};