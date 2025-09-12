#include <bits/stdc++.h>
using namespace std;

class IImage {
  public:
    virtual void display() = 0;
    virtual ~IImage() = default;
};

class RealImage : public IImage {
  private:
    string filename;

  public:
    RealImage(const string &fname) : filename(fname) {
        // Heavy loading operation
        cout << "[RealImage] Loading image from disk: " << filename << endl;
    }

    void display() override { cout << "Displaying " << filename << endl; }
};

class ImageProxy : public IImage {
  private:
    string filename;
    RealImage *realImage;

  public:
    ImageProxy(const string &fname) : filename(fname), realImage(nullptr) {}

    ~ImageProxy() {
        if (realImage) {
            delete realImage;
        }
    }

    void display() override {
        if (!realImage) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
};

int main() {
    IImage *image = new ImageProxy("test_image.jpg");

    cout << "Image proxy created." << endl;
    cout << "Image not loaded yet." << endl;

    // Image will be loaded from disk only when display is called
    image->display();

    delete image;
    return 0;
}
