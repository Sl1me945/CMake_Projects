#pragma once
#include <string>
#include <iostream>
#include "Task.h"

// Function to convert TaskStatus enum to string
inline TaskStatus stringToStatus(const std::string& statusStr) {
	if (statusStr == "ToDo") {
		return TaskStatus::ToDo;
	}
	else if (statusStr == "InProgress") {
		return TaskStatus::InProgress;
	}
	else if (statusStr == "Done") {
		return TaskStatus::Done;
	}
	else {
		throw std::invalid_argument("Invalid task status string");
	}
}
inline std::string statusToString(const TaskStatus& status) {
	switch (status) {
	case TaskStatus::ToDo:
		return "To Do";
	case TaskStatus::InProgress:
		return "In Progress";
	case TaskStatus::Done:
		return "Done";
	default:
		throw std::invalid_argument("Invalid task status");
	}
}
inline std::ostream& operator<<(std::ostream& os, const TaskStatus& status) {
	os << statusToString(status);
	return os;
}

// Function to convert a time_point to a string
inline std::string timePointToString(const std::chrono::system_clock::time_point& timePoint) {
	auto timeT = std::chrono::system_clock::to_time_t(timePoint);
	auto tm = *std::localtime(&timeT);
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
	return std::string(buffer);
}
inline std::ostream& operator<<(std::ostream& os, const std::chrono::system_clock::time_point& timePoint) {
	os << timePointToString(timePoint);
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const Task& task) {
	os << "Task ID: " << task.getId() << "\n"
		<< "Description: " << task.getDescription() << ", "
		<< "Status: " << task.getStatus() << "\n"
		<< "Created At: " << task.getCreatedAt() << "\n"
		<< "Updated At: " << task.getUpdatedAt() << "\n";
	return os;
}