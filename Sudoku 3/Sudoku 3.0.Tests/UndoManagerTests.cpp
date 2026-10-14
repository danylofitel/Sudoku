// Danylo Fitel 2026
// Unit tests for UndoManager: undo/redo histories, batches, and change notification,
// exercised against a real Board (UI-free).

#include "UndoManager.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class UndoManagerTests
    {
    private:
        literal int Cells = 81;

        int changeCount;
        UndoManager^ observed;
        bool canUndoSeenInCallback;
        bool canRedoSeenInCallback;

        void onChanged()
        {
            ++this->changeCount;
            this->canUndoSeenInCallback = this->observed->canUndo;
            this->canRedoSeenInCallback = this->observed->canRedo;
        }

        UndoManager^ NewManager()
        {
            this->changeCount = 0;
            this->observed = gcnew UndoManager(gcnew System::Action(this, &UndoManagerTests::onChanged));
            return this->observed;
        }

        static Board^ NewBoard() { return gcnew Board(Cells); }

        // The way the form performs a user edit: record the cell, then change it.
        static void SetValue(UndoManager^ u, Board^ b, unsigned int index, unsigned char value)
        {
            u->record(b, index);
            b->setUserValue(index, value);
        }

        static void TogglePencil(UndoManager^ u, Board^ b, unsigned int index, int digit)
        {
            u->record(b, index);
            b->togglePencilMark(index, digit);
        }

        static void RevealHint(UndoManager^ u, Board^ b, unsigned int index, unsigned char value)
        {
            u->record(b, index);
            b->reveal(index, value, CellKind::Hint);
        }

        static void AssertSameBoard(Board^ a, Board^ b)
        {
            for (unsigned int i = 0; i < (unsigned int)Cells; ++i)
            {
                Assert::AreEqual((int)a->valueAt(i), (int)b->valueAt(i));
                Assert::IsTrue(a->kindAt(i) == b->kindAt(i));
                Assert::AreEqual(a->pencilMarksAt(i), b->pencilMarksAt(i));
            }
        }

    public:
        // ---- Initial state ----

        [TestMethod]
        void New_CannotUndoOrRedo()
        {
            UndoManager^ u = this->NewManager();
            Assert::IsFalse(u->canUndo);
            Assert::IsFalse(u->canRedo);
            Assert::AreEqual(0, this->changeCount); // construction is not a change
        }

        [TestMethod]
        void Undo_OnEmpty_ReturnsEmptyAndDoesNotNotify()
        {
            UndoManager^ u = this->NewManager();
            Assert::AreEqual(0, u->undo(NewBoard())->Count);
            Assert::AreEqual(0, this->changeCount);
        }

        [TestMethod]
        void Redo_OnEmpty_ReturnsEmptyAndDoesNotNotify()
        {
            UndoManager^ u = this->NewManager();
            Assert::AreEqual(0, u->redo(NewBoard())->Count);
            Assert::AreEqual(0, this->changeCount);
        }

        [TestMethod]
        void NullCallback_IsAllowed()
        {
            UndoManager^ u = gcnew UndoManager(nullptr);
            Board^ b = NewBoard();
            SetValue(u, b, 0, 5);
            u->undo(b);
            u->redo(b);
            u->clear();
            Assert::IsFalse(u->canUndo);
        }

        // ---- Record ----

        [TestMethod]
        void Record_EnablesUndoOnly_AndNotifies()
        {
            UndoManager^ u = this->NewManager();
            SetValue(u, NewBoard(), 5, 3);
            Assert::IsTrue(u->canUndo);
            Assert::IsFalse(u->canRedo);
            Assert::AreEqual(1, this->changeCount);
        }

        // ---- Undo / redo of a single value edit ----

        [TestMethod]
        void Undo_RestoresPreviousValue_AndEnablesRedo()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 5, 3);

            List<unsigned int>^ touched = u->undo(b);

            Assert::AreEqual(1, touched->Count);
            Assert::AreEqual((unsigned int)5, touched[0]);
            Assert::AreEqual(0, (int)b->valueAt(5));
            Assert::IsTrue(b->kindAt(5) == CellKind::UserEmpty);
            Assert::AreEqual((unsigned int)0, b->FilledCount);
            Assert::IsFalse(u->canUndo);
            Assert::IsTrue(u->canRedo);
        }

        [TestMethod]
        void Redo_ReappliesUndoneValue_AndEnablesUndo()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 5, 3);
            u->undo(b);

            List<unsigned int>^ touched = u->redo(b);

            Assert::AreEqual(1, touched->Count);
            Assert::AreEqual((unsigned int)5, touched[0]);
            Assert::AreEqual(3, (int)b->valueAt(5));
            Assert::IsTrue(b->kindAt(5) == CellKind::UserFilled);
            Assert::AreEqual((unsigned int)1, b->FilledCount);
            Assert::IsTrue(u->canUndo);
            Assert::IsFalse(u->canRedo);
        }

        [TestMethod]
        void UndoRedo_RoundTripsRepeatedly()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 4);
            SetValue(u, b, 0, 8); // overwrite: undo should go back to 4, not to empty

            for (int round = 0; round < 3; ++round)
            {
                u->undo(b);
                Assert::AreEqual(4, (int)b->valueAt(0));
                u->redo(b);
                Assert::AreEqual(8, (int)b->valueAt(0));
            }
        }

        [TestMethod]
        void Undo_OfClearing_RestoresValue_AndRedoClearsAgain()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            b->setUserValue(3, 6);
            SetValue(u, b, 3, 0);

            u->undo(b);
            Assert::AreEqual(6, (int)b->valueAt(3));
            u->redo(b);
            Assert::AreEqual(0, (int)b->valueAt(3));
            Assert::IsTrue(b->kindAt(3) == CellKind::UserEmpty);
        }

        // ---- Ordering across several operations ----

        [TestMethod]
        void MultipleOperations_UndoLifo_RedoInOriginalOrder()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            SetValue(u, b, 1, 2);
            SetValue(u, b, 2, 3);

            Assert::AreEqual((unsigned int)2, u->undo(b)[0]);
            Assert::AreEqual((unsigned int)1, u->undo(b)[0]);
            Assert::AreEqual((unsigned int)1, b->FilledCount); // only cell 0 left filled
            Assert::AreEqual(1, (int)b->valueAt(0));

            Assert::AreEqual((unsigned int)1, u->redo(b)[0]);
            Assert::AreEqual((unsigned int)2, u->redo(b)[0]);
            Assert::AreEqual(2, (int)b->valueAt(1));
            Assert::AreEqual(3, (int)b->valueAt(2));
            Assert::IsFalse(u->canRedo);
        }

        [TestMethod]
        void UndoAll_ThenRedoAll_ReturnsToFinalState()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            for (unsigned int i = 0; i < 9; ++i)
                SetValue(u, b, i, (unsigned char)(i + 1));

            while (u->canUndo) u->undo(b);
            Assert::AreEqual((unsigned int)0, b->FilledCount);

            while (u->canRedo) u->redo(b);
            Assert::AreEqual((unsigned int)9, b->FilledCount);
            for (unsigned int i = 0; i < 9; ++i)
                Assert::AreEqual((int)(i + 1), (int)b->valueAt(i));
        }

        // ---- A new action discards the redo history ----

        [TestMethod]
        void Record_AfterUndo_ClearsRedo()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            SetValue(u, b, 1, 2);
            u->undo(b);
            Assert::IsTrue(u->canRedo);

            SetValue(u, b, 2, 3);

            Assert::IsFalse(u->canRedo);
            Assert::AreEqual(0, u->redo(b)->Count);
            Assert::AreEqual(0, (int)b->valueAt(1)); // the discarded edit never comes back
            // History is now: cell 0, then cell 2
            Assert::AreEqual((unsigned int)2, u->undo(b)[0]);
            Assert::AreEqual((unsigned int)0, u->undo(b)[0]);
            Assert::IsFalse(u->canUndo);
        }

        [TestMethod]
        void Batch_AfterUndo_ClearsRedo()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            u->undo(b);

            u->beginBatch();
            SetValue(u, b, 4, 4);
            u->endBatch();

            Assert::IsFalse(u->canRedo);
        }

        [TestMethod]
        void EmptyBatch_AfterUndo_KeepsRedo_AndDoesNotNotify()
        {
            // A Fix that finds nothing to fix must not cost the player their redo history.
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            u->undo(b);
            int before = this->changeCount;

            u->beginBatch();
            u->endBatch();

            Assert::IsTrue(u->canRedo);
            Assert::IsFalse(u->canUndo);
            Assert::AreEqual(before, this->changeCount);
        }

        // ---- Pencil marks ----

        [TestMethod]
        void PencilToggle_UndoAndRedo_RoundTripMarks()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            TogglePencil(u, b, 7, 2);
            TogglePencil(u, b, 7, 9);

            u->undo(b);
            Assert::AreEqual(1 << 2, b->pencilMarksAt(7));
            u->undo(b);
            Assert::AreEqual(0, b->pencilMarksAt(7));
            u->redo(b);
            u->redo(b);
            Assert::AreEqual((1 << 2) | (1 << 9), b->pencilMarksAt(7));
        }

        [TestMethod]
        void UndoOfFilling_RestoresMarksTheFillCleared()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            b->togglePencilMark(4, 3);
            b->togglePencilMark(4, 5);
            SetValue(u, b, 4, 5); // filling clears the marks

            u->undo(b);
            Assert::AreEqual((1 << 3) | (1 << 5), b->pencilMarksAt(4));
            u->redo(b);
            Assert::AreEqual(5, (int)b->valueAt(4));
            Assert::AreEqual(0, b->pencilMarksAt(4));
        }

        // ---- Hints keep their locked kind ----

        [TestMethod]
        void HintReveal_UndoMakesCellEditable_RedoRelocksAsHint()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            RevealHint(u, b, 10, 7);

            u->undo(b);
            Assert::IsTrue(b->kindAt(10) == CellKind::UserEmpty);
            Assert::IsTrue(b->isEditable(10));
            Assert::AreEqual((unsigned int)0, b->countOfKind(CellKind::Hint));

            u->redo(b);
            Assert::AreEqual(7, (int)b->valueAt(10));
            Assert::IsTrue(b->kindAt(10) == CellKind::Hint);
            Assert::IsFalse(b->isEditable(10));
            Assert::AreEqual((unsigned int)1, b->countOfKind(CellKind::Hint));
        }

        [TestMethod]
        void HintOverWrongGuess_UndoRestoresGuess()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            b->setUserValue(10, 2);
            RevealHint(u, b, 10, 7);

            u->undo(b);
            Assert::AreEqual(2, (int)b->valueAt(10));
            Assert::IsTrue(b->kindAt(10) == CellKind::UserFilled);
        }

        [TestMethod]
        void HintOverPencilMarks_UndoRestoresMarks()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            b->togglePencilMark(10, 7);
            RevealHint(u, b, 10, 7);

            u->undo(b);
            Assert::AreEqual(1 << 7, b->pencilMarksAt(10));
        }

        // ---- Batches (Fix) ----

        [TestMethod]
        void Batch_UndoneAndRedoneAsOneOperation()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            b->setUserValue(1, 4);
            b->setUserValue(2, 5);
            SetValue(u, b, 0, 9); // a separate, earlier operation

            u->beginBatch();
            SetValue(u, b, 1, 0);
            SetValue(u, b, 2, 0);
            u->endBatch();

            List<unsigned int>^ touched = u->undo(b);
            Assert::AreEqual(2, touched->Count);
            Assert::AreEqual(4, (int)b->valueAt(1));
            Assert::AreEqual(5, (int)b->valueAt(2));
            Assert::AreEqual(9, (int)b->valueAt(0)); // the earlier operation is untouched
            Assert::IsTrue(u->canUndo);

            touched = u->redo(b);
            Assert::AreEqual(2, touched->Count);
            Assert::AreEqual(0, (int)b->valueAt(1));
            Assert::AreEqual(0, (int)b->valueAt(2));
            Assert::IsFalse(u->canRedo);
        }

        [TestMethod]
        void Batch_UndoRestoresInReverseRecordingOrder()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            u->beginBatch();
            SetValue(u, b, 3, 1);
            SetValue(u, b, 8, 2);
            u->endBatch();

            List<unsigned int>^ touched = u->undo(b);
            Assert::AreEqual((unsigned int)8, touched[0]);
            Assert::AreEqual((unsigned int)3, touched[1]);
        }

        [TestMethod]
        void Batch_TouchingSameCellTwice_UndoesToOldest_RedoesToNewest()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            b->setUserValue(0, 1);

            u->beginBatch();
            SetValue(u, b, 0, 2);
            SetValue(u, b, 0, 3);
            u->endBatch();

            u->undo(b);
            Assert::AreEqual(1, (int)b->valueAt(0));
            u->redo(b);
            Assert::AreEqual(3, (int)b->valueAt(0));
            u->undo(b);
            Assert::AreEqual(1, (int)b->valueAt(0));
        }

        [TestMethod]
        void Batch_NotifiesOnceOnEnd_NotPerRecord()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            u->beginBatch();
            SetValue(u, b, 0, 1);
            SetValue(u, b, 1, 2);
            Assert::AreEqual(0, this->changeCount);
            Assert::IsFalse(u->canUndo); // nothing is undoable until the batch closes
            u->endBatch();
            Assert::AreEqual(1, this->changeCount);
            Assert::IsTrue(u->canUndo);
        }

        [TestMethod]
        void EndBatch_WithoutBegin_IsHarmless()
        {
            UndoManager^ u = this->NewManager();
            u->endBatch();
            Assert::IsFalse(u->canUndo);
            Assert::AreEqual(0, this->changeCount);
        }

        // ---- Clear ----

        [TestMethod]
        void Clear_DisablesUndoAndRedo_AndNotifies()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            SetValue(u, b, 1, 2);
            u->undo(b);
            Assert::IsTrue(u->canUndo && u->canRedo);
            int before = this->changeCount;

            u->clear();

            Assert::IsFalse(u->canUndo);
            Assert::IsFalse(u->canRedo);
            Assert::IsTrue(this->changeCount > before);
            Assert::AreEqual(0, u->undo(b)->Count);
            Assert::AreEqual(0, u->redo(b)->Count);
        }

        [TestMethod]
        void Clear_DiscardsOpenBatch()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            u->beginBatch();
            SetValue(u, b, 0, 1);
            u->clear();
            u->endBatch(); // the discarded batch must not be committed

            Assert::IsFalse(u->canUndo);

            SetValue(u, b, 1, 2); // and recording works normally again (not inside a batch)
            Assert::IsTrue(u->canUndo);
        }

        // ---- Notification ----

        [TestMethod]
        void UndoAndRedo_Notify_WithUpdatedState()
        {
            // The form syncs its buttons from inside the callback, so the callback must see the
            // histories in their final state.
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);

            u->undo(b);
            Assert::AreEqual(2, this->changeCount);
            Assert::IsFalse(this->canUndoSeenInCallback);
            Assert::IsTrue(this->canRedoSeenInCallback);

            u->redo(b);
            Assert::AreEqual(3, this->changeCount);
            Assert::IsTrue(this->canUndoSeenInCallback);
            Assert::IsFalse(this->canRedoSeenInCallback);
        }

        // ---- Export / import (save and load) ----

        [TestMethod]
        void Export_OnEmpty_ReturnsEmptyArrays()
        {
            UndoManager^ u = this->NewManager();
            Assert::AreEqual(0, u->exportUndo()->Length);
            Assert::AreEqual(0, u->exportRedo()->Length);
        }

        [TestMethod]
        void Export_OrdersOperationsOldestFirst_AndKeepsBatches()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            u->beginBatch();
            SetValue(u, b, 3, 4);
            SetValue(u, b, 8, 5);
            u->endBatch();
            SetValue(u, b, 20, 6);

            array<array<UndoManager::CellState^>^>^ undo = u->exportUndo();
            Assert::AreEqual(3, undo->Length);
            Assert::AreEqual((unsigned int)0, undo[0][0]->cellIndex);
            Assert::AreEqual(2, undo[1]->Length);              // the batch stays one operation
            Assert::AreEqual((unsigned int)3, undo[1][0]->cellIndex); // in recording order
            Assert::AreEqual((unsigned int)8, undo[1][1]->cellIndex);
            Assert::AreEqual((unsigned int)20, undo[2][0]->cellIndex); // newest last
            Assert::IsTrue(undo[2][0]->kind == CellKind::UserEmpty);
        }

        [TestMethod]
        void ExportRedo_LastOperationIsNextToRedo()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            SetValue(u, b, 1, 2);
            u->undo(b); // cell 1 undone first
            u->undo(b); // then cell 0 - so cell 0 is the next to redo

            array<array<UndoManager::CellState^>^>^ redo = u->exportRedo();
            Assert::AreEqual(2, redo->Length);
            Assert::AreEqual((unsigned int)1, redo[0][0]->cellIndex);
            Assert::AreEqual((unsigned int)0, redo[1][0]->cellIndex);
            Assert::AreEqual(1, (int)redo[1][0]->value); // the state redo will restore
        }

        [TestMethod]
        void Export_IsASnapshot_NotAffectedByLaterChanges()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            array<array<UndoManager::CellState^>^>^ undo = u->exportUndo();

            SetValue(u, b, 1, 2);
            u->clear();

            Assert::AreEqual(1, undo->Length);
        }

        [TestMethod]
        void ExportThenImport_BehavesIdentically()
        {
            // Two boards in the same state, one with the original history and one with a manager
            // that imported it: every undo and redo must produce the same board.
            UndoManager^ original = gcnew UndoManager(nullptr);
            Board^ a = NewBoard();
            SetValue(original, a, 0, 1);
            TogglePencil(original, a, 5, 3);
            RevealHint(original, a, 9, 7);
            original->beginBatch();
            SetValue(original, a, 0, 0);
            SetValue(original, a, 12, 0);
            original->endBatch();
            SetValue(original, a, 12, 8);
            original->undo(a); // leave something to redo as well

            Board^ b = NewBoard();
            for (unsigned int i = 0; i < (unsigned int)Cells; ++i)
                b->restoreCell(i, a->valueAt(i), a->kindAt(i), a->pencilMarksAt(i));
            UndoManager^ imported = gcnew UndoManager(nullptr);
            imported->importHistory(original->exportUndo(), original->exportRedo());

            Assert::IsTrue(imported->canUndo);
            Assert::IsTrue(imported->canRedo);
            while (original->canUndo)
            {
                original->undo(a);
                imported->undo(b);
                AssertSameBoard(a, b);
            }
            Assert::IsFalse(imported->canUndo);
            while (original->canRedo)
            {
                original->redo(a);
                imported->redo(b);
                AssertSameBoard(a, b);
            }
            Assert::IsFalse(imported->canRedo);
        }

        [TestMethod]
        void Import_ReplacesHistory_AndNotifies()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            SetValue(u, b, 1, 2);
            u->undo(b);
            int before = this->changeCount;

            array<array<UndoManager::CellState^>^>^ undo = gcnew array<array<UndoManager::CellState^>^>(1);
            undo[0] = gcnew array<UndoManager::CellState^>(1);
            undo[0][0] = gcnew UndoManager::CellState(40, 0, CellKind::UserEmpty, 0);
            u->importHistory(undo, nullptr);

            Assert::IsTrue(this->changeCount > before);
            Assert::IsTrue(this->canUndoSeenInCallback);
            Assert::IsFalse(this->canRedoSeenInCallback);
            Assert::AreEqual((unsigned int)40, u->undo(b)[0]);
            Assert::IsFalse(u->canUndo);
        }

        [TestMethod]
        void Import_Nulls_ClearsBothHistories()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            SetValue(u, b, 1, 2);
            u->undo(b);

            u->importHistory(nullptr, nullptr);

            Assert::IsFalse(u->canUndo);
            Assert::IsFalse(u->canRedo);
        }

        [TestMethod]
        void Import_DiscardsOpenBatch()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            u->beginBatch();
            SetValue(u, b, 0, 1);
            u->importHistory(nullptr, nullptr);
            u->endBatch();

            Assert::IsFalse(u->canUndo);
        }

        [TestMethod]
        void Record_AfterUndo_NotifiesWithRedoCleared()
        {
            UndoManager^ u = this->NewManager();
            Board^ b = NewBoard();
            SetValue(u, b, 0, 1);
            u->undo(b);

            SetValue(u, b, 1, 2);
            Assert::IsTrue(this->canUndoSeenInCallback);
            Assert::IsFalse(this->canRedoSeenInCallback);
        }
    };
}
