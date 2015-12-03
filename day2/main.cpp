#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>

struct Present {
  int l, w, h;

  int getTotalSurfaceArea() const {
    return 2*l*w + 2*w*h + 2*h*l;
  }

  int getSmallestSideArea() const {
    return qMin(qMin(l*w, w*h), h*l);
  }

  int getTotalPaperNeeded() const {
    return getTotalSurfaceArea() + getSmallestSideArea();
  }

  int getVolume() const {
    return l*w*h;
  }

  int getSmallestFacePerimeter() const {
    QList<int> tmp;
    tmp << l << w << h;
    std::sort(tmp.begin(), tmp.end());
    return 2*tmp[0] + 2*tmp[1];
  }

  int getTotalRibbonNeeded() const {
    return getSmallestFacePerimeter() + getVolume();
  }
};

int main(int argc, char *argv[]) {
  QFile input_file("input.txt");

  if (!input_file.open(QIODevice::ReadOnly)) {
    qCritical() << "Failed to open input.txt";
    return 1;
  }

  QTextStream stream(&input_file);

  QList<Present> presents;

  while (!stream.atEnd()) {
    const auto dimensions_string = stream.readLine();
    const auto dimensions = dimensions_string.split('x');
    Q_ASSERT(dimensions.size() == 3);

    Present present;
    present.l = dimensions[0].toInt();
    present.w = dimensions[1].toInt();
    present.h = dimensions[2].toInt();

    presents.append(present);
  }

  const auto total_paper = std::accumulate(std::cbegin(presents), std::cend(presents), 0,
                                           [](const int sum, const Present& present) { return sum + present.getTotalPaperNeeded(); });

  const auto total_ribbon = std::accumulate(presents.cbegin(), presents.cend(), 0,
                                            [](const int sum, const Present& present) { return sum + present.getTotalRibbonNeeded(); });

  qDebug() << total_paper << total_ribbon;

  return 0;
}
