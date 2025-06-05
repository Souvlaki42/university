#include "Student.h"
#include "Lesson.h"
#include "Record.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using std::cout, std::vector, std::ofstream, std::ifstream, std::stringstream, std::set, std::getline, std::invalid_argument;

void Record::addStudent(const Student &student)
{
  this->students.push_back(student);
}

void Record::fixStudent(const Student &student)
{
  for (int i = 0; i < this->students.size(); i++)
  {
    if (this->students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      this->students[i] = student;
      return;
    }
  }
  throw RecordException("Δεν υπάρχει φοιτητής με AM " + std::to_string(student.getRegistrationNumber()));
}

void Record::removeStudent(const Student &student)
{
  for (size_t i = 0; i < this->students.size();)
  {
    if (this->students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      this->students.erase(this->students.begin() + i);
      return;
    }
    else
    {
      ++i;
    }
  }
  throw RecordException("Δεν υπάρχει φοιτητής με AM " + std::to_string(student.getRegistrationNumber()));
}

void Record::addLesson(const Lesson &lesson)
{
  this->lessons.push_back(lesson);
};

void Record::fixLesson(const Lesson &lesson)
{
  for (int i = 0; i < this->lessons.size(); i++)
  {
    if (this->lessons[i].getCode() == lesson.getCode())
    {
      this->lessons[i] = lesson;
      return;
    }
  }
  throw RecordException("Δεν υπάρχει μάθημα με κωδικό " + lesson.getCode());
};

void Record::removeLesson(const Lesson &lesson)
{
  for (size_t i = 0; i < this->lessons.size();)
  {
    if (this->lessons[i].getCode() == lesson.getCode())
    {
      this->lessons.erase(this->lessons.begin() + i);
      return;
    }
    else
    {
      ++i;
    }
  }
  throw RecordException("Δεν υπάρχει μάθημα με κωδικό " + lesson.getCode());
}

void Record::sendEmailToAllStudents(const string &message)
{
  cout << "Στάλθηκε email με μήνυμα \"" << message << "\" σε όλους τους φοιτητές του τμήματος με επιτυχία!\n";
}

void Record::sendEmailToAllProfessors(const string &message)
{
  cout << "Στάλθηκε email με μήνυμα \"" << message << "\" σε όλους τους καθηγητές του τμήματος με επιτυχία!\n";
}

void Record::addGrade(const Student &student, Lesson &lesson, float grade)
{
  if (grade < 0 || grade > 10)
  {
    throw RecordException("Ο βαθμός πρέπει να είναι μεταξύ 0 και 10");
  }

  int lessonIndex = -1;
  for (int i = 0; i < this->lessons.size(); i++)
  {
    if (this->lessons[i].getCode() == lesson.getCode())
    {
      lessonIndex = i;
      break;
    }
  }

  if (lessonIndex == -1)
  {
    throw RecordException("Δεν υπάρχει μάθημα με κωδικό " + lesson.getCode());
  }

  int studentIndex = -1;
  for (int i = 0; i < this->students.size(); i++)
  {
    if (this->students[i].getRegistrationNumber() == student.getRegistrationNumber())
    {
      studentIndex = i;
      break;
    }
  }

  if (studentIndex == -1)
  {
    throw RecordException("Δεν υπάρχει φοιτητής με AM " + std::to_string(student.getRegistrationNumber()));
  }

  Lesson &selectedLesson = this->lessons[lessonIndex];
  vector<float> grades = selectedLesson.getGrades();

  if (grades.size() <= studentIndex)
  {
    grades.resize(this->students.size(), -1);
  }
  grades[studentIndex] = grade;
  selectedLesson.setGrades(grades);
}

void Record::fixGrade(const Student &student, Lesson &lesson, float grade)
{
  try
  {
    addGrade(student, lesson, grade);
  }
  catch (const RecordException &e)
  {
    throw RecordException(e);
  }
}

