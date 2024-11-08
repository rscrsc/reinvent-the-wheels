#include <iostream>
#include "data_fetcher.hpp"

int main(){
	static constexpr char urlTrain[] = "http://d2l-data.s3-accelerate.amazonaws.com/kaggle_house_pred_train.csv";
	static constexpr char urlTest[] = "http://d2l-data.s3-accelerate.amazonaws.com/kaggle_house_pred_test.csv";
	const std::string dataFilenameTrain = data_fetcher::download_url(urlTrain);
	const std::string dataFilenameTest = data_fetcher::download_url(urlTest);
	return 0;
}
