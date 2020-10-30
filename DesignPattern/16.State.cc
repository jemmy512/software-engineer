#include <iostream>

class MarioStateMachine;
using IMarioStatePtr = std::shared_ptr<IMarioState>;

enum class MarioStateEnum {
    Small,
    Super,
    Fire,
    Cape
};

class IMarioState {
public:
    virtual MarioStateEnum getName() = 0;
    virtual void onObtainMushRoom(MarioStateMachinePtr& sm) { };
    virtual void onObtainFireFlow(MarioStateMachinePtr& sm) { };
    virtual void onObtainCape(MarioStateMachinePtr& sm) { };
    virtual void onMeetMonster(MarioStateMachinePtr& sm) { };

    virtual ~IMarioState() = default;
};

using MarioStateMachinePtr = std::shared_ptr<MarioStateMachine>;

class SmallMario;
class SuperMario;
class FireMario;
class CapeMario;


class SmallMario : public IMarioState {
public:
    MarioStateEnum getName() {
        return MarioStateEnum::Small;
    }

    static IMarioStatePtr getInstance() {
        static const IMarioStatePtr instance = std::make_shared<SmallMario>();;

        return instance;
    }

    void onObtainMushRoom(MarioStateMachinePtr& sm) override {
        sm->setState(SuperMario::getInstance());
        sm->setScore(sm->getScore() + 100);
    }

    void onObtainFireFlow(MarioStateMachinePtr& sm) override {
        sm->setState(FireMario::getInstance());
        sm->setScore(sm->getScore() + 200);
    }

    void onObtainCape(MarioStateMachinePtr& sm) override {
        sm->setState(CapeMario::getInstance());
        sm->setScore(sm->getScore() + 300);
    }
};

class MarioStateMachine : public std::enable_shared_from_this<MarioStateMachine> {
public:
    int getScore() {
        return mScore;
    }

    void setScore(int score) {
        mScore = score;
    }

    void setState(IMarioStatePtr state) {
        mMarioState = state;
    }

    void onObtainMushRoom() {
        mMarioState->onObtainMushroom(shared_from_this());
    }

    void onObtainFireFlow() {
        mMarioState->onObtainFireFlow(shared_from_this());
    }

    void onObtainCape() {
        mMarioState->onObtainCape(shared_from_this());
    }

    void onMeetMonster() {
        mMarioState->onMeetMonstrer(shared_from_this());
    }

private:
    int mScore{0};
    IMarioStatePtr mMarioState = SmallMario::getInstance();
};

int main() {

    return 0;
}


/**
 * Allow an object to alter its behavior when its internal state changes.The object will appear to change its class.
 *
 * Three Implementation ways:
 * 1. branch logic method
 * 2. look-up table
 * 3. state mode: avoids judging branch logic by dividing event-triggered state transitions and action execution
 *    into different state classes. */