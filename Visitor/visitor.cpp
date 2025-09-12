#include <bits/stdc++.h>
using namespace std;

// Forward declarations for all file types
class TextFile;
class ImageFile;
class VideoFile;

// Visitor interface
class FileSystemVisitor {
  public:
    virtual void visit(TextFile *file) = 0;
    virtual void visit(ImageFile *file) = 0;
    virtual void visit(VideoFile *file) = 0;
    virtual ~FileSystemVisitor() = default;
};

// File interface
class FileSystemItem {
  protected:
    string name;

  public:
    FileSystemItem(const string &name) : name(name) {}
    virtual void accept(FileSystemVisitor *visitor) = 0;
    virtual string getName() const { return name; }
    virtual ~FileSystemItem() = default;
};

class TextFile : public FileSystemItem {
  private:
    string content;

  public:
    TextFile(const string &name, const string &fileContent)
        : FileSystemItem(name), content(fileContent) {}

    void accept(FileSystemVisitor *visitor) override { visitor->visit(this); }

    string getContent() const { return content; }
};

class ImageFile : public FileSystemItem {
  private:
    int width, height;

  public:
    ImageFile(const string &name, int w, int h)
        : FileSystemItem(name), width(w), height(h) {}

    void accept(FileSystemVisitor *visitor) override { visitor->visit(this); }

    pair<int, int> getDimensions() const { return {width, height}; }
};

class VideoFile : public FileSystemItem {
  private:
    int duration; // in seconds

  public:
    VideoFile(const string &name, int dur)
        : FileSystemItem(name), duration(dur) {}

    void accept(FileSystemVisitor *visitor) override { visitor->visit(this); }

    int getDuration() const { return duration; }
};

// 1. Size calculation visitor
class SizeCalculator : public FileSystemVisitor {
  private:
    int totalSize;

  public:
    SizeCalculator() : totalSize(0) {}

    void visit(TextFile *file) override {
        totalSize += file->getContent().size();
        cout << "Calculating size of text file: " << file->getName()
             << ", size: " << file->getContent().size() << endl;
    }

    void visit(ImageFile *file) override {
        auto [width, height] = file->getDimensions();
        int size = width * height * 3; // Assuming 3 bytes per pixel (RGB)
        totalSize += size;
        cout << "Calculating size of image file: " << file->getName()
             << ", size: " << size << endl;
    }

    void visit(VideoFile *file) override {
        int size = file->getDuration() * 1000; // Assuming 1000 bytes per second
        totalSize += size;
        cout << "Calculating size of video file: " << file->getName()
             << ", size: " << size << endl;
    }
};

// 2. Compression visitor
class Compressor : public FileSystemVisitor {
  public:
    void visit(TextFile *file) override {
        cout << "Compressing text file: " << file->getName() << endl;
        // Simple compression: just reduce content size by half
        string compressedContent =
            file->getContent().substr(0, file->getContent().size() / 2);
        cout << "Original size: " << file->getContent().size()
             << ", Compressed size: " << compressedContent.size() << endl;
    }

    void visit(ImageFile *file) override {
        cout << "Compressing image file: " << file->getName() << endl;
        auto [width, height] = file->getDimensions();
        int originalSize = width * height * 3;
        int compressedSize = originalSize / 2; // Simple compression
        cout << "Original size: " << originalSize
             << ", Compressed size: " << compressedSize << endl;
    }

    void visit(VideoFile *file) override {
        cout << "Compressing video file: " << file->getName() << endl;
        int originalSize = file->getDuration() * 1000;
        int compressedSize = originalSize / 2; // Simple compression
        cout << "Original size: " << originalSize
             << ", Compressed size: " << compressedSize << endl;
    }
};

// 3. Virus scan visitor
class VirusScanner : public FileSystemVisitor {
  public:
    void visit(TextFile *file) override {
        cout << "Scanning text file for viruses: " << file->getName()
             << " - No threats found." << endl;
    }

    void visit(ImageFile *file) override {
        cout << "Scanning image file for viruses: " << file->getName()
             << " - No threats found." << endl;
    }

    void visit(VideoFile *file) override {
        cout << "Scanning video file for viruses: " << file->getName()
             << " - No threats found." << endl;
    }
};

int main() {
    FileSystemItem *files[] = {
        new TextFile("document.txt", "This is a sample text file."),
        new ImageFile("photo.jpg", 1920, 1080),
        new VideoFile("movie.mp4", 3600)};

    files[0]->accept(new SizeCalculator());
    files[1]->accept(new SizeCalculator());
    files[2]->accept(new SizeCalculator());

    files[0]->accept(new Compressor());
    files[1]->accept(new Compressor());
    files[2]->accept(new Compressor());

    files[0]->accept(new VirusScanner());
    files[1]->accept(new VirusScanner());
    files[2]->accept(new VirusScanner());

    for (auto file : files) {
        delete file;
    }

    return 0;
}
