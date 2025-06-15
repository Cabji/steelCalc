#pragma once

#include <wx/timer.h>
#include <wx/event.h>
#include <map>
#include <string>
#include <functional>
#include <memory>

// CustomEventScheduler: Schedules arbitrary callbacks by key, supports one-shot and repeating events.
class CustomEventScheduler : public wxEvtHandler
{
public:
    // Singleton access
    static CustomEventScheduler& Get();

    // Schedule or reschedule an event
    // key: unique identifier for the event
    // callback: function to call when the event fires
    // delayMs: delay in milliseconds before firing
    // repeat: if true, event repeats every delayMs; if false, fires once
    void Schedule(const std::string& key, std::function<void()> callback, int delayMs, bool repeat = false);

    // Cancel a scheduled event by key
    void Cancel(const std::string& key);

    // Cancel all scheduled events
    void CancelAll();

private:
    struct EventInfo {
        std::function<void()> callback;
        int delayMs;
        bool repeat;
        std::unique_ptr<wxTimer> timer;
    };

    std::map<std::string, EventInfo> m_events;

    // Internal handler for timer events
    void OnTimer(wxTimerEvent& event);

    // Private constructor for singleton
    CustomEventScheduler();
    ~CustomEventScheduler();

    // Disallow copy/move
    CustomEventScheduler(const CustomEventScheduler&) = delete;
    CustomEventScheduler& operator=(const CustomEventScheduler&) = delete;

    wxDECLARE_EVENT_TABLE();
};