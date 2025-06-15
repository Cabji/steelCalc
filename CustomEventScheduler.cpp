#include "CustomEventScheduler.h"

wxBEGIN_EVENT_TABLE(CustomEventScheduler, wxEvtHandler)
    // No static event bindings; timers will be bound dynamically
wxEND_EVENT_TABLE()

CustomEventScheduler::CustomEventScheduler()
    : wxEvtHandler()
{
    // Nothing to initialize at construction; timers are created per event
}

CustomEventScheduler::~CustomEventScheduler()
{
    CancelAll(); // Ensure all timers are stopped and cleaned up
}

// Singleton instance
CustomEventScheduler& CustomEventScheduler::Get()
{
    static CustomEventScheduler instance;
    return instance;
}

void CustomEventScheduler::CancelAll()
{
}
