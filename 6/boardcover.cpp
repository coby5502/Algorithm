#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 블록 종류 4가지 (dx, dy)
const int coverType[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}}};

void input(vector<vector<int> > &board)
{
    int h, w;
    cin >> h >> w;

    for (int i = 0; i < h; i++)
    {
        string x;
        cin >> x;

        vector<int> arr;

        for (int j = 0; j < w; j++)
        {
            if (x[j] == '#')
                arr.push_back(1);
            else
                arr.push_back(0);
        }

        board.push_back(arr);
    }
}

// board의 (y,x)를 type 방법으로 덮거나 없앤다.
// delta = 1 이면 덮고, -1 이면 없앤다.
// 블록이 제대로 덮이지 않은 경우
// (게임판 밖으로 나감, 겹침, 검은칸 덮을때) -> false 반환
bool set(vector<vector<int> > &board, int y, int x, int type, int delta)
{
    bool ok = true;

    for (int i = 0; i < 3; ++i)
    {
        const int ny = y + coverType[type][i][0];
        const int nx = x + coverType[type][i][1];

        // 게임판 밖
        if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
            ok = false;
        else if ((board[ny][nx] += delta) > 1)
            ok = false;
    }

    return ok;
}

// board의 모든 빈 칸을 덮을 수 있는 방법의 수를 반환한다.
// board[i][j] = 1 이면 덮인 칸 또는 검은 칸
// board[i][j] = 0 이면 아직 덮이지 않은 칸
int cover(vector<vector<int> > &board)
{
    // 아직 채우지 못한 칸 중 가장 윗줄 왼칸을 찾는다.
    int y = -1, x = -1;
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (board[i][j] == 0)
            {
                y = i;
                x = j;
                break;
            }
        }

        if (y != -1)
            break;
    }

    // 기저 사례 : 모든 칸을 채우면 1을 반환한다.
    if (y == -1)
        return 1;
    int ret = 0;
    for (int type = 0; type < 4; ++type)
    {
        // 만약 board[y][x]를 type 형태로 덮을 수 있으면 재귀 호출 한다.
        if (set(board, y, x, type, 1))
            ret += cover(board);
        // 덮었던 블록을 치운다.
        set(board, y, x, type, -1);
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    int c;

    cin >> c;

    for (int i = 0; i < c; i++)
    {
        vector<vector<int> > board;
        input(board);
        cout << cover(board) << endl;
    }

    return 0;
}