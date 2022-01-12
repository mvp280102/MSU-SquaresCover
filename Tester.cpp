#include "Tester.h"


/*
 * TODO: Написать комментарий.
 */
void Tester::save_results(TestResults &test_results, TaskResults &task_results)
{
	test_results.average_time += task_results.time;
	test_results.average_points += task_results.points.size();
	test_results.average_steps += task_results.steps;
	test_results.average_error += task_results.error;
	test_results.results.push_back(task_results);
}


/*
 * TODO: Написать комментарий.
 */
void Tester::conclude_average(TestResults &test_results) const
{
	test_results.average_time /= data.tests_amount;
	test_results.average_steps /= data.tests_amount;
	test_results.average_error /= data.tests_amount;
	test_results.average_points /= data.tests_amount;
}


/*
 * Запускает решение задачи о покрытии квадратов точками
 * простым и жадным алгоритмами заданное число раз на
 * случайно сгенерированных тестовых данных.
 */
void Tester::run_tests()
{
	TaskResults res;
	vector<Square> squares;

	srandom(static_cast<unsigned int>(time(nullptr)));

	for (int i = 0; i < data.tests_amount; ++i)
	{
		cout << "Running test " << i + 1 << ":\n";

		squares.reserve(data.squares_amount);

		for (int j = 0; j < data.squares_amount; ++j)
			squares.push_back(Square{false, {static_cast<double>(random() % (data.range - data.side_length)), static_cast<double>(random() % (data.range - data.side_length))}});

		solver = new Solver(TaskData{data.side_length, squares});

		cout << "Simple algorithm...\n";

		res = solver->cover_simple();
		save_results(results_simple, res);

		cout << "Greedy algorithm...\n";

		res = solver->cover_greedy();
		save_results(results_greedy, res);

		cout << endl;

		squares.clear();
		delete solver;
	}

	conclude_average(results_simple);
	conclude_average(results_greedy);
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

	cout << setw(20) << left << "\t\tAlgorithm type:"
		 << setw(10) << left << "SIMPLE"
		 << setw(10) << left << "GREEDY" << endl;

	for (int i = 0; i < data.tests_amount; ++i)
	{
		cout << "Test " << i + 1 << setw(2) << left << ":";

		cout << setw(20) << left << "Time: "
			 << setw(10) << left << results_simple.results.at(i).time
			 << setw(10) << left << results_greedy.results.at(i).time << "\n";

		cout << setw(20) << left << "\t\tSteps amount: "
			 << setw(10) << left << results_simple.results.at(i).steps
			 << setw(10) << left << results_greedy.results.at(i).steps << "\n";

		cout << setw(20) << left << "\t\tError: "
			 << setw(10) << left << results_simple.results.at(i).error
			 << setw(10) << left << results_greedy.results.at(i).error << "\n";

		cout << setw(20) << left << "\t\tPoints amount: "
			 << setw(10) << left << results_simple.results.at(i).points.size()
			 << setw(10) << left << results_greedy.results.at(i).points.size() << "\n"
			 << endl;
	}

	cout << endl
		 << "Average time for test: " << results_simple.average_time << "\t\t" << results_greedy.average_time << "\n"
		 << "Average steps amount: " << results_simple.average_steps << "\t\t" << results_greedy.average_steps << "\n"
		 << "Average error: " << results_simple.average_error << "\t\t" << results_greedy.average_error << "\n"
		 << "Average points amount: " << results_simple.average_points << "\t\t" << results_greedy.average_points << "\n"
		 << endl;
}


/*
 * TODO: Написать комментарий.
 */
/*
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
*/


/*
 * TODO: Написать комментарий.
 */
void Tester::create_diagram(const char *filename)
{

}