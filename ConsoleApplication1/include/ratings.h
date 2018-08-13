#pragma once
#include<string>

using namespace std;
#include"util.h"

class rating
{
public:
	uint user_id;
	uint item_id;
	double score;
	string timestamp;

	rating(uint uid = 0, uint iid = 0, double score = 0, string timestamp = "") {
		user_id = uid;
		item_id = iid;
		this->score = score;
		this->timestamp = timestamp;
	}
};