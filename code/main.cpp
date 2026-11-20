// SFML view of the hospital simulation. Space advances one minute.
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "simulation.h"
#include "datacontroller.h"

int main()
{
    /*
    Simulation sim({
                       {"Ann", 34, "1991-04-02", 8, PatientStatus::SCHEDULED, {}, 480},
                       {"Ben", 61, "1964-09-17", 7, PatientStatus::SCHEDULED, {}, 480},
                       {"Cal", 22, "2003-01-30", 6, PatientStatus::SCHEDULED, {}, 482},
                       {"Dee", 45, "1980-06-11", 8, PatientStatus::SCHEDULED, {}, 485},
                       {"Eli", 9, "2016-12-03", 7, PatientStatus::SCHEDULED, {}, 485},
                       {"Fay", 28, "1997-08-14", 2, PatientStatus::SCHEDULED, {}, 488},
                       {"Gus", 73, "1952-11-25", 3, PatientStatus::SCHEDULED, {}, 490},
                       {"Hal", 16, "2009-02-07", 1, PatientStatus::SCHEDULED, {}, 495},
                       {"Ivy", 50, "1975-05-19", 4, PatientStatus::SCHEDULED, {}, 500},
                       {"Jon", 39, "1986-10-02", 2, PatientStatus::SCHEDULED, {}, 505},
                       {"Kim", 27, "1998-03-14", 6, PatientStatus::SCHEDULED, {}, 512},
                       {"Leo", 64, "1961-07-29", 9, PatientStatus::SCHEDULED, {}, 520},
                       {"Mia", 19, "2006-11-05", 3, PatientStatus::SCHEDULED, {}, 530},
                       {"Ned", 55, "1970-01-18", 8, PatientStatus::SCHEDULED, {}, 545},
                       {"Ora", 41, "1984-09-22", 5, PatientStatus::SCHEDULED, {}, 560},
                       {"Pat", 33, "1992-06-09", 7, PatientStatus::SCHEDULED, {}, 580},
                       {"Rae", 70, "1955-04-30", 9, PatientStatus::SCHEDULED, {}, 605},
                       {"Sam", 12, "2013-08-15", 2, PatientStatus::SCHEDULED, {}, 630},
                       {"Tia", 48, "1977-12-11", 6, PatientStatus::SCHEDULED, {}, 660},
                       {"Vic", 29, "1996-02-27", 8, PatientStatus::SCHEDULED, {}, 690},
                       {"Wes", 58, "1967-05-03", 4, PatientStatus::SCHEDULED, {}, 715},
                       {"Zoe", 36, "1989-10-19", 7, PatientStatus::SCHEDULED, {}, 735},
                   },
                   {
                       {"Dr. Fox", 52, "1973-03-08", 10, true, 480, 500},
                       {"Dr. Gray", 38, "1987-07-21", 6, true, 484, 570},
                       {"Dr. Vale", 44, "1981-08-12", 10, true, 500, 750},
                   });
    */

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
        for (Doctor *d : sim.getDoctors())
        {
            draw(doctor, 350, y);
            write(d->getName() + "  skill " + std::to_string(d->getSkill()), 395, y);
            write(timestamp(d->getStartTime()) + " - " + timestamp(d->getEndTime()), 395, y + 25);
            if (Patient *p = sim.patientOf(d))
                write(p->getName() + "  " + std::to_string(p->getCondition()) +
                          "/10  done " + timestamp(p->getETA()),
                      395, y + 50);
            else
                write(sim.isOnShift(d) ? "Available" : "Off shift", 395, y + 50);
            y += 115.f;
        }
        write("Upcoming arrivals: " + std::to_string(scheduled), 20, 605);
        window.display();
    }
}
