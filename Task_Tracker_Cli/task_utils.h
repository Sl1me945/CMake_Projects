#pragma once
#include <iostream>
#include "Task.h"

// Function with TaskStatus
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
		throw std::invalid_argument("Invalid task status");
	}
}
inline std::string statusToString(const TaskStatus& status) {
	switch (status) {
	case TaskStatus::ToDo:
		return "ToDo";
	case TaskStatus::InProgress:
		return "InProgress";
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

// Functions with time_point
inline std::string timePointToString(const std::chrono::system_clock::time_point& timePoint) {
	auto timeT = std::chrono::system_clock::to_time_t(timePoint);
	std::tm tm = *std::gmtime(&timeT);  // <-- зміна тут
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}
inline std::chrono::system_clock::time_point stringToTimePoint(const std::string& timeStr) {
	std::tm tm = {};
	std::istringstream iss(timeStr);
	iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	if (iss.fail()) {
		throw std::invalid_argument("Invalid time format");
	}
#if defined(_WIN32)
	// Windows doesn't have timegm, so we simulate it
	_putenv_s("TZ", "UTC");
	_tzset();
	time_t timeT = std::mktime(&tm);
	_putenv_s("TZ", "");
	_tzset();
#else
	time_t timeT = timegm(&tm); // Linux/Mac
#endif
	return std::chrono::system_clock::from_time_t(timeT);
}

inline std::ostream& operator<<(std::ostream& os, const std::chrono::system_clock::time_point& timePoint) {
	os << timePointToString(timePoint);
	return os;
}

// Overload the << operator for Task class
inline std::ostream& operator<<(std::ostream& os, const Task& task) {
	os << "Task ID: " << task.getId() << "\n"
		<< "Description: " << task.getDescription() << ", "
		<< "Status: " << task.getStatus() << "\n"
		<< "Created At: " << task.getCreatedAt() << "\n"
		<< "Updated At: " << task.getUpdatedAt() << "\n";
	return os;
}

// Function with json
inline std::string taskToJson(const Task& task) {
	return "{ \"id\": " + std::to_string(task.getId()) +
		", \"description\": \"" + task.getDescription() +
		"\", \"status\": \"" + statusToString(task.getStatus()) +
		"\", \"createdAt\": \"" + timePointToString(task.getCreatedAt()) +
		"\", \"updatedAt\": \"" + timePointToString(task.getUpdatedAt()) + "\" }";
}
inline Task jsonToTask(const std::string& json) {
	int id = 0;
	std::string description, statusStr, createdAtStr, updatedAtStr;

	auto getValue = [](const std::string& src, const std::string& key) -> std::string {
		auto keyPos = src.find("\"" + key + "\"");
		if (keyPos == std::string::npos) return "";
		auto colonPos = src.find(":", keyPos);
		auto start = src.find_first_of("\"", colonPos + 1) + 1;
		auto end = src.find_first_of("\"", start);
		return src.substr(start, end - start);
		};

	auto getNumber = [](const std::string& src, const std::string& key) -> int {
		auto keyPos = src.find("\"" + key + "\"");
		if (keyPos == std::string::npos) return 0;
		auto colonPos = src.find(":", keyPos);
		auto start = src.find_first_not_of(" \t", colonPos + 1);
		auto end = src.find_first_of(",}", start);
		return std::stoi(src.substr(start, end - start));
		};

	id = getNumber(json, "id");
	description = getValue(json, "description");
	statusStr = getValue(json, "status");
	createdAtStr = getValue(json, "createdAt");
	updatedAtStr = getValue(json, "updatedAt");

	return Task(
		id,
		description,
		stringToStatus(statusStr),
		stringToTimePoint(createdAtStr),
		stringToTimePoint(updatedAtStr)
	);
}
