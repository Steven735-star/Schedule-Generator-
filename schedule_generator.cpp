#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <limits>

// Class to represent an activity in the schedule
class Activity {
private:
    std::string name;
    int day;           // 1-7 (Monday-Sunday)
    int startHour;     // 0-23
    int startMinute;   // 0-59
    int endHour;
    int endMinute;
    std::string location;

public:
    // Constructor
    Activity(std::string n, int d, int hI, int mI, int hF, int mF, std::string u)
        : name(n), day(d), startHour(hI), startMinute(mI), 
          endHour(hF), endMinute(mF), location(u) {}

    // Getters
    std::string getName() const { return name; }
    int getDay() const { return day; }
    int getStartHour() const { return startHour; }
    int getStartMinute() const { return startMinute; }
    int getEndHour() const { return endHour; }
    int getEndMinute() const { return endMinute; }
    std::string getLocation() const { return location; }

    // Method to check for conflicts with another activity
    bool conflictsWith(const Activity& other) const {
        if (day != other.day) return false;

        // Convert hours to minutes for easier comparison
        int startA = startHour * 60 + startMinute;
        int endA = endHour * 60 + endMinute;
        int startB = other.startHour * 60 + other.startMinute;
        int endB = other.endHour * 60 + other.endMinute;

        // There's a conflict if the start or end of one activity is within the range of another
        return (startA < endB && startB < endA);
    }

    // Method to get a string representation of the activity
    std::string toString() const {
        std::stringstream ss;
        ss << name << "," << day << "," << startHour << "," << startMinute << ","
           << endHour << "," << endMinute << "," << location;
        return ss.str();
    }

    // Method to display the activity in a readable format
    void display() const {
        static const std::string weekDays[] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        std::cout << "- " << name << " (" << weekDays[day] << " " 
                  << std::setfill('0') << std::setw(2) << startHour << ":" 
                  << std::setw(2) << startMinute << " - "
                  << std::setw(2) << endHour << ":" 
                  << std::setw(2) << endMinute << ") at " << location << std::endl;
    }
};

// Class to manage the complete schedule
class Schedule {
private:
    std::vector<Activity> activities;
    std::string name;

public:
    // Constructor
    Schedule(std::string n = "My Schedule") : name(n) {}

    // Method to add an activity
    bool addActivity(const Activity& newActivity) {
        // Check for conflicts
        for (const auto& activity : activities) {
            if (activity.conflictsWith(newActivity)) {
                std::cout << "Error: Schedule conflict detected." << std::endl;
                std::cout << "The new activity: ";
                newActivity.display();
                std::cout << "Conflicts with: ";
                activity.display();
                return false;
            }
        }

        // If no conflicts, add the activity
        activities.push_back(newActivity);
        return true;
    }

    // Method to display the entire schedule
    void displaySchedule() const {
        if (activities.empty()) {
            std::cout << "The schedule is empty." << std::endl;
            return;
        }

        std::cout << "\n=== " << name << " ===" << std::endl;
        
        for (int day = 1; day <= 7; day++) {
            static const std::string weekDays[] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            std::cout << "\n" << weekDays[day] << ":" << std::endl;
            
            bool hasActivities = false;
            std::vector<Activity> dayActivities;
            
            for (const auto& activity : activities) {
                if (activity.getDay() == day) {
                    dayActivities.push_back(activity);
                    hasActivities = true;
                }
            }
            
            if (!hasActivities) {
                std::cout << "  No activities." << std::endl;
            } else {
                // Sort by start time
                std::sort(dayActivities.begin(), dayActivities.end(), 
                    [](const Activity& a, const Activity& b) {
                        int startA = a.getStartHour() * 60 + a.getStartMinute();
                        int startB = b.getStartHour() * 60 + b.getStartMinute();
                        return startA < startB;
                    });
                
                for (const auto& activity : dayActivities) {
                    std::cout << "  ";
                    activity.display();
                }
            }
        }
    }

    // Method to remove an activity by name
    bool removeActivity(const std::string& activityName) {
        auto it = std::find_if(activities.begin(), activities.end(),
                              [&activityName](const Activity& a) { return a.getName() == activityName; });
        
        if (it != activities.end()) {
            activities.erase(it);
            std::cout << "Activity '" << activityName << "' successfully removed." << std::endl;
            return true;
        }
        
        std::cout << "No activity found with the name '" << activityName << "'." << std::endl;
        return false;
    }

