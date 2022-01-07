#pragma once

#include "Solver.h"

#include <iostream>
#include <fstream>
using namespace std;


// Набор общих данных для тестов.
struct TestData
{
	unsigned int tests_amount;          // Количество тестов.
	unsigned int range;                 // Размер части плоскости.
	unsigned int squares_amount;        // Количество квадратов.
	unsigned int side_length;           // Длина стороны одного квадрата.
};

// Результаты одного теста.
struct TestResults
{
	vector<Square> squares;             // Квадраты.
	vector<Point> points;               // Точки покрытия.

	unsigned int steps;                 // Количество шагов в тесте.
	double time;                        // Время, затраченное на тест.
};


// Класс, генерирующий задачи и тестирующий алгоритм.
class Tester
{
	private:

	Solver *solver = nullptr;               // Экземпляр класса, решающего задачу.
	TestData data;                          // Набор общих данных для тестов.

	double average_time = 0;                // Среднее время, затраченное на тест.
	unsigned long int average_points = 0;   // Среднее количество точек покрытия в тесте.
	unsigned long int average_steps = 0;    // Среднее количество шагов в тесте.

	vector<TestResults> results;            // Набор результатов для тестов.


	public:

	// Конструктор.
	explicit Tester(TestData data) : data(data) {}

	/*
	 * Запускает решение задачи о покрытии квадратов точками
	 * заданное число раз на случайно сгенерированных тестовых данных.
	 */
	void run_tests();

	/*
	 * TODO: Написать комментарий.
	 */
	void show_results();

	/*
	 * TODO: Написать комментарий.
	 */
	void write_details(const char *filename);
};