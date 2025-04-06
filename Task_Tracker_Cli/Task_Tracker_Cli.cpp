#include "Task_Tracker_Cli.h"


int main()
{
	TaskTracker taskTracker;
	do {
		std::string command;
		std::cout << "Enter command (add, update, delete, list, exit, save, load): ";
		std::cin >> command;
		if (command == "add") {
			std::string description;
			std::cout << "Enter task description: ";
			std::cin.ignore();
			std::getline(std::cin, description);
			taskTracker.addTask(description);
		}
		else if (command == "update") {
			int id;
			std::string description;
			std::cout << "Enter task ID to update: ";
			std::cin >> id;
			std::cout << "Enter new task description: ";
			std::cin.ignore();
			std::getline(std::cin, description);
			taskTracker.updateTask(id, description);
		}
		else if (command == "delete") {
			int id;
			std::cout << "Enter task ID to delete: ";
			std::cin >> id;
			taskTracker.deleteTask(id);
		}
		else if (command == "list") {
			TaskStatus status;
			std::string statusStr;
			std::cout << "Enter task status to list (ToDo, InProgress, Done or All): ";
			std::cin >> statusStr;
			if (statusStr == "All") {
				taskTracker.listAllTasks();
				continue;
			}
			status = stringToStatus(statusStr);
			taskTracker.listTasksByStatus(status);
		}
		else if (command == "save") {
			std::string filename;
			std::cout << "Enter filename to save tasks: ";
			std::cin >> filename;
			taskTracker.saveTasksToJson(filename);
		}
		else if (command == "load") {
			std::string filename;
			std::cout << "Enter filename to load tasks: ";
			std::cin >> filename;
			taskTracker.loadTasksFromJson(filename);
		}
		else if (command == "exit") {
			break;
		}
		else {
			std::cerr << "Unknown command." << std::endl;
		}
	} while (true);

	return 0;
}