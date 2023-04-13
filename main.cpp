#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <gflags/gflags.h>
#include <string>
#include <sstream>
#include <fstream>

DEFINE_string(input, "", "Path to the text file of the URL described by newline characters.");

std::atomic<int> progress(0);  // 進捗状況

std::string read_list(){
    
}

std::vector<std::string> get_URL_list(std::string input_string){
    std::stringstream ss(input_string);
    std::string line;
    std::vector<std::string> string_vector;
    while (std::getline(ss, line)) {  // 改行区切りで一行ずつ読み込む
        string_vector.push_back(line);
    }

    return string_vector;
}

void download_files(const std::vector<std::string>& urls) {
    for (const auto& url : urls) {
        check_url(url);
        ++progress;  // 進捗状況を更新
    }
}

void display_progress_bar(int total) {
    const int bar_width = 40;
    std::cout << "[";
    int pos = 0;
    while (pos < bar_width) {
        const int progress_val = progress.load();
        const float progress_ratio = static_cast<float>(progress_val) / total;
        const int bar_pos = static_cast<int>(progress_ratio * bar_width);
        while (pos < bar_pos) {
            std::cout << "=";
            ++pos;
        }
        if (pos < bar_width) {
            std::cout << ">";
            ++pos;
        }
        std::cout << " ";
    }
    std::cout << "] " << progress << "/" << total << " (" << progress_ratio * 100 << "%)\r";
    std::cout.flush();
}

int main() {
    std::vector<std::string> myList = {...};  // myListの初期化
    const int num_threads = 4;  // スレッド数
    const int group_size = myList.size() / num_threads;  // グループのサイズ

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        const auto begin = myList.begin() + i * group_size;
        const auto end = (i == num_threads - 1) ? myList.end() : begin + group_size;
        threads.emplace_back(download_files, std::vector<std::string>(begin, end));
    }

    const int total = myList.size();
    while (progress.load() < total) {
        display_progress_bar(total);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    display_progress_bar(total);
    std::cout << std::endl;

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
