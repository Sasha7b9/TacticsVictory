// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "GovernorFloat.h"
#include "GUI/Controls/Button.h"
#include "GUI/Cursor.h"
#include "GUI/Controls/Label.h"
#include "GUI/Windows/Console.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GovernorCell::GovernorCell(Context *) :
    WindowRTS()
{
    SetMovable(false);
    SetStyleAuto();
    SetStyle("WindowGovernorCell");
    //ApplyAttributes();
    SetFixedSize(SET::MENU::GOVERNOR::CELL::SIZE);

    label = new Text(gContext);
    label->SetFont(gFont, 8);
    label->SetAlignment(HA_CENTER, VA_CENTER);

    label->SetStyle("WindowNoBorder");
    label->SetAlignment(HA_LEFT, VA_TOP);
    label->SetPosition(1, -1);
    AddChild(label);

    SubscribeToEvent(E_UIMOUSECLICK, URHO3D_HANDLER(GovernorCell, HandleMouseDown));
    SubscribeToEvent(E_MOUSEBUTTONUP, URHO3D_HANDLER(GovernorCell, HandleMouseUp));
    SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(GovernorCell, HandleMouseMove));
    SubscribeToEvent(this, E_HOVERBEGIN, URHO3D_HANDLER(GovernorCell, HandleHoverBegin));
    SubscribeToEvent(this, E_HOVEREND, URHO3D_HANDLER(GovernorCell, HandleHoverEnd));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::SetSelected()
{
    selected = true;
    SetSymbol(symbol);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::SetNormal()
{
    selected = false;
    SetSymbol(symbol);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::SetSymbol(char symbol_)
{
    symbol = symbol_;
    label->SetText(String(symbol));
    label->SetPosition(symbol == '0' ? 0 : 1, -1);
    label->SetColor(selected ? Color::YELLOW : Color::WHITE);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::SetSymbolWithEvent(char symbol_)
{
    symbol = symbol_;
    label->SetText(String(symbol));
    label->SetPosition(symbol == '0' ? 0 : 1, -1);
    label->SetColor(selected ? Color::YELLOW : Color::WHITE);

    VariantMap eventData = GetEventDataMap();
    eventData[GovernorCellChanged::P_ELEMENT] = this;
    eventData[GovernorCellChanged::P_SYMBOL] = symbol;
    SendEvent(E_GOVERNORCELLCHANGED, eventData);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
char GovernorCell::GetSymbol()
{
    return symbol;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::HandleMouseDown(StringHash, VariantMap&)
{
    if(type == CellType_Static)
    {
        return;
    }
    if(mouseOver)
    {
        delta = 0;
        mouseIsDown = true;
        gCursor->Hide();
        posCursor = gCursor->GetCursor()->GetPosition();
        SetSelected();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::HandleMouseMove(StringHash, VariantMap& eventData)
{
    if(type == CellType_Static)
    {
        return;
    }

    if(!mouseIsDown)
    {
        return;
    }

    gCursor->GetCursor()->SetPosition(posCursor);

    delta -= (int)eventData[MouseMove::P_DY].GetInt();

    if(delta > 20 || delta < -20)
    {
        ChangeValue(delta);
        delta = 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::ChangeValue(int d)
{
    if(type == CellType_Sign)
    {
        SetSymbolWithEvent(symbol == '-' ? '+' : '-');
    }
    else if(type == CellType_Digit)
    {
        if(d > 0)
        {
            if(symbol == '9')
            {
                SetSymbolWithEvent('0');
            }
            else
            {
                SetSymbolWithEvent(symbol + 1);
            }
        }
        else
        {
            if(symbol == '0')
            {
                SetSymbolWithEvent('9');
            }
            else
            {
                SetSymbolWithEvent(symbol - 1);
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::HandleMouseUp(StringHash, VariantMap&)
{
    if(type == CellType_Static)
    {
        return;
    }
    gCursor->Show();
    mouseIsDown = false;
    SetNormal();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::HandleHoverBegin(StringHash, VariantMap& eventData)
{
    if(type == CellType_Static)
    {
        return;
    }
    GovernorCell *cell = (GovernorCell*)eventData[HoverBegin::P_ELEMENT].GetPtr();
    if(cell == this)
    {
        mouseOver = true;
        gCursor->SetSelected();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::HandleHoverEnd(StringHash, VariantMap&)
{
    if(type == CellType_Static)
    {
        return;
    }
    mouseOver = false;
    mouseIsDown = false;
    gCursor->SetNormal();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorCell::RegisterObject(Context *context)
{
    context->RegisterFactory<GovernorCell>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowRTS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
GovernorFloat::GovernorFloat(Context *context) :
    WindowRTS()
{
    SetMovable(false);
    SetStyle("WindowNoBorder");

    int widthLabel = 168;

    label = Label::Create("Camera position Y", true, 8, widthLabel, 13);
    label->SetAlignment(HA_LEFT, VA_CENTER);
    AddChild(label);

    for(int i = 0; i < numCells; i++)
    {
        SharedPtr<GovernorCell> cell(new GovernorCell(context));
        cell->SetPosition(i * (SET::MENU::GOVERNOR::CELL::WIDTH - 1) + widthLabel + (i > 1 ? SET::MENU::GOVERNOR::CELL::WIDTH : 0), 0);
        cell->SetSymbol((char)(0x30 + i));
        AddChild(cell);
        cells.Push(cell);

        if(i == 0 || i == 7)
        {
            cell->SetType(CellType_Sign);
            cell->SetSymbol('+');
        }
        else
        {
            cell->SetType(CellType_Digit);
            cell->SetSymbol('0');
        }
        SubscribeToEvent(E_GOVERNORCELLCHANGED, URHO3D_HANDLER(GovernorFloat, HandleGovernorCellChanged));
    }

    SharedPtr<GovernorCell> cell(new GovernorCell(context));
    cell->SetType(CellType_Static);
    cell->SetPosition(2 * (SET::MENU::GOVERNOR::CELL::WIDTH - 1) + widthLabel, 0);
    cell->SetSymbol('.');
    AddChild(cell);

    SetFixedSize((SET::MENU::GOVERNOR::CELL::WIDTH - 1) * (numCells + 1) + 17 + widthLabel, SET::MENU::GOVERNOR::CELL::HEIGHT);

    buttonDown = new Button(gContext);
    buttonDown->SetStyle("DropDownButtonDown");
    AddChild(buttonDown);
    buttonDown->SetPosition((numCells + 1) * (SET::MENU::GOVERNOR::CELL::WIDTH - 1) + 4 + widthLabel, 0); //-V112

    SubscribeToEvent(buttonDown, E_HOVERBEGIN, URHO3D_HANDLER(GovernorFloat, HandleHoverButtonBegin));
    SubscribeToEvent(buttonDown, E_HOVEREND, URHO3D_HANDLER(GovernorFloat, HandleHoverButtonEnd));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::RegisterObject(Context *context)
{
    context->RegisterFactory<GovernorFloat>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowRTS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::SetFunctionFloat(char *title_, pFuncFV funcRead_, pFuncVF funcWrite_)
{
    funcRead = funcRead_;
    funcWrite = funcWrite_;
    title = title_;
    label->SetText(title);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::Update(float timeStep)
{
    UIElement::Update(timeStep);

    if(funcWrite && valueChanged)
    {
        float value = GetValue();
        funcWrite(value);
        valueChanged = false;
    }
    else if(funcRead)
    {
        WriteValue(funcRead());
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::WriteValue(float value)
{
    int order = 0;
    int mantiss = 0;
    GetOrderAndMantiss(value, &order, &mantiss);

    WriteMantiss(mantiss);
    WriteOrder(order);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static char NextDigit(int *mantiss)
{
    char retValue = (char)((*mantiss - (*mantiss / 10) * 10) | 0x30);
    *mantiss /= 10;
    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::WriteMantiss(int mantiss)
{
    cells[0]->SetSymbol(mantiss >= 0 ? '+' : '-');

    if(mantiss < 0)
    {
        mantiss = -mantiss;
    }
    
    for(uint i = 6; i >= 1; i--)
    {
        cells[i]->SetSymbol(NextDigit(&mantiss));
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::WriteOrder(int order)
{
    cells[7]->SetSymbol(order >= 0 ? '+' : '-');

    if(order < 0)
    {
        order = -order;
    }

    for(uint i = 10; i >= 8; i--)
    {
        cells[i]->SetSymbol(NextDigit(&order));
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::GetOrderAndMantiss(float value, int *order, int *mantiss)
{
    static const int SIZE_BUFFER = 30;
    char buffer[SIZE_BUFFER];
    sprintf_s(buffer, "%e", value);
    int first = 0;
    for(int i = 0; i < SIZE_BUFFER; i++)
    {
        if(buffer[i] == 'e')
        {
            first = i + 1;
            break;
        }
    }

    int sign = buffer[first] == '-' ? -1 : 1;

    int startOrder = first + 1;                 // Индекс первого символа порядка
    int lastOrder = startOrder;
    while(buffer[lastOrder + 1])
    {
        lastOrder++;                            // Находим индекс последнего символа порядка
    }

    int units = buffer[lastOrder--] ^ 0x30;                                     // Количество единиц
    int tens = (lastOrder < startOrder) ? 0 : (buffer[lastOrder--] ^ 0x30);     // Количество десятков
    int hundrend = (lastOrder < startOrder) ? 0 : (buffer[lastOrder] ^ 0x30);   // Количество сотен

    *order = sign *(units + tens * 10 + hundrend * 100);

    sign = buffer[0] == '-' ? -1 : 1;
    first = sign < 0 ? 1 : 0;

    int last = first + 6;

    int buf[6];

    for(int index = first; index <= last; index++)
    {
        if(index != first + 1)
        {
            int iBuf = index == first ? 0 : index - 1 - first;
            buf[iBuf] = buffer[index] ^ 0x30;
        }
    }

    int pow = 1;

    *mantiss = 0;

    for(int i = 5; i >= 0; i--)
    {
        *mantiss += buf[i] * pow;
        pow *= 10;
    }

    *mantiss *= sign;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float GovernorFloat::GetValue()
{
    int pow = 1;
    int mantiss = 0;
    for(uint i = 6; i >= 1; i--)
    {
        int value = cells[i]->GetSymbol() ^ 0x30;
        mantiss += value * pow;
        pow *= 10;
    }

    pow = 1;
    int order = 0;

    for(uint i = 10; i >= 8; i--)
    {
        int value = cells[i]->GetSymbol() ^ 0x30;
        order += value * pow;
        pow *= 10;
    }

    float mul = cells[7]->GetSymbol() == '-' ? -1e1f : 1e1f;
    float value = (float)mantiss;

    for(int i = 0; i < order; i++)
    {
        value *= mul;
    }
    value /= 1e5f;

    if(cells[0]->GetSymbol() == '-')
    {
        value = -value;
    }

    return value;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::HandleGovernorCellChanged(StringHash, VariantMap&)
{
    valueChanged = true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::HandleHoverButtonBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorFloat::HandleHoverButtonEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}
