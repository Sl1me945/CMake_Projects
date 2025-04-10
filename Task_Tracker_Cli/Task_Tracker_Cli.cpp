#include "Task_Tracker_Cli.h"

void printHelp();

int main(int argc, char* argv[]) {
    TaskTracker taskTracker;
    std::string filename{ "tasks" };

    try {
        taskTracker.loadTasksFromJson(filename);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load tasks: " << e.what() << std::endl;

        auto createNewTaskFile = [&]() -> bool {
            std::cout << "Creating new task file." << std::endl;
            try {
                taskTracker.saveTasksToJson(filename);
                return true;
            }
            catch (const std::exception& saveError) {
                std::cerr << "Error saving tasks: " << saveError.what() << std::endl;
                return false;
            }
            };

        if (!createNewTaskFile()) {
            return 1;
        }
        return 0; // або можеш return 0, якщо це не критична помилка
    }



    if (argc < 2) {
        std::cerr << "No command provided. Use --help to see usage" << std::endl;
        return 1;
    }

    std::string command = argv[1];

	if (command == "--help") {
		printHelp();
		return 0;
	}
    else if (command == "add") {
        if (argc < 3) {
            std::cerr << "Usage: add <description>" << std::endl;
            return 1;
        }
        std::string description = argv[2];
        for (int i = 3; i < argc; ++i) {
            description += " ";
            description += argv[i];
        }
        taskTracker.addTask(description);
    }
    else if (command == "update") {
        if (argc < 4) {
            std::cerr << "Usage: update <id> <new_description>" << std::endl;
            return 1;
        }
        int id = std::stoi(argv[2]);
        std::string description = argv[3];
        for (int i = 4; i < argc; ++i) {
            description += " ";
            description += argv[i];
        }
        taskTracker.updateTask(id, description);
    }
    else if (command == "delete") {
        if (argc < 3) {
            std::cerr << "Usage: delete <id>" << std::endl;
            return 1;
        }
        int id = std::stoi(argv[2]);
        taskTracker.deleteTask(id);
    }
    else if(command == "mark") {
		if (argc < 4) {
			std::cerr << "Usage: mark <id> <status>" << std::endl;
			return 1;
		}
		int id = std::stoi(argv[2]);
		std::string statusStr = argv[3];
		try {
			TaskStatus status = stringToStatus(statusStr);
			taskTracker.updateTaskStatus(id, status);
		}
		catch (const std::exception& e) {
			std::cerr << "Invalid status: " << e.what() << std::endl;
			return 1;
		}
    }
    else if (command == "list") {
        if (argc == 2) {
            taskTracker.listAllTasks();
            return 0;
        }
        else {
            std::string statusStr = argv[2];
            try {
                TaskStatus status = stringToStatus(statusStr);
                taskTracker.listTasksByStatus(status);
				return 0;
            }
            catch (const std::exception& e) {
                std::cerr << "Invalid status: " << e.what() << std::endl;
                return 1;
            }
        }
    }
    else {
        std::cerr << "Unknown command. Use --help to see available commands.\n";
        return 1;
    }

    taskTracker.saveTasksToJson(filename);

    return 0;
}

void printHelp() {
    std::cout << "Available commands:\n"
        << "  add <description>          Add a new task\n"
        << "  update <id> <description>  Update a task\n"
        << "  delete <id>                Delete a task\n"
        << "  mark <id> <status>         Mark a task as ToDo, InProgress, or Done\n"
        << "  list [status]              List all tasks or tasks by status\n"
        << "  --help                     Show this help message\n";
}