#pragma once


#include <vector>
using namespace std;


// Точка на плоскости.
struct Point
{
	double x;                            // Координата x.
	double y;                            // Координата y.
};

// Квадрат на плоскости.
struct Square
{
	bool covered = false;                // Флаг покрытия квадрата точкой.
	Point corner{};                      // Координаты левого нижнего угла.
};

// Отрезок на прямой.
struct Segment
{
	double begin;                         // Координата начала.
	double end;                           // Координата конца.
};

// Набор данных для задачи.
struct TaskData
{
	unsigned int squares_amount;        // Количество квадратов.
	unsigned int side_length;           // Длина стороны одного квадрата.
	vector<Square> squares;             // Вектор квадратов.
};


// Класс, решающий задачу.
class Solver
{
	private:

	TaskData data;                      // Набор данных для задачи.


	public:

	// Конструктор.
	explicit Solver(TaskData data) : data(move(data)) {}
};