void Record::saveToCsv()
{
  ofstream profFile("professors_record.csv");
  if (!profFile.is_open())
  {
    throw RecordException("Το αρχείο καθηγητών δεν μπόρεσε να ανοιχθεί");
  }

  profFile << "ID,name,birthYear,address,phone,email,code,specialty\n";

  set<string> writtenProfessorIds;

  for (const auto &lesson : lessons)
  {
    const Professor &prof = lesson.getProfessor();
    if (writtenProfessorIds.insert(prof.getID()).second)
    {
      profFile << prof.getID() << "," << prof.getName() << ","
               << prof.getBirthYear() << "," << prof.getAddress() << ","
               << prof.getPhone() << "," << prof.getEmail() << ","
               << prof.getCode() << "," << prof.getSpecialty() << "\n";
    }
  }
  profFile.close();

  ofstream lessonFile("lessons_record.csv");
  if (!lessonFile.is_open())
  {
    throw RecordException("Το αρχείο μαθημάτων δεν μπόρεσε να ανοιχθεί");
  }

  lessonFile << "code,name,semester,professorID\n";
  for (const auto &lesson : lessons)
  {
    lessonFile << lesson.getCode() << "," << lesson.getName() << ","
               << lesson.getSemester() << "," << lesson.getProfessor().getID()
               << "\n";
  }
  lessonFile.close();

  ofstream studentFile("students_record.csv");
  if (!studentFile.is_open())
  {
    throw RecordException("Το αρχείο μαθητών δεν μπόρεσε να ανοιχθεί");
  }

  studentFile << "ID,name,birthYear,address,phone,email,registrationNumber,semester,lessonsCode\n";
  for (const auto &student : students)
  {
    const vector<Lesson> &lessons = student.getLessons();
    if (lessons.empty())
    {
      studentFile << student.getID() << "," << student.getName() << ","
                  << student.getBirthYear() << "," << student.getAddress() << ","
                  << student.getPhone() << "," << student.getEmail() << ","
                  << student.getRegistrationNumber() << ","
                  << student.getSemester() << "," << "\n";
    }
    else
    {
      for (const auto &lesson : lessons)
      {
        studentFile << student.getID() << "," << student.getName() << ","
                    << student.getBirthYear() << "," << student.getAddress() << ","
                    << student.getPhone() << "," << student.getEmail() << ","
                    << student.getRegistrationNumber() << ","
                    << student.getSemester() << "," << lesson.getCode() << "\n";
      }
    }
  }
  studentFile.close();

  ofstream gradeFile("grades_record.csv");
  if (!gradeFile.is_open())
  {
    throw RecordException("Το αρχείο βαθμών δεν μπόρεσε να ανοιχθεί");
  }

  gradeFile << "studentID,lessonCode,grade\n";
  for (const auto &lesson : lessons)
  {
    const vector<float> &grades = lesson.getGrades();
    for (size_t i = 0; i < grades.size() && i < students.size(); ++i)
    {
      if (grades[i] >= 0)
      {
        gradeFile << students[i].getID() << "," << lesson.getCode() << ","
                  << grades[i] << "\n";
      }
    }
  }
  gradeFile.close();
}

