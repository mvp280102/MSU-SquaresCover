#include "Tester.h"


/*
 * Запускает решение задачи о покрытии квадратов точками
 * заданное число раз на случайно сгенерированных тестовых данных.
 */
void Tester::run_tests()
{
	TaskResults res{};

	results.reserve(data.tests_amount);

	srandom(static_cast<unsigned int>(time(nullptr)));

	for (int i = 0; i < data.tests_amount; ++i)
	{
		cout << "Running test " << i + 1 << "...\n";

		clock_t start, stop;

		res.squares.reserve(data.squares_amount);

		for (int j = 0; j < data.squares_amount; ++j)
			res.squares.push_back(Square{false, {static_cast<double>(random() % (data.range - data.side_length)), static_cast<double>(random() % (data.range - data.side_length))}});

		solver = new Solver(TaskData{data.side_length, res.squares});

		start = clock();
		res.steps = solver->cover(res.points);
		stop = clock();

		res.time = (double)(stop - start) / CLOCKS_PER_SEC;

		average_time += res.time;
		average_points += res.points.size();
		average_steps += res.steps;

		delete solver;

		results.push_back(res);
		res.squares.clear();
		res.points.clear();
	}

	average_time /= data.tests_amount;
	average_points /= data.tests_amount;
	average_steps /= data.tests_amount;
}


/*
 * TODO: Написать комментарий.
 */
void Tester::show_results()
{
	cout << endl
		 << data.tests_amount << " tests:\n"
		 << endl
		 << "Common data:\n"
		 << "Range: " << data.range << ".\n"
		 << "Squares amount: " << data.squares_amount << ".\n"
		 << "Side length: " << data.side_length << ".\n"
		 << endl;

	for (int i = 0; i < results.size(); ++i)
	{
		cout << "Test " << i + 1 << ":\n"
			 << "Points amount: " << results.at(i).points.size() << ".\n"
			 << "Steps amount: " << results.at(i).steps << ".\n"
			 << "Time: " << results.at(i).time << " s.\n"
			 << endl;
	}

	cout << "Average time for test: " << average_time << " s.\n"
		 << "Average points amount: " << average_points << ".\n"
		 << "Average steps amount: " << average_steps << ".\n"
		 << endl;
}


/*
 * TODO: Написать комментарий.
 */
void Tester::write_details(const char *filename)
{
	ofstream out;

	out.open(filename);

	if (out.fail())
	{
		cout << "Output file opening error!\n"
			 << "Aborting application!\n";

		exit(1);
	}

	out << data.tests_amount << " tests:\n"
		<< endl
		<< "Common data:\n"
		<< "Range: " << data.range << ".\n"
		<< "Squares amount: " << data.squares_amount << ".\n"
		<< "Side length: " << data.side_length << ".\n"
		<< endl << endl;

	for (int i = 0; i < results.size(); ++i)
	{
		out << "Test " << i + 1 << ":\n" << endl;

		out << "Coordinates of squares:\n";

		for (auto & square : results.at(i).squares)
			out << "(" << square.corner.x << "; " << square.corner.y << ")\n";

		out << endl
			<< "Coordinates of points:\n";

		for (auto & point : results.at(i).points)
			out << "(" << point.x << "; " << point.y << ")\n";

		out << endl
			<< "Points amount: " << results.at(i).points.size() << ".\n"
			<< "Steps amount: " << results.at(i).steps << ".\n"
		    << "Time: " << results.at(i).time << " s.\n"
		    << endl;
	}

	out << endl
		<< "Average time for test: " << average_time << " s.\n"
		<< "Average points amount: " << average_points << ".\n"
		<< "Average steps amount: " << average_steps << ".\n"
		<< endl;

	out.close();
}