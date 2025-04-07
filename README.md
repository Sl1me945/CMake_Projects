# Task Tracker CLI

A simple command-line task tracker built in modern C++ without third-party libraries. Tasks are saved to and loaded from a `.json` file across runs.

🔗 **This project was built as part of the challenge at [roadmap.sh/projects/task-tracker](https://roadmap.sh/projects/task-tracker)**

## ⚙️ Features

- Add new tasks with descriptions
- Update task descriptions by ID
- Delete tasks
- Change task status (`ToDo`, `InProgress`, `Done`)
- List all tasks or filter by status
- Data is saved to a JSON file (`tasks.json` by default)

## Build Instructions

### Requirements
- C++17 or higher
- CMake

### Clone and Build
```bash
git clone <repo-url>
cd <repo-directory>
mkdir build
cd build
cmake ..
cmake --build .
```

## 📦 Usage

Run the compiled executable with one of the following commands:

### Add a Task
```bash
./Task_Tracker_Cli add "Buy groceries"
```

### Update a Task
```bash
./Task_Tracker_Cli update 1 "Buy groceries and fruits"
```

### Delete a Task
```bash
./Task_Tracker_Cli delete 1
```

### Change Task Status
```bash
./Task_Tracker_Cli mark 1 Done
```

### List All Tasks
```bash
./Task_Tracker_Cli list
```

### List Tasks by Status
```bash
./Task_Tracker_Cli list InProgress
```

### Show Help
```bash
./Task_Tracker_Cli --help
```

## Notes
- Tasks are saved automatically after each operation to the `tasks.json` file.
- If the file does not exist, it will be created automatically on the first save.

## License
MIT (or specify your preferred license)

