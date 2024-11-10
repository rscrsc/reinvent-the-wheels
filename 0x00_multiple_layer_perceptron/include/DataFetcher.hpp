#ifndef HPP_DATAFETCHER
#define HPP_DATAFETCHER

#include <string>

class DataFetcherException : public std::runtime_error {
public:
	explicit DataFetcherException(const std::string& message) : std::runtime_error(message) {}
};

class DataFetcher
{
private:

static constexpr char DATA_DIR[] = "../data";
static std::string getBasename (const std::string& url);
static size_t mWriteCallback (void* contents, size_t size, size_t nmemb, 
  std::ofstream* userp); // Callback function to write data to a file

public:

static std::string downloadURL (const std::string& url);
DataFetcher() = delete;
};
#endif
