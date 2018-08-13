#pragma once
#include<iostream>
#include"util.h"
#include<assert.h>

using namespace std;

struct Trituple {	//�Զ������ݽṹ������Ԫ�ص��У��У�ֵ
	uint row;
	uint col;
	double value;
	Trituple& operator = (Trituple& x) {
		row = x.row;
		col = x.col;
		value = x.value;
		return *this;
	}
};

const int DefaultSize = 100;

class SpareseMatrix {	//ϡ�����
private:
	int rows, cols, terms;	//����������������Ԫ�ظ���
	Trituple *smArray;		//�����Ԫ�ص���Ԫ����
	int maxTerms;			//��Ԫ���������ɵ�Ԫ�ظ���
};

