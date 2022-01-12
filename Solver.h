#pragma once


#include <ctime>
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
	double begin;                        // Координата начала.
	double end;                          // Координата конца.
};

// Данные для задачи.
struct TaskData
{
	unsigned int side_length;           // Длина стороны одного квадрата.
	vector<Square> squares;             // Квадраты.
};

// Результаты решения задачи.
struct TaskResults
{
	unsigned long int steps;            // Количество шагов в тесте.
	double time;                        // Время, затраченное на тест.
	vector<Point> points;               // Точки покрытия.
};


// Класс, решающий задачу.
class Solver
{
	private:

	TaskData data{};                    // Данные для задачи.
	TaskResults results{};              // Результаты решения задачи.

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Если квадраты пересекаются, возвращает указатель на
	 * координаты середины их пересечения, иначе - nullptr.
	 *
	 * ПАРАМЕТРЫ:
	 * unsigned int first - номер первого квадрата
	 * unsigned int second - номер второго квадрата
	 */
	Point* middle(unsigned int first, unsigned int second);

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Определяет, пересекаются ли отрезки.
	 * Если первый пересекается со вторым слева, возвращает -1.
	 * Если первый пересекается со вторым справа, возвращает 1.
	 * Если первый полностью лежит во втором, возвращает 2.
	 * Во всех остальных случаях возвращает 0.
	 *
	 * ПАРАМЕТРЫ:
	 * const Segment &first - первый отрезок
	 * const Segment &second - второй отрезок
	 */
	static int intersection(const Segment &first, const Segment &second);

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Если точка принадлежит квадрату, возвращает true, иначе - false.
	 *
	 * ПАРАМЕТРЫ:
	 * Point &point - точка
	 * Square &square - квадрат
	 */
	bool belong(const Point &point, const Square &square);


	public:

	/*
	 * КОНСТРУКТОР.
	 */
	explicit Solver(TaskData data) : data(move(data)) {}

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Решает задачу покрытия квадратов точками простым алгоритмом.
	 * Возвращает указатель на структуру с результатами решения задачи.
	 *
	 * АЛГОРИТМ:
	 * Под шагом понимается анализ пары квадратов на предмет их пересечения, и
	 * вычисление координат середины этого пересечения в соответствующем случае.
	 * На каждом шаге все пары еще не покрытых квадратов сравниваются на предмет
	 * их пересечения. Если они пересекаются, точкой покрытия считается середина
	 * их пересечения, а квадраты помечаются как покрытые. Если какой-либо непокрытый
	 * квадрат не пересекается с другими непокрытыми, точка покрытия - его середина.
	 * Алгоритм завершается, когда все квадраты покрыты точками.
	 *
	 * ВЫЧСЛИТЕЛЬНАЯ СЛОЖНОСТЬ:
	 * O(n^2 / 2) - сравнение каждого с каждым по правилу треугольника.
	 */
	TaskResults* cover_simple();

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Решает задачу покрытия квадратов точками жадным алгоритмом.
	 * Возвращает указатель на структуру с результатами решения задачи.
	 *
	 * АЛГОРИТМ:
	 * Под шагом понимается анализ пары квадратов на предмет их пересечения.
	 * На каждом шаге из списка квадратов выбирается первый непокрытый квадрат.
	 * Он считается начальным пересечением. Затем для каждого следующего в списке
	 * непокрытого квадрата вычисляется его пересечение с пересечением, полученным
	 * на предыдущем шаге. Процесс прекращается, когда в списке не остается квадратов,
	 * пересекающихся с уже полученным пересечением. Когда максимальное пересечение
	 * получено, точкой покрытия считается его середина, а все квадраты, вошедшие
	 * в максимальное пересечение, помечаются как покрытые. Алгоритм завершается,
	 * когда все квадраты покрыты точками.
	 *
	 * ВЫЧИСЛИТЕЛЬНАЯ СЛОЖНОСТЬ:
	 * O(n^2 / 2) - сравнение каждого с каждым по правилу треугольника.
	 */
	TaskResults* cover_greedy();

	/*
	 * ОПИСАНИЕ ФУНКЦИИ:
	 * Вычисляет суммарную ошибку для решения текущей задачи.
	 * Для покрытия квадрата достаточно одной точки. Под ошибкой для
	 * квадрата понимается количество лишних точек, его покрывающих.
	 * Суммарная ошибка - сумма ошибок для каждого квадрата.
	 */
	unsigned long int error();
};
