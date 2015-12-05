#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QRegularExpression>

// Part 1
int countVowels(const QString& string) {
  return string.count(QRegularExpression("[aeiou]"));
}

bool hasDoubleLetter(const QString& string) {
  return string.contains(QRegularExpression("(\\w)\\1"));
}

bool containsForbiddenSequence(const QString& string) {
  return string.contains(QRegularExpression("ab|cd|pq|xy"));
}

bool stringIsNice(const QString& string) {
  return (countVowels(string) >= 3 && hasDoubleLetter(string) && !containsForbiddenSequence(string));
}

// Part 2
bool hasPair(const QString& string) {
  return string.contains(QRegularExpression("(\\w{2})\\w*\\1"));
}

bool hasRepeatingLetter(const QString& string) {
  return string.contains(QRegularExpression("(\\w)\\w\\1"));
}

bool stringIsNice2(const QString& string) {
  return (hasPair(string) && hasRepeatingLetter(string));
}

int main(int argc, char *argv[]) {
  QFile input_file("input.txt");

  if (!input_file.open(QIODevice::ReadOnly)) {
    qCritical() << "Failed to open input.txt";
    return 1;
  }

  QTextStream stream(&input_file);

  auto nice_string_count = 0;
  auto nice_string_count2 = 0;

  while (!stream.atEnd()) {
    const auto string = stream.readLine();

    if (stringIsNice(string)) {
      ++nice_string_count;
    }

    if (stringIsNice2(string)) {
      ++nice_string_count2;
    }
  }

  qDebug() << nice_string_count << nice_string_count2;

  return 0;
}
