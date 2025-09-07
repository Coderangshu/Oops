#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <memory>

// Base class for all events
class Event {
public:
  virtual ~Event() = default; // ensure polymorphic deletion
  virtual int getEventType() const = 0;
  virtual double getData() const = 0;
};

// Event created by a Publisher
class PublisherEvent : public Event {
private:
  int publisherID;
  int eventType;
  double data;

public:
  PublisherEvent(int pubID, int type, double d)
      : publisherID(pubID), eventType(type), data(d) {}

  int getPublisherID() const { return publisherID; }
  int getEventType() const override { return eventType; }
  double getData() const override { return data; }

  void print() const {
    std::cout << "[PublisherEvent] From Publisher " << publisherID
              << ", Type: " << eventType << ", Data: " << data << std::endl;
  }
};

// Event delivered to a Subscriber
class SubscriberEvent : public Event {
private:
  int eventType;
  double data;

public:
  SubscriberEvent(int type, double d) : eventType(type), data(d) {}

  int getEventType() const override { return eventType; }
  double getData() const override { return data; }
};

#endif // EVENT_H
