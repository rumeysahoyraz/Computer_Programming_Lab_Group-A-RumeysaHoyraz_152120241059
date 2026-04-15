#include <iostream>

using namespace std;

struct Song {
    string title;
    string artist;
    int ratings[3];
    Song *next;
    Song *prev;

    Song(string t, string a, int r[]): title(t), artist(a), next(nullptr), prev(nullptr){
        for(int i=0; i<3; i++){
            ratings[i] = r[i];
        }
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    Playlist(): head(nullptr), tail(nullptr), current(nullptr){}

    void addSong(string title, string artist, int ratings[]){
        Song* newSong = new Song(title, artist, ratings);
        if(!head){
            head=tail=current=newSong;
        }else{
            tail->next = newSong;
            newSong->prev=tail;
            tail=newSong;
        }
    }

    void moveNext(){
        if(current && current->next){
            current = current->next;
        }else{
            cout << "reached the end of the playlist" << endl;
        }
    }

    void movePrev(){
        if(current && current->prev){
            current = current->prev;
        }else{
            cout << "already at the start of the playlist" << endl;
        }
    }

    void removeCurrent(){
        if (!current) return;

        Song* toDelete = current;

        if(toDelete->prev) toDelete->prev->next = toDelete->next;
        if(toDelete->next) toDelete->next->prev = toDelete->prev;

        if(toDelete==head) head=toDelete->next;
        if(toDelete==tail) tail=toDelete->prev;

        if (toDelete->next) current = toDelete->next;
        else current = toDelete->prev;

        delete toDelete;
        cout << "song removed" << endl;
    }

    void display(){
        if(!head){
            cout << "playlist is empty" << endl;
            return;
        }

        Song* temp = head;

        while(temp){
            if (temp == current) cout << "->";
            else cout << " ";

            cout << "[" << temp->title << " by " << temp->artist << "] ratings:";

            for(int i=0; i<3; i++){
                cout << temp->ratings[i] << " ";
            }
            cout << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    Playlist myPlaylist;

    int r1[3] = {8,9,7};
    int r2[3] = {10,10,9};
    int r3[3] = {6,7,8};

    myPlaylist.addSong("al beni", "kalben", r1);
    myPlaylist.addSong("magnolia", "laufey", r2);
    myPlaylist.addSong("abbey", "mitski", r3);

    cout << "initial playlist:" << endl;
    myPlaylist.moveNext();
    myPlaylist.display();

    return 0;
}
