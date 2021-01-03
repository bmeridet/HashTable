#include <iostream>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

class HTable
{
private:
	struct Node
	{
		int data;
		Node* next;
		Node(int val) { data = val; next = nullptr; }
	};

	Node** bins;
	int binSize;

	void Initialize(int n);
	int GetIndex(int val);

public:
	HTable(int n);
	~HTable();

	void Insert(int val);
	int Delete(int val);
	int Search(int val);

	void Print();
};

int main()
{
	HTable t(10);

	t.Insert(5);
	t.Insert(1);
	t.Insert(10);
	t.Insert(16);
	t.Insert(37);
	t.Insert(2);

	t.Print();

	return 0;
}

void HTable::Initialize(int n)
{
	for (int i = 0; i < n; ++i)
		bins[i] = nullptr;
}

int HTable::GetIndex(int val)
{
	return val % 10;
}

HTable::HTable(int n)
{
	binSize = n;
	bins = new Node * [binSize];

	Initialize(binSize);
}

HTable::~HTable()
{
	for (int i = 0; i < binSize; ++i)
	{
		Node* ptr = bins[i];

		while (ptr != nullptr)
		{
			Node* del = ptr;
			ptr = ptr->next;
			delete del;
		}
	}

	delete[] bins;
}

void HTable::Insert(int val)
{
	int idx = GetIndex(val);

	Node* temp = new Node(val);

	if (bins[idx] == nullptr)
		bins[idx] = temp;
	else
	{
		Node* p = bins[idx];
		Node* q = bins[idx];

		while (p && p->data < val)
		{
			q = p;
			p = p->next;
		}

		if (q == bins[idx])
		{
			temp->next = bins[idx];
			bins[idx] = temp;
		}
		else
		{
			temp->next = q->next;
			q->next = temp;
		}
	}
}

int HTable::Delete(int val)
{
	int idx = GetIndex(val);

	Node* ptr = bins[idx];
	Node* q = bins[idx];

	while (ptr != nullptr && ptr->data <= val)
	{
		if (ptr->data == val)
		{
			Node* temp = ptr;
			int val = temp->data;

			if (ptr == bins[idx])
			{
				bins[idx] = temp->next;
				delete temp;

				return val;
			}
			else
			{
				temp->next = q->next;
				q->next = temp;
				delete temp;

				return val;
			}
		}

		q = ptr;
		ptr = ptr->next;
	}

	return -1;
}

int HTable::Search(int val)
{
	int idx = GetIndex(val);

	Node* ptr = bins[idx];

	while (ptr != nullptr && ptr->data <= val)
	{
		if (ptr->data == val)
			return val;

		ptr = ptr->next;
	}

	return -1;
}

void HTable::Print()
{
	for (int i = 0; i < binSize; ++i)
	{
		cout << "Bin " << i << ": ";

		Node* ptr = bins[i];

		while (ptr != nullptr)
		{
			cout << ptr->data << " ";
			ptr = ptr->next;
		}

		cout << endl;
	}

	cout << endl;
}