#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <filesystem>
#include <fstream>
#include "json.hpp"
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;
using json = nlohmann::json;

// Done
void bindExecutable(const std::string& executablePath) {
    std::string x = "\"" + executablePath + "\"";
    int result = system(x.c_str());
}

// Done
void updateGrid(tgui::Gui& gui, tgui::HorizontalWrap::Ptr grid, std::vector<tgui::BitmapButton::Ptr>& buttons, int page) {
    const int b = 10;
    int sI = page * b;
    int eI = std::min(static_cast<int>(buttons.size()), sI + b);

    grid->removeAllWidgets();

    int r = 0, c = 0;
    for (int i = sI; i < eI; i++) {
        grid->add(buttons[i]);
        c++;
        if (c == 5) { c = 0; r++; }
    }
}

// Done
fs::path getIcon (fs::path folder) {
    if (fs::exists(folder / "icon.png")) {
        return fs::relative(folder / "icon.png");
    }
    else if (fs::exists(folder / "icon.svg")) {
        return fs::relative(folder / "icon.svg");
    }
    else if (fs::exists(folder / "icon.bmp")) {
        return fs::relative(folder / "icon.bmp");
    }
    else if (fs::exists(folder / "icon.jpg")) {
        return fs::relative(folder / "icon.jpg");
    }
    else if (fs::exists(folder / "icon.pic")) {
        return fs::relative(folder / "icon.pic");
    }
    else { return "./NO-ICON.png"; }
}

// Done
tgui::BitmapButton::Ptr createButton(std::string name, fs::path executable, fs::path icon) {

    tgui::BitmapButton::Ptr button = tgui::BitmapButton::create();

    button->onClick([executable] { bindExecutable(fs::relative(executable.string())); });
    
    sf::Texture t; t.loadFromFile(icon); tgui::Texture T;
    T.loadFromPixelData(t.getSize(), t.copyToImage().getPixelsPtr());
    button->setImage(T);
    button->setText(name);
    button->setImageScaling(1);
    button->setSize(250, 250);
    return button;
}


int main() {

    sf::RenderWindow window{ {sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height}, "TGUI example - SFML_GRAPHICS backend" };

    tgui::Gui gui{window};

    std::vector<fs::path> folders;

    // Get game folders
    for (const auto& entry : fs::directory_iterator(fs::current_path() / "Games")) {
        if (entry.is_directory()) { folders.push_back(entry.path()); }
    }

    std::sort(folders.begin(), folders.end());

    std::vector<tgui::BitmapButton::Ptr> buttons;

    // Create buttons for every game
    for (const auto& folder : folders) {

        // Game information
        std::string name;
        fs::path executable;
        fs::path icon;
        fs::path info = folder / "app_info.json";

        if (fs::exists(info) && fs::is_regular_file(info)) {
            
            std::ifstream file(info);
            json Json;
            file >> Json;

            name = Json["name"];
            executable = folder / Json["executable name"];
            icon = getIcon(folder);

            buttons.push_back(createButton(name, executable, icon));
        }
    }

    int page = 0;

    // Gui Start
    auto L = tgui::HorizontalLayout::create();

    // Left Panel Start
    auto p1 = tgui::Panel::create();
    p1->getRenderer()->setBackgroundColor(tgui::Color (255,209,220));

    // See line 143

    L->add(p1, 0.15f);
    // Left Panel End

    // Vertical Layout Start
    auto v = tgui::Panel::create();
    L->add(v);
    v->setPosition("(parent.innersize - size) / 2");

    // Label Start
    auto t = tgui::Label::create();
    t->setText("Meow");
    t->setTextSize(36);
    t->setSize("100%", "35%");
    t->setPosition(0, 0);
    v->add(t);
    // Lable End

    // Panel Start
    auto p = tgui::Panel::create();
    p->getRenderer()->setBackgroundColor(tgui::Color (137,207,240));
    p->setPosition(0, "35%");
    p->setSize("100%", "65%");
    v->add(p);


    // Grid Start
    auto w = tgui::HorizontalWrap::create();
    
    w->setPosition(0, "7%");
    w->getRenderer()->setPadding({25});
    p->add(w);
    
    

    
    
    // Grid End

    
    // Vertical Layout End



    // Right Panel Start
    auto p2 = tgui::Panel::create();
    p2->getRenderer()->setBackgroundColor(tgui::Color (255,209,220));

    // Previous Button Start
    auto previous = tgui::Button::create("Previous");
    previous->onClick([&]() {
        if (page > 0) {
            page--;
            updateGrid(gui, w, buttons, page);
        }
    });
    p1->add(previous);
    // Previous Button End

    // Next Button Start
    auto next = tgui::Button::create("Next");
    next->onClick([&]() {
        if ((page +1 ) * 12 < buttons.size()) {
            page++;
            updateGrid(gui, w, buttons, page);
        }
    });
    p2->add(next);
    // Next Button End

    L->add(p2, 0.15f);
    // Right Panel End

    // Horizontal Layout End

    gui.add(L);
    // Gui End

    updateGrid(gui, w, buttons, page);

    gui.mainLoop();

}