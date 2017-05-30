#include "activitystate.h"

const QString ActivityState::INACTIVE = QString("inactive");
const QString ActivityState::ACTIVE = QString("active");
const QString ActivityState::SUCCESS = QString("success");
const QString ActivityState::FAIL = QString("fail");

ActivityState::ActivityState()
{
    state = INACTIVE;
}

ActivityState::ActivityState(const QString State)
{
    state = State;
}

void ActivityState::setState(const QString State)
{
    state = State;
}

QString ActivityState::getState() const
{
    return state;
}
