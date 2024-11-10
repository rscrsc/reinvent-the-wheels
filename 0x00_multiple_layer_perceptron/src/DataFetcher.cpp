#include "DataFetcher.hpp"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include <fmt/core.h>
#include <stdexcept>

// For logging
// TODO: use adv. logging libs when needed
#define LOG_INFO printf

constexpr char DataFetcher::DATA_DIR[];

inline
std::string DataFetcher::getBasename(const std::string& url){
	size_t lastSplashPos = url.find_last_of('/');
	if(lastSplashPos != std::string::npos){
		return url.substr(lastSplashPos + 1);
	}else{
		return url;
	}
}

size_t DataFetcher::mWriteCallback(void* contents, size_t size, size_t nmemb, 
  std::ofstream* userp){
    size_t totalSize = size * nmemb;
    userp->write(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string DataFetcher::downloadURL(const std::string& url){
	const std::string outFilename = getBasename(url);
	const std::string outFileRelPath = 
	  fmt::format("{}/{}", DATA_DIR, outFilename);
	
	// Initialize cURL
	CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
	if(res != 0) {
		throw DataFetcherException("Failed to initialize cURL");
	}
	CURL* curl = curl_easy_init();
	if(!curl) {
		throw DataFetcherException("Failed to initialize cURL");
	}
	try {
		std::ofstream file(outFileRelPath, std::ios::binary);
		if (!file.is_open()) {
			throw DataFetcherException(
			  fmt::format("Failed to open file for writing: {}", outFileRelPath)
			);
		}

		// Set up the cURL options
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, mWriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L); // Fail on HTTP error

		// Perform the request
		CURLcode res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			throw DataFetcherException(
			  fmt::format("curl_easy_perform() failed: {}", curl_easy_strerror(res))
			);
		}

		file.close();
	} catch(DataFetcherException& e) {
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		throw;
	}

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	LOG_INFO("[INFO] Downloaded data file `%s` at `%s`\n", outFilename.c_str(), DATA_DIR);

	return outFilename;
}
