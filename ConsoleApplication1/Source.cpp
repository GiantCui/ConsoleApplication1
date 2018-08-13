#include"include\data_utility.h"
#include<vector>
#include"include\operator.h"

int main()
{
	vector<rating> ratings;
	vector<rating> base_ratings;
	vector<rating> test_ratings;
	
	//get_ratings("D:\\codes\\ml-100k\\u.data", ratings);
	get_ratings("D:\\codes\\ml-100k\\u5.test", test_ratings);
	get_ratings("D:\\codes\\ml-100k\\u5.base", base_ratings);

	//cout << ratings.size() << endl;
	//split_ratings(ratings, base_ratings, test_ratings);

	double base_mean = globalmean(base_ratings);
	//double test_mean = globalmean(test_ratings);
	cout << "base_ratings_globalmean:" << base_mean << endl;
	//cout << "test_ratings_globalmean:" << test_mean << endl;

	double a = RMSE_ItemMean(test_ratings, base_ratings, base_mean);
	double b = MAE_ItemMean(test_ratings, base_ratings, base_mean);
	cout << "RMSE:" << a << "\t" 
		<< "MAE:" << b;
	return 0;
}