#pragma once

#define COMMON_TITLE_WIDTH 60
#define COMMON_LABEL_WIDTH 30
#define CELL_TITLE_WIDTH 20
#define CELL_DATA_WIDTH 15
#define DIVIDER "*-------------------------------------------------------------*\n"

#include "Solver.h"

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


// Общие данные для тестов.
struct TestData
{
	unsigned int tests_amount;                          // Количество тестов.
	unsigned int range;                                 // Размер части плоскости.
	unsigned int squares_amount;                        // Количество квадратов.
	unsigned int side_length;                           // Длина стороны одного квадрата.
	bool error_conclude = false;                        // Флаг необходимости вычисления ошибки.
};

// Результаты тестов.
struct TestResults
{
	double average_total_time = 0;                      // Среднее время, затраченное на тест.
	double average_step_time = 0;                       // Среднее время, затраченное на шаг теста.
	unsigned long int average_steps = 0;                // Среднее количество шагов в тесте.
	unsigned long int average_error = 0;                // Средняя ошибка для теста.
	unsigned long int average_points = 0;               // Среднее количество точек покрытия в тесте.
	vector<TaskResults> results;                        // Набор результатов тестов.
};


// Класс, генерирующий задачи и тестирующий алгоритм.
class Tester
{
	private:

	Solver *solver = nullptr;                           // Экземпляр класса, решающего задачу.
	TestData data{};                                    // Общие данные для тестов.
	TestResults results_simple{};                       // Результаты тестов простого алгоритма.
	TestResults results_greedy{};                       // Результаты тестов жадного алгоритма.

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Добавляет результаты решения текущей задачи к результатам тестов.
	 *
	 * ПАРАМЕТРЫ:
	 * TestResults &test_results - результаты тестов
	 * TaskResults &task_results - результаты решения текущей задачи
	 */
	static void save_results(TestResults &test_results, TaskResults &task_results);

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Вычисляет средние значения для результатов тестов.
	 *
	 * ПАРАМЕТРЫ:
	 * TestResults &test_results - результаты тестов
	 */
	void conclude_average(TestResults &test_results) const;


	public:

	/*
	 * Конструктор.
	 */
	explicit Tester(TestData data) : data(data) {}

	/*
	 * Запускает решение задачи о покрытии квадратов точками
	 * простым и жадным алгоритмами заданное число раз на
	 * случайно сгенерированных тестовых данных.
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

	/*
	 * TODO: Написать комментарий.
	 */
	void create_csv(const char *filename);
};