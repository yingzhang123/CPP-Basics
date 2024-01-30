#include <iostream>
#include <stack>

const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

const int WAY_NUM = 4;

const int YES = 4;
const int NO = 5;

class Node
{

};

class Maze
{
public:
	// ��ʼ���Թ��������û�����������������ɴ洢�Թ�·����Ϣ�Ķ�ά����
	Maze(int row, int col)
		: _row(row)
		, _col(col)
	{
		_pMaze = new Node * [_row];
		for (int i = 0; i < _row; ++i)
		{
			_pMaze[i] = new Node[_col];
		}
	}
	// ��ʼ���Թ�·���ڵ���Ϣ
	void initNode(int x, int y, int val)
	{
		_pMaze[x][y]._val = val;
		_pMaze[x][y]._x = x;
		_pMaze[x][y]._y = y;
		// �ڵ��ĸ�����Ĭ�ϳ�ʼ��
		for (int i = 0; i < WAY_NUM; ++i)
		{
			_pMaze[x][y]._state[i] = NO;
		}
	}

	//��ʼ���ĸ�����Ŀ���״̬
	void setNodeState()
	{
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; ++j)
			{
				if (_pMaze[i][j]._val == 1)
				{
					continue;
				}

				if (j < _col - 1 && _pMaze[i][j + 1]._val == 0)
				{
					_pMaze[i][j]._state[RIGHT] = YES;
				}
				if (i < _row - 1 && _pMaze[i + 1][j]._val == 0)
				{
					_pMaze[i][j]._state[DOWN] = YES;
				}
				if (j > 0 && _pMaze[i][j - 1]._val == 0)
				{
					_pMaze[i][j]._state[LEFT] = YES;
				}
				if (i > 0 && _pMaze[i - 1][j]._val == 0)
				{
					_pMaze[i][j]._state[UP] = YES;
				}
			}
		}
	}

	void searchMazePath()
	{
		if (_pMaze[0][0]._val == 1)
			return;
		_stack.push(_pMaze[0][0]);

		while (!_stack.empty())
		{
			Node top = _stack.top();
			int x = top._x;
			int y = top._y;

			if (x == _row - 1 && y == _col - 1)
				return;

			if (_pMaze[x][y]._state[RIGHT] == YES)
			{
				_pMaze[x][y]._state[RIGHT] = NO;
				_pMaze[x][y + 1]._state[LEFT] = NO;
				_stack.push(_pMaze[x][y + 1]);
				continue;
			}
			if (_pMaze[x][y]._state[DOWN] == YES)
			{
				_pMaze[x][y]._state[DOWN] = NO;
				_pMaze[x + 1][y]._state[UP] = NO;
				_stack.push(_pMaze[x + 1][y]);
				continue;
			}
			if (_pMaze[x][y]._state[LEFT] == YES)
			{
				_pMaze[x][y]._state[LEFT] = NO;
				_pMaze[x][y - 1]._state[RIGHT] = NO;
				_stack.push(_pMaze[x][y - 1]);
				continue;
			}
			if (_pMaze[x][y]._state[UP] == YES)
			{
				_pMaze[x][y]._state[UP] = NO;
				_pMaze[x - 1][y]._state[DOWN] = NO;
				_stack.push(_pMaze[x - 1][y]);
				continue;
			}
			_stack.pop();
		}
	}

	void showMazePath()
	{
		if (_stack.empty())
			std::cout << "������һ���Թ�·����" << std::endl;
		else
		{
			while (!_stack.empty())
			{
				Node top = _stack.top();
				_pMaze[top._x][top._y]._val = '*';
				_stack.pop();
			}
		}
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; ++j)
			{
				if (_pMaze[i][j]._val == '*')
					std::cout << "* ";
				else
					std::cout << _pMaze[i][j]._val << " ";
			}
			std::cout << std::endl;
		}
	}
private:
	struct Node
	{
		int _x;
		int _y;
		int _val; // �ڵ��ֵ
		int _state[WAY_NUM];// ��¼�ڵ��ĸ������״̬
	};
	int _row;
	int _col;
	Node** _pMaze; // ��̬�����Թ�·��
	std::stack<Node> _stack;
};

int main()
{
	std::cout << "�������Թ��������������磺10 10����";
	int row, col, data;
	std::cin >> row >> col;

	Maze maze(row, col);

	std::cout << "�������Թ���·����Ϣ��0��ʾ�����ߣ�1��ʾ�������ߣ���" << std::endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			std::cin >> data;
			maze.initNode(i, j, data);
		}
	}

	maze.setNodeState();

	maze.searchMazePath();

	maze.showMazePath();

	return 0;
}