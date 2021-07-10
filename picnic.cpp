#include <iostream>

using namespace std;

int n, m;
bool friends[10][10];

void init()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            friends[i][j] = 0;
        }
    }
}

void input()
{
    cin >> n >> m;

    init();

    for (int i = 0; i < m; i++)
    {
        int x, y;

        cin >> x >> y;

        friends[x][y] = 1;
        friends[y][x] = 1;
    }
}

int count(bool taken[10])
{
    // 남은 학생들 중에 번호가 가장 빠른 학생을 찾는다.
    int first = -1;
    for (int i = 0; i < n; i++)
    {
        if (!taken[i])
        {
            first = i;
            break;
        }
    }

    // 기저 사례 : 모든 학생이 짝을 찾으면 종료
    if (first == -1)
        return 1;
    int ret = 0;

    // first와 짝지을 학생 찾기
    for (int pair = first + 1; pair < n; ++pair)
    {
        if (!taken[pair] && friends[first][pair])
        {
            taken[first] = taken[pair] = 1;
            ret += count(taken);
            taken[first] = taken[pair] = 0;
        }
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    int c;

    cin >> c;

    for (int i = 0; i < c; i++)
    {
        input();
        bool taken[10] = {};
        cout << count(taken) << endl;
    }

    return 0;
}