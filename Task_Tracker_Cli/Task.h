#pragma once
#include <string>
#include <chrono>
#include <array>

enum class TaskStatus {
	ToDo,
	InProgress,
	Done
};

// Task class to represent a task in the task tracker
class Task {
public:
	// Constructor to initialize a task with a description and status
	Task(const std::string& description)
		: id(nextId++), description(description), status(TaskStatus::ToDo),
		createdAt(std::chrono::system_clock::now()), updatedAt(std::chrono::system_clock::now()) {
	}

	// Getters for task properties
	int getId() const { return id; }
	const std::string& getDescription() const { return description; }
	TaskStatus getStatus() const { return status; }
	std::chrono::system_clock::time_point getCreatedAt() const { return createdAt; }
	std::chrono::system_clock::time_point getUpdatedAt() const { return updatedAt; }

	// Setters for task properties
	void setDescription(const std::string& newDescription) {
		description = newDescription;
		updatedAt = std::chrono::system_clock::now();
	}
	void setStatus(TaskStatus newStatus) {
		status = newStatus;
		updatedAt = std::chrono::system_clock::now();
	}

private:
	static int nextId; // Static member to keep track of the next ID
	int id;
	std::string description;
	TaskStatus status;
	std::chrono::system_clock::time_point createdAt;
	std::chrono::system_clock::time_point updatedAt;
};

inline int Task::nextId = 1; // Initialize static member variable