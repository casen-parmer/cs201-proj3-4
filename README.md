# cs201-proj3-4

**Brainstorming and project planning**

For project proposals and reports, see /latex folder

Need:

- GUI (view current patient/doctor pairings)
- Data gen
- Test harness
- B-tree for doctor, patient data
- Priority queue or heap for patient priority, weighted by time left to be seen
- Priority queue for heap doctor assignment (needs empty, shift time)

Extension:

- Room requirements/limits?
- B-tree delete
- B-tree visualizer

Tasks:

| Riley            |                 Shelbe                  |                   Casen |
| :--------------- | :-------------------------------------: | ----------------------: |
| B-tree structure |                   GUI                   |                Data gen |
| Heaps            | Business logic (doctor/patient pairing) |            Test harness |
| Project proposal |                                         |            Final report |
|                  |                                         | doctor, patient classes |

---

**Assumptions**

- Time is given in minutes in 24hr format: 1440 minutes in a day
- Makefile will have two run commands: project 3 version, then seperate command to add extensions -> therefore, any extension code should be listed in seperate .h/.tpp
- Don't forget every file needs header comment, and every function needs description/input/output comment
- For LaTeX, make sure you have LaTeX, VS Code LaTeX viewer, ltmermaid package, and mmdc (mermaid CLI) package installed

**Riley Notes**

- Ensure B-tree structure owns doctor, patient classes -> heaps just contain pointers
- Rebuild heap/redistribute keys on a regular basis

**Shelbe Notes**

- Develop a formula to determine treatment length considering doctor skill and patient condition

**Casen Notes**

---

Prereq:

1. Test harness has been populated with data from makefile datagen tool

General flow:

1. Program is launched, UI initializes
2. Test harness (if enabled) progressively loads data into doctor, patient, B-trees and adds to queue
3. Datagen called any time test harness is missing or empty
4. Button on UI allows time to progress, or button allows time to progress at set rate
5. Step through time

Doctor-patient pairing must consider the following factors:

- non-empty queues
- shift time of doctor

Therefore, on each "step" through time, the following must be done:

1. Any completed doctor/patient visits must be cleared - patient status is updated, doctor is readded to queue
2. Datagen/test harness must read any new data into system - new patients, doctors
3. GUI should update
4. Doctor-patient pairings must occur until there is no valid pairing left
5. "Time" is complete


Ideas for Part 4
1. Adding and deleting doctors (hiring/firing)
