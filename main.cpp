#include <SFML/Graphics.hpp>

#include <optional>
#include <string>
#include <vector>

#include "classes/doctor.h"

int main()
{
    std::vector<Patient> patients = {
        {"Ann", 34, "1991-04-02", 8, PatientStatus::WAITING},
        {"Ben", 61, "1964-09-17", 7, PatientStatus::WAITING},
        {"Cal", 22, "2003-01-30", 6, PatientStatus::WAITING},
        {"Dee", 45, "1980-06-11", 8, PatientStatus::IN_VISIT, 5},
        {"Eli", 9, "2016-12-03", 7, PatientStatus::IN_VISIT, 4},
    };
    std::vector<Doctor> doctors = {
        {"Dr. Fox", 52, "1973-03-08", 9, false, 480, 1200, &patients[3]},
        {"Dr. Gray", 38, "1987-07-21", 6, false, 480, 1200, &patients[4]},
    };

    sf::RenderWindow window(sf::VideoMode({600, 400}), "Patients & Doctors");
    const sf::Font font("C:/Windows/Fonts/arial.ttf");

    // set up paitent and doctor shapes
    sf::Text text(font, "", 20);
    sf::RectangleShape patient({40.f, 40.f});
    sf::CircleShape doctor(20.f);
    text.setFillColor(sf::Color::Black);
    patient.setOutlineColor(sf::Color::Black);
    patient.setOutlineThickness(2.f);
    doctor.setOutlineColor(sf::Color::Black);
    doctor.setOutlineThickness(2.f);

    // lambda for dray. takes a shape and position and draws the shape at the position
    auto draw = [&](auto& d, float x, float y) { d.setPosition({x, y}); window.draw(d); };
    // labmda fir wrutung. takes a string and location and writes
    auto write = [&](const std::string& s, float x, float y) { text.setString(s); draw(text, x, y); };
    // Takes an integer and returns it out of 10 as a string
    auto outOf10 = [](int n) { return std::to_string(n) + "/10"; };

    while (window.isOpen())
    {
        // close when closed
        while (const std::optional event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();

        window.clear(sf::Color::White);

        // UI
        write("Waiting", 20, 20);
        write("Currently being seen", 220, 20);
        write("Doctors", 430, 20);

        float y = 70.f;

        // Draw paitents who are waiting
        for (Patient& p : patients)
            if (p.getStatus() == PatientStatus::WAITING)
            {
                draw(patient, 20, y);
                write(outOf10(p.getCondition()), 70, y + 8);
                y += 60.f;
            }

        y = 70.f;
        // Draw doctors seeing paitents
        for (Doctor& d : doctors)
        {
            // Draw doctors and skill levels
            draw(doctor, 430, y);
            write(outOf10(d.getSkill()), 480, y + 8);

            // If doctor is seeing a paitent
            if (Patient* p = d.getPatient())
            {   
                // Draw the paitent and write severity and eta
                draw(patient, 290, y);
                write(outOf10(p->getCondition()), 340, y + 8);
                if (p->getEta())
                    write("eta " + std::to_string(*p->getEta()), 220, y + 8);
            }
            y += 60.f;
        }

        window.display();
    }
}
