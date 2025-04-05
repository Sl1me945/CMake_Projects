#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include "Task.h"
#include "task_utils.h"


class TaskTracker {
public:
	TaskTracker() = default;
	void addTask(const std::string& description);
	void updateTask(int id, const std::string& description);
	void deleteTask(int id);
	void updateTaskStatus(int id, TaskStatus status);
	void listAllTasks() const;
	void listTasksByStatus(const TaskStatus& status) const;
private:
	std::vector<Task> tasks;
};