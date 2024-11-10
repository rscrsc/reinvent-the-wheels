#include <iostream>
#include "DataFetcher.hpp"

int main(){
	static constexpr char urlTrain[] = "http://d2l-data.s3-accelerate.amazonaws.com/kaggle_house_pred_train.csv";
	static constexpr char urlTest[] = "http://d2l-data.s3-accelerate.amazonaws.com/kaggle_house_pred_test.csv";
	const std::string dataFilenameTrain = DataFetcher::downloadURL(urlTrain);
	const std::string dataFilenameTest = DataFetcher::downloadURL(urlTest);
	return 0;
}
