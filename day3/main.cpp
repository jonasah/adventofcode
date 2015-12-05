#include <QtCore/QDebug>
#include <QtCore/QFile>

struct Location {
  int x, y;

  bool operator==(const Location& rhs) const {
    return (x == rhs.x && y == rhs.y);
  }
};

uint qHash(const Location location, uint) {
  return qHash(qMakePair(location.x, location.y));
}

void move(Location& current_location, const QChar c, QSet<Location>& locations_visited) {
  if (c == '^') {
    ++current_location.y;
  }
  else if (c == 'v') {
    --current_location.y;
  }
  else if (c == '>') {
    ++current_location.x;
  }
  else if (c == '<') {
    --current_location.x;
  }
  else {
    return;
  }

  locations_visited.insert(current_location);
}

int main(int /*argc*/, char * /*argv*/[]) {
  QFile input_file("input.txt");

  if (!input_file.open(QIODevice::ReadOnly)) {
    qCritical() << "Failed to open input.txt";
    return 1;
  }

  const QString input = input_file.readLine();

  {
    Location current_location = {0, 0}; // starting location

    QSet<Location> locations_visited;
    locations_visited.insert(current_location);

    for (const auto c : input) {
      move(current_location, c, locations_visited);
    }

    qDebug() << locations_visited.size();
  }

  {
    // starting locations
    Location current_santa_location = {0, 0};
    Location current_robo_santa_location = {0, 0};

    QSet<Location> santa_locations_visited, robo_santa_locations_visited;
    santa_locations_visited.insert(current_santa_location);
    robo_santa_locations_visited.insert(current_robo_santa_location);

    auto counter = 0;

    for (const auto c: input) {
      if (counter % 2 == 0) {
        move(current_santa_location, c, santa_locations_visited);
      }
      else {
        move(current_robo_santa_location, c, robo_santa_locations_visited);
      }

      ++counter;
    }

    santa_locations_visited.unite(robo_santa_locations_visited);

    qDebug() << santa_locations_visited.size();
  }

  qDebug() << "foo";

  return 0;
}
