#include "ansComp.h"
#include "bmplib.h"
#include "histogram.h"
#include "matplotlibcpp.h"
#include <numeric>
#define WITHOUT_NUMPY
namespace plt = matplotlibcpp;

int main() {
  anslib::bmplib::BmpImage inImg;
  inImg.bmpRead(CMAKE_SOURCE_DIR
                "/test_images/PHOTO_CD_KODAK/BMP_IMAGES/IMG0001.bmp");
  inImg.bmpWrite("doopa.bmp");
  std::cout << inImg.fileHeader_ << inImg.infoHeader_;
  anslib::Image img(inImg);

  int i = 1;
  for (auto plane : img.dataPlanes) {
    Histogram<uint8_t> h0(plane);
    // Histogram<uint8_t> h1(img.dataPlanes.at(1));
    // Histogram<uint8_t> h2(img.dataPlanes.at(2));

    // h0.print(90, true);
    // h1.print(90, true);
    // h2.print(90, true);
    h0.sort_counts();

    std::vector<long> counts;
    for (auto pair : h0.sorted) {
      counts.push_back(pair.second);
    }
    
    std::vector<int> xs (h0.cumul.size());
    std::iota(xs.begin(), xs.end(), 0);

    plt::figure(i++);
    plt::grid(true);
    plt::subplot(2,2,1);
    plt::plot(xs, std::vector<long>(h0.cumul.begin(), h0.cumul.end()), "b.");
    h0.norm_freqs();
    plt::subplot(2,2,2);
    plt::plot(xs, std::vector<long>(h0.cumul_norm.begin(), h0.cumul_norm.end()), "r.");
    plt::show(false);
    plt::subplot(2,2,3);
    xs.pop_back();
    plt::plot(xs, std::vector<long>(h0.counts.begin(), h0.counts.end()), "r.");
    plt::show(false);
    plt::subplot(2,2,4);
    plt::plot(xs, std::vector<long>(h0.counts_norm.begin(), h0.counts_norm.end()), "r.");
    plt::show(false);
  }

  plt::show();

}