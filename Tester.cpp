#include "Tester.h"


/*
 * Добавляет результаты решения текущей задачи к результатам тестов.
 */
void Tester::save_results(TestResults &test_results, TaskResults &task_results)
{
	test_results.average_total_time += task_results.total_time;
	test_results.average_step_time += task_results.step_time;
	test_results.average_points += task_results.points.size();
	test_results.average_steps += task_results.steps;
	test_results.average_error += task_results.error;
	test_results.results.push_back(task_results);
}


/*
 * Вычисляет средние значения для результатов тестов.
 */
void Tester::conclude_average(TestResults &test_results) const
{
	test_results.average_total_time /= data.tests_amount;
	test_results.average_step_time /= data.tests_amount;
	test_results.average_steps /= data.tests_amount;
	test_results.average_error /= data.tests_amount;
	test_results.average_points /= data.tests_amount;
}


/*
 * Запускает решение задачи о покрытии квадратов точками простым и
 * жадным алгоритмами на случайно сгенерированных тестовых данных.
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

		solver = new Solver(TaskData{data.error_conclude, data.side_length, squares});

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
	cout.setf(ios::left);

	cout << DIVIDER
	     << "| "
		 << setw(COMMON_TITLE_WIDTH) << "COMMON DATA" << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Tests amount: "
	     << setw(CELL_DATA_WIDTH * 2) << data.tests_amount << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Range: "
	     << setw(CELL_DATA_WIDTH * 2) << data.range << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Squares amount: "
	     << setw(CELL_DATA_WIDTH * 2) << data.squares_amount << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Side length: "
	     << setw(CELL_DATA_WIDTH * 2) << data.side_length << "|\n";

	cout << DIVIDER
	     << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Algorithm type:"
	     << setw(CELL_DATA_WIDTH) << "SIMPLE"
	     << setw(CELL_DATA_WIDTH) << "GREEDY"
		 << "|\n";

	for (int i = 0; i < data.tests_amount; ++i)
	{
		cout << DIVIDER
			 << "| Test " << setw(2) << right << i + 1 << ":  " << left;

		cout << setw(CELL_TITLE_WIDTH) << "Total time:"
		     << setw(CELL_DATA_WIDTH) << results_simple.results.at(i).total_time
		     << setw(CELL_DATA_WIDTH) << results_greedy.results.at(i).total_time << "|\n";

		cout << "|\t\t\t"
		     << setw(CELL_TITLE_WIDTH) << "Time for step:"
		     << setw(CELL_DATA_WIDTH) << results_simple.results.at(i).step_time
		     << setw(CELL_DATA_WIDTH) << results_greedy.results.at(i).step_time << "|\n";

		cout << "|\t\t\t"
		     << setw(CELL_TITLE_WIDTH) << "Steps amount:"
		     << setw(CELL_DATA_WIDTH) << results_simple.results.at(i).steps
		     << setw(CELL_DATA_WIDTH) << results_greedy.results.at(i).steps << "|\n";

		if (data.error_conclude)
			cout << "|\t\t\t"
			     << setw(CELL_TITLE_WIDTH) << "Error:"
			     << setw(CELL_DATA_WIDTH) << results_simple.results.at(i).error
			     << setw(CELL_DATA_WIDTH) << results_greedy.results.at(i).error << "|\n";

		cout << "|\t\t\t"
		     << setw(CELL_TITLE_WIDTH) << "Points amount: "
		     << setw(CELL_DATA_WIDTH) << results_simple.results.at(i).points.size()
		     << setw(CELL_DATA_WIDTH) << results_greedy.results.at(i).points.size() << "|\n";
	}

	cout << DIVIDER
	     << "| "
	     << setw(COMMON_TITLE_WIDTH) << "AVERAGE VALUES" << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Average total time:"
	     << setw(CELL_DATA_WIDTH) << results_simple.average_total_time
	     << setw(CELL_DATA_WIDTH) << results_greedy.average_total_time << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Average time for step:"
	     << setw(CELL_DATA_WIDTH) << results_simple.average_step_time
	     << setw(CELL_DATA_WIDTH) << results_greedy.average_step_time << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Average steps amount:"
	     << setw(CELL_DATA_WIDTH) << results_simple.average_steps
	     << setw(CELL_DATA_WIDTH) << results_greedy.average_steps << "|\n";

	if (data.error_conclude)
		cout << "| "
		     << setw(COMMON_LABEL_WIDTH) << "Average error:"
		     << setw(CELL_DATA_WIDTH) << results_simple.average_error
		     << setw(CELL_DATA_WIDTH) << results_greedy.average_error << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Average points amount:"
	     << setw(CELL_DATA_WIDTH) << results_simple.average_points
	     << setw(CELL_DATA_WIDTH) << results_greedy.average_points << "|\n";

	cout << DIVIDER;
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
		    << "Time: " << results.at(i).total_time << " s.\n"
		    << endl;
	}

	out << endl
		<< "Average total_time for test: " << average_total_time << " s.\n"
		<< "Average points amount: " << average_points << ".\n"
		<< "Average steps amount: " << average_steps << ".\n"
		<< endl;

	out.close();
}
*/


/*
 * TODO: Написать комментарий.
 */
void Tester::create_csv(const char *filename)
{

}