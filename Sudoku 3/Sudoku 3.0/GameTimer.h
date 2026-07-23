// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // Tracks the time spent on the current puzzle.
    //
    // Backed by a monotonic Stopwatch (immune to system clock changes) for the currently
    // running segment, plus an accumulated span carried across pauses and loaded saves.
    // Timing is cumulative across restarts of the same puzzle, matching how the hint and
    // fix counters behave.
    ref class GameTimer
    {
    private:
        // Time accumulated before the current running segment (from stops and loaded saves)
        System::TimeSpan accumulated;

        // Measures the current running segment; reset whenever timing stops
        System::Diagnostics::Stopwatch^ stopwatch;

    public:
        GameTimer()
        {
            this->accumulated = System::TimeSpan::Zero;
            this->stopwatch = gcnew System::Diagnostics::Stopwatch();
        }

        // Starts timing a new puzzle from zero.
        void restart()
        {
            this->accumulated = System::TimeSpan::Zero;
            this->stopwatch->Restart();
        }

        // Sets the elapsed time from a loaded save, stopped. Call resume() to continue timing.
        void restore(System::TimeSpan elapsed)
        {
            this->accumulated = elapsed;
            this->stopwatch->Reset();
        }

        // Freezes the elapsed time (puzzle finished or no longer playable). Idempotent.
        void stop()
        {
            if (this->stopwatch->IsRunning)
            {
                this->accumulated += this->stopwatch->Elapsed;
                this->stopwatch->Reset();
            }
        }

        // Continues timing after stop() or restore(), keeping the accumulated time.
        // No-op if already running.
        void resume()
        {
            if (!this->stopwatch->IsRunning)
            {
                this->stopwatch->Restart();
            }
        }

        // Total time spent on the current puzzle so far. Safe to poll at any moment,
        // running or stopped.
        property System::TimeSpan Elapsed
        {
            System::TimeSpan get()
            {
                return this->accumulated + this->stopwatch->Elapsed;
            }
        }
    };
}
