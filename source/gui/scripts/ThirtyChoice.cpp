/*
*   This file is part of PKSM
*   Copyright (C) 2016-2018 Bernardo Giordano, Admiral Fish, piepie62
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "ThirtyChoice.hpp"
#include "gui.hpp"

void ThirtyChoice::draw() const
{
    C2D_SceneBegin(g_renderTargetTop);
    Gui::sprite(ui_sheet_part_mtx_5x6_idx, 0, 0);

    int x = (hid.index() % 6) * 67;
    int y = (hid.index() / 6) * 48;
    // Selector
    C2D_DrawRectSolid(x, y, 0.5f, 66, 47, COLOR_MASKBLACK);
    C2D_DrawRectSolid(x, y, 0.5f, 66, 1, COLOR_YELLOW);
    C2D_DrawRectSolid(x, y, 0.5f, 1, 47, COLOR_YELLOW);
    C2D_DrawRectSolid(x + 65, y, 0.5f, 1, 47, COLOR_YELLOW);
    C2D_DrawRectSolid(x, y + 46, 0.5f, 66, 1, COLOR_YELLOW);

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 6; x++)
        {
            size_t index = x + y * 6 + hid.page() * hid.maxVisibleEntries();
            if (index >= (size_t) items)
            {
                break;
            }
            Gui::pkm(pkms[index].species, pkms[index].form, gen, x * 67 + 18, y * 48 + 7);
            Gui::dynamicText(x * 67, y * 48 + 30, 67, labels[index], FONT_SIZE_9, FONT_SIZE_9, COLOR_WHITE);
        }
    }

    drawBottom();
}

void ThirtyChoice::update(touchPosition* touch)
{
    hid.update(items);
    if (hidKeysDown() & KEY_A)
    {
        finalVal = hid.fullIndex();
        done = true;
    }
}