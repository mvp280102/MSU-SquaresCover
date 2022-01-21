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
#include <cmath>
using namespace std;


// Общие данные для тестов.
struct TestData
{
	unsigned int tests_amount;                                          // Количество тестов.
	unsigned int area_range;                                            // Размер части плоскости.
	unsigned int side_length;                                           // Длина стороны одного квадрата.
	unsigned int squares_amount;                                        // Количество квадратов.
	bool error_conclude = false;                                        // Флаг необходимости вычисления ошибки.
};

// Базовые результаты тестов.
struct TestResultsBase
{
	unsigned int squares_amount = 0;                                    // Количество квадратов.
	double average_total_time = 0;                                      // Среднее время, затраченное на тест.
	double average_step_time = 0;                                       // Среднее время, затраченное на шаг теста.
	unsigned long int average_steps = 0;                                // Среднее количество шагов в тесте.
};

// Расширенные результаты тестов.
struct TestResultsExtended : TestResultsBase
{
	unsigned long int average_error = 0;                                // Средняя ошибка для теста.
	unsigned long int average_points = 0;                               // Среднее количество точек покрытия в тесте.
	vector<TaskResults> task_results;                                   // Набор результатов тестов.
};


// Класс, генерирующий задачи и тестирующий алгоритмы.
class Tester
{
	private:

	Solver *solver = nullptr;                                           // Экземпляр класса, решающего задачу.
	TestData test_data{};                                               // Общие данные для тестов.
	pair<TestResultsExtended, TestResultsExtended> results;             // Результаты тестов обоих алгоритмов.
	vector< pair<TestResultsBase, TestResultsBase> > results_data;      // Набор результатов тестов обоих алгоритмов.


	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Добавляет результаты решения текущей задачи к результатам тестов.
	 *
	 * ПАРАМЕТРЫ:
	 * TestResultsExtended &test_results - результаты тестов
	 * TaskResults &task_results - результаты решения текущей задачи
	 */
	static void save_results(TestResultsExtended &test_results, TaskResults &task_results);

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Вычисляет средние значения для результатов тестов.
	 *
	 * ПАРАМЕТРЫ:
	 * TestResultsExtended &test_results - результаты тестов
	 */
	void conclude_average(TestResultsExtended &test_results) const;

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Теоретическая оценка вычислительной сложности простого алгоритма - O(N).
	 * Возвращает значение указанной функции теоретической оценки на данном количестве квадратов.
	 *
	 * ПАРАМЕТРЫ:
	 * unsigned int squares_amount - количество квадратов
	 */
	static inline double complexity_grade_simple(unsigned int squares_amount) ;

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Теоретическая оценка вычислительной сложности жадного алгоритма - O(N*log2(N)).
	 * Возвращает значение указанной функции теоретической оценки на данном количестве квадратов.
	 *
	 * ПАРАМЕТРЫ:
	 * unsigned int squares_amount - количество квадратов
	 */
	static inline double complexity_grade_greedy(unsigned int squares_amount) ;


	public:

	/*
	 * КОНСТРУКТОР.
	 */
	explicit Tester(TestData data) : test_data(data) {}

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Запускает решение задачи простым и жадным алгоритмами на одинаковых
	 * случайно сгенерированных по текущему критерию тестовых данных.
	 *
	 * ПАРАМЕТРЫ:
	 * bool output - флаг вывода описания процесса выполнения
	 */
	void test_current_data(bool output = false);

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Выводит на экран сводную таблицу по всем тестам для обоих
	 * алгоритмов, а также средние значения по полученным данным.
	 */
	void results_current_data();

	/*
	 * TODO: Написать комментарий.
	 */
	void details_current_data(const char *filename);

	/*
	 * TODO: Написать комментарий.
	 */
	void test_range_data(unsigned int high_squares_amount, unsigned int step, bool output = false);

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Выводит в csv-файл таблицу со средними значениями по тестам алгоритмов,
	 * запущенных в определенном диапазоне критерия тестовых данных.
	 *
	 * ПАРАМЕТРЫ:
	 * const char *filename - имя файла для вывода
	 */
	void csv_range_data(const char *filename) const;
};