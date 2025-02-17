#ifndef WORKING_WITH_BUFFER_H
#define WORKING_WITH_BUFFER_H

#include <mutex>
#include <thread>
#include <condition_variable>

#include "conn_linux_socket.h"


class working_with_buffer
{
public:
	working_with_buffer() = default;
	void processString()
	{
		while (true)
		{
			std::string input;
			// Добавлено ради последуемости вывода команд)
    		std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Enter text (letters only, max 64 characters): ";
			std::cin >> input;
			
			if (checking_conditions(input))
			{
				std::map<char, int> characters_count;
				for (char i : input) 
				{
					characters_count[i]++;
				}	

				{
					std::lock_guard<std::mutex> lock(buffer_mutex);
					shared_buffer = characters_count;
					data_ready = true;
				}

				cv.notify_one();
			}
		}
	}


	void processData() 
	{
		while (true) 
		{
			std::unique_lock<std::mutex> lock(buffer_mutex);
			cv.wait(lock, [this]{return data_ready;}); 
			
			std::cout << "Data processing: \n";

			for (const auto& pair : shared_buffer) {
				std::cout << "'" << pair.first << "' occurs " << pair.second << " times\n";
			}

			// send buffer to server(proga_2)
			client.sendMessage(shared_buffer);

			shared_buffer.clear();
			data_ready = false;
		}
	}

private:
	bool checking_conditions(const std::string& input_func)
	{
		if (input_func.length() <= 64)
		{
			bool check_to_alpha = true;
			for (char i : input_func)
			{
				if (!std::isalpha(i))
				{
					check_to_alpha = false;
					break;
				}
			}

			if (!check_to_alpha)
			{
				std::cout << "Error: string must contain only letters!" << std::endl;
				return false;
			}
			else { return true; }
		}
		else 
		{ 
			std::cout << "Error: line exceeds 64 characters!" << std::endl;
			return false;
		}

	}

private:
	SocketClient client;
	std::map<char, int> shared_buffer;
	std::mutex buffer_mutex;           
	std::condition_variable cv;        
	std::string input;
	bool data_ready = false;
};


#endif // !WORKING_WITH_BUFFER_H