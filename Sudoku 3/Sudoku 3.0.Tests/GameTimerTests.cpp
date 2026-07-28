// Danylo Fitel 2026
// Unit tests for GameTimer. Only the deterministic behaviour is asserted (restore/stop while
// not running); running segments are asserted with loose lower/upper bounds to avoid flakiness.

#include "GameTimer.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class GameTimerTests
    {
    public:
        [TestMethod]
        void New_ElapsedIsZero()
        {
            GameTimer^ t = gcnew GameTimer();
            Assert::AreEqual(0.0, t->Elapsed.TotalSeconds);
        }

        [TestMethod]
        void Restore_SetsElapsed_WhenStopped()
        {
            GameTimer^ t = gcnew GameTimer();
            t->restore(TimeSpan::FromSeconds(100));
            // restore() leaves the timer stopped, so the value is exact.
            Assert::AreEqual(100.0, t->Elapsed.TotalSeconds);
        }

        [TestMethod]
        void Stop_IsIdempotent_AndFreezesRestoredValue()
        {
            GameTimer^ t = gcnew GameTimer();
            t->restore(TimeSpan::FromSeconds(42));
            t->stop();
            t->stop();
            Assert::AreEqual(42.0, t->Elapsed.TotalSeconds);
        }

        [TestMethod]
        void Resume_ContinuesFromAccumulated()
        {
            GameTimer^ t = gcnew GameTimer();
            t->restore(TimeSpan::FromSeconds(50));
            t->resume();
            // Now running from a 50s base; elapsed must be at least the accumulated amount.
            Assert::IsTrue(t->Elapsed.TotalSeconds >= 50.0);
            Assert::IsTrue(t->Elapsed.TotalSeconds < 51.0); // a test won't take a second here
        }

        [TestMethod]
        void Stop_AfterResume_FreezesAccumulated()
        {
            GameTimer^ t = gcnew GameTimer();
            t->restore(TimeSpan::FromSeconds(10));
            t->resume();
            t->stop();
            double first = t->Elapsed.TotalSeconds;
            double second = t->Elapsed.TotalSeconds; // must not advance while stopped
            Assert::AreEqual(first, second);
            Assert::IsTrue(first >= 10.0);
        }

        [TestMethod]
        void Restart_ResetsToZeroBase()
        {
            GameTimer^ t = gcnew GameTimer();
            t->restore(TimeSpan::FromSeconds(500));
            t->restart();
            // Running again from zero; effectively no time has passed in the test.
            Assert::IsTrue(t->Elapsed.TotalSeconds < 1.0);
        }
    };
}
