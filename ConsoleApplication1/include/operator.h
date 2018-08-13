#pragma once
#include<iostream>
#include"ratings.h"
#include<math.h>

using namespace std;

const int num_user = 943;
const int num_item = 1682;
double globalmean(const std::vector<rating>& ratings)
{
	double sum = 0;
	for (vector<rating>::const_iterator it = ratings.begin(); it != ratings.end(); ++it)
		sum += it->score;
	return sum / ratings.size();
}

double RMSE_GlobalMean(const std::vector<rating>& ratings, double mean)
{
	double sum = 0.0;
	for (vector<rating>::const_iterator it = ratings.begin(); it != ratings.end(); ++it) {
		double error = it->score - mean;
		sum += error * error; // pow(it->score - mean, 2);
	}
		
	return sqrt(sum / ratings.size());
}

double MAE_GlobalMean(const std::vector<rating>& ratings, double mean)
{
	double sum = 0;
	for (vector<rating>::const_iterator it = ratings.begin(); it != ratings.end(); ++it) {
		sum += abs(it->score - mean);
	}	
	return sum / ratings.size();
}

class user {
public:
	double sscore;
	double count;
	user(double sscore = 0, double count = 0) {
		this->sscore = sscore;
		this->count = count;
	}
};

void users_mean(const std::vector<rating>& base_ratings, vector<user>& users)
{
	for (vector<rating>::const_iterator it = base_ratings.begin(); it != base_ratings.end(); ++it) {
		users[it->user_id].sscore += it->score;
		users[it->user_id].count++;
	}
}

void item_mean(const std::vector<rating>& base_ratings, vector<user>& users)
{
	for (vector<rating>::const_iterator it = base_ratings.begin(); it != base_ratings.end(); ++it) {
		users[it->item_id].sscore += it->score;
		users[it->item_id].count++;
	}
}

double MAE_UserMean(const std::vector<rating>& test_ratings, const std::vector<rating>& base_ratings, double global)
{
	vector<user> users(num_user);	
	users_mean(base_ratings, users);
	
	double usermean = 0;
	double error = 0;
	double aerr = 0;
	for (vector<rating>::const_iterator it = test_ratings.begin(); it != test_ratings.end(); ++it) {
		if (users[it->user_id].count == 0)
			usermean = global;
		else
			usermean = users[it->user_id].sscore / users[it->user_id].count;
		error = abs(it->score - usermean);
		aerr += error;		
	}
	
	return aerr / test_ratings.size();
}

double RMSE_UserMean(const std::vector<rating>& test_ratings, const std::vector<rating>& base_ratings, double global)
{
	vector<user> users(num_user);
	users_mean(base_ratings, users);

	double usermean = 0;
	double error = 0;
	double aerr = 0;
	for (vector<rating>::const_iterator it = test_ratings.begin(); it != test_ratings.end(); ++it) {	
		if (users[it->user_id].count == 0)
			usermean = global;
		else
			usermean = users[it->user_id].sscore / users[it->user_id].count;
		error = abs(it->score - usermean);
		aerr += error * error;
	}

	return sqrt(aerr / test_ratings.size());
}

double RMSE_ItemMean(const std::vector<rating>& test_ratings, const std::vector<rating>& base_ratings, double global)
{
	vector<user> users(num_item);

	item_mean(base_ratings, users);

	double usermean = 0;
	double error = 0;
	double aerr = 0;
	for (vector<rating>::const_iterator it = test_ratings.begin(); it != test_ratings.end(); ++it) {		
		if (users[it->item_id].count == 0)
			usermean = global;
		else
			usermean = users[it->item_id].sscore / users[it->item_id].count;
		error = abs(it->score - usermean);
		aerr += error * error;
		//cout << usermean << '\t' << error << '\t' << aerr << endl;
	}

	return sqrt(aerr / test_ratings.size());
}

double MAE_ItemMean(const std::vector<rating>& test_ratings, const std::vector<rating>& base_ratings, double global)
{
	vector<user> users(num_item);

	item_mean(base_ratings, users);

	double usermean = 0;
	double error = 0;
	double aerr = 0;
	for (vector<rating>::const_iterator it = test_ratings.begin(); it != test_ratings.end(); ++it) {
		if (users[it->item_id].count == 0)
			usermean = global;
		else
			usermean = users[it->item_id].sscore / users[it->item_id].count;
		error = abs(it->score - usermean);
		aerr += error;
	}

	return aerr / test_ratings.size();
}