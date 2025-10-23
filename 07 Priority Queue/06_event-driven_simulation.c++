// Event-Driven O(E log E) -> O(N log N)
    // conpare to time-driven O(T) -> O(N^2)
//Time-driven simulation processes every time step whether or not an event occurs, while event-driven simulation jumps directly between events, making it more efficient when events are sparse.

// event-driven simulation         - colision simulation   -biliard

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ---------- Event struct ----------
struct Event {
    double time;      // when the event will occur
    string desc;      // description of the event

    // Order by time (min-heap)
    bool operator>(const Event& other) const {
        return time > other.time;
    }
};

int main() {
    // Priority queue sorted by smallest time first
    priority_queue<Event, vector<Event>, greater<Event>> pq;

    // Insert some example events
    pq.push({5.0, "Particle A hits wall"});
    pq.push({2.5, "Particle B collides with Particle C"});
    pq.push({7.2, "Redraw screen"});
    pq.push({1.0, "Simulation starts"});

    double currentTime = 0.0;

    // Main event-driven loop
    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();

        // Advance simulation time
        currentTime = e.time;

        cout << "[t=" << currentTime << "] " << e.desc << endl;

        // Example: insert a new event dynamically
        if (e.desc == "Particle A hits wall") {
            pq.push({currentTime + 3.0, "Particle A hits opposite wall"});
        }
    }

    return 0;
}
