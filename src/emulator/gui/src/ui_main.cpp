// Vita3K emulator project
// Copyright (C) 2018 Vita3K team
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include <gui/functions.h>
#include <host/app.h>
#include <host/state.h>

#include <imgui.h>

void DrawGameSelector(HostState &host, AppRunType *run_type) {
    ImGui::SetNextWindowPos(ImVec2(0, 19), ImGuiSetCond_Always);
    ImGui::SetNextWindowSize(ImVec2(host.display.window_size.width, host.display.window_size.height - MENUBAR_HEIGHT), ImGuiSetCond_Always);
    ImGui::Begin("", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
    switch (host.gui.game_selector.state) {
    case SELECT_APP:
        ImGui::TextColored(ImVec4(255, 255, 0, 255), "Select the game/application to start");
        ImGui::Separator();
        int i = 0;
        for (auto titleid : host.gui.game_selector.title_ids) {
            std::string button_text = host.gui.game_selector.titles.at(i++);
            button_text += " (" + titleid + ")";
            if (ImGui::Button(button_text.c_str())) {
                host.gui.game_selector.title_id = titleid;
                *run_type = AppRunType::Extracted;
            }
        }
        break;
    }
    ImGui::End();
}

void DrawReinstallDialog(HostState &host, GenericDialogState *status) {
    ImGui::SetNextWindowPosCenter();
    ImGui::SetNextWindowSize(ImVec2(0, 0));
    ImGui::Begin("Reinstall this application?");
    ImGui::Text("This application is already installed.");
    ImGui::Text("Do you want to reinstall it and overwrite existing data?");
    if (ImGui::Button("Yes")) {
        *status = CONFIRM_STATE;
    }
    ImGui::SameLine();
    if (ImGui::Button("No")) {
        *status = CANCEL_STATE;
    }
    ImGui::End();
}

void DrawUI(HostState &host) {
    DrawMainMenuBar(host);

    if (host.gui.threads_dialog) {
        DrawThreadsDialog(host);
    }
    if (host.gui.semaphores_dialog) {
        DrawSemaphoresDialog(host);
    }
    if (host.gui.mutexes_dialog) {
        DrawMutexesDialog(host);
    }
    if (host.gui.lwmutexes_dialog) {
        DrawLwMutexesDialog(host);
    }
    if (host.gui.condvars_dialog) {
        DrawCondvarsDialog(host);
    }
    if (host.gui.lwcondvars_dialog) {
        DrawLwCondvarsDialog(host);
    }
    if (host.gui.eventflags_dialog) {
        DrawEventFlagsDialog(host);
    }
}
