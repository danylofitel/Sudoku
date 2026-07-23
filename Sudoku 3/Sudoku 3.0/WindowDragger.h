// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // Implements borderless-window dragging for a Form.
    // Wire the form's (and any drag-handle control's) MouseDown/Move/Up events
    // to onMouseDown/onMouseMove/onMouseUp respectively.
    ref class WindowDragger
    {
    private:
        System::Windows::Forms::Form^ form;
        bool dragging;
        System::Drawing::Point offset;

    public:
        WindowDragger(System::Windows::Forms::Form^ form)
            : form(form), dragging(false), offset(System::Drawing::Point::Empty)
        {
            if (form == nullptr)
            {
                throw gcnew System::ArgumentNullException("form");
            }
        }

        void onMouseDown(System::Windows::Forms::MouseEventArgs^ e)
        {
            this->dragging = true;
            this->offset = System::Drawing::Point(e->X, e->Y);
        }

        void onMouseMove(System::Windows::Forms::MouseEventArgs^ e)
        {
            if (this->dragging)
            {
                System::Drawing::Point screenPos = this->form->PointToScreen(e->Location);
                this->form->Location = System::Drawing::Point(
                    screenPos.X - this->offset.X,
                    screenPos.Y - this->offset.Y);
            }
        }

        void onMouseUp()
        {
            this->dragging = false;
        }
    };
}
