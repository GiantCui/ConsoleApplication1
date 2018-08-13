#pragma once
#include<iostream>
#include"util.h"
#include<assert.h>

using namespace std;

struct Trituple {	//自定义数据结构：矩阵元素的行，列，值
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

class SpareseMatrix {	//稀疏矩阵
private:
	int rows, cols, terms;	//行数，列数，非零元素个数
	Trituple *smArray;		//存非零元素的三元数组
	int maxTerms;			//三元组最大可容纳的元素个数
};

