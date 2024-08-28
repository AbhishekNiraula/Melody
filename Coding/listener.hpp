#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "popup.hpp"
#include "User.hpp"

using namespace std;

class Song {
private:
    string songName;
    string musicianName;
    string filePath;
    string imagePath;

public:
    Song(const string& songName, const string& musicianName,
         const string& filePath, const string& imagePath)
        : songName(songName), musicianName(musicianName),
          filePath(filePath), imagePath(imagePath) {}

    string getSongName() const { return songName; }
    string getMusicianName() const { return musicianName; }
    string getFilePath() const { return filePath; }
    string getImagePath() const { return imagePath; }

    void printDetails() const {
        cout << "Song Name: " << songName << endl;
        cout << "Musician Name: " << musicianName << endl;
        cout << "File Path: " << filePath << endl;
        cout << "Image Path: " << imagePath << endl;
    }

    string serialize() const {
        return songName + "|" + musicianName + "|" + filePath + "|" + imagePath;
    }

    static Song deserialize(const string& data) {
        size_t pos1 = data.find('|');
        size_t pos2 = data.find('|', pos1 + 1);
        size_t pos3 = data.find('|', pos2 + 1);

        string songName = data.substr(0, pos1);
        string musicianName = data.substr(pos1 + 1, pos2 - pos1 - 1);
        string filePath = data.substr(pos2 + 1, pos3 - pos2 - 1);
        string imagePath = data.substr(pos3 + 1);

        return Song(songName, musicianName, filePath, imagePath);
    }
};

class listener : public User {
private:
    string name;
    vector<Song> collection;
    vector<Song> favorites;

public:
    listener(const string& name) : name(name) {}

    void addSong(const Song& song) {
        collection.push_back(song);
    }

    void viewCollection() const {
        cout << "\n" << name << "'s Music Collection:\n";
        for (size_t i = 0; i < collection.size(); ++i) {
            cout << "\nSong " << (i + 1) << ":\n";
            collection[i].printDetails();
        }
    }

    void viewFilePath(const string& songName) const {
        for (const auto& song : collection) {
            if (song.getSongName() == songName) {
                cout << "File Path for '" << songName << "': " << song.getFilePath() << endl;
                return;
            }
        }
        cout << "Song '" << songName << "' not found in the collection." << endl;
    }

    void deleteSong(const string& songName) {
        auto it = remove_if(collection.begin(), collection.end(),
            [&songName](const Song& song) { return song.getSongName() == songName; });
        collection.erase(it, collection.end());
    }

    int addToFavorites(const string& songName) {
        loadFromFile();
        for (const auto& song : collection) {
            if (song.getSongName() == songName) {
                if (find_if(favorites.begin(), favorites.end(),
                            [&songName](const Song& fav) { return fav.getSongName() == songName; }) == favorites.end()) {
                    favorites.push_back(song);
                    saveToFile();
                    return 1;
                } else {
                    cout << "Song '" << songName << "' is already in favorites." << endl;
                    return 2;
                }
            }
        }
        cout << "Song '" << songName << "' not found in the collection." << endl;
        return 3;
    }

    int removeFromFavorites(const string& songName) {
        loadFromFile();
        auto it = find_if(favorites.begin(), favorites.end(),
                        [&songName](const Song& song) { return song.getSongName() == songName; });

        if (it != favorites.end()) {
            favorites.erase(it);
            saveToFile();
            return 1;
        } else {
            cout << "Song '" << songName << "' not found in favorites." << endl;
            return 2;
        }
    }

    void saveToFile() const {
        ofstream outFile("collection.txt");
        if (!outFile) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        outFile << "Collection\n";
        for (const auto& song : collection) { 
            outFile << song.serialize() << endl;
        }

        outFile << "Favorites\n";
        for (const auto& song : favorites) {
            outFile << song.serialize() << endl;
        }

        outFile.close();
    }

    void loadFromFile() {
        collection.clear();  // Clear collection and favorites before loading
        favorites.clear();
        ifstream inFile("collection.txt");
        if (!inFile) {
            cerr << "Error opening file for reading." << endl;
            return;
        }

        string line;
        string section;
        while (getline(inFile, line)) {
            if (line == "Collection") {
                section = "Collection";
            } else if (line == "Favorites") {
                section = "Favorites";
            } else {
                if (section == "Collection") {
                    collection.push_back(Song::deserialize(line));
                } else if (section == "Favorites") {
                    favorites.push_back(Song::deserialize(line));
                }
            }
        }

        inFile.close();
    }

    bool isFavorites(const string& name) const {
        for (const auto& song : favorites) {
            if (song.getSongName() == name) {
                return true;
            }
        }
        return false;
    }

    const vector<Song>& getCollection() const {
        return collection;
    }

    const vector<Song>& getFavorites() const {
        return favorites;
    }
};

#endif
