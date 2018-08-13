#pragma once

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

#include"ratings.h"



string trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),���ַ���str�д�����0��ʼ�������״β�ƥ��"\t\r\n"��λ��
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}


void get_ratings(const std::string& file_name, std::vector<rating>& ratings)
{
	ifstream fin(file_name); //���ļ�������
	string line;
	while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
	{
		// cout << "ԭʼ�ַ�����" << line << endl; //�������
		line = trim(line);
		istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
		vector<string> fields; //����һ���ַ�������
		string field;
		while (getline(sin, field, '\t')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
		{
			fields.push_back(field); //���ոն�ȡ���ַ�����ӵ�����fields��
		}

		if (fields.size() == 4)
		{
			int user_id = std::stoi(trim(fields[0])); //���������fields�е�һ��Ԫ�ص���Ч�ַ�������ֵ������name
			int item_id = std::stoi(trim(fields[1])); //���������fields�еڶ���Ԫ�ص���Ч�ַ�������ֵ������age
			double score = std::stof(trim(fields[2])); //���������fields�е�����Ԫ�ص���Ч�ַ�������ֵ������birthday
			string timestamp = trim(fields[3]);
			ratings.push_back(rating(user_id, item_id, score, timestamp));
		}
	}
}

void write_ratings(const std::string& to_file, std::vector<rating>& ratings)
{
	ofstream of(to_file);
	for (vector<rating>::iterator it = ratings.begin(); it != ratings.end(); ++it) {
		of << it->user_id << "\t" << it->item_id << "\t" << it->score << "\t" << it->timestamp << "\n";
	}
}


void split_ratings(const std::vector<rating>& ratings, std::vector<rating>& base_ratings, std::vector<rating>& test_ratings, double test_size = 0.2)
{
	for (vector<rating>::const_iterator it = ratings.begin(); it != ratings.end(); ++it)
	{
		double ran = rand() % 10 / 10.0;
		if (ran < test_size)
			test_ratings.push_back(rating(it->user_id, it->item_id, it->score, it->timestamp));
		else
			base_ratings.push_back(rating(it->user_id, it->item_id, it->score, it->timestamp));
	}
}