void Record::loadFromCsv()
{
  using std::getline;
  using std::ifstream;
  using std::invalid_argument;
  using std::set;
  using std::stof;
  using std::stoi;
  using std::string;
  using std::stringstream;
  using std::vector;

  ifstream profFile("professors_record.csv");
  if (!profFile.is_open())
  {
    throw RecordException("Το αρχείο καθηγητών δεν μπόρεσε να ανοιχθεί");
  }

  vector<Professor> profs;

  string line;
  getline(profFile, line);

  while (getline(profFile, line))
  {
    stringstream ss(line);
    string id, name, birthYearStr, address, phone, email, code, specialty;

    getline(ss, id, ',');
    getline(ss, name, ',');
    getline(ss, birthYearStr, ',');
    getline(ss, address, ',');
    getline(ss, phone, ',');
    getline(ss, email, ',');
    getline(ss, code, ',');
    getline(ss, specialty, ',');

    try
    {
      int birthYear = stoi(birthYearStr);
      Professor prof(id.c_str(), name.c_str(), birthYear, address.c_str(),
                     phone.c_str(), email.c_str(), code.c_str(),
                     specialty.c_str());
      profs.push_back(prof);
    }
    catch (const invalid_argument &e)
    {
      throw RecordException("Σφάλμα στην ανάλυση του έτους γέννησης για τον "
                            "καθηγητή " +
                            id);
    }
  }
  profFile.close();

  ifstream lessonFile("lessons_record.csv");
  if (!lessonFile.is_open())
  {
    throw RecordException("Το αρχείο μαθημάτων δεν μπόρεσε να ανοιχθεί");
  }

  getline(lessonFile, line);

  vector<Lesson> lessons;
  while (getline(lessonFile, line))
  {
    stringstream ss(line);
    string code, name, semesterStr, professorID;

    getline(ss, code, ',');
    getline(ss, name, ',');
    getline(ss, semesterStr, ',');
    getline(ss, professorID, ',');

    try
    {
      int semester = stoi(semesterStr);
      Professor *foundProfessor = nullptr;
      for (auto &prof : profs)
      {
        if (string(prof.getID()) == professorID)
        {
          foundProfessor = &prof;
          break;
        }
      }
      if (foundProfessor == nullptr)
      {
        throw RecordException("Δεν βρέθηκε καθηγητής με ID: " + professorID +
                              " για το μάθημα: " + code);
      }

      Lesson lesson(code, name, semester, *foundProfessor);
      lessons.push_back(lesson);
    }
    catch (const invalid_argument &e)
    {
      throw RecordException("Σφάλμα στην ανάλυση του εξαμήνου για το μάθημα " +
                            code);
    }
  }
  lessonFile.close();

  ifstream studentFile("students_record.csv");
  if (!studentFile.is_open())
  {
    throw RecordException("Το αρχείο μαθητών δεν μπόρεσε να ανοιχθεί");
  }

  getline(studentFile, line);

  while (getline(studentFile, line))
  {
    stringstream ss(line);
    string id, name, birthYearStr, address, phone, email, regNumStr, semesterStr, lessonCode;

    getline(ss, id, ',');
    getline(ss, name, ',');
    getline(ss, birthYearStr, ',');
    getline(ss, address, ',');
    getline(ss, phone, ',');
    getline(ss, email, ',');
    getline(ss, regNumStr, ',');
    getline(ss, semesterStr, ',');
    getline(ss, lessonCode, ',');

    try
    {
      int birthYear = stoi(birthYearStr);
      int semester = stoi(semesterStr);
      int registrationNumber = stoi(regNumStr);

      Student student(id.c_str(), name.c_str(), birthYear, address.c_str(),
                      phone.c_str(), email.c_str(), registrationNumber,
                      semester, {});
      bool studentExists = false;
      for (auto &existingStudent : students)
      {
        if (string(existingStudent.getID()) == id)
        {
          student = existingStudent;
          studentExists = true;
          break;
        }
      }
      if (!studentExists)
      {
        students.push_back(student);
      }
      if (!lessonCode.empty())
      {
        for (auto &lesson : lessons)
        {
          if (lesson.getCode() == lessonCode)
          {
            vector<Lesson> studentLessons = student.getLessons();
            bool lessonAlreadyAdded = false;
            for (const auto &l : studentLessons)
            {
              if (l.getCode() == lessonCode)
              {
                lessonAlreadyAdded = true;
                break;
              }
            }
            if (!lessonAlreadyAdded)
            {
              studentLessons.push_back(lesson);
              student.setLessons(studentLessons);
            }
            break;
          }
        }
      }
    }
    catch (const invalid_argument &e)
    {
      throw RecordException("Σφάλμα στην ανάλυση των δεδομένων μαθητή για τον μαθητή " + id);
    }
  }
  studentFile.close();

  ifstream gradeFile("grades_record.csv");
  if (!gradeFile.is_open())
  {
    throw RecordException("Το αρχείο βαθμών δεν μπόρεσε να ανοιχθεί");
  }

  getline(gradeFile, line);

  while (getline(gradeFile, line))
  {
    stringstream ss(line);
    string studentID, lessonCode, gradeStr;

    getline(ss, studentID, ',');
    getline(ss, lessonCode, ',');
    getline(ss, gradeStr, ',');

    try
    {
      float grade = stof(gradeStr);

      for (size_t i = 0; i < lessons.size(); ++i)
      {
        if (lessons[i].getCode() == lessonCode)
        {
          for (size_t j = 0; j < students.size(); ++j)
          {
            if (string(students[j].getID()) == studentID)
            {
              vector<float> grades = lessons[i].getGrades();
              if (grades.size() <= j)
              {
                grades.resize(students.size(), -1);
              }
              grades[j] = grade;
              lessons[i].setGrades(grades);
              break;
            }
          }
          break;
        }
      }
    }
    catch (const invalid_argument &e)
    {
      throw RecordException("Σφάλμα στην ανάλυση του βαθμού για τον μαθητή " +
                            studentID + ", μάθημα " + lessonCode);
    }
  }

  gradeFile.close();
}