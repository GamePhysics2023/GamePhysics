#pragma once

#include <string>

// Simple storing of preferences in a file.
namespace Preferences {
// Load the preferences from the file.
void load();
void setBool(const std::string& key, bool value);
bool getBool(const std::string& key, bool defaultValue=false);
void setInt(const std::string& key, int value);
int getInt(const std::string& key, int defaultValue=0);
void setFloat(const std::string& key, float value);
float getFloat(const std::string& key, float defaultValue = 0.0f);
void setString(const std::string& key, const std::string& value);
const std::string& getString(const std::string& key,
                             const std::string& defaultValue = "");
// Store the preferences to the file.
void save();
}