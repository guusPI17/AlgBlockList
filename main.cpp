#include<iostream>
#include<windows.h>
using namespace std;
const int M = 4; // размер блока
const int N = 5; // размер индекс. таблицы
struct Data
{
	int kod;
	char name[5];
};
struct BlockNode
{
	Data value[M];
	BlockNode *pNext;
	BlockNode *pPrev;
	int Count = 0; // количество заполненных элементов 
};
struct IndexTable
{
	int NumberBlock;
	int OneIndexBlock;
	BlockNode *pElement = NULL;
};
struct BlockList
{
	IndexTable Table[N];
	BlockNode *pBegin = NULL;
	BlockNode *pEnd;
	int Size = 0; // количество блоков
	int SizeElement = 0; // количетсво элементов всего
};
void InputData(struct Data &primer);
void outup(struct BlockList *List);
void InsertToHead(struct BlockNode *One, struct Data primer, struct BlockList *List);
void InsertToTail(struct BlockNode*One, struct Data primer, struct BlockList *List);
void InsertIndex(struct BlockNode*One, struct Data primer, struct BlockList *List, int index);
void reindex(struct BlockNode*One, struct BlockList *List);
void OneBlock(BlockList *List, BlockNode *&One, struct Data primer); // создача самого превого блока
void SearchBlock(int &kolTable, int &IndexFound, int index, struct BlockNode*&One, struct BlockList *List); // поиск нужных блоков и индекса
void DeleteIndex(struct BlockNode*One, struct BlockList *List, int index);
void SetElementIndex(struct BlockNode*One, struct Data primer, struct BlockList *List, int index);
void GetElementIndex(struct BlockNode*One, struct Data &primer, struct BlockList *List, int index);
void ClearBlockNode(struct BlockList *List);
void ControlElementData(struct BlockList *List); // если указатели указывают на один элемент, то присвоение одинаковых данных
void main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	BlockNode *One;
	BlockList *List = new BlockList;
	Data primer[1];
	int otvet;
	cout << "Задавать начальное количество элементов(1-yes,2-no)?\n";
	cin >> otvet;
	if (otvet == 1)
	{
		cout << "Начальное количество элементов: ";
		int kol_element;
		cin >> kol_element;
		for (int i = 0;i < kol_element;i++)
		{
			InputData(primer[0]);
			if (i == 0)
				OneBlock(List, One, primer[0]);
			else
				InsertToTail(One, primer[0], List);
		}
		cout << "Начальное количество элементов = " << kol_element << endl;
	}
	else cout << "Начальное количество элементов = 0\n";
	cout << "Меню" << endl;
	cout << "1)Добавить в вершину\n" << "2)Добавить в хвост\n" << "3)Добавить в index\n" << "4)Индексация списка\n" << "5)Удалить по индексу\n" << "6)Изменить по индексу\n";
	cout << "7)Вывести по индексу\n" << "8)Вывод всех данных\n" << "9)Очистка списка\n" << "10)Очистка экрана\n" << "0)Выход\n";
	while (1)
	{
		int t;
		cin >> t;
		switch (t)
		{
		case 1:
		{
			InputData(primer[0]);
			if (List->pBegin == NULL) OneBlock(List, One, primer[0]);
			else InsertToHead(One, primer[0], List);
			break;
		}
		case 2:
		{
			InputData(primer[0]);
			if (List->pBegin == NULL) OneBlock(List, One, primer[0]);
			else InsertToTail(One, primer[0], List);
			break;
		}
		case 3:
		{
			int index;
			cout << "Введите индекс для добавления в него значения: ";
			cin >> index;
			if (index > List->SizeElement || index<0)
			{
				cout << "Error(такого индекса нету)\n";
				break;
			}
			InputData(primer[0]);
			if (List->pBegin == NULL) OneBlock(List, One, primer[0]);
			InsertIndex(One, primer[0], List, index);
			break;
		}
		case 4:
		{
			reindex(One, List);
			cout << "Переиндексация произошла\n";
			break;
		}
		case 5:
		{
			int index;
			cout << "Введите индекс для удаления: ";
			cin >> index;
			if (index > List->SizeElement - 1 || index<0)
			{
				cout << "Error(такого индекса нету)\n";
				break;
			}
			DeleteIndex(One, List, index);
			cout << "Индекс удален\n";
			break;
		}
		case 6:
		{
			int index;
			cout << "Введите индекс для изменения его значения: ";
			cin >> index;
			if (index > List->SizeElement - 1 || index<0)
			{
				cout << "Error(такого индекса нету)\n";
				break;
			}
			InputData(primer[0]);
			SetElementIndex(One, primer[0], List, index);
			break;
		}
		case 7:
		{
			int index;
			cout << "Введите индекс для вывода элемента: ";
			cin >> index;
			if (index > List->SizeElement - 1 || index<0)
			{
				cout << "Error(такого индекса нету)\n";
				break;
			}
			GetElementIndex(One, primer[0], List, index);
			cout << "Что вывели: " << primer[0].kod << endl;
			break;
		}
		case 8:
		{
			outup(List);
			break;
		}
		case 9:
		{
			ClearBlockNode(List);
			cout << "Список очищен\n";
			break;
		}
		case 10:
		{
			system("cls");
			cout << "Меню" << endl;
			cout << "1)Добавить в вершину\n" << "2)Добавить в хвост\n" << "3)Добавить в index\n" << "4)Индексация списка\n" << "5)Удалить по индексу\n" << "6)Изменить по индексу\n";
			cout << "7)Вывести по индексу\n" << "8)Вывод всех данных\n" << "9)Очистка списка\n" << "10)Очистка экрана\n" << "0)Выход\n";
			break;
		}
		case 0:
		{
			ClearBlockNode(List);
			return;
		}
		}
	}
}
void InputData(struct Data &primer)
{
	primer.name[0] = { 'a' };
	primer.kod = rand() % 150;
	cout << "Число  " << primer.kod << "  получено\n";
}
void ControlElementData(struct BlockList *List)  // если указатели указывают на один элемент, то присвоение одинаковых данных
{
	for (int i = 0;i < N;i++)
	{
		for (int j = 1;j < N;j++)
		{
			if (List->Table[j].pElement == List->Table[i].pElement)
			{
				List->Table[j].NumberBlock = List->Table[i].NumberBlock;
				List->Table[j].OneIndexBlock = List->Table[i].OneIndexBlock;
			}
		}
	}
}
void DeleteIndex(struct BlockNode*One, struct BlockList *List, int index)
{
	int kolTable, IndexFound;
	SearchBlock(kolTable, IndexFound, index, One, List);
	if (One->Count == 1)
	{
		if (One->pNext == NULL && One->pPrev == NULL) // если ласт элемент
		{
			List->pBegin = NULL;
			List->pEnd = NULL;
			List->Size--;
			List->SizeElement--;
			delete One;
			return;
		}
		if (One->pNext == NULL)
		{
			for (int t = 0;t < N;t++) // проверка и перевод всех указателей равные с пятым указателем
			{
				if (List->Table[t].pElement == List->Table[N-1].pElement)
					List->Table[t].pElement = One->pPrev;
			}
			List->Table[N-1].OneIndexBlock -= List->Table[N-1].pElement->Count;
			One->pPrev->pNext = NULL;
			List->pEnd=One->pPrev;
			List->Size--;
			List->SizeElement--;
			List->Table[N-1].NumberBlock = List->Size;
			delete One;
		}
		else if (One->pPrev == NULL)
		{
			for (int t = 0;t < N;t++) // проверка и перевод всех указателей равные с первым указателем
			{
				if (List->Table[t].pElement == List->Table[0].pElement && t != 0)
					List->Table[t].pElement = One->pNext;
			}
			List->Table[0].pElement = One->pNext;
			List->pBegin=One->pNext;
			One->pNext->pPrev = NULL;
			List->Size--;
			List->SizeElement--;
			delete One;
		}
		else
		{
			for (int i = kolTable;i < N;i++)
			{
				if (One->pNext == List->Table[i].pElement)
				{
					for (int j = 0;j < N;j++)// проверка и перевод всех указателей равные с x указателем
					{
						if (List->Table[j].pElement == List->Table[i - 1].pElement && j != (i - 1))  // j!=(i-1) чтобы не изменить сравнивающий указатель, он заменятеся в конце
							List->Table[j].pElement = List->Table[i].pElement;
					}
					List->Table[i - 1].pElement = List->Table[i].pElement;
				}
				else 
				{
					for (int t = 0;t < N;t++)
					{
						if (List->Table[t].pElement==List->Table[kolTable-1].pElement && t!=(kolTable-1)) //проверка и перевод всех указателей равные с x указателем
							List->Table[t].pElement = One->pNext;
					}
					List->Table[kolTable - 1].pElement = One->pNext;
				}
			}
			One->pPrev->pNext = One->pNext;
			One->pNext->pPrev = One->pPrev;
			List->Size--;
			List->SizeElement--;
			delete One;
		}
		for (int i = kolTable;i < N;i++)
		{
			List->Table[i].NumberBlock--;
			List->Table[i].OneIndexBlock--;
		}
	}
	else
	{
		List->SizeElement--;
		if (IndexFound == One->Count)
			One->Count--;
		else
		{
			One->Count--;
			for (int i = IndexFound;i < M - 1;i++)
				One->value[i] = One->value[i + 1];
		}
		for (int i = kolTable;i < N;i++)
			List->Table[i].OneIndexBlock--;
	}
	ControlElementData(List);
}
void ClearBlockNode(struct BlockList *List)
{
	BlockNode *One = List->pBegin;
	BlockNode *Two;
	while (One != NULL)
	{
		Two = One->pNext;
		delete One;
		One = Two;
	}
	List->pBegin = NULL;
	List->pEnd = NULL;
	List->Size = 0;
	List->SizeElement = 0;
	for (int i = 0;i < N;i++)
	{
		List->Table[i].NumberBlock = 0;
		List->Table[i].OneIndexBlock = 0;
		List->Table[i].pElement = NULL;
	}
}
void GetElementIndex(struct BlockNode*One, struct Data &primer, struct BlockList *List, int index)
{
	int kolTable, IndexFound;
	SearchBlock(kolTable, IndexFound, index, One, List);
	primer=One->value[IndexFound];
}
void SetElementIndex(struct BlockNode*One, struct Data primer, struct BlockList *List, int index)
{
	int kolTable, IndexFound;
	SearchBlock(kolTable, IndexFound, index, One, List);
	One->value[IndexFound] = primer;
}
void reindex(struct BlockNode*One, struct BlockList *List)
{
	One = List->pBegin;
	if (List->Size / N >= 1)
	{
		int k = List->Size / N;// через сколько указатель новый будет
		int tmp = 1;  // для подсчета номера блока
		int kol = 0; // для подсчета индексов 
		for (int i = 0;i < N - 1;i++)
		{
			if (i != 0)
			{
				tmp += k;
				for (int j = 0;j < k;j++)
				{
					kol += One->Count;
					One = One->pNext;
				}
			}
			List->Table[i].pElement = One;
			List->Table[i].NumberBlock = tmp;
			List->Table[i].OneIndexBlock = kol;
		}
		List->Table[N-1].pElement = List->pEnd;
		List->Table[N - 1].NumberBlock = List->Size;
		List->Table[N - 1].OneIndexBlock = List->SizeElement - List->pEnd->Count;
	}
}
void SearchBlock(int &kolTable, int &IndexFound, int index, struct BlockNode*&One, struct BlockList *List) // поиск нужных блоков и индекса
{
	One = List->pBegin;
	int nomer = 0; // индекс первого элемента блока
	kolTable = 0;
	for (int i = 0;i < N;i++)
	{
		kolTable++;
		nomer = List->Table[i].OneIndexBlock;
		if (index == nomer)
		{
			One = List->Table[i].pElement;
			break;
		}
		else if (index > nomer)
			if (i + 1 == N) One=List->Table[i].pElement;
			else One = List->Table[i+1].pElement;
		else if (index<nomer)
		{
			One = List->Table[i - 1].pElement;
			nomer = List->Table[i - 1].OneIndexBlock;
			kolTable--;
			break;
		}
	}
	IndexFound = (index - nomer) - M;
	while (IndexFound >= 0)
	{
		One = One->pNext;
		IndexFound -= M;
	}
	IndexFound += M;
}
void InsertIndex(struct BlockNode*One, struct Data primer, struct BlockList *List, int index)
{
	List->SizeElement++;
	int kolTable, IndexFound;
	SearchBlock(kolTable, IndexFound, index, One, List);
	int LastCount = One->Count;
	if (IndexFound > LastCount)
	{
		cout << "Error(нельзя добавить элемент перед незаполненным индексом)\n";
		return;
	}
	if (One->Count == M) // если блок заполнен
	{
		Data rtm = One->value[M - 1];
		BlockNode *One1 = new BlockNode;
		if (One->pNext == NULL)
		{
			One1->pPrev = One;
			One->pNext = One1;
			List->pEnd = One1;
			One1->pNext = NULL;
			List->Table[N - 1].NumberBlock = List->Size;;
			List->Table[N - 1].pElement = One1;
		}
		else if (One->pPrev == NULL)
		{
			One1->pNext = One->pNext;
			One1->pPrev = One;
			One->pNext = One1;
			List->pBegin = One;
			List->Table[0].NumberBlock = 1;
			List->Table[0].pElement = One;
		}
		else
		{
			One1->pNext = One->pNext;
			One->pNext->pPrev = One1;
			One1->pPrev = One;
			One->pNext = One1;
		}
		One1->Count++;
		List->Size++;
		One1->value[0] = rtm;
		int ppp = M - (IndexFound + 1);
		for (int i = M - 1;ppp > 0;i--, ppp--) // переставляем элементы после индекса
			One->value[i] = One->value[i - 1];
		One->value[IndexFound] = primer;
		if (One1->pNext == NULL)
		{
			List->Table[N - 1].OneIndexBlock += One->Count;
			List->Table[N - 1].NumberBlock++;
		}
		for (int i = kolTable;i < N;i++)
		{
			List->Table[i].NumberBlock++;
			List->Table[i].OneIndexBlock++;
		}
	}
	else
	{
		if (IndexFound>LastCount - 1) // если индекс еще не заполнен
		{
			One->value[LastCount] = primer;
			One->Count++;
		}
		else // если индекс уже заполнен
		{
			int ppp = M - (IndexFound + 1);
			for (int i = M - 1;ppp > 0;i--, ppp--) // переставляем элементы после индекса
			{
				One->value[i] = One->value[i - 1];
			}
			One->value[IndexFound] = primer;
			One->Count++;
		}
		for (int i = kolTable;i < N;i++)
			List->Table[i].OneIndexBlock++;
	}
}
void OneBlock(BlockList *List, BlockNode *&One, struct Data primer)
{
	One = new BlockNode;
	One->value[0] = primer;
	One->pNext = NULL;
	One->pPrev = NULL;
	List->pBegin = One;
	List->pEnd = One;
	One->Count++;
	List->Size++;
	List->SizeElement++;
	for (int i = 0;i < N;i++)
	{
		List->Table[i].NumberBlock = 1;
		List->Table[i].pElement = One;
		List->Table[i].OneIndexBlock = 0;
	}
}
void InsertToTail(struct BlockNode*One, struct Data primer, struct BlockList *List)
{
	BlockNode *One1;
	One = List->pEnd;
	if (One->Count == M)
	{
		One1 = new BlockNode;
		One1->value[0] = primer;
		if (One->pPrev == NULL)
		{
			One1->pPrev = One;
			One->pNext = One1;
			List->pEnd = One1;
			List->pBegin = One;
			One1->pNext = NULL;
		}
		else
		{
			One1->pPrev = List->pEnd;
			One1->pPrev->pNext = One1;
			List->pEnd = One1;
			One1->pNext = NULL;
		}
		One1->Count++;
		List->Size++;
		List->Table[N - 1].NumberBlock = List->Size;
		List->Table[N - 1].pElement = One1;
		List->Table[N - 1].OneIndexBlock = List->SizeElement;
	}
	else
	{
		One->value[One->Count] = primer;
		One->Count++;
	}
	List->SizeElement++;
}
void InsertToHead(struct BlockNode *One, struct Data primer, struct BlockList *List)
{
	One = List->pBegin;
	if (One->Count == M)
	{
		BlockNode *One1 = new BlockNode;
		Data rtm = One->value[M - 1];
		List->Table[0].NumberBlock = 1;
		List->Table[0].pElement = One;
		List->Table[0].OneIndexBlock = 0;
		for (int i = M - 1;i >= 0;i--)
			if (i != M - 1) One->value[i + 1] = One->value[i];
		One->value[0] = primer;
		One1->value[0] = rtm;
		List->Size++;
		One1->Count++;
		if (One->pNext == NULL)
		{
			One1->pPrev = One;
			One->pNext = One1;
			List->pEnd = One1;
			List->pBegin = One;
			One1->pNext = NULL;
		}
		else
		{
			One->pNext->pPrev = One1;
			One1->pNext = One->pNext;
			One1->pPrev = One;
			One->pNext = One1;
		}
		for (int i = 1;i < N;i++)
		{
			List->Table[i].OneIndexBlock++;
			List->Table[i].NumberBlock++;
		}
	}
	else
	{
		for (int i = One->Count;i != 0;i--)
		{
			One->value[i] = One->value[i - 1];
		}
		One->value[0] = primer;
		One->Count++;
		for (int i = 1;i < N;i++)
			List->Table[i].OneIndexBlock++;
	}
	List->SizeElement++;
	ControlElementData(List);
}

void outup(struct BlockList *List)
{
	BlockNode *ptr = List->pBegin;
	if (ptr == NULL) cout << "Пусто.\n";
	int j = 0;
	while (ptr != NULL)
	{
		cout << "[" << j + 1 << "] ";
		for (int i = 0;i < ptr->Count;i++)
		{
			cout << ptr->value[i].kod;
			cout << " |" << ptr->value[i].name[0] << "|" << "\t";
		}
		ptr = ptr->pNext;
		j++;
		cout << endl;
	}
	cout << endl << "Количество элементов: " << List->SizeElement << endl;
	cout << "Количество блоков: " << List->Size << endl;
	cout << "№block" << "\t" << "index" <<"\t" << "element" << endl;
	for (int i = 0;i < N && List->Table[i].pElement!=NULL;i++)
		cout << "  " << List->Table[i].NumberBlock << "\t " << List->Table[i].OneIndexBlock << "\t  " << List->Table[i].pElement->value[0].kod << endl;
}
