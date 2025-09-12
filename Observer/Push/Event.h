#include <bits/stdc++.h>
using namespace std;

class Event {
protected:
  int eventType;

public:
  Event(int type) : eventType(type) {}
  virtual ~Event() = default;

  int getEventType() const { return eventType; }

  virtual Event *clone() const = 0;
  virtual void print() const = 0;
};

class PublisherEvent : public Event {
private:
  int publisherID;
  double data;

public:
  PublisherEvent(int publisherID, int eventType, double data)
      : Event(eventType), publisherID(publisherID), data(data) {}

  int getPublisherID() const { return publisherID; }
  double getData() const { return data; }

  Event *clone() const override { return new PublisherEvent(*this); }

  void print() const override {
    cout << "[PublisherEvent] From Publisher " << publisherID
         << ", Type: " << eventType << ", Data: " << data << endl;
  }
};

class SubscriberEvent : public Event {
private:
  double data;

public:
  SubscriberEvent(int eventType, double data) : Event(eventType), data(data) {}

  double getData() const { return data; }

  Event *clone() const override { return new SubscriberEvent(*this); }

  void print() const override {
    cout << "[SubscriberEvent] From EventChannel to Subscriber"
         << ", Type: " << eventType << ", Data: " << data << endl;
  }
};
