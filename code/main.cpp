/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Runs the SFML hospital simulation viewer. Space advances one minute.
*/

#include <SFML/Graphics.hpp>
#include <filesystem>
#include "simulation.h"
#include "datacontroller.h"

// Launches the SFML hospital simulation window and event loop. Input: N/A. Output: exit status code.
int main()
{
    Simulation sim;
    dataController::loadData(sim, 100, 10, false);

    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Hospital Simulation");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    sf::Font font;
    for (const char *path : {"C:/Windows/Fonts/arial.ttf",
                             "/System/Library/Fonts/Supplemental/Arial.ttf"})
    {
        if (std::filesystem::exists(path) && font.openFromFile(path))
            break;
    }

    sf::Text text(font, "", 18);
    text.setFillColor(sf::Color::Black);
    sf::RectangleShape patient({26.f, 26.f});
    patient.setOutlineColor(sf::Color::Black);
    patient.setOutlineThickness(1.f);
    sf::CircleShape doctor(16.f);
    doctor.setFillColor(sf::Color::Blue);


    //setup the draw of the firing button for every doctor
    sf::RectangleShape fireButton({26.f, 26.f});
    fireButton.setFillColor(sf::Color::Red);
    std::vector<std::pair<sf::FloatRect, Doctor *>> fireButtons;

    auto draw = [&](auto &shape, float x, float y)
    {
        shape.setPosition({x, y});
        window.draw(shape);
    };
    auto write = [&](const std::string &s, float x, float y)
    {
        text.setString(s);
        draw(text, x, y);
    };
    auto timestamp = [](int t)
    {
        return std::to_string(t / 60) + ":" + (t % 60 < 10 ? "0" : "") + std::to_string(t % 60);
    };

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto *key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Space)
                    sim.stepPhase();
            }

            //check for mouse click on fire button
            if (const auto *mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                //get mouse click position
                sf::Vector2i pixelPos(mouseClick->position.x, mouseClick->position.y);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    
                //check all the fire buttons
                for (auto &[rect, d] : fireButtons){
                    if (rect.getGlobalBounds().contains(worldPos)){
                        sim.fireDoctor(d);
                        break;
                    }
                }
                
            }
        }
        if (!window.isOpen())
            break;

        window.clear(sf::Color::White);
        write(timestamp(sim.getTime()) + (sim.isPaired() ? "  (after pairing)" : "  (before pairing)"), 20, 15);
        write(sim.isPaired() ? "Space: +1 min (updates)" : "Space: pair & close", 20, 45);
        write("Waiting (red = critical)", 20, 95);
        write("Doctors / current visits", 350, 95);
        write("Departed", 780, 95);

        write("Failed to treat", 960, 95);
        float waiting_y = 135.f, departed_y = 135.f, failed_y = 135.f;
        int scheduled = sim.getUpcomingCount();
        for (Patient *p : sim.getWaiting())
        {
            patient.setFillColor(p->getCondition() == 10 ? sf::Color::Red : sf::Color::Yellow);
            draw(patient, 20, waiting_y);
            write(p->getName() + "  " + std::to_string(p->getCondition()) + "/10", 60, waiting_y);
            waiting_y += 42.f;
        }
        for (Patient *p : sim.getFailed())
        {
            write(p->getName() + "  10/10", 960, failed_y);
            failed_y += 42.f;
        }
        for (Patient *p : sim.getDischarged())
        {
            write(p->getName() + "  0/10", 780, departed_y);
            departed_y += 42.f;
        }

        float y = 135.f;

        //clear the old fire buttons
        fireButtons.clear();

        for (Doctor *d : sim.getDoctors())
        {
            //ensures doctors finish the shift before fired
            if (!d->isHired() && !sim.patientOf(d))
            {
                continue;
            }

            draw(doctor, 350, y);
            write(d->getName() + "  skill " + std::to_string(d->getSkill()), 395, y);
            write(timestamp(d->getStartTime()) + " - " + timestamp(d->getEndTime()), 395, y + 25);
            if (Patient *p = sim.patientOf(d))
                write(p->getName() + "  " + std::to_string(p->getCondition()) +
                          "/10  done " + timestamp(p->getETA()),
                      395, y + 50);
            else
                write(sim.isOnShift(d) ? "Available" : "Off shift", 395, y + 50);

            // draw the fire button for every doctor that is currently hired
            if (d->isHired()) {
                draw(fireButton, 660, y);
                fireButtons.push_back({fireButton.getGlobalBounds(), d});
            }
            
            y += 115.f;
        }
        write("Upcoming arrivals: " + std::to_string(scheduled), 20, 605);
        window.display();
    }
}
