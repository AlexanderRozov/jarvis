#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
using namespace std;

struct Point // структура для хранения координат точки
{
    double x, y;
};
// Найти ориентацию упорядоченного триплета (p, q, r).
// Функция возвращает следующие значения
// по сути дела ищем косинус угла между точками
// 0 --> p, q и r лежат на одной прямой
// 1 --> надо идти по часовой стрелке
// 2 --> надо идти против часовой стрелки
int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
                 (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}
// Выводит выпуклую оболочку множества из n точек.
void Jarvis(Point points[], int n)
{
    //  �� ����� 3  �����
    if (n < 3)
        return;
    //  складываем все точки в контейнер типа Vector про него можно почитать
    vector<Point> hull;

    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    int p = l, q;
    do
    {
        hull.push_back(points[p]);
    q = (p+1)%n;
    for (int i = 0; i < n; i++)
    {

        if (orientation(points[p], points[i], points[q]) == 2)
            q = i;
    }
    p = q;
} while (p != l);

for (int i = 0; i < hull.size(); i++)
cout << "(" << hull[i].x << ", "
<< hull[i].y << ")\n";
}
void ReadPointsFromFile(Point points[])
{

    char *File= reinterpret_cast<char *>('t1.txt');
    int i = 0;
    ifstream f(File);
    if (!(f.is_open()))
        cout<<" ERROR: not file "<<File;
    else
    {
        while(!f.eof())
        {

            f>>points[i].x>>points[i].y;

            cout<<" x:"<<points[i].x<<" y:"<<points[i].y<<endl;
            i++;
        }
    }
    f.close();

}

int main(int argc, char** argv) {
    Point points[6];
    ReadPointsFromFile(points);

    /*тестовое значение*/

    /* Point points[] = {{1, 3}, {2, 2}, {1, 1}, {2, 1},
                       {3, 0}, {0, 0}, {3, 3}};
    */
    int n = sizeof(points)/sizeof(points[0]);
    Jarvis(points, n);
    return 0;
}
