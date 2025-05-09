# Schedule Generator

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Version](https://img.shields.io/badge/Version-1.0-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

A comprehensive C++ application for time management and schedule optimization with conflict detection.

## 📋 Overview

Schedule Generator is a console-based C++ application designed to help users manage their weekly schedules efficiently. The system allows users to create, edit, and visualize their activities while automatically preventing time conflicts. With features like free time detection and persistent storage, it provides a complete solution for personal time management.

## ✨ Features

- **Activity Management**: Add and remove scheduled activities with all relevant details
- **Automatic Conflict Detection**: System prevents scheduling overlapping activities
- **Day View**: View all activities for a specific day of the week
- **Weekly Overview**: Comprehensive view of the entire weekly schedule
- **Free Time Finder**: Identify available time slots on any given day
- **Persistence**: Save and load schedules from files for continued use
- **User-Friendly Interface**: Simple console-based menu system

## 🔧 Technical Implementation

The application is built on solid object-oriented design principles:

- **Actividad (Activity) Class**: Encapsulates individual scheduled events with properties and conflict detection logic
- **Horario (Schedule) Class**: Manages the collection of activities with sorting and filtering capabilities
- **Time Conversion**: Efficient time comparison using minute-based integers
- **CSV Persistence**: Simple file format for saving and loading schedules

## 📚 Class Structure

### Actividad (Activity)
Represents a single scheduled event with:
- Name
- Day of week (1-7)
- Start time (hour and minute)
- End time (hour and minute)
- Location

### Horario (Schedule)
Container and manager for activities with methods for:
- Adding activities with conflict validation
- Removing activities by name
- Displaying activities sorted by day and time
- Finding free time slots
- File I/O operations

## 💻 Usage

### Building the Application

```bash
# Clone the repository
git clone https://github.com/Steven735-star/Schedule-Generator-
cd Schedule-Generator-

# Compile with g++
g++ -o schedule_generator schedule_generator.cpp

# Run the application
./schedule_generator.exe
```

### Menu Options

1. **Add Activity**: Create a new scheduled activity
2. **Delete Activity**: Remove an existing activity by name
3. **Show Complete Schedule**: View your entire weekly schedule
4. **Show Activities for a Day**: View activities for a specific day
5. **Find Free Time Slots**: Identify available time on a specific day
6. **Save Schedule**: Save your schedule to a file
7. **Load Schedule**: Load a schedule from a file
8. **Change Schedule Name**: Modify the name of your schedule
0. **Exit**: Close the application

## 📝 Example

When running the application, you'll see a menu like this:

```
=== SCHEDULE GENERATOR ===
1. Add activity
2. Delete activity
3. Show complete schedule
4. Show activities for a day
5. Find free time slots in a day
6. Save schedule
7. Load schedule
8. Change schedule name
0. Exit
Select an option:
```

### Adding an Activity

```
Name of the activity: Math Class
Day of the week (1=Monday, 2=Tuesday, ..., 7=Sunday): 1
Start time (0-23): 10
Start minute (0-59): 30
End time (0-23): 12
End minute (0-59): 0
Location: Room 101
```

### Viewing Your Schedule

```
=== My Schedule ===

Monday:
  - Math Class (Monday 10:30 - 12:00) in Room 101
  - Lunch (Monday 12:15 - 13:00) in Cafeteria

Tuesday:
  - Team Meeting (Tuesday 09:00 - 10:30) in Conference Room
  ...
```

## 📈 Project Structure

```
Schedule-Generator-/
├── main.cpp          # Main application with class definitions and UI
├── horario.txt       # Default save file for schedules
├── README.md         # This file
└── LICENSE           # License information
```

## 🚀 Future Enhancements

- Graphical user interface
- Recurring activity support
- Activity categories and priorities
- Notifications and reminders
- Multi-user support
- Mobile version

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Contributing

Contributions, issues and feature requests are welcome! Feel free to check the [issues page](https://github.com/Steven735-star/Schedule-Generator-/issues).

## 📧 Contact

If you have any questions or feedback, please open an issue on the GitHub repository.

---

⭐️ From [Steven735-star](https://github.com/Steven735-star)
