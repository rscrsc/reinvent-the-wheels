#ifndef HPP_DATAFETCHER
#define HPP_DATAFETCHER

#include<string>
#include<curl/curl.h>
#include<fstream>
#include<fmt/core.h>

// For logging
// TODO: use adv. logging libs when needed
#define LOG_INFO printf

namespace data_fetcher
{

static constexpr char DATA_DIR[] = "../data";

std::string inline getBasename(const std::string& url){
	size_t lastSplashPos = url.find_last_of('/');
	if(lastSplashPos != std::string::npos){
		return url.substr(lastSplashPos + 1);
	}else{
		return url;
	}
}

// Callback function to write data to a file
size_t WriteCallback(void* contents, size_t size, size_t nmemb, 
  std::ofstream* userp) {
    size_t totalSize = size * nmemb;
    userp->write(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string inline download_url(const std::string& url){
	const std::string outFilename = getBasename(url);
	const std::string outFileRelPath = 
	  fmt::format("{}/{}", DATA_DIR, outFilename);
	
	// Initialize cURL
	CURL* curl = curl_easy_init();
	if(curl) {
		std::ofstream file(outFileRelPath, std::ios::binary);
		if (!file.is_open()) {
			std::cerr << "Failed to open file for writing: " << outFileRelPath << std::endl;
			exit(1);
		}

		// Set up the cURL options
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L); // Fail on HTTP error

		// Perform the request
		CURLcode res = curl_easy_perform(curl);

		// Check for errors
		if (res != CURLE_OK) {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		}

		// Clean up
		file.close();
		curl_easy_cleanup(curl);
	} else {
		std::cerr << "Failed to initialize cURL" << std::endl;
		exit(1);
	}

	LOG_INFO("[INFO] Downloaded data file `%s` at `%s`\n", outFilename.c_str(), DATA_DIR);
	return outFilename;
}
}
#endif
