#pragma once

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

#include"ratings.h"



string trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}


void get_ratings(const std::string& file_name, std::vector<rating>& ratings)
{
	ifstream fin(file_name); //打开文件流操作
	string line;
	while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
	{
		// cout << "原始字符串：" << line << endl; //整行输出
		line = trim(line);
		istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
		vector<string> fields; //声明一个字符串向量
		string field;
		while (getline(sin, field, '\t')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
		{
			fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
		}

		if (fields.size() == 4)
		{
			int user_id = std::stoi(trim(fields[0])); //清除掉向量fields中第一个元素的无效字符，并赋值给变量name
			int item_id = std::stoi(trim(fields[1])); //清除掉向量fields中第二个元素的无效字符，并赋值给变量age
			double score = std::stof(trim(fields[2])); //清除掉向量fields中第三个元素的无效字符，并赋值给变量birthday
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