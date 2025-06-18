#include "CustomEventScheduler.h"

wxBEGIN_EVENT_TABLE(CustomEventScheduler, wxEvtHandler)
    EVT_TIMER(wxID_ANY, CustomEventScheduler::OnTimer)
wxEND_EVENT_TABLE()

CustomEventScheduler::CustomEventScheduler()
    : wxEvtHandler()
{
}

CustomEventScheduler::~CustomEventScheduler()
{
    CancelAll();
}

CustomEventScheduler& CustomEventScheduler::Get()
{
    static CustomEventScheduler instance;
    return instance;
}

void CustomEventScheduler::Schedule(const std::string& key, std::function<void()> callback, int delayMs, bool repeat)
{
    Cancel(key); // Cancel any existing timer for this key

    auto timer = std::make_unique<wxTimer>(this, wxNewId());
    m_events[key] = EventInfo{callback, delayMs, repeat, std::move(timer)};
    m_events[key].timer->StartOnce(delayMs);
}

void CustomEventScheduler::Cancel(const std::string& key)
{
    auto it = m_events.find(key);
    if (it != m_events.end())
    {
        if (it->second.timer && it->second.timer->IsRunning())
            it->second.timer->Stop();
        m_events.erase(it);
    }
}

void CustomEventScheduler::CancelAll()
{
    for (auto& [key, info] : m_events)
    {
        if (info.timer && info.timer->IsRunning())
            info.timer->Stop();
    }
    m_events.clear();
}

void CustomEventScheduler::OnTimer(wxTimerEvent& event)
{
    int timerId = event.GetId();
    for (auto it = m_events.begin(); it != m_events.end(); )
    {
        auto& info = it->second;
        if (info.timer && info.timer->GetId() == timerId)
        {
            if (info.callback) info.callback();
            if (info.repeat)
            {
                info.timer->StartOnce(info.delayMs);
                ++it;
            }
            else
            {
                it = m_events.erase(it);
            }
            return;
        }
        else
        {
            ++it;
        }
    }
}