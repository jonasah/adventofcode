#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>

int main(int argc, char *argv[]) {
  QFile input_file("input.txt");

  if (!input_file.open(QIODevice::ReadOnly)) {
    qCritical() << "Failed to open input.txt";
    return 1;
  }

  const QString input = input_file.readLine();
  auto floor = 0;
  auto position = 1;
  auto basement_entered = false;

  for (const auto c : input) {
    if (c == '(') {
      ++floor;
    }
    else if (c == ')') {
      --floor;
    }

    if (!basement_entered) {
      if (floor == -1) {
        basement_entered = true;
      }
      else {
        ++position;
      }
    }
  }

  qDebug() << floor << position;

  return 0;
}
