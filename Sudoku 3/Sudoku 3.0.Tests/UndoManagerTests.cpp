// Danylo Fitel 2026
// Unit tests for UndoManager: stack + batch logic and change notification (UI-free).

#include "UndoManager.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class UndoManagerTests
    {
    private:
        int changeCount;
        void onChanged() { ++this->changeCount; }

        UndoManager^ NewManager()
        {
            this->changeCount = 0;
            return gcnew UndoManager(gcnew System::Action(this, &UndoManagerTests::onChanged));
        }

    public:
        [TestMethod]
        void New_CannotUndo()
        {
            Assert::IsFalse(this->NewManager()->canUndo);
        }

        [TestMethod]
        void Push_EnablesUndo_AndNotifies()
        {
            UndoManager^ u = this->NewManager();
            int before = this->changeCount;
            u->push(5, 3, 0);
            Assert::IsTrue(u->canUndo);
            Assert::IsTrue(this->changeCount > before);
        }

        [TestMethod]
        void PopOperation_ReturnsSingleEntry_WithStoredState()
        {
            UndoManager^ u = this->NewManager();
            u->push(5, 3, 1 << 2);

            System::Collections::Generic::List<UndoManager::Entry^>^ ops = u->popOperation();
            Assert::AreEqual(1, ops->Count);
            Assert::AreEqual((unsigned int)5, ops[0]->cellIndex);
            Assert::AreEqual(3, (int)ops[0]->previousValue);
            Assert::AreEqual(1 << 2, ops[0]->previousPencilMarks);
            Assert::IsFalse(u->canUndo);
        }

        [TestMethod]
        void Batch_PoppedAsOneOperation()
        {
            UndoManager^ u = this->NewManager();
            u->beginBatch();
            u->push(1, 4, 0);
            u->push(2, 5, 0);
            u->endBatch();

            System::Collections::Generic::List<UndoManager::Entry^>^ ops = u->popOperation();
            Assert::AreEqual(2, ops->Count);
            Assert::IsFalse(u->canUndo); // the whole batch was consumed at once
        }

        [TestMethod]
        void PopOperation_OnEmpty_ReturnsEmptyList()
        {
            Assert::AreEqual(0, this->NewManager()->popOperation()->Count);
        }

        [TestMethod]
        void Clear_DisablesUndo()
        {
            UndoManager^ u = this->NewManager();
            u->push(1, 2, 0);
            u->clear();
            Assert::IsFalse(u->canUndo);
        }
    };
}
