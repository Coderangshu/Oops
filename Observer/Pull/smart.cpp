// PULL MODEL WITH SMART POINTERS

#include "Event.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Subscriber;
class Publisher;
class EventChannel;

class Subscriber {
private:
  int id;
  unordered_map<int, vector<double>> eventData;

public:
  int getID() const { return id; }
  void putID(int newID) { id = newID; }

  void addEventType(int eventType) {
    eventData[eventType]; // initialize
    cout << "[Subscriber " << id << "] Subscribed to event type: " << eventType
         << endl;
  }

  void signalEvent(shared_ptr<SubscriberEvent> event) {
    int eventType = event->getEventType();
    double data = event->getData();
    eventData[eventType].push_back(data);
    cout << "[Subscriber " << id << "] Pulled event type " << eventType
         << " with data: " << data << endl;
  }

  void subscribe(shared_ptr<EventChannel> channel, int eventType);
  void pull(shared_ptr<EventChannel> channel);
};

class EventChannel : public enable_shared_from_this<EventChannel> {
private:
  unordered_map<int, unordered_set<int>> eventTypeToSubscriberIDs;
  vector<shared_ptr<PublisherEvent>> eventQueue;
  int idCounter = 0;

public:
  void registerSubscriber(shared_ptr<Subscriber> sub) {
    sub->putID(idCounter++);
    cout << "[EventChannel] Registered Subscriber with id = " << sub->getID()
         << endl;
  }

  void subscribe(int subscriberID, int eventType) {
    if (subscriberID < idCounter) {
      eventTypeToSubscriberIDs[eventType].insert(subscriberID);
      cout << "[EventChannel] Subscriber " << subscriberID
           << " subscribed to event type " << eventType << endl;
    } else {
      cerr << "[EventChannel] Error: Subscriber ID " << subscriberID
           << " not found.\n";
    }
  }

  void unsubscribe(int subscriberID) {
    for (auto &[eventType, subIDs] : eventTypeToSubscriberIDs) {
      subIDs.erase(subscriberID);
    }
    cout << "[EventChannel] Unsubscribed and removed Subscriber "
         << subscriberID << endl;
  }

  void receiveEvent(shared_ptr<PublisherEvent> event) {
    event->print();
    eventQueue.push_back(event); // Store event
  }

  vector<shared_ptr<SubscriberEvent>> getEventsFor(int subscriberID) {
    vector<shared_ptr<SubscriberEvent>> results;
    for (auto &event : eventQueue) {
      int type = event->getEventType();
      double data = event->getData();
      if (eventTypeToSubscriberIDs[type].count(subscriberID)) {
        results.push_back(make_shared<SubscriberEvent>(type, data));
      }
    }
    return results;
  }
};

void Subscriber::subscribe(shared_ptr<EventChannel> channel, int eventType) {
  cout << "[Subscriber " << id << "] Subscribing to event type: " << eventType
       << endl;
  channel->subscribe(id, eventType);
  addEventType(eventType);
}

void Subscriber::pull(shared_ptr<EventChannel> channel) {
  cout << "[Subscriber " << id << "] Pulling events from channel...\n";
  auto subsEvents = channel->getEventsFor(id);
  for (auto &event : subsEvents) {
    signalEvent(event);
    // no delete needed!
  }
}

class Publisher {
private:
  int id;

public:
  Publisher(int id) : id(id) {}

  int getID() const { return id; }

  void publish(shared_ptr<EventChannel> channel, int eventType, double data) {
    cout << "[Publisher " << id << "] wants to publish event type " << eventType
         << " with data: " << data << endl;
    auto event = make_shared<PublisherEvent>(id, eventType, data);
    channel->receiveEvent(event);
  }
};

int main() {
  auto channel = make_shared<EventChannel>();

  // Create and register Subscribers
  vector<shared_ptr<Subscriber>> subs;
  for (int i = 0; i < 5; ++i) {
    auto sub = make_shared<Subscriber>();
    subs.push_back(sub);
    channel->registerSubscriber(sub);
  }

  // Create Publisher
  auto pub = make_shared<Publisher>(0);

  // Subscriptions
  subs[0]->subscribe(channel, 0);
  subs[1]->subscribe(channel, 0);
  subs[2]->subscribe(channel, 1);
  subs[3]->subscribe(channel, 2);
  subs[4]->subscribe(channel, 3);

  // Publisher sends events
  pub->publish(channel, 0, 10.1);
  pub->publish(channel, 1, 20);
  pub->publish(channel, 2, 9);
  pub->publish(channel, 3, 4);
  pub->publish(channel, 2, 8);

  // Each subscriber pulls its own events
  for (auto &sub : subs) {
    sub->pull(channel);
  }

  // No need to delete anything — smart pointers clean up automatically
  return 0;
}
