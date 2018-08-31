//#include 

#include <vector>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

namespace Fw {

class ImagesKeeper {
public:
	ImagesKeeper(const std::string& pathToImages) {
	}
	;
	ImagesKeeper() = delete;

private:

	std::vector<cv::Mat> m_images;

};

class FileReader {

public:
	explicit FileReader(const std::string&& pathToFile) :
			m_pathToFile(pathToFile) {
		openFile();
		readContent();
	}
	~FileReader() {
		closeFile();
	}

	const std::vector<std::string> getContent() const {
		return m_content;
	}

private:
	void readContent() {
		std::string line;
		while (std::getline(m_file, line)) {
			m_content.push_back(line);
		}
	}
	void openFile() {
		if (doesFileExist(m_pathToFile)) {
			m_file.open(m_pathToFile);
		}
	}
	void closeFile() {
		m_file.close();
	}
	const bool doesFileExist(const std::string& name) const {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}
	std::ifstream m_file;
	const std::string m_pathToFile;
	std::vector<std::string> m_content;
};

class FolderReader {
public:
	explicit FolderReader(const std::string& pathToFolder) {
		if (openFolder(pathToFolder)) {
			readFolder();
		}
	}

	~FolderReader() {
		closeFolder();
	}
	const std::vector<std::string> getContent() {
		return m_filesInFolder;
	}
private:
	bool openFolder(const std::string& pathToFolder) {
		m_directory = opendir(pathToFolder.c_str());
		if (m_directory == nullptr) {
			std::cout << "Directory " << pathToFolder <<" not found \n";
			exit(1);
			return false;
		}
		return true;
	}

	void readFolder() {
		while ((m_ent = readdir(m_directory))) {
			if (m_ent == nullptr) {
				std::cout << "pent Problem";
				exit(2);
			}
			// found true image (eg. no hidden files)
			if (m_ent->d_namlen > 9) {
				m_filesInFolder.push_back(m_ent->d_name);
			}
		}

	}

	void closeFolder() {
		closedir(m_directory);
	}

	DIR* m_directory { nullptr };
	struct dirent* m_ent { nullptr };
	std::vector<std::string> m_filesInFolder;
};

//std::vector<cv::Mat>
void fillImageVectorFromPath(const std::string& path) {
//   using namespace cv;
//
//   Mat image;
//
//   image = imread(path);

}

} // End of Namespace Fw
