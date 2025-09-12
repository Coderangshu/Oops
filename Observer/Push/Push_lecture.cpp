// PUSH MODEL

#include "Event.h"
#include <bits/stdc++.h>
using namespace std;

class Subscriber {
private:
  int id;
  unordered_map<int, vector<double>> eventData;

public:
  Subscriber(int id) : id(id) {}

  int getID() const { return id; }

  void addEventType(int eventType) {
    eventData[eventType];
    cout << "[Subscriber " << id << "] Subscribed to event type: " << eventType
         << endl;
  }

  void signalEvent(shared_ptr<SubscriberEvent> event) {
    int eventType = event->getEventType();
    int data = event->getData();
    eventData[eventType].push_back(data);
    cout << "[Subscriber " << id << "] Received event type " << eventType
         << " with data: " << data << endl;
  }
};

class EventChannel {
private:
  unordered_map<int, shared_ptr<Subscriber>> idToSubscriber;
  unordered_map<int, unordered_set<int>> eventTypeToSubscriberIDs;

public:
  void registerSubscriber(shared_ptr<Subscriber> sub) {
    int id = sub->getID();
    idToSubscriber[id] = sub;
    cout << "[EventChannel] Registered Subscriber " << id << endl;
  }

  void subscribe(int subscriberID, int eventType) {
    if (idToSubscriber.count(subscriberID)) {
      idToSubscriber[subscriberID]->addEventType(eventType);
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
    idToSubscriber.erase(subscriberID);
    cout << "[EventChannel] Unsubscribed and removed Subscriber "
         << subscriberID << endl;
  }

  void receiveEvent(shared_ptr<PublisherEvent> event) {
    auto publisherID = event->getPublisherID();
    auto eventType = event->getEventType();
    auto data = event->getData();

    cout << "\n[EventChannel] Publisher " << publisherID
         << " published event type " << eventType << " with data: " << data
         << endl;

    if (!eventTypeToSubscriberIDs.count(eventType)) {
      cout << "[EventChannel] No subscribers for this event type.\n";
      return;
    }

    for (int subID : eventTypeToSubscriberIDs[eventType]) {
      if (idToSubscriber.count(subID)) {
        auto event = make_shared<SubscriberEvent>(eventType, data);
        idToSubscriber[subID]->signalEvent(event);
      }
    }
  }
};

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

  // Create Subscribers and register them
  vector<shared_ptr<Subscriber>> subs;
  for (int i = 0; i < 5; ++i) {
    auto sub = make_shared<Subscriber>(i);
    subs.push_back(sub);
    channel->registerSubscriber(subs[i]);
  }

  // Create Publisher (not tied to channel)
  auto pub = make_shared<Publisher>(0);

  // Setup subscriptions
  channel->subscribe(0, 0);
  channel->subscribe(1, 0);
  channel->subscribe(2, 1);
  channel->subscribe(3, 2);
  channel->subscribe(4, 3);

  // Publish events using EventChannel
  pub->publish(channel, 0, 10.1);
  pub->publish(channel, 1, 20);
  pub->publish(channel, 2, 9);
  pub->publish(channel, 3, 4);
  pub->publish(channel, 2, 8);

  // Unsubscribe
  channel->unsubscribe(1);

  pub->publish(channel, 0, 30.1);

  channel->unsubscribe(4);

  pub->publish(channel, 3, 135);
  pub->publish(channel, 4, 256);
  pub->publish(channel, 4, 32);

  return 0;
}
