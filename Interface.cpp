#include "Interface.h"


/*
 * Считывает с клавиатуры данные для одной задачи и
 * инициализирует ими экземпляр класса, решающего ее.
 */
void Interface::read_data()
{
	TaskData data{};
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

	solver = new Solver(data);
}