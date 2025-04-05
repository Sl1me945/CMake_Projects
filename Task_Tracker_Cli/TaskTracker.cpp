#include "TaskTracker.h"


void TaskTracker::addTask(const std::string& description)
{
	Task task(description);
	tasks.push_back(task);
	std::cout << "Task added: " << task << std::endl;
}

void TaskTracker::updateTask(int id, const std::string& description)
{
	for (auto& task : tasks) {
		if (task.getId() == id) {
			task.setDescription(description);
			std::cout << "Task updated: " << task << std::endl;
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

	std::cout << "All tasks:" << std::endl;
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

	std::cout << "Tasks with status " << statusToString(status) << ":" << std::endl;
	for (const auto& task : tasks) {
		if (task.getStatus() == status) {
			std::cout << task << std::endl;
		}
	}
}

// Compare this snippet from Task_Tracker_Cli/task_utils.h: