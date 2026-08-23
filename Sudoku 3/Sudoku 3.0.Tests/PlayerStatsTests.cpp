// Danylo Fitel 2026
// Unit tests for PlayerStats streak rules: a win always advances the win streak, a clean win
// also advances the clean streak, a win with assistance resets the clean streak, and a give-up
// resets both.

#include "PlayerStats.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class PlayerStatsTests
    {
    public:
        [TestMethod]
        void RecordWin_Clean_AdvancesBothStreaks()
        {
            PlayerStats^ p = gcnew PlayerStats();
            p->recordWin(true);
            p->recordWin(true);
            Assert::AreEqual(2, (int)p->winStreak);
            Assert::AreEqual(2, (int)p->cleanWinStreak);
        }

        [TestMethod]
        void RecordWin_WithAssist_AdvancesWinResetsClean()
        {
            PlayerStats^ p = gcnew PlayerStats();
            p->recordWin(true);
            p->recordWin(true);      // 2 / 2
            p->recordWin(false);     // win continues, clean breaks

            Assert::AreEqual(3, (int)p->winStreak);
            Assert::AreEqual(0, (int)p->cleanWinStreak);
        }

        [TestMethod]
        void RecordWin_CleanAfterAssist_RestartsCleanStreak()
        {
            PlayerStats^ p = gcnew PlayerStats();
            p->recordWin(false);     // 1 / 0
            p->recordWin(true);      // 2 / 1

            Assert::AreEqual(2, (int)p->winStreak);
            Assert::AreEqual(1, (int)p->cleanWinStreak);
        }

        [TestMethod]
        void RecordGiveUp_ResetsBothStreaks()
        {
            PlayerStats^ p = gcnew PlayerStats();
            p->recordWin(true);
            p->recordWin(true);      // 2 / 2
            p->recordGiveUp();

            Assert::AreEqual(0, (int)p->winStreak);
            Assert::AreEqual(0, (int)p->cleanWinStreak);
        }
    };
}
