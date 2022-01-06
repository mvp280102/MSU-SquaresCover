#include "Tester.h"


/*
 * Запускает решение задачи о покрытии квадратов точками
 * заданное число раз на случайно сгенерированных тестовых данных.
 */
void Tester::run_tests()
{
	TestResults res{};

	results.reserve(data.tests_amount);

	srandom(static_cast<unsigned int>(time(nullptr)));

	for (int i = 0; i < data.tests_amount; ++i)
	{
		cout << "Running test " << i + 1 << "...\n";

		clock_t start, stop;                            // Время начала и конца выполнения определенного теста.

		res.squares.reserve(data.squares_amount);

		for (int j = 0; j < data.squares_amount; ++j)
			res.squares.push_back(Square{false, {static_cast<double>(random() % (data.range - data.side_length)), static_cast<double>(random() % (data.range - data.side_length))}});

		solver = new Solver(TaskData{data.side_length, res.squares});

		start = clock();
		res.steps = solver->cover(res.points, false);
		stop = clock();

		average_steps += res.steps;

		res.time = (double)(stop - start) / CLOCKS_PER_SEC;
		average_time += res.time;

		delete solver;

		results.push_back(res);
		res.squares.clear();
		res.points.clear();
	}

	average_time /= data.tests_amount;
	average_steps /= data.tests_amount;
}


/*
 * Выводит на экран общие данные для тестов, результаты
 * для каждого теста и среднее время, затраченное на тест.
 */
void Tester::show_results()
{
	cout << endl
		 << data.tests_amount << " tests.\n"
		 << endl
		 << "Common data:\n"
		 << "Range: " << data.range << ".\n"
		 << "Squares amount: " << data.squares_amount << ".\n"
		 << "Side length: " << data.side_length << ".\n"
		 << endl;

	for (int i = 0; i < results.size(); ++i)
	{
		cout << "Test " << i + 1 << ":\n"
			 << "Steps amount: " << results.at(i).steps << ".\n"
			 << "Time: " << results.at(i).time << " s.\n"
			 << endl;
	}

	cout << "Average steps amount: " << average_steps << ".\n"
		 << "Average time: " << average_time << " s.\n"
		 << endl;
}