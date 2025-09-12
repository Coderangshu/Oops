// PULL MODEL

#include "Event.h"
#include <bits/stdc++.h>
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

  void signalEvent(SubscriberEvent *event) {
    int eventType = event->getEventType();
    double data = event->getData();
    eventData[eventType].push_back(data);
    cout << "[Subscriber " << id << "] Pulled event type " << eventType
         << " with data: " << data << endl;
  }

  void subscribe(EventChannel *channel, int eventType);

  void pull(EventChannel *channel);
};

class EventChannel {

private:
  unordered_map<int, unordered_set<int>> eventTypeToSubscriberIDs;
  vector<PublisherEvent *> eventQueue;
  int idCounter = 0;

public:
  void registerSubscriber(Subscriber *sub) {
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

  void receiveEvent(PublisherEvent *event) {
    event->print();
    eventQueue.push_back(event); // Store event
  }

  vector<SubscriberEvent *> getEventsFor(int subscriberID) {
    vector<SubscriberEvent *> results;
    for (auto &event : eventQueue) {
      int type = event->getEventType();
      double data = event->getData();
      if (eventTypeToSubscriberIDs[type].count(subscriberID)) {
        results.push_back(new SubscriberEvent(type, data));
      }
    }
    return results;
  }
};

void Subscriber::subscribe(EventChannel *channel, int eventType) {
  cout << "[Subscriber " << id << "] Subscribing to event type: " << eventType
       << endl;
  channel->subscribe(id, eventType);
  addEventType(eventType);
}

void Subscriber::pull(EventChannel *channel) {
  cout << "[Subscriber " << id << "] Pulling events from channel...\n";
  auto subsEvents = channel->getEventsFor(id);
  for (auto &event : subsEvents) {
    signalEvent(event);
    delete event;
  }
}

class Publisher {
private:
  int id;

public:
  Publisher(int id) : id(id) {}

  int getID() const { return id; }

  void publish(EventChannel *channel, int eventType, double data) {
    cout << "[Publisher " << id << "] wants to publish event type " << eventType
         << " with data: " << data << endl;
    auto event = new PublisherEvent(id, eventType, data);
    channel->receiveEvent(event);
  }
};

int main() {
  auto channel = new EventChannel();

  // Create and register Subscribers
  vector<Subscriber *> subs;
  for (int i = 0; i < 5; ++i) {
    auto sub = new Subscriber();
    subs.push_back(sub);
    channel->registerSubscriber(sub);
  }

  // Create Publisher
  auto pub = new Publisher(0);

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

  // Clean up
  for (auto &sub : subs) {
    delete sub;
  }
  delete channel;
  delete pub;

  return 0;
}
