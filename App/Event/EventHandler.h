//
// Created by gerdzio21 on 09.08.2023.
//

#ifndef UNTITLED_EVENTHANDLER_H
#define UNTITLED_EVENTHANDLER_H


#include <functional>
#include "Event.h"
class EventHandler {
    public:
    using EventCallback = std::function<void(const Event&)>;
    using SubscriptionId = size_t;

    SubscriptionId subscribe(EventType eventType, EventCallback callback) {
        eventSubscriptions[eventType].emplace_back(++subscriptionCounter, callback);
        return subscriptionCounter;
    }
    void unsubscribe(EventType eventType, SubscriptionId subscriptionId) {
        auto& subscriptions = eventSubscriptions[eventType];
        subscriptions.erase(
                std::remove_if(subscriptions.begin(), subscriptions.end(),
                               [subscriptionId](const auto& sub) { return sub.first == subscriptionId; }),
                subscriptions.end());
    }

    void notify(const Event& event) {
        auto& subscriptions = eventSubscriptions[event.type];
        for (const auto& sub : subscriptions) {
            sub.second(event);
        }
    }

private:
    std::unordered_map<EventType, std::vector<std::pair<SubscriptionId, EventCallback>>> eventSubscriptions;
    SubscriptionId subscriptionCounter = 0;
};




#endif //UNTITLED_EVENTHANDLER_H
