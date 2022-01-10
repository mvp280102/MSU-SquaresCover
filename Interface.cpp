#include "Interface.h"


/*
 * Считывает с клавиатуры данные для одной задачи.
 */
void Interface::read_data()
{
	Point corner{};

	unsigned int squares_amount;

	cout << "Squares amount: ";
	cin >> squares_amount;
	cout << "Side length: ";
	cin >> data.side_length;

	data.squares.reserve(squares_amount);

	cout << "Squares left corner coordinates:\n";

	for (int i = 0; i < squares_amount; ++i)
	{
		cin >> corner.x >> corner.y;
		data.squares.push_back(Square{false, Point{corner.x, corner.y}});
	}
}


/*
 * Запускает решение задачи на данных, введенных с клавиатуры.
 * В зависимости от переданного параметра описывает решение
 * подробно или просто выдает конечный ответ.
 */
void Interface::solve(bool show_steps)
{
	TaskResults res{};
	clock_t start, stop;

	solver = new Solver(data);

	start = clock();
	res.steps = solver->cover(res.points);
	stop = clock();

	res.time = (double)(stop - start) / CLOCKS_PER_SEC;

	delete solver;
}
