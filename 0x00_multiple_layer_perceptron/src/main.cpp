#include <iostream>
#include "DataFetcher.hpp"

int main(){
	static constexpr char urlTrain[] = "http://d2l-data.s3-accelerate.amazonaws.com/kaggle_house_pred_train.csv";
	static constexpr char urlTest[] = "http://d2l-data.s3-accelerate.amazonaws.com/kaggle_house_pred_test.csv";
	try {
		const std::string dataFilenameTrain = DataFetcher::downloadURL(urlTrain);
		const std::string dataFilenameTest = DataFetcher::downloadURL(urlTest);
	} catch(DataFetcherException& e) {
		std::cerr << "[ERROR] DataFetcher Error: " << e.what() << std::endl;
		return 1;
	} catch(std::exception& e) {
		std::cerr << "[ERROR] Unknown Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