    // Method to display activities for a specific day
    void displayDay(int day) const {
        static const std::string weekDays[] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        
        if (day < 1 || day > 7) {
            std::cout << "Invalid day. Must be a number between 1 (Monday) and 7 (Sunday)." << std::endl;
            return;
        }
        
        std::cout << "\nActivities for " << weekDays[day] << ":" << std::endl;
        
        bool hasActivities = false;
        std::vector<Activity> dayActivities;
        
        for (const auto& activity : activities) {
            if (activity.getDay() == day) {
                dayActivities.push_back(activity);
                hasActivities = true;
            }
        }
        
        if (!hasActivities) {
            std::cout << "  No activities for this day." << std::endl;
            return;
        }
        
        // Sort by start time
        std::sort(dayActivities.begin(), dayActivities.end(), 
            [](const Activity& a, const Activity& b) {
                int startA = a.getStartHour() * 60 + a.getStartMinute();
                int startB = b.getStartHour() * 60 + b.getStartMinute();
                return startA < startB;
            });
        
        for (const auto& activity : dayActivities) {
            std::cout << "  ";
            activity.display();
        }
    }

    // Method to save the schedule to a file
    bool saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            std::cout << "Error: Could not open file for writing." << std::endl;
            return false;
        }
        
        file << name << std::endl;
        
        for (const auto& activity : activities) {
            file << activity.toString() << std::endl;
        }
        
        file.close();
        std::cout << "Schedule successfully saved to '" << filename << "'." << std::endl;
        return true;
    }

    // Method to load the schedule from a file
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            std::cout << "Error: Could not open file for reading." << std::endl;
            return false;
        }
        
        activities.clear();  // Clear current activities
        
        // Read the schedule name
        std::getline(file, name);
        
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string activityName, location, value;
            int day, startHour, startMinute, endHour, endMinute;
            
            // Read comma-separated fields
            std::getline(ss, activityName, ',');
            std::getline(ss, value, ','); day = std::stoi(value);
            std::getline(ss, value, ','); startHour = std::stoi(value);
            std::getline(ss, value, ','); startMinute = std::stoi(value);
            std::getline(ss, value, ','); endHour = std::stoi(value);
            std::getline(ss, value, ','); endMinute = std::stoi(value);
            std::getline(ss, location);
            
            Activity activity(activityName, day, startHour, startMinute, endHour, endMinute, location);
            activities.push_back(activity);
        }
        
        file.close();
        std::cout << "Schedule successfully loaded from '" << filename << "'." << std::endl;
        return true;
    }

    // Method to change the schedule name
    void changeName(const std::string& newName) {
        name = newName;
        std::cout << "Schedule name changed to: " << name << std::endl;
    }

    // Method to find free time slots in a specific day
    void findFreeSlots(int day) const {
        static const std::string weekDays[] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        
        if (day < 1 || day > 7) {
            std::cout << "Invalid day. Must be a number between 1 (Monday) and 7 (Sunday)." << std::endl;
            return;
        }
        
        std::vector<Activity> dayActivities;
        for (const auto& activity : activities) {
            if (activity.getDay() == day) {
                dayActivities.push_back(activity);
            }
        }
        
        // Sort by start time
        std::sort(dayActivities.begin(), dayActivities.end(), 
            [](const Activity& a, const Activity& b) {
                int startA = a.getStartHour() * 60 + a.getStartMinute();
                int startB = b.getStartHour() * 60 + b.getStartMinute();
                return startA < startB;
            });
        
        std::cout << "\nFree time slots for " << weekDays[day] << ":" << std::endl;
        
        if (dayActivities.empty()) {
            std::cout << "  The entire day is free." << std::endl;
            return;
        }
        
        // Typical daytime schedule (8:00 - 22:00)
        int dayStart = 8 * 60;  // 8:00 AM
        int dayEnd = 22 * 60;    // 10:00 PM
        
        // Free slot at the beginning of the day
        if (dayActivities[0].getStartHour() * 60 + dayActivities[0].getStartMinute() > dayStart) {
            std::cout << "  " << formatTime(dayStart) << " - " 
                      << formatTime(dayActivities[0].getStartHour() * 60 + dayActivities[0].getStartMinute()) 
                      << std::endl;
        }
        
        // Free slots between activities
        for (size_t i = 0; i < dayActivities.size() - 1; i++) {
            int currentEnd = dayActivities[i].getEndHour() * 60 + dayActivities[i].getEndMinute();
            int nextStart = dayActivities[i+1].getStartHour() * 60 + dayActivities[i+1].getStartMinute();
            
            if (nextStart > currentEnd) {
                std::cout << "  " << formatTime(currentEnd) << " - " << formatTime(nextStart) << std::endl;
            }
        }
        
        // Free slot at the end of the day
        int lastEnd = dayActivities.back().getEndHour() * 60 + dayActivities.back().getEndMinute();
        if (lastEnd < dayEnd) {
            std::cout << "  " << formatTime(lastEnd) << " - " << formatTime(dayEnd) << std::endl;
        }
    }

