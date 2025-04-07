#include "TaskTracker.h"


void TaskTracker::addTask(const std::string& description)
{
	Task task(description);
	tasks.push_back(task);
	std::cout << "======Task added======" << std::endl 
		<< task << std::endl;
}

void TaskTracker::updateTask(int id, const std::string& description)
{
	for (auto& task : tasks) {
		if (task.getId() == id) {
			task.setDescription(description);
			std::cout << "======Updated======" << std::endl 
				<< task << std::endl;
			return;
		}
	}
	std::cerr << "Task with ID " << id << " not found." << std::endl;
}

void TaskTracker::deleteTask(int id)
{
	auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
		return task.getId() == id;
		});
	if (it != tasks.end()) {
		tasks.erase(it, tasks.end());
		std::cout << "Task with ID " << id << " deleted." << std::endl;
	}
	else {
		std::cerr << "Task with ID " << id << " not found." << std::endl;
	}
}

void TaskTracker::updateTaskStatus(int id, TaskStatus status)
{
	for (auto& task : tasks) {
		if (task.getId() == id) {
			task.setStatus(status);
			std::cout << "Task status updated: " << task << std::endl;
			return;
		}
	}
	std::cerr << "Task with ID " << id << " not found." << std::endl;
}

void TaskTracker::listAllTasks() const
{
	if (tasks.empty()) {
		std::cout << "No tasks available." << std::endl;
		return;
	}

	std::cout << "======All tasks======" << std::endl;
	for (const auto& task : tasks) {
		std::cout << task << std::endl;
	}
}

void TaskTracker::listTasksByStatus(const TaskStatus& status) const
{

	if (tasks.empty()) {
		std::cout << "No tasks available." << std::endl;
		return;
	}

	std::cout << "======Tasks with status " << statusToString(status) << "=====" << std::endl;
	for (const auto& task : tasks) {
		if (task.getStatus() == status) {
			std::cout << task << std::endl;
		}
	}
}

void TaskTracker::saveTasksToJson(const std::string& filename) const
{
	std::ofstream file(filename + ".json");
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}
	file << "[\n";
	for (size_t i = 0; i < tasks.size(); ++i) {
		file << taskToJson(tasks[i]);
		if (i != tasks.size() - 1) {
			file << ",\n";
		}
	}
	file << "\n]\n";
	file.close();
	std::cout << "Tasks saved to " << filename << std::endl;
}

void TaskTracker::loadTasksFromJson(const std::string& filename)
{
	std::ifstream file(filename + ".json");
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}

	std::string line, buffer;
	while (std::getline(file, line)) {
		buffer += line;
	}
	file.close();

	size_t pos = 0;
	while ((pos = buffer.find("{", pos)) != std::string::npos) {
		auto end = buffer.find("}", pos);
		if (end == std::string::npos) break;
		std::string jsonEntry = buffer.substr(pos, end - pos + 1);
		tasks.push_back(jsonToTask(jsonEntry));
		pos = end + 1;
	}
	Task::setNextId(tasks.back().getId() + 1);

}


// Compare this snippet from Task_Tracker_Cli/task_utils.h: