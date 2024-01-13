#ifndef BEHINDSERVER_HPP
#define BEHINDSERVER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <sstream>

class HTMLFile {
public:
    HTMLFile(const std::string& filePath) : filePath(filePath) {}

    void read() {
        std::ifstream fileStream(filePath);
        if (!fileStream) {
            throw std::runtime_error("Cannot open file: " + filePath);
        }
        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        content = buffer.str();
    }

    void modify(const std::string& tag, const std::string& newValue) {
        std::string startTag = "<" + tag + ">";
        std::string endTag = "</" + tag + ">";
        std::size_t startPos = content.find(startTag);
        std::size_t endPos = content.find(endTag);

        if (startPos != std::string::npos && endPos != std::string::npos) {
            startPos += startTag.length();
            content.replace(startPos, endPos - startPos, newValue);
        }
    }

    void save(const std::string& newFilePath) {
        std::ofstream fileStream(newFilePath);
        if (!fileStream) {
            throw std::runtime_error("Cannot open file: " + newFilePath);
        }
        fileStream << content;
    }

    static void newFile(const std::string& content, const std::string& filename) {
        std::ofstream fileStream(filename);
        if (!fileStream) {
            throw std::runtime_error("Cannot create file: " + filename);
        }
        fileStream << content;
    }

private:
    std::string filePath;
    std::string content;
};

#endif // BEHINDSERVER_HPP
