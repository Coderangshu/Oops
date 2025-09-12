#include <bits/stdc++.h>
using namespace std;

// Iterator and Iterable Heirarchy
template <typename T> class Iterator {
  public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() {}
};

template <typename T> class Iterable {
  public:
    virtual Iterator<T> *createIterator() = 0;
    virtual ~Iterable() {}
};

// Concrete class for LinkedList
class LinkedList : public Iterable<int> {
  public:
    int data;
    LinkedList *next;
    LinkedList(int value) : data(value), next(nullptr) {}
    Iterator<int> *createIterator() override;
};

// Concrete class for BinaryTree
class BinaryTree : public Iterable<int> {
  public:
    int data;
    BinaryTree *left;
    BinaryTree *right;
    BinaryTree(int value) : data(value), left(nullptr), right(nullptr) {}
    Iterator<int> *createIterator() override;
};

// Concrete class for Song Playlist
class Song {
  public:
    string title;
    string artist;

    Song(const string &t, const string &a) : title(t), artist(a) {}
};

class Playlist : public Iterable<Song> {
  private:
    vector<Song> songs;

  public:
    void addSong(const Song &song) { songs.push_back(song); }

    vector<Song> getSongs() const { return songs; }

    Iterator<Song> *createIterator() override;
};

// LinkedList Iterator Implementation
class LinkedListIterator : public Iterator<int> {
  private:
    LinkedList *current;

  public:
    LinkedListIterator(LinkedList *head) : current(head) {}

    bool hasNext() override { return current != nullptr; }

    int next() override {
        if (!hasNext())
            throw runtime_error("No more elements");
        int value = current->data;
        current = current->next;
        return value;
    }
};

// BinaryTree Iterator Implementation (In-order Traversal)
class BinaryTreeInorderIterator : public Iterator<int> {
  private:
    stack<BinaryTree *> nodeStack;
    BinaryTree *current;

    void pushLeft(BinaryTree *node) {
        while (node) {
            nodeStack.push(node);
            node = node->left;
        }
    }

  public:
    BinaryTreeInorderIterator(BinaryTree *root) : current(root) {
        pushLeft(current);
    }

    bool hasNext() override { return !nodeStack.empty(); }

    int next() override {
        if (!hasNext())
            throw runtime_error("No more elements");
        BinaryTree *node = nodeStack.top();
        nodeStack.pop();
        int value = node->data;
        pushLeft(node->right);
        return value;
    }
};

class PlaylistIterator : public Iterator<Song> {
  private:
    vector<Song> songs;
    size_t index;

  public:
    PlaylistIterator(Playlist *playlist)
        : songs(playlist->getSongs()), index(0) {}

    bool hasNext() override { return index < songs.size(); }

    Song next() override {
        if (!hasNext())
            throw runtime_error("No more songs");
        return songs[index++];
    }
};

// Attaching Iterators
Iterator<int> *LinkedList::createIterator() {
    return new LinkedListIterator(this);
}

Iterator<int> *BinaryTree::createIterator() {
    return new BinaryTreeInorderIterator(this);
}

Iterator<Song> *Playlist::createIterator() {
    return new PlaylistIterator(this);
}

int main() {
    //  LinkedList: 1 -> 2 -> 3
    LinkedList *head = new LinkedList(1);
    head->next = new LinkedList(2);
    head->next->next = new LinkedList(3);

    Iterator<int> *listIterator = head->createIterator();

    cout << "LinkedList elements: ";
    while (listIterator->hasNext()) {
        cout << listIterator->next() << " ";
    }
    cout << endl;
    delete listIterator;

    // BinaryTree:
    //      2
    //     / \
    //    1  3

    BinaryTree *root = new BinaryTree(2);
    root->left = new BinaryTree(1);
    root->right = new BinaryTree(3);
    Iterator<int> *treeIterator = root->createIterator();
    cout << "BinaryTree elements (In-order): ";
    while (treeIterator->hasNext()) {
        cout << treeIterator->next() << " ";
    }
    cout << endl;
    delete treeIterator;

    // Playlist with Songs
    Playlist *playlist = new Playlist();
    playlist->addSong(Song("Song1", "Artist1"));
    playlist->addSong(Song("Song2", "Artist2"));
    playlist->addSong(Song("Song3", "Artist3"));
    Iterator<Song> *playlistIterator = playlist->createIterator();
    cout << "Playlist songs: " << endl;
    while (playlistIterator->hasNext()) {
        Song song = playlistIterator->next();
        cout << "Title: " << song.title << ", Artist: " << song.artist << endl;
    }
    delete playlistIterator;

    return 0;
}
