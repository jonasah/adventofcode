#include <array>

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QRegularExpression>

template <typename T, int M, int N>
using Matrix = std::array<std::array<T, N>, M>;

struct Light {
  // part one
  bool lit = false;

  // part two
  int brightness = 0;

  void turnOn() {
    lit = true;

    ++brightness;
  }

  void turnOff() {
    lit = false;

    brightness = qMax(0, brightness - 1);
  }

  void toggle() {
    lit = !lit;

    brightness += 2;
  }
};

using LightGrid = Matrix<Light, 1000, 1000>;

int main(int /*argc*/, char * /*argv*/[]) {
  QFile input_file("input.txt");

  if (!input_file.open(QIODevice::ReadOnly)) {
    qCritical() << "Failed to open input.txt";
    return 1;
  }

  QTextStream stream(&input_file);

  LightGrid light_grid;

  while (!stream.atEnd()) {
    const auto instruction = stream.readLine();

    static const QRegularExpression regexp("(turn off|turn on|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");
    const auto match = regexp.match(instruction);

    Q_ASSERT(match.capturedTexts().size() == 6);

    const auto action = match.captured(1);
    const auto x1 = match.captured(2).toInt();
    const auto y1 = match.captured(3).toInt();
    const auto x2 = match.captured(4).toInt();
    const auto y2 = match.captured(5).toInt();

    for (int i = x1; i <= x2; ++i) {
      for (int j = y1; j <= y2; ++j) {
        if (action == "turn off") {
          light_grid[i][j].turnOff();
        }
        else if (action == "turn on") {
          light_grid[i][j].turnOn();
        }
        else {
          light_grid[i][j].toggle();
        }
      }
    }
  }

  auto lights_lit = 0;
  auto total_brightness = 0;

  for (const auto& light_row : light_grid) {
    for (const auto& light : light_row) {
      lights_lit += (light.lit ? 1 : 0);
      total_brightness += light.brightness;
    }
  }

  qDebug() << lights_lit << total_brightness;

  return 0;
}
