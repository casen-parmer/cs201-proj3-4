// header comment

#include "datacontroller.h"

#include <random>
#include <string>
#include <vector>

namespace dataController
{
    std::mt19937 rng(std::random_device{}());

    // https://www.ssa.gov/oact/babynames/decades/century.html
    const std::vector<std::string> names = {
        // male
        "James",
        "Michael",
        "John",
        "Robert",
        "David",
        "William",
        "Richard",
        "Joseph",
        "Thomas",
        "Christopher",
        "Charles",
        "Daniel",
        "Matthew",
        "Anthony",
        "Mark",
        "Steven",
        "Andrew",
        "Donald",
        "Joshua",
        "Paul",
        "Kevin",
        "Kenneth",
        "Brian",
        "Timothy",
        "Ronald",
        "Jason",
        "George",
        "Edward",
        "Jeffrey",
        "Jacob",
        "Ryan",
        "Nicholas",
        "Gary",
        "Eric",
        "Jonathan",
        "Stephen",
        "Larry",
        "Justin",
        "Benjamin",
        "Scott",
        "Brandon",
        "Samuel",
        "Alexander",
        "Gregory",
        "Patrick",
        "Jack",
        "Frank",
        "Raymond",
        "Dennis",
        "Aaron",
        "Tyler",
        "Jerry",
        "Jose",
        "Nathan",
        "Adam",
        "Henry",
        "Zachary",
        "Douglas",
        "Peter",
        "Noah",
        "Ethan",
        "Kyle",
        "Christian",
        "Jeremy",
        "Austin",
        "Keith",
        "Sean",
        "Terry",
        "Roger",
        "Dylan",
        "Walter",
        "Gerald",
        "Jordan",
        "Gabriel",
        "Carl",
        "Bryan",
        "Jesse",
        "Logan",
        "Lawrence",
        "Elijah",
        "Arthur",
        "Bruce",
        "Harold",
        "Billy",
        "Liam",
        "Alan",
        "Juan",
        "Joe",
        "Mason",
        "Lucas",
        "Randy",
        "Willie",
        "Wayne",
        "Vincent",
        "Caleb",
        "Albert",
        "Luke",
        "Isaac",
        "Bradley",
        "Cameron",
        // female
        "Mary",
        "Patricia",
        "Jennifer",
        "Linda",
        "Elizabeth",
        "Barbara",
        "Susan",
        "Jessica",
        "Karen",
        "Sarah",
        "Lisa",
        "Nancy",
        "Sandra",
        "Ashley",
        "Emily",
        "Kimberly",
        "Michelle",
        "Donna",
        "Margaret",
        "Carol",
        "Betty",
        "Amanda",
        "Melissa",
        "Deborah",
        "Stephanie",
        "Rebecca",
        "Sharon",
        "Cynthia",
        "Laura",
        "Amy",
        "Kathleen",
        "Angela",
        "Emma",
        "Shirley",
        "Dorothy",
        "Brenda",
        "Nicole",
        "Pamela",
        "Samantha",
        "Anna",
        "Olivia",
        "Katherine",
        "Christine",
        "Debra",
        "Rachel",
        "Maria",
        "Carolyn",
        "Janet",
        "Heather",
        "Diane",
        "Julie",
        "Catherine",
        "Victoria",
        "Joyce",
        "Lauren",
        "Kelly",
        "Christina",
        "Helen",
        "Joan",
        "Hannah",
        "Judith",
        "Andrea",
        "Evelyn",
        "Megan",
        "Cheryl",
        "Ruth",
        "Virginia",
        "Sophia",
        "Madison",
        "Jacqueline",
        "Abigail",
        "Isabella",
        "Teresa",
        "Sara",
        "Charlotte",
        "Janice",
        "Kathryn",
        "Martha",
        "Gloria",
        "Ann",
        "Judy",
        "Amber",
        "Danielle",
        "Denise",
        "Grace",
        "Julia",
        "Natalie",
        "Diana",
        "Marilyn",
        "Brittany",
        "Beverly",
        "Alice",
        "Theresa",
        "Jean",
        "Kayla",
        "Alexis",
        "Frances",
        "Ava",
        "Tiffany",
        "Lori",
    };

    int randomInt(int low, int high)
    {
        return std::uniform_int_distribution<int>(low, high)(rng);
    }
    std::string randomName()
    {
        return names[randomInt(0, static_cast<int>(names.size()) - 1)];
    }
    std::string randomBirthdate(int age)
    {
        int year = 2025 - age;
        int month = randomInt(1, 12);
        int day = randomInt(1, 28);
        return std::to_string(year) + "-" + (month < 10 ? "0" : "") + std::to_string(month) + "-" +
               (day < 10 ? "0" : "") + std::to_string(day);
    }
    void loadData(Simulation &sim, int numPatients, int numDoctors, bool enableTestHarness)
    {
        for (int i = 0; i < numPatients; i++)
        {
            sim.addPerson(generatePatient());
        }
        for (int i = 0; i < numDoctors; i++)
        {
            sim.addPerson(generateDoctor());
        }
    }

    Patient generatePatient()
    {
        int age = randomInt(1, 90);
        return Patient(randomName(), age, randomBirthdate(age), randomInt(1, 9), randomInt(480, 780));
    }

    Doctor generateDoctor()
    {
        int age = randomInt(28, 70);
        int start = randomInt(480, 600);
        return Doctor("Dr. " + randomName(), age, randomBirthdate(age), randomInt(1, 10), true, start, start + randomInt(60, 240));
    }
}
