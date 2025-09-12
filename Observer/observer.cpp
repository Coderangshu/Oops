#include <bits/stdc++.h>
using namespace std;

// Abstrat Observer interface: subscribers must implement update()
class ISubscriber {
  public:
    virtual void update() = 0;
    virtual ~ISubscriber() {}
};

// Abstract Observable interface: a YouTuber channel interface
class IObservable {
  public:
    virtual void subscribe(ISubscriber *subscriber) = 0;
    virtual void unsubscribe(ISubscriber *subscriber) = 0;
    virtual void notify() = 0;
    virtual ~IObservable() {}
};

// Concrete Subject: a YouTuber channel that observes can subscribe to
class YouTubeChannel : public IObservable {
  private:
    unordered_set<ISubscriber *> subscribers;
    string channelName;
    string latestVideo;

  public:
    YouTubeChannel(const string &name) : channelName(name) {}

    // Add a subscriber (avoid duplicates)
    void subscribe(ISubscriber *subscriber) override {
        subscribers.insert(subscriber);
    }

    // Remove a subscriber
    void unsubscribe(ISubscriber *subscriber) override {
        subscribers.erase(subscriber);
    }

    // Notify all subscribers of the latest video
    void notify() override {
        for (auto subscriber : subscribers) {
            subscriber->update();
        }
    }

    // Upload a new video and notify subscribers
    void uploadVideo(const string &videoTitle) {
        latestVideo = videoTitle;
        cout << channelName << " uploaded a new video: " << latestVideo << endl;
        notify();
    }

    // Read video data
    string getVideoData() const {
        return "\nCheckout the new video: " + latestVideo + "\n" + channelName +
               "\n";
    }
};

// Concrete Observer: a subscriber who gets notified of new videos
class Subscriber : public ISubscriber {
  private:
    string name;
    YouTubeChannel *channel;

  public:
    Subscriber(const string &subscriberName, YouTubeChannel *ch)
        : name(subscriberName), channel(ch) {
        channel->subscribe(this);
    }

    // Called by channel: prints notification message
    void update() override {
        cout << "Hey " << name << ", " << channel->getVideoData() << endl;
    }
};

int main() {
    // Create a YouTube channel
    string channelName = "Tech Insights";
    YouTubeChannel *techChannel = new YouTubeChannel(channelName);

    // Create subscribers
    Subscriber *alice = new Subscriber("Alice", techChannel);
    Subscriber *bob = new Subscriber("Bob", techChannel);

    // Upload new videos
    techChannel->uploadVideo("Understanding Observer Pattern");
    techChannel->uploadVideo("C++ Design Patterns");

    // Bob unsubscribes from the channel
    techChannel->unsubscribe(bob);

    // Upload another video
    techChannel->uploadVideo("Advanced C++ Techniques");

    return 0;
}
