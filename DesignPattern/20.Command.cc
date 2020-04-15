#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <functional>

enum class Event {
    GOT_DIAMOND,
    GOT_STAR,
    HIT_OBSTACLE,
    ARCHIVE
};

class Request {
public:
    Event getEvent() const {
        return Event::GOT_DIAMOND;
    }
};


class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};
using CommandPtr = std::shared_ptr<Command>;


class GotDiamondCommand : public Command {
public:
    GotDiamondCommand(const Request& request) { }
    void execute() override { }
private:
};
using GotDiamondCommandPtr = std::shared_ptr<GotDiamondCommand>;


class CommandFactory {
public:
    using CommandMapType = std::map<Event, std::function<CommandPtr(const Request&)>>;

    static CommandPtr createCommand(const Request& request) {
        auto event = request.getEvent(); // const object can only call const functions which don't modify the object

        return commandMap.at(event)(request);
    }

private:
    static CommandMapType commandMap;
};


CommandFactory::CommandMapType CommandFactory::commandMap = {
    {Event::GOT_DIAMOND, [](const Request& request) { return std::make_shared<GotDiamondCommand>(request);} },
    {Event::GOT_STAR, [](const Request& request) { return std::make_shared<GotDiamondCommand>(request);} },
    {Event::HIT_OBSTACLE, [](const Request& request) { return std::make_shared<GotDiamondCommand>(request);} },
};


class Application {
public:
    void mainloop() {
        while (true) {
            std::vector<Request> requests;

            // get requets from epoll

            for (const auto& request : requests) {
                commandQueue.emplace(CommandFactory::createCommand(request));
            }

            int handledCount = 0;
            while (handledCount++ < MAX_HANDLED_REQ_COUNT_PER_LOOP) {
                if (commandQueue.empty()) {
                    break;
                }

                auto command = commandQueue.front();
                commandQueue.pop();

                command->execute();
            }
        }
    }

private:
    const int MAX_HANDLED_REQ_COUNT_PER_LOOP = 100;

    std::queue<CommandPtr> commandQueue;
};

int main() {

    return 0;
}

/**
 * The command pattern encapsulates a request as an object,
 * thereby letting us parameterize other objects with different requests,
 * queue or log requests, and support undoable operations.
 *
 *
 * Command pattern's primary purpose and application scenario: control the execution of the command,
 * e.g., async, dealy, queue execute, undo, redo, log...
 *
 *
 * Strategy VS Command:
 * 1. Different Strategies have the same goal, but different implementation, they are interchangeable
 * 2. Different commands have different goals, and they aren't interchangeable
 *
 *
 * Strategy VS Factory:
 * 1. Strategy focus on strategies or algorithms, select different strategies according to different scenarios
 * 2. Factory focus on the creation of objects, regardless of scenarios */