#include <gui/widgets/file_select.h>
#include <regex>
#include <filesystem>
#include <gui/file_dialogs.h>
#include <core.h>

FileSelect::FileSelect(std::string defaultPath, std::vector<std::string> filter) {
    _filter = filter;
    root = (std::string)core::args["root"];
    setPath(defaultPath);
}

bool FileSelect::render(std::string id) {
    bool _pathChanged = false;
    float menuColumnWidth = ImGui::GetContentRegionAvail().x;

    float buttonWidth = ImGui::CalcTextSize("...").x + 20.0f;
    bool lastPathValid = pathValid;
    if (!lastPathValid) {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
    }
    ImGui::SetNextItemWidth(menuColumnWidth - buttonWidth);
    if (ImGui::InputText(id.c_str(), strPath, 2047)) {
        path = std::string(strPath);
        std::string expandedPath = expandString(strPath);
        if (!std::filesystem::is_regular_file(expandedPath)) {
            pathValid = false;
        }
        else {
            pathValid = true;
            _pathChanged = true;
        }
    }
    if (!lastPathValid) {
        ImGui::PopStyleColor();
    }
    ImGui::SameLine();
    if (ImGui::Button(("..." + id + "_winselect").c_str(), ImVec2(buttonWidth - 8.0f, 0)) && !dialogOpen) {
        dialogOpen = true;
        if (workerThread.joinable()) { workerThread.join(); }
        workerThread = std::thread(&FileSelect::worker, this);
    }

    _pathChanged |= pathChanged;
    pathChanged = false;
    return _pathChanged;
}

void FileSelect::setPath(std::string path, bool markChanged) {
    this->path = path;
    std::string expandedPath = expandString(path);
    // pathValid = std::filesystem::is_regular_file(expandedPath);
    pathValid = std::filesystem::is_regular_file(std::filesystem::path(expandedPath));
    if (markChanged) { pathChanged = true; }
    // std::strcpy(strPath, path.c_str());
    // Copying the path string to strPath using safer alternatives
    std::strncpy(strPath, expandedPath.c_str(), sizeof(strPath) - 1);
    strPath[sizeof(strPath) - 1] = '\0';  // Ensure null-termination
}

std::string FileSelect::expandString(std::string input) {
    input = std::regex_replace(input, std::regex("%ROOT%"), root);
    return std::regex_replace(input, std::regex("//"), "/");
}

bool FileSelect::pathIsValid() {
    return pathValid;
}

void FileSelect::worker() {
    auto file = pfd::open_file("Open File", pathValid ? std::filesystem::path(expandString(path)).parent_path().string() : "", _filter);
    std::vector<std::string> res = file.result();

    if (res.size() > 0) {
        path = res[0];
        // strcpy(strPath, path.c_str());
        std::strncpy(strPath, path.c_str(), sizeof(strPath) - 1);
        strPath[sizeof(strPath) - 1] = '\0';
        pathChanged = true;
    }

    pathValid = std::filesystem::is_regular_file(expandString(path));
    dialogOpen = false;
}