private:
    // Helper method to format time (convert minutes to HH:MM format)
    static std::string formatTime(int minutes) {
        int hours = minutes / 60;
        int mins = minutes % 60;
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hours << ":" 
           << std::setfill('0') << std::setw(2) << mins;
        return ss.str();
    }
};

// Main function implementing the interactive menu
int main() {
    Schedule mySchedule;
    std::string filename = "schedule.txt";
    
    // Try to load the schedule from file at startup
    std::ifstream testFile(filename);
    if (testFile.good()) {
        testFile.close();
        mySchedule.loadFromFile(filename);
    }
    
    int option;
    do {
        std::cout << "\n=== SCHEDULE GENERATOR ===" << std::endl;
        std::cout << "1. Add activity" << std::endl;
        std::cout << "2. Remove activity" << std::endl;
        std::cout << "3. Display complete schedule" << std::endl;
        std::cout << "4. Display activities for a day" << std::endl;
        std::cout << "5. Find free time slots in a day" << std::endl;
        std::cout << "6. Save schedule" << std::endl;
        std::cout << "7. Load schedule" << std::endl;
        std::cout << "8. Change schedule name" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Select an option: ";
        std::cin >> option;
        
        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (option) {
            case 1: {
                std::string name, location;
                int day, startHour, startMinute, endHour, endMinute;
                
                std::cout << "Activity name: ";
                std::getline(std::cin, name);
                
                std::cout << "Day of week (1=Monday, 2=Tuesday, ..., 7=Sunday): ";
                std::cin >> day;
                
                std::cout << "Start hour (0-23): ";
                std::cin >> startHour;
                
                std::cout << "Start minute (0-59): ";
                std::cin >> startMinute;
                
                std::cout << "End hour (0-23): ";
                std::cin >> endHour;
                
                std::cout << "End minute (0-59): ";
                std::cin >> endMinute;
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                std::cout << "Location: ";
                std::getline(std::cin, location);
                
                if (day < 1 || day > 7 || startHour < 0 || startHour > 23 || 
                    startMinute < 0 || startMinute > 59 || endHour < 0 || endHour > 23 || 
                    endMinute < 0 || endMinute > 59) {
                    std::cout << "Error: Values out of range." << std::endl;
                    break;
                }
                
                if (startHour > endHour || (startHour == endHour && startMinute >= endMinute)) {
                    std::cout << "Error: End time must be after start time." << std::endl;
                    break;
                }
                
                Activity newActivity(name, day, startHour, startMinute, endHour, endMinute, location);
                mySchedule.addActivity(newActivity);
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Name of activity to remove: ";
                std::getline(std::cin, name);
                mySchedule.removeActivity(name);
                break;
            }
            case 3: {
                mySchedule.displaySchedule();
                break;
            }
            case 4: {
                int day;
                std::cout << "Day of week (1=Monday, 2=Tuesday, ..., 7=Sunday): ";
                std::cin >> day;
                mySchedule.displayDay(day);
                break;
            }
            case 5: {
                int day;
                std::cout << "Day of week (1=Monday, 2=Tuesday, ..., 7=Sunday): ";
                std::cin >> day;
                mySchedule.findFreeSlots(day);
                break;
            }
            case 6: {
                std::string file;
                std::cout << "Filename (leave blank to use '" << filename << "'): ";
                std::getline(std::cin, file);
                if (file.empty()) {
                    file = filename;
                }
                mySchedule.saveToFile(file);
                break;
            }
            case 7: {
                std::string file;
                std::cout << "Filename (leave blank to use '" << filename << "'): ";
                std::getline(std::cin, file);
                if (file.empty()) {
                    file = filename;
                }
                mySchedule.loadFromFile(file);
                break;
            }
            case 8: {
                std::string name;
                std::cout << "New name for the schedule: ";
                std::getline(std::cin, name);
                mySchedule.changeName(name);
                break;
            }
            case 0:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
        
    } while (option != 0);
    
    return 0;
}