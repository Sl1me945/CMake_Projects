#pragma once
#include <vector>
#include <fstream>
#include "task_utils.h"


class TaskTracker {
public:
	void addTask(const std::string& description);
	void updateTask(int id, const std::string& description);
	void deleteTask(int id);
	void updateTaskStatus(int id, TaskStatus status);
	void listAllTasks() const;
	void listTasksByStatus(const TaskStatus& status) const;
	void saveTasksToJson(const std::string& filename) const;
	void loadTasksFromJson(const std::string& filename);
private:
	std::vector<Task> tasks;
};