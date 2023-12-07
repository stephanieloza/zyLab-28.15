#include <iostream>
using namespace std;

//playlist.h

#ifndef PLAYLISTNODE_H
#define PLAYLISTNODE_H

#include <iostream>
using namespace std;

class PlaylistNode {
private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;

public:
    // Constructors
    PlaylistNode();
    PlaylistNode(string id, string song, string artist, int length);


    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;

    void InsertAfter(PlaylistNode* nodePtr);
    void SetNext(PlaylistNode* nodePtr);
    void PrintPlaylistNode() const;
};

#endif

//playlist.cpp

#include "PlaylistNode.h"
#include <iostream>


PlaylistNode::PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {}


PlaylistNode::PlaylistNode(std::string id, std::string song, std::string artist, int length)
    : uniqueID(id), songName(song), artistName(artist), songLength(length), nextNodePtr(nullptr) {}


   string PlaylistNode::GetID() const { 
      return uniqueID; 
      }
   string PlaylistNode::GetSongName() const { 
      return songName; 
      }
   string PlaylistNode::GetArtistName() const { 
      return artistName; 
      }
   int PlaylistNode::GetSongLength() const { 
      return songLength; 
      }
   PlaylistNode* PlaylistNode::GetNext() const { 
      return nextNodePtr; 
      }


void PlaylistNode::InsertAfter(PlaylistNode* nodePtr) {
    PlaylistNode* tempNext = nullptr;
    tempNext = nextNodePtr;
    nextNodePtr = nodePtr;
    nodePtr->nextNodePtr = tempNext;
}

void PlaylistNode::SetNext(PlaylistNode* nodePtr) {
    nextNodePtr = nodePtr;
}

void PlaylistNode::PrintPlaylistNode() const {
         cout << "Unique ID: " << uniqueID << "\n"
              << "Song Name: " << songName << "\n"
              << "Artist Name: " << artistName << "\n"
              << "Song Length (in seconds): " << songLength << endl;
}

//main.cpp

#include <iostream>
#include "PlaylistNode.h"

using namespace std;

void PrintMenu(const string playlistTitle) {
    cout << playlistTitle << " PLAYLIST MENU\n"
         << "a - Add song\n"
         << "d - Remove song\n"
         << "c - Change position of song\n"
         << "s - Output songs by specific artist\n"
         << "t - Output total time of playlist (in seconds)\n"
         << "o - Output full playlist\n"
         << "q - Quit\n"
         << endl;
        cout << "Choose an option:";
        cout << endl;
     
}

PlaylistNode* ExecuteMenu(char option, string playlistTitle, PlaylistNode* headNode) {
    switch (option) {
        case 'a': 
        {
            string uniqueID, songName, artistName;
            int songLength;

            cout << "ADD SONG\n";
            cout << "Enter song's unique ID:" << endl;
            getline(cin, uniqueID);

            cout << "Enter song's name:" << endl;
            getline(cin, songName);

            cout << "Enter artist's name:" << endl;
            getline(cin, artistName);

            cout << "Enter song's length (in seconds):" << endl;
            cin >> songLength;
            cin.ignore();

            PlaylistNode* newNode = new PlaylistNode(uniqueID, songName, artistName, songLength);

            if (!headNode) {
                headNode = newNode;
            } else {
                headNode->InsertAfter(newNode);
            }

            
            break;
        }

        case 'd': // Remove song
        {
            if (!headNode) {
                cout << "Playlist is empty. Nothing to remove.\n";
            } else {
                string uniqueID;
                cout << "REMOVE SONG\n";
                cout << "Enter song's unique ID: ";
                getline(cin, uniqueID);

                PlaylistNode* current = headNode;
                PlaylistNode* previous = nullptr;

                while (current && current->GetID() != uniqueID) {
                    previous = current;
                    current = current->GetNext();
                }

                if (!current) {
                    cout << "Song with ID " << uniqueID << " not found.\n";
                } else {
                    if (!previous) {
                        // Removing the head node
                        headNode = current->GetNext();
                    } else {
                        previous->SetNext(current->GetNext());
                    }

                    delete current;
                    cout << "Song removed successfully.\n";
                }
            }
            break;
        }

        case 's': 
        {
            if (!headNode) {
                cout << "Playlist is empty. No songs to output.\n";
            } else {
                string artistName;

                cout << "OUTPUT SONGS BY SPECIFIC ARTIST\n";
                cout << "Enter artist's name: ";
                getline(cin, artistName);

                int position = 1;
                PlaylistNode* current = headNode;

                while (current) {
                    if (current->GetArtistName() == artistName) {
                        cout << position << ".";
                        cout << endl;
                       
                        current->PrintPlaylistNode();
                        position++;
                    }

                    current = current->GetNext();
                }

                if (position == 1) {
                    cout << "No songs found for artist \"" << artistName << "\".\n";
                }
            }
            break;
        }

        case 't': 
        {
            if (!headNode) {
                cout << "Playlist is empty. Total time: 0 seconds.\n";
            } else {
                int totalTime = 0;
                PlaylistNode* current = headNode;

                while (current) {
                    totalTime += current->GetSongLength();
                    current = current->GetNext();
                }

                cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n\n";
                cout << "Total time: " << totalTime << " seconds\n";
            }
            break;
        }

        case 'o': 
        {
            if (!headNode) {
                cout << playlistTitle << " - OUTPUT FULL PLAYLIST Playlist is empty";
            } else {
                cout << playlistTitle << " - OUTPUT FULL PLAYLIST\n";
                int position = 1;
                PlaylistNode* current = headNode;

                while (current) {
                    cout << position << ". ";
                    current->PrintPlaylistNode();
                    current = current->GetNext();
                    position++;
                }
            }
            break;
        }

        case 'q':
            
            
            break;

        default:
            cout << "Invalid option. Please try again.\n";
    }

    return headNode;
}

int main() {
    string playlistTitle;
    cout << "Enter playlist's title:";
    cout << endl;
    cout << endl;
    getline(cin, playlistTitle);

    PlaylistNode* headNode = nullptr;

    char option;
    do {
        PrintMenu(playlistTitle);
        cin >> option;
        cin.ignore(); 

        headNode = ExecuteMenu(option, playlistTitle, headNode);
    } while (option != 'q');

    
    PlaylistNode* current = headNode;
    while (current) {
        PlaylistNode* next = current->GetNext();
        delete current;
        current = next;
    }

    return 0;